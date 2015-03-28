

#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include "types.h"

using namespace std;

// Create scanner
class Scanner {
private:

  // Current character code
  unsigned int m_ch;

  // Current position.
  unsigned int m_pos = 0;

  // Current position of token.
  unsigned int m_tokenPos = 0;

  // Start position.
  unsigned int m_startPos = 0;

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
public:
  Scanner(string* source);
  Scanner(string source);
  ~Scanner();

  // Get next token from scanner
  SyntaxKind nextToken();
};

#endif