

#include <string>
#include <map>
#include <iostream>
#include "scanner.h"
#include "types.h"
#include "utils.h"


using namespace std;


// Flag for preceding linebreak.
bool precedingLineBreak = false;


map<string, SyntaxKind> textToToken {
  { "any", SyntaxKind::AnyKeyword},
  { "break", SyntaxKind::BreakKeyword}
};


bool isLineBreak(unsigned int ch) {
  return
  ch == CharCode::LineFeed ||
  ch == CharCode::CarriageReturn ||
  ch == CharCode::LineSeparator ||
  ch == CharCode::ParagraphSeparator ||
  ch == CharCode::NextLine;
}


bool isIdentifierStart(unsigned int ch) {
  return
  (ch >= CharCode::A && ch <= CharCode::Z) ||
  (ch >= CharCode::a && ch <= CharCode::z) ||
  ch == CharCode::$ ||
  ch == CharCode::_ ||
  ch > CharCode::MaxAsciiCharacter;
}


bool isIdentifierPart(unsigned int ch) {
  return
  (ch >= CharCode::A && ch <= CharCode::Z) ||
  (ch >= CharCode::a && ch <= CharCode::z) ||
  (ch >= CharCode::_0 && ch <= CharCode::_9) ||
  ch == CharCode::$ ||
  ch == CharCode::_ ||
  ch > CharCode::MaxAsciiCharacter;
}


bool isWhiteSpace(unsigned int ch) {
  return
  ch == CharCode::Space ||
  ch == CharCode::Tab ||
  ch == CharCode::VerticalTab ||
  ch == CharCode::FormFeed ||
  ch == CharCode::NonBreakingSpace ||
  ch == CharCode::Ogham ||
  (ch >= CharCode::EnQuad && ch <= CharCode::ZeroWidthSpace) ||
  ch == CharCode::NarrowNoBreakSpace ||
  ch == CharCode::MathematicalSpace ||
  ch == CharCode::IdeographicSpace ||
  ch == CharCode::ByteOrderMark;
}


bool isLineBreak(int ch) {
  return
  ch == CharCode::LineFeed ||
  ch == CharCode::CarriageReturn ||
  ch == CharCode::LineSeparator ||
  ch == CharCode::ParagraphSeparator ||
  ch == CharCode::NextLine;
}


Scanner::Scanner(string* source) {
  m_source = source;
  m_pos = 0;
  m_len = (*source).length();
}


Scanner::Scanner(string fsource) {
  string* tmpSource = "" + fsource;
  Scanner(&tmpSource);
}


Scanner::~Scanner() {}

SyntaxKind Scanner::getIdentifierToken() {
  int len = m_tokenValue.length();
  if (len >= 2 && len <= 11) {
    int ch = m_tokenValue.at(0);
    if (ch >= CharCode::a && ch <= CharCode::z
        && textToToken.find(m_tokenValue) != textToToken.end()) {
      m_token = textToToken.at(m_tokenValue);
      return m_token;
    }
  }
  return SyntaxKind::Identifier;
}

string Scanner::scanIdentifierParts () {
  string result = "";
  unsigned int start = m_pos;
  while (m_pos < m_len) {
    unsigned int m_ch = (int)(*m_source)[m_pos];
    if (isIdentifierPart(m_ch)) {
      m_pos++;
    }
    else {
      break;
    }
  }
  result += (*m_source).substr(start, m_pos - start);
  return result;
}

SyntaxKind Scanner::nextToken() {
  m_ch = (*m_source).at(m_pos);
  while (true) {
    m_tokenPos = m_pos;
    if (m_pos >= m_len) {
      m_token = SyntaxKind::EndOfFileToken;
      break;
    }
    switch (m_ch) {

      // New-lines
      case CharCode::LineFeed:
      case CharCode::CarriageReturn:
        precedingLineBreak = true;
        if (m_ch == CharCode::CarriageReturn
        && m_pos + 1 < m_len
        && (int)(*m_source)[m_pos + 1] == CharCode::LineFeed) {

          // Consume both CR and LF.
          m_pos += 2;
        }
        else {
          m_pos++;
        }
        return m_token = SyntaxKind::NewLineTrivia;


      // White-space
      case CharCode::Tab:
      case CharCode::VerticalTab:
      case CharCode::FormFeed:
      case CharCode::Space:
        while (m_pos < m_len && isWhiteSpace((*m_source).at(m_pos))) {
          m_pos++;
        }
        return m_token = SyntaxKind::WhitespaceTrivia;
        

      // Default
      default:
        if (isIdentifierStart(m_ch)) {
          m_pos++;
          while (m_pos < m_len && isIdentifierPart(m_ch = (int)(*m_source)[m_pos])) {
            m_pos++;
          }
          m_tokenValue = (*m_source).substr(m_tokenPos, m_pos - m_tokenPos);
          if (m_ch == CharCode::Backslash) {
            m_tokenValue += scanIdentifierParts();
          }
          return m_token = getIdentifierToken();
        }
        else if (isWhiteSpace(m_ch)) {
          m_pos++;
          continue;
        }
        else if (isLineBreak(m_ch)) {
          precedingLineBreak = true;
          m_pos++;
          continue;
        }
        m_pos++;
        m_token = SyntaxKind::Unknown;
    }
  }

  return m_token;
};