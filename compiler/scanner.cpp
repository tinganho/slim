

#include <string>
#include <map>
#include "scanner.h"
#include "types.h"
#include "utils.h"


using namespace std;


// Current character code
unsigned int ch;


// Current position.
unsigned int pos = 0;


// Current position of token.
unsigned int tokenPos = 0;


// Start position.
unsigned int startPos = 0;


// Token value.
string tokenValue;


// Current lengt of source file.
int len;


// Current token.
SyntaxKind token;


// Current source.
string* source;


// Flag for preceding linebreak.
bool precedingLineBreak = false;


map<string, SyntaxKind> textToToken {
  {"any", SyntaxKind::AnyKeyword},
  {"break", SyntaxKind::BreakKeyword}
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


string scanIdentifierParts () {
    string result = "";
    unsigned int start = pos;
    while (pos < len) {
      unsigned int ch = (int)(*source)[pos];
      if (isIdentifierPart(ch)) {
        pos++;
      }
      else {
        break;
      }
    }
    result += (*source).substr(start, pos - start);
    return result;
}


SyntaxKind getIdentifierToken() {
  int len = tokenValue.length();
  if (len >= 2 && len <= 11) {
    int ch = tokenValue.at(0);
    if (ch >= CharCode::a && ch <= CharCode::z
    && textToToken.find(tokenValue) != textToToken.end()) {
      token = textToToken.at(tokenValue);
      return token;
    }
  }
  return SyntaxKind::Identifier;
}


string createScanner(string* mainSource) {
  source = mainSource;
  while (true) {
    tokenPos = pos;
    if (pos >= len) {
      token = SyntaxKind::EndOfFileToken;
      break;
    }
    switch(ch) {
      case CharCode::LineFeed:
      case CharCode::CarriageReturn:
        precedingLineBreak = true;
        if (ch == CharCode::CarriageReturn
        && pos + 1 < len
        && (int)(*source)[pos + 1] == CharCode::LineFeed) {

          // Consume both CR and LF.
          pos += 2;
        }
        else {
          pos++;
        }
        token = SyntaxKind::NewLineTrivia;
        break;
      default:
        if (isIdentifierStart(ch)) {
          pos++;
          while (pos < len && isIdentifierPart(ch = (int)(*source)[pos]))
            pos++;
          tokenValue = (*source).substr(tokenPos, pos - tokenPos);
          if (ch == CharCode::Backslash) {
            tokenValue += scanIdentifierParts();
          }
          token = getIdentifierToken();
          break;
        }
        else if (isWhiteSpace(ch)) {
          pos++;
          continue;
        }
        else if (isLineBreak(ch)) {
          precedingLineBreak = true;
          pos++;
          continue;
        }
        pos++;
        token = SyntaxKind::Unknown;
    }
  }

  return *source;
}

void setTextPos(int textPos) {
  pos = textPos;
  startPos = textPos;
  token = SyntaxKind::Unknown;
  precedingLineBreak = false;
}

void setText(string newText) {
  string text = newText;
  len = text.length();
  setTextPos(0);
}