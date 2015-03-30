

#include <string>
#include <map>
#include <iostream>
#include "scanner.h"
#include "types.h"
#include "utils.h"
#include "diagnostics.h"


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


Scanner::Scanner(string source) {
  m_source = &source;
  m_pos = 0;
  m_len = (source).length();
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


void Scanner::setErrorCallback(ErrorCallback error) {
  m_error = error;
}


string Scanner::getTokenValue() {
  return m_tokenValue;
}


unsigned int Scanner::getStartPos() {
  return m_startPos;
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


string Scanner::scanEscapeSequence() {
  m_pos++;
  if (m_pos >= m_len) {
    m_error(Diagnostic::UnexpectEndOfInput);
    return "";
  }
  char ch = (*m_source).at(m_pos++);
  switch (ch) {
    case CharCode::_0:
      return "\0";
    case CharCode::b:
      return "\b";
    case CharCode::t:
      return "\t";
    case CharCode::n:
      return "\n";
    case CharCode::v:
      return "\v";
    case CharCode::f:
      return "\f";
    case CharCode::r:
      return "\r";
    case CharCode::SingleQuote:
      return "\'";
    case CharCode::DoubleQuote:
      return "\"";
//    case CharCode::u:
//      // '\u{DDDDDDDD}'
//      if (m_pos < m_len && (*m_source).at(m_pos) == CharCode::OpenBrace) {
//        hasExtendedUnicodeEscape = true;
//        pos++;
//        return scanExtendedUnicodeEscape();
//      }
//
//      // '\uDDDD'
//      return scanHexadecimalEscape(/*numDigits*/ 4)
//
//    case CharCode::x:
//      // '\xDD'
//      return scanHexadecimalEscape(/*numDigits*/ 2)
//
//      // when encountering a LineContinuation (i.e. a backslash and a line terminator sequence),
//      // the line terminator is interpreted to be "the empty code unit sequence".
//    case CharacterCodes.carriageReturn:
//      if (m_pos < m_len && (*m_source).at(m_pos) == CharCode::LineFeed) {
//        m_pos++;
//      }
      // fall through
    case CharCode::LineFeed:
      return "";
    default:
      return string(1, ch);
  }
}


string Scanner::scanString() {
  int quote = (int)(*m_source).at(m_pos++);
  string result = "";
  unsigned int start = m_pos;
  while (true) {
    if (m_pos >= m_len) {
      result += (*m_source).substr(start, m_pos - start + 1);
      m_tokenIsUnterminated = true;
      m_error(Diagnostic::UnterminatedStringLiteral);
      break;
    }
    unsigned int ch = (*m_source).at(m_pos);
    if (ch == quote) {
      result += (*m_source).substr(start, m_pos - start);
      m_pos++;
      break;
    }
    if (ch == CharCode::Backslash) {
      result += (*m_source).substr(start, m_pos - start + 1);
      result += scanEscapeSequence();
      start = m_pos;
      continue;
    }
    if (isLineBreak((char)ch)) {
      result += (*m_source).substr(start, m_pos - start + 1);
      m_tokenIsUnterminated = true;
      m_error(Diagnostic::UnterminatedStringLiteral);
      break;
    }
    m_pos++;
  }
  return result;
}


SyntaxKind Scanner::scan() {
  if (m_pos >= m_len) {
    return m_token = SyntaxKind::EndOfFileToken;
  }
  m_ch = (*m_source).at(m_pos);
  while (true) {
    m_tokenPos = m_pos;
    if (m_pos >= m_len) {
      return m_token = SyntaxKind::EndOfFileToken;
    }
    switch (m_ch) {


      // New-lines
      case CharCode::LineFeed:
      case CharCode::CarriageReturn:
        precedingLineBreak = true;
        if (m_ch == CharCode::CarriageReturn
        && m_pos + 1 < m_len
        && (int)(*m_source)[m_pos + 1] == CharCode::LineFeed) {
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


      // Exclamation
      case CharCode::Exclamation:
        if (m_pos + 1 != m_len && (*m_source).at(m_pos + 1) == CharCode::Equals) {
          return m_pos += 2, m_token = SyntaxKind::ExclamationEqualsToken;
        }
        return m_pos++, m_token = SyntaxKind::ExclamationToken;


      // String literals
      case CharCode::DoubleQuote:
      case CharCode::SingleQuote:
        m_tokenValue = scanString();
        return m_token = SyntaxKind::StringLiteral;


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