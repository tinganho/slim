

#include <vector>
#include <functional>
#include "parser.h"
#include "scanner.h"
#include "types.h"
#include "utils.h"


Parser::Parser() {};


Parser::~Parser() {
  delete m_scanner;
};


struct SourceFile Parser::parseSourceFile(string fileName, string* source) {
  m_parsingContext = ParsingContext::SourceElements;

  // Create source file node
  struct SourceFile sourceFile;
  sourceFile.source = source;
  sourceFile.fileName = fileName;
  m_scanner = new Scanner(source);
  nextToken();
  sourceFile.statements = parseList(m_parsingContext, std::bind(&Parser::parseSourceElement, this));
  return sourceFile;
}


vector<Node> Parser::parseList(ParsingContext parsingContext, std::function<Node()> parseElement) {
  vector<Node> result;
  while (isListTerminator(parsingContext)) {
    if (isListElement(parsingContext, /*inErrorRecovery:*/ false)) {
      Node element = parseElement();
      result.push_back(element);
    }
  }

  return result;
}


bool Parser::isIdentifier() {
  return m_token == SyntaxKind::Identifier;
}


bool Parser::isBinaryOperator() {
  if (/*inDisallowInContext() &&*/ m_token == SyntaxKind::InKeyword) {
    return false;
  }

  return getBinaryOperatorPrecedence() > 0;
}


unsigned short int Parser::getBinaryOperatorPrecedence() {
  switch (m_token) {
    case SyntaxKind::BarBarToken:
      return 1;
    case SyntaxKind::AmpersandAmpersandToken:
      return 2;
    case SyntaxKind::BarToken:
      return 3;
    case SyntaxKind::CaretToken:
      return 4;
    case SyntaxKind::AmpersandToken:
      return 5;
    case SyntaxKind::EqualsEqualsToken:
    case SyntaxKind::ExclamationEqualsToken:
      return 6;
    case SyntaxKind::LessThanToken:
    case SyntaxKind::GreaterThanToken:
    case SyntaxKind::LessThanEqualsToken:
    case SyntaxKind::GreaterThanEqualsToken:
    case SyntaxKind::InstanceOfKeyword:
    case SyntaxKind::InKeyword:
      return 7;
    case SyntaxKind::LessThanLessThanToken:
    case SyntaxKind::GreaterThanGreaterThanToken:
    case SyntaxKind::GreaterThanGreaterThanGreaterThanToken:
      return 8;
    case SyntaxKind::PlusToken:
    case SyntaxKind::MinusToken:
      return 9;
    case SyntaxKind::AsteriskToken:
    case SyntaxKind::SlashToken:
    case SyntaxKind::PercentToken:
      return 10;
    default:
      // -1 is lower than all other precedences.  Returning it will cause binary expression
      // parsing to stop.
      return -1;
  }
}


bool Parser::isStartOfExpression() {
  switch (m_token) {
    case SyntaxKind::ThisKeyword:
    case SyntaxKind::SuperKeyword:
    case SyntaxKind::NullKeyword:
    case SyntaxKind::TrueKeyword:
    case SyntaxKind::FalseKeyword:
    case SyntaxKind::NumericLiteral:
    case SyntaxKind::StringLiteral:
    case SyntaxKind::NoSubstitutionTemplateLiteral:
    case SyntaxKind::TemplateHead:
    case SyntaxKind::OpenParenToken:
    case SyntaxKind::OpenBracketToken:
    case SyntaxKind::OpenBraceToken:
    case SyntaxKind::FunctionKeyword:
    case SyntaxKind::NewKeyword:
    case SyntaxKind::SlashToken:
    case SyntaxKind::SlashEqualsToken:
    case SyntaxKind::PlusToken:
    case SyntaxKind::MinusToken:
    case SyntaxKind::TildeToken:
    case SyntaxKind::ExclamationToken:
    case SyntaxKind::DeleteKeyword:
    case SyntaxKind::TypeOfKeyword:
    case SyntaxKind::VoidKeyword:
    case SyntaxKind::PlusPlusToken:
    case SyntaxKind::MinusMinusToken:
    case SyntaxKind::LessThanToken:
    case SyntaxKind::Identifier:
    case SyntaxKind::YieldKeyword:
      // Yield always starts an expression.  Either it is an identifier (in which case
      // it is definitely an expression).  Or it's a keyword (either because we're in
      // a generator, or in strict mode (or both)) and it started a yield expression.
      return true;
    default:
      // Error tolerance.  If we see the start of some binary operator, we consider
      // that the start of an expression.  That way we'll parse out a missing identifier,
      // give a good message about an identifier being missing, and then consume the
      // rest of the binary expression.
      if (isBinaryOperator()) {
        return true;
      }

      return isIdentifier();
  }
}


bool Parser::isStartOfStatement(bool inErrorRecovery) {
  // Functions and variable statements are allowed as a statement. But as per the grammar,
  // they also allow modifiers.  So we have to check for those statements that might be
  // following modifiers.This ensures that things work properly when incrementally parsing
  // as the parser will produce the same FunctionDeclaraiton or VariableStatement if it has
  // the same text regardless of whether it is inside a block or not.
  if (isModifier(&m_token)) {
    bool result = true; /*lookAhead(parseVariableStatementOrFunctionDeclarationWithModifiers);*/
    if (result) {
      return true;
    }
  }

  switch (m_token) {
    case SyntaxKind::SemicolonToken:
      // If we're in error recovery, then we don't want to treat ';' as an empty statement.
      // The problem is that ';' can show up in far too many contexts, and if we see one
      // and assume it's a statement, then we may bail out inappropriately from whatever
      // we're parsing.  For example, if we have a semicolon in the middle of a class, then
      // we really don't want to assume the class is over and we're on a statement in the
      // outer module.  We just want to consume and move on.
      return !inErrorRecovery;
    case SyntaxKind::OpenBraceToken:
    case SyntaxKind::VarKeyword:
    case SyntaxKind::LetKeyword:
    case SyntaxKind::FunctionKeyword:
    case SyntaxKind::IfKeyword:
    case SyntaxKind::DoKeyword:
    case SyntaxKind::WhileKeyword:
    case SyntaxKind::ForKeyword:
    case SyntaxKind::ContinueKeyword:
    case SyntaxKind::BreakKeyword:
    case SyntaxKind::ReturnKeyword:
    case SyntaxKind::WithKeyword:
    case SyntaxKind::SwitchKeyword:
    case SyntaxKind::ThrowKeyword:
    case SyntaxKind::TryKeyword:
    case SyntaxKind::DebuggerKeyword:
      // 'catch' and 'finally' do not actually indicate that the code is part of a statement,
      // however, we say they are here so that we may gracefully parse them and error later::
    case SyntaxKind::CatchKeyword:
    case SyntaxKind::FinallyKeyword:
      return true;
    case SyntaxKind::ConstKeyword:
      // const keyword can precede enum keyword when defining constant enums
      // 'const enum' do not start statement.
      // In ES 6 'enum' is a future reserved keyword, so it should not be used as identifier
//      bool isConstEnum = lookAhead(nextTokenIsEnumKeyword);
      return true; /*!isConstEnum;*/
    case SyntaxKind::InterfaceKeyword:
    case SyntaxKind::ClassKeyword:
    case SyntaxKind::ModuleKeyword:
    case SyntaxKind::EnumKeyword:
    case SyntaxKind::TypeKeyword:
      // When followed by an identifier, these do not start a statement but might
      // instead be following declarations
      if (isDeclarationStart()) {
        return false;
      }
    case SyntaxKind::PublicKeyword:
    case SyntaxKind::PrivateKeyword:
    case SyntaxKind::ProtectedKeyword:
    case SyntaxKind::StaticKeyword:
      // When followed by an identifier or keyword, these do not start a statement but
      // might instead be following type members
//      if (lookAhead(nextTokenIsIdentifierOrKeywordOnSameLine)) {
//        return false;
//      }
    default:
      return isStartOfExpression();
  }
}


bool Parser::isSourceElement(bool inErrorRecovery) {
  return isDeclarationStart() || isStartOfStatement(inErrorRecovery);
}


bool Parser::isLiteralPropertyName() {
  return isIdentifierOrKeyword() ||
    m_token == SyntaxKind::StringLiteral ||
    m_token == SyntaxKind::NumericLiteral;
}


bool Parser::isListElement(ParsingContext parsingContext, bool inErrorRecovery) {
//    Node node = currentNode(parsingContext);
//    if (node) {
//      return true;
//    }

    switch (parsingContext) {
      case ParsingContext::SourceElements:
      case ParsingContext::ModuleElements:
        return isSourceElement(inErrorRecovery);
      case ParsingContext::BlockStatements:
      case ParsingContext::SwitchClauseStatements:
        return isStartOfStatement(inErrorRecovery);
      case ParsingContext::SwitchClauses:
        return m_token == SyntaxKind::CaseKeyword || m_token == SyntaxKind::DefaultKeyword;
//      case ParsingContext::TypeMembers:
//        return isStartOfTypeMember();
//      case ParsingContext::ClassMembers:
//        return lookAhead(isClassMemberStart);
      case ParsingContext::EnumMembers:
        // Include open bracket computed properties. This technically also lets in indexers,
        // which would be a candidate for improved error reporting.
        return m_token == SyntaxKind::OpenBracketToken || isLiteralPropertyName();
//      case ParsingContext.ObjectLiteralMembers:
//        return token == SyntaxKind::OpenBracketToken || token === SyntaxKind.AsteriskToken || isLiteralPropertyName();
      case ParsingContext::ObjectBindingElements:
        return isLiteralPropertyName();
//      case ParsingContext.TypeReferences:
//        // We want to make sure that the "extends" in "extends foo" or the "implements" in
//        // "implements foo" is not considered a type name.
//        return isIdentifier() && !isNotHeritageClauseTypeName();
//      case ParsingContext.VariableDeclarations:
//        return isIdentifierOrPattern();
//      case ParsingContext.ArrayBindingElements:
//        return token === SyntaxKind.CommaToken || token === SyntaxKind.DotDotDotToken || isIdentifierOrPattern();
//      case ParsingContext.TypeParameters:
//        return isIdentifier();
//      case ParsingContext.ArgumentExpressions:
//      case ParsingContext.ArrayLiteralMembers:
//        return token === SyntaxKind.CommaToken || token === SyntaxKind.DotDotDotToken || isStartOfExpression();
//      case ParsingContext.Parameters:
//        return isStartOfParameter();
//      case ParsingContext.TypeArguments:
//      case ParsingContext.TupleElementTypes:
//        return token === SyntaxKind.CommaToken || isStartOfType();
//      case ParsingContext.HeritageClauses:
//        return isHeritageClause();
//      case ParsingContext.ImportOrExportSpecifiers:
//        return isIdentifierOrKeyword();
      default:
        throw "Non-exhaustive case in 'isListElement'.";
    }
}


SyntaxKind Parser::nextToken() {
  return m_token = m_scanner->scan();
}


bool Parser::isListTerminator(ParsingContext kind) {
  if (m_token == SyntaxKind::EndOfFileToken) {
    // Being at the end of the file ends all lists.
    return true;
  }

  switch (kind) {
    case ParsingContext::ModuleElements:
    case ParsingContext::BlockStatements:
    case ParsingContext::SwitchClauses:
    case ParsingContext::TypeMembers:
    case ParsingContext::ClassMembers:
    case ParsingContext::EnumMembers:
    case ParsingContext::ObjectLiteralMembers:
    case ParsingContext::ObjectBindingElements:
    case ParsingContext::ImportOrExportSpecifiers:
      return m_token == SyntaxKind::CloseBraceToken;
    case ParsingContext::SwitchClauseStatements:
      return m_token == SyntaxKind::CloseBraceToken || m_token == SyntaxKind::CaseKeyword || m_token == SyntaxKind::DefaultKeyword;
    case ParsingContext::TypeReferences:
      return m_token == SyntaxKind::OpenBraceToken || m_token == SyntaxKind::ExtendsKeyword || m_token == SyntaxKind::ImplementsKeyword;
//    case ParsingContext::VariableDeclarations:
//      return isVariableDeclaratorListTerminator();
    case ParsingContext::TypeParameters:
      // Tokens other than '>' are here for better error recovery
      return m_token == SyntaxKind::GreaterThanToken || m_token == SyntaxKind::OpenParenToken || m_token == SyntaxKind::OpenBraceToken || m_token == SyntaxKind::ExtendsKeyword || m_token == SyntaxKind::ImplementsKeyword;
    case ParsingContext::ArgumentExpressions:
      // Tokens other than ')' are here for better error recovery
      return m_token == SyntaxKind::CloseParenToken || m_token == SyntaxKind::SemicolonToken;
    case ParsingContext::ArrayLiteralMembers:
    case ParsingContext::TupleElementTypes:
    case ParsingContext::ArrayBindingElements:
      return m_token == SyntaxKind::CloseBracketToken;
    case ParsingContext::Parameters:
      // Tokens other than ')' and ']' (the latter for index signatures) are here for better error recovery
      return m_token == SyntaxKind::CloseParenToken || m_token == SyntaxKind::CloseBracketToken /*|| token === SyntaxKind.OpenBraceToken*/;
    case ParsingContext::TypeArguments:
      // Tokens other than '>' are here for better error recovery
      return m_token == SyntaxKind::GreaterThanToken || m_token == SyntaxKind::OpenParenToken;
    case ParsingContext::HeritageClauses:
      return m_token == SyntaxKind::OpenBraceToken || m_token == SyntaxKind::CloseBraceToken;
    default:
      return false;
  }
}


int Parser::getNodePos() {
  return m_scanner->getStartPos();
}


Node Parser::parseSourceElement() {
  return isDeclarationStart()
    ? parseDeclaration()
    : parseDeclaration();
}


Node Parser::parseDeclaration() {
  int fullStart = getNodePos();
  vector<enum Modifier> modifiers = parseModifiers();
  switch (m_token) {
    case SyntaxKind::VarKeyword:
    case SyntaxKind::LetKeyword:
    case SyntaxKind::ConstKeyword:
      return parseVariableDeclaration(fullStart, modifiers);
//    case SyntaxKind.FunctionKeyword:
//      return parseFunctionDeclaration(fullStart, modifiers);
//    case SyntaxKind.ClassKeyword:
//      return parseClassDeclaration(fullStart, modifiers);
//    case SyntaxKind.InterfaceKeyword:
//      return parseInterfaceDeclaration(fullStart, modifiers);
//    case SyntaxKind.TypeKeyword:
//      return parseTypeAliasDeclaration(fullStart, modifiers);
//    case SyntaxKind.EnumKeyword:
//      return parseEnumDeclaration(fullStart, modifiers);
//    case SyntaxKind.ModuleKeyword:
//      return parseModuleDeclaration(fullStart, modifiers);
//    case SyntaxKind.ImportKeyword:
//      return parseImportDeclarationOrImportEqualsDeclaration(fullStart, modifiers);
    default:
      throw "Mismatch between isDeclarationStart and parseDeclaration";
  }
  return parseVariableDeclaration(fullStart, modifiers);
}


vector<enum Modifier> Parser::parseModifiers() {
  vector<enum Modifier> modifiers;
  return modifiers;
}


Node Parser::parseVariableDeclaration(int start, vector<enum Modifier> modifiers) {

}

bool Parser::isIdentifierOrKeyword() {
  return m_token >= SyntaxKind::Identifier;
}


bool Parser::nextTokenIsIdentifierOrKeyword() {
  nextToken();
  return isIdentifierOrKeyword();
}


template <typename T>
T Parser::lookAhead(std::function<T()> callback) {
  return speculationHelper(callback, /*isLookAhead:*/ true);
}


template <typename T>
T Parser::tryScan(std::function<T()> callback) {
  return speculationHelper(callback, /*isLookAhead:*/ false);
}


template <typename T>
T Parser::speculationHelper(std::function<T()> callback, bool isLookAhead) {
  // Keep track of the state we'll need to rollback to if lookahead fails (or if the
  // caller asked us to always reset our state).
  SyntaxKind saveToken = m_token;
//  var saveParseDiagnosticsLength = sourceFile.parseDiagnostics.length;
//  var saveParseErrorBeforeNextFinishedNode = parseErrorBeforeNextFinishedNode;

  // Note: it is not actually necessary to save/restore the context flags here.  That's
  // because the saving/restorating of these flags happens naturally through the recursive
  // descent nature of our parser.  However, we still store this here just so we can
  // assert that that invariant holds.
//  var saveContextFlags = contextFlags;

  // If we're only looking ahead, then tell the scanner to only lookahead as well.
  // Otherwise, if we're actually speculatively parsing, then tell the scanner to do the
  // same.
  T result = isLookAhead
    ? m_scanner->lookAhead(callback)
    : m_scanner->tryScan(callback);

//  Debug.assert(saveContextFlags === contextFlags);
//
//  // If our callback returned something 'falsy' or we're just looking ahead,
//  // then unconditionally restore us to where we were.
  if (!result || isLookAhead) {
    m_token = saveToken;
//    sourceFile.parseDiagnostics.length = saveParseDiagnosticsLength;
//    parseErrorBeforeNextFinishedNode = saveParseErrorBeforeNextFinishedNode;
  }

  return result;
}


bool Parser::isDeclarationStart() {
  switch (m_token) {
    case SyntaxKind::VarKeyword:
    case SyntaxKind::ConstKeyword:
    case SyntaxKind::FunctionKeyword:
      return true;
    case SyntaxKind::ClassKeyword:
    case SyntaxKind::InterfaceKeyword:
    case SyntaxKind::EnumKeyword:
    case SyntaxKind::TypeKeyword:
      // Not true keywords so ensure an identifier follows
      return lookAhead<bool>(std::bind(&Parser::nextTokenIsIdentifierOrKeyword, this));
//    case SyntaxKind::ImportKeyword:
//      // Not true keywords so ensure an identifier follows or is string literal or asterisk or open brace
//      return lookAhead(nextTokenCanFollowImportKeyword);
//    case SyntaxKind::ExportKeyword:
//      // Check for export assignment or modifier on source element
//      return lookAhead(nextTokenCanFollowExportKeyword);
//    case SyntaxKind::DeclareKeyword:
//    case SyntaxKind::PublicKeyword:
//    case SyntaxKind::PrivateKeyword:
//    case SyntaxKind::ProtectedKeyword:
//    case SyntaxKind::StaticKeyword:
//      // Check for modifier on source element
//      return lookAhead(nextTokenIsDeclarationStart);
    default:
      return false;
  }
}