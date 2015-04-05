

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "types.h"


using namespace std;


// Create scanner
class Scanner {
public:

  // Skip trivial
  bool skipTrivia = true;

  Scanner(string* source);
  Scanner(string source);
  ~Scanner();


  string getTokenValue();
  unsigned int getStartPos();
  unsigned int getTextPos();
  unsigned int getTokenPos();
  bool hasPrecedingLineBreak();
  template <typename T>
  T lookAhead(std::function<T()> callback) {
    return speculationHelper(callback, /*isLookAhead:*/ true);
  }
  SyntaxKind scan();
  void setErrorCallback(ErrorCallback error);
  template <typename T>
  T tryScan(std::function<T()> callback) {
    return speculationHelper(callback, /*isLookAhead:*/ false);
  }


private:

  // Current character code
  unsigned int m_ch;

  // Current position.
  unsigned int m_pos = 0;

  // Current position of token.
  unsigned int m_tokenPos = 0;

  // Start position.
  unsigned int m_startPos = 0;

  // Token is unterminated flag.
  bool m_tokenIsUnterminated;

  // Preceding line break flag.
  bool m_precedingLineBreak;

  // Error callback.
  ErrorCallback m_error = NULL;

  // Token value.
  string m_tokenValue;

  // Current lengt of source file.
  int m_len;

  // Current token
  SyntaxKind m_token;

  // Source text
  string* m_source;

  SyntaxKind getIdentifierToken();
  string scanIdentifierParts();

  // Get next token from scanner
  void error(Diagnostic diagnostic);

  string scanString();
  string scanEscapeSequence();
  void scanTemplateAndSetTokenValue();

  template <typename T>
  T speculationHelper(std::function<T()> callback, bool isLookAhead) {
    int savePos = m_pos;
    int saveStartPos = m_startPos;
    int saveTokenPos = m_tokenPos;
    SyntaxKind saveToken = m_token;
    string saveTokenValue = m_tokenValue;
    bool savePrecedingLineBreak = m_precedingLineBreak;
    T result = callback();

    // If our callback returned something 'falsy' or we're just looking ahead,
    // then unconditionally restore us to where we were.
    if (!result || isLookAhead) {
      m_pos = savePos;
      m_startPos = saveStartPos;
      m_tokenPos = saveTokenPos;
      m_token = saveToken;
      m_tokenValue = saveTokenValue;
      m_precedingLineBreak = savePrecedingLineBreak;
    }
    return result;
  }
};

#endif