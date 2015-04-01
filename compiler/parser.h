
//
//  parser.h
//  Slim
//
//  Created by Tingan Ho on 3/31/15.
//
//

#ifndef __Slim__parser__
#define __Slim__parser__


#include <string>
#include "scanner.h"
#include "types.h"
#include <functional>


using namespace std;


class Parser {
private:
  SyntaxKind m_token;
  ParsingContext m_parsingContext;
  Scanner* m_scanner = NULL;

public:
  Parser();
  ~Parser();

  // Check if token is a start of a declaration.
  Node currentNode();
  bool isBinaryOperator();
  bool isDeclarationStart();
  bool isIdentifierOrKeyword();
  bool isListTerminator(ParsingContext kind);
  bool isListElement(ParsingContext kind, bool inErrorRecovery);
  bool isLiteralPropertyName();
  bool isIdentifier();
  bool isSourceElement(bool inErrorRecovery);
  bool isStartOfExpression();
  bool isStartOfStatement(bool inErrorRecovery);
  unsigned short int getBinaryOperatorPrecedence();
  int getNodePos();
  SyntaxKind nextToken();
  bool nextTokenIsIdentifierOrKeyword();
  vector<Node> parseList(ParsingContext kind, std::function<Node()> parseElement);
  Node parseDeclaration();
  Node parseSourceElement();
  struct SourceFile parseSourceFile(string fileName, string* source);
  vector<enum Modifier> parseModifiers();
  Node parseVariableDeclaration(int start, vector<enum Modifier> modifiers);
  template<typename T>
  T speculationHelper(std::function<T()> callback, bool isLookAhead);
  template<typename T>
  T lookAhead(std::function<T()> callback);
  template<typename T>
  T tryScan(std::function<T()> callback);
};


#endif /* defined(__Slim__parser__) */
