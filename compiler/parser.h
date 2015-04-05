
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
public:
  Parser();
  ~Parser();

  // Check if token is a start of a declaration.
  struct SourceFile* parseSourceFile(string fileName, string* source);


private:
  SyntaxKind m_token;
  ParsingContext m_parsingContext;
  Scanner* m_scanner = NULL;
  vector<string> m_identifiers;
  unsigned int m_identifierCount = 0;


  bool canParseSemicolon();
  struct Identifier* createIdentifier(bool isIdentifier, Diagnostic diagnostic);
  template <typename T>
  T* createNode(SyntaxKind kind, int start);
  Node currentNode();
  template <typename T>
  T finishNode(T node);
  unsigned short int getBinaryOperatorPrecedence();
  int getNodePos();
  string getTokenValue();
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
  template<typename T>
  T lookAhead(std::function<T()> callback);
  SyntaxKind nextToken();
  bool nextTokenIsIdentifierOrKeyword();
  Node* parseDeclaration();
  bool parseExpected(SyntaxKind kind);
  bool parseExpected(SyntaxKind kind, Diagnostic diagnostic);
  struct Identifier* parseIdentifier();
  vector<Node*> parseList(ParsingContext kind, std::function<Node*()> parseElement);
  vector<enum Modifier> parseModifiers();
  bool parseSemicolon();
  Node* parseSourceElement();
  struct TypeAnnotation* parseTypeAnnotation();
  struct VariableDeclaration* parseVariableStatement(int start, vector<enum Modifier> modifiers);
  void parseVariableDeclaration(struct VariableDeclaration* node);
  template<typename T>
  T speculationHelper(std::function<T()> callback, bool isLookAhead);
  void setModifiers(Node* node, vector<enum Modifier> modifiers);
  template<typename T>
  T tryScan(std::function<T()> callback);
};


#endif /* defined(__Slim__parser__) */
