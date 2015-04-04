
#ifndef TYPES_H
#define TYPES_H


#include <string>
#include <vector>
#include "diagnostics.h"


using namespace std;


enum CharCode {
  NullCharacter = 0,
  MaxAsciiCharacter = 0x7F,

  LineFeed = 0x0A,              // \n
  CarriageReturn = 0x0D,        // \r
  LineSeparator = 0x2028,
  ParagraphSeparator = 0x2029,
  NextLine = 0x0085,

  // Unicode 3.0 space characters
  Space = 0x0020,   // " "
  NonBreakingSpace = 0x00A0,   //
  EnQuad = 0x2000,
  EmQuad = 0x2001,
  EnSpace = 0x2002,
  EmSpace = 0x2003,
  ThreePerEmSpace = 0x2004,
  FourPerEmSpace = 0x2005,
  SixPerEmSpace = 0x2006,
  FigureSpace = 0x2007,
  PunctuationSpace = 0x2008,
  ThinSpace = 0x2009,
  HairSpace = 0x200A,
  ZeroWidthSpace = 0x200B,
  NarrowNoBreakSpace = 0x202F,
  IdeographicSpace = 0x3000,
  MathematicalSpace = 0x205F,
  Ogham = 0x1680,

  _ = 0x5F,
  $ = 0x24,

  _0 = 0x30,
  _1 = 0x31,
  _2 = 0x32,
  _3 = 0x33,
  _4 = 0x34,
  _5 = 0x35,
  _6 = 0x36,
  _7 = 0x37,
  _8 = 0x38,
  _9 = 0x39,

  a = 0x61,
  b = 0x62,
  c = 0x63,
  d = 0x64,
  e = 0x65,
  f = 0x66,
  g = 0x67,
  h = 0x68,
  i = 0x69,
  j = 0x6A,
  k = 0x6B,
  l = 0x6C,
  m = 0x6D,
  n = 0x6E,
  o = 0x6F,
  p = 0x70,
  q = 0x71,
  r = 0x72,
  s = 0x73,
  t = 0x74,
  u = 0x75,
  v = 0x76,
  w = 0x77,
  x = 0x78,
  y = 0x79,
  z = 0x7A,

  A = 0x41,
  B = 0x42,
  C = 0x43,
  D = 0x44,
  E = 0x45,
  F = 0x46,
  G = 0x47,
  H = 0x48,
  I = 0x49,
  J = 0x4A,
  K = 0x4B,
  L = 0x4C,
  M = 0x4D,
  N = 0x4E,
  O = 0x4F,
  P = 0x50,
  Q = 0x51,
  R = 0x52,
  S = 0x53,
  T = 0x54,
  U = 0x55,
  V = 0x56,
  W = 0x57,
  X = 0x58,
  Y = 0x59,
  Z = 0x5a,

  Ampersand = 0x26,             // &
  Asterisk = 0x2A,              // *
  At = 0x40,                    // @
  Backslash = 0x5C,             
  Backtick = 0x60,              // `
  Bar = 0x7C,                   // |
  Caret = 0x5E,                 // ^
  CloseBrace = 0x7D,            // }
  CloseBracket = 0x5D,          // ]
  CloseParen = 0x29,            // )
  Colon = 0x3A,                 // :
  Comma = 0x2C,                 // ,
  Dot = 0x2E,                   // .
  DoubleQuote = 0x22,           // "
  Equals = 0x3D,                // =
  Exclamation = 0x21,           // !
  GreaterThan = 0x3E,           // >
  Hash = 0x23,                  // #
  LessThan = 0x3C,              // <
  Minus = 0x2D,                 // -
  OpenBrace = 0x7B,             // {
  OpenBracket = 0x5B,           // [
  OpenParen = 0x28,             // (
  Percent = 0x25,               // %
  Plus = 0x2B,                  // +
  Question = 0x3F,              // ?
  Semicolon = 0x3B,             // ;
  SingleQuote = 0x27,           // '
  Slash = 0x2F,                 // /
  Tilde = 0x7E,                 // ~

  Backspace = 0x08,             // \b
  FormFeed = 0x0C,              // \f
  ByteOrderMark = 0xFEFF,
  Tab = 0x09,                   // \t
  VerticalTab = 0x0B,           // \v
};


enum SyntaxKind {
  Unknown,
  EndOfFileToken,
  SingleLineCommentTrivia,
  MultiLineCommentTrivia,
  NewLineTrivia,
  WhitespaceTrivia,
  // We detect and provide better error recovery when we encounter a git merge marker.  This
  // allows us to edit files with git-conflict markers in them in a much more pleasant manner.
  ConflictMarkerTrivia,
  // Literals
  NumericLiteral,
  StringLiteral,
  RegularExpressionLiteral,
  NoSubstitutionTemplateLiteral,
  // Pseudo-literals
  TemplateHead,
  TemplateMiddle,
  TemplateTail,
  // Punctuation
  OpenBraceToken,
  CloseBraceToken,
  OpenParenToken,
  CloseParenToken,
  OpenBracketToken,
  CloseBracketToken,
  DotToken,
  DotDotDotToken,
  SemicolonToken,
  CommaToken,
  LessThanToken,
  GreaterThanToken,
  LessThanEqualsToken,
  GreaterThanEqualsToken,
  EqualsEqualsToken,
  ExclamationEqualsToken,
  EqualsGreaterThanToken,
  PlusToken,
  MinusToken,
  AsteriskToken,
  SlashToken,
  PercentToken,
  PlusPlusToken,
  MinusMinusToken,
  LessThanLessThanToken,
  GreaterThanGreaterThanToken,
  GreaterThanGreaterThanGreaterThanToken,
  AmpersandToken,
  BarToken,
  CaretToken,
  ExclamationToken,
  TildeToken,
  AmpersandAmpersandToken,
  BarBarToken,
  QuestionToken,
  ColonToken,
  // Assignments
  EqualsToken,
  PlusEqualsToken,
  MinusEqualsToken,
  AsteriskEqualsToken,
  SlashEqualsToken,
  PercentEqualsToken,
  LessThanLessThanEqualsToken,
  GreaterThanGreaterThanEqualsToken,
  GreaterThanGreaterThanGreaterThanEqualsToken,
  AmpersandEqualsToken,
  BarEqualsToken,
  CaretEqualsToken,
  // Identifiers
  Identifier,
  // Reserved words
  BreakKeyword,
  CaseKeyword,
  CatchKeyword,
  ClassKeyword,
  ConstKeyword,
  ContinueKeyword,
  DebuggerKeyword,
  DefaultKeyword,
  DeleteKeyword,
  DoKeyword,
  ElseKeyword,
  EnumKeyword,
  ExportKeyword,
  ExtendsKeyword,
  FalseKeyword,
  FinallyKeyword,
  ForKeyword,
  FunctionKeyword,
  IfKeyword,
  ImportKeyword,
  InKeyword,
  InstanceOfKeyword,
  NewKeyword,
  NullKeyword,
  ReturnKeyword,
  SetKeyword,
  SuperKeyword,
  SwitchKeyword,
  ThisKeyword,
  ThrowKeyword,
  TrueKeyword,
  TryKeyword,
  TypeOfKeyword,
  VoidKeyword,
  WhileKeyword,
  WithKeyword,
  // Strict mode reserved words
  AsKeyword,
  ImplementsKeyword,
  InterfaceKeyword,
  LetKeyword,
  PackageKeyword,
  PrivateKeyword,
  ProtectedKeyword,
  PublicKeyword,
  StaticKeyword,
  YieldKeyword,
  // Contextual keywords
  AnyKeyword,
  BooleanKeyword,
  ConstructorKeyword,
  DeclareKeyword,
  GetKeyword,
  ModuleKeyword,
  RequireKeyword,
  NumberKeyword,
  StringKeyword,
  SymbolKeyword,
  TypeKeyword,
  FromKeyword,
  OfKeyword, // LastKeyword and LastToken

  // Parse tree nodes

  // Names
  QualifiedName,
  ComputedPropertyName,
  // Signature elements
  TypeParameter,
  Parameter,
  // TypeMember
  PropertySignature,
  PropertyDeclaration,
  MethodSignature,
  MethodDeclaration,
  Constructor,
  GetAccessor,
  SetAccessor,
  CallSignature,
  ConstructSignature,
  IndexSignature,
  // Type
  TypeReference,
  FunctionType,
  ConstructorType,
  TypeQuery,
  TypeLiteral,
  ArrayType,
  TupleType,
  UnionType,
  ParenthesizedType,
  // Binding patterns
  ObjectBindingPattern,
  ArrayBindingPattern,
  BindingElement,
  // Expression
  ArrayLiteralExpression,
  ObjectLiteralExpression,
  PropertyAccessExpression,
  ElementAccessExpression,
  CallExpression,
  NewExpression,
  TaggedTemplateExpression,
  TypeAssertionExpression,
  ParenthesizedExpression,
  FunctionExpression,
  ArrowFunction,
  DeleteExpression,
  TypeOfExpression,
  VoidExpression,
  PrefixUnaryExpression,
  PostfixUnaryExpression,
  BinaryExpression,
  ConditionalExpression,
  TemplateExpression,
  YieldExpression,
  SpreadElementExpression,
  OmittedExpression,
  // Misc
  TemplateSpan,
  // Element
  Block,
  VariableStatement,
  EmptyStatement,
  ExpressionStatement,
  IfStatement,
  DoStatement,
  WhileStatement,
  ForStatement,
  ForInStatement,
  ForOfStatement,
  ContinueStatement,
  BreakStatement,
  ReturnStatement,
  WithStatement,
  SwitchStatement,
  LabeledStatement,
  ThrowStatement,
  TryStatement,
  DebuggerStatement,
  VariableDeclaration,
  VariableDeclarationList,
  FunctionDeclaration,
  ClassDeclaration,
  InterfaceDeclaration,
  TypeAliasDeclaration,
  EnumDeclaration,
  ModuleDeclaration,
  ModuleBlock,
  ImportEqualsDeclaration,
  ImportDeclaration,
  ImportClause,
  NamespaceImport,
  NamedImports,
  ImportSpecifier,
  ExportAssignment,
  ExportDeclaration,
  NamedExports,
  ExportSpecifier,

  // Module references
  ExternalModuleReference,

  // Clauses
  CaseClause,
  DefaultClause,
  HeritageClause,
  CatchClause,

  // Property assignments
  PropertyAssignment,
  ShorthandPropertyAssignment,

  // Enum
  EnumMember,
  
  // Top-level nodes
  SourceFile,

  // Synthesized list
  
  SyntaxList,
  // Enum value count
  
  Count,
  // Markers
  FirstAssignment = EqualsToken,
  LastAssignment = CaretEqualsToken,
  FirstReservedWord = BreakKeyword,
  LastReservedWord = WithKeyword,
  FirstKeyword = BreakKeyword,
  LastKeyword = OfKeyword,
  FirstFutureReservedWord = ImplementsKeyword,
  LastFutureReservedWord = YieldKeyword,
  FirstTypeNode = TypeReference,
  LastTypeNode = ParenthesizedType,
  FirstPunctuation = OpenBraceToken,
  LastPunctuation = CaretEqualsToken,
  FirstToken = Unknown,
  LastToken = LastKeyword,
  FirstTriviaToken = SingleLineCommentTrivia,
  LastTriviaToken = ConflictMarkerTrivia,
  FirstLiteralToken = NumericLiteral,
  LastLiteralToken = NoSubstitutionTemplateLiteral,
  FirstTemplateToken = NoSubstitutionTemplateLiteral,
  LastTemplateToken = TemplateTail,
  FirstBinaryOperator = LessThanToken,
  LastBinaryOperator = CaretEqualsToken,
  FirstNode = QualifiedName
};


enum Modifier {
  Export =            0x00000001,  // Declarations
  Ambient =           0x00000002,  // Declarations
  Public =            0x00000010,  // Property/Method
  Private =           0x00000020,  // Property/Method
  Protected =         0x00000040,  // Property/Method
  Static =            0x00000080,  // Property/Method
  Default =           0x00000100,  // Function/Class (export default declaration)
  MultiLine =         0x00000200,  // Multi-line array or object literal
  Synthetic =         0x00000400,  // Synthetic node (for full fidelity)
  DeclarationFile =   0x00000800,  // Node is a .d.ts file
  Let =               0x00001000,  // Variable declaration
  Const =             0x00002000,  // Variable declaration
  OctalLiteral =      0x00004000,

  Modifier = Export | Ambient | Public | Private | Protected | Static | Default,
  AccessibilityModifier = Public | Private | Protected
};


enum ParsingContext {
  SourceElements,            // Elements in source file
  ModuleElements,            // Elements in module declaration
  BlockStatements,           // Statements in block
  SwitchClauses,             // Clauses in switch statement
  SwitchClauseStatements,    // Statements in switch clause
  TypeMembers,               // Members in interface or type literal
  ClassMembers,              // Members in class declaration
  EnumMembers,               // Members in enum declaration
  TypeReferences,            // Type references in extends or implements clause
  VariableDeclarations,      // Variable declarations in variable statement
  ObjectBindingElements,     // Binding elements in object binding list
  ArrayBindingElements,      // Binding elements in array binding list
  ArgumentExpressions,       // Expressions in argument list
  ObjectLiteralMembers,      // Members in object literal
  ArrayLiteralMembers,       // Members in array literal
  Parameters,                // Parameters in parameter list
  TypeParameters,            // Type parameters in type parameter list
  TypeArguments,             // Type arguments in type argument list
  TupleElementTypes,         // Element types in tuple element type list
  HeritageClauses,           // Heritage clauses for a class or interface declaration.
  ImportOrExportSpecifiers,  // Named import clause's import specifier list
};


// Error callback definitition
typedef void (*ErrorCallback)(Diagnostic);


struct TextRange {
public:
  int start;
  int end;
};


struct Node: public TextRange {
public:
  Node(int start, int end, SyntaxKind kind, vector<enum Modifier> modifiers) {
    this->start = start;
    this->end = end;
    this->kind = kind;
    this->modifiers = modifiers;
  }

  Node(int start, int end, SyntaxKind kind) {
    this->start = start;
    this->end = end;
    this->kind = kind;
  }

  virtual ~Node() {}

  SyntaxKind kind;
  vector<enum Modifier> modifiers;
};


struct Identifier: public Node {
public:
  Identifier(int start, int end, SyntaxKind kind, vector<enum Modifier> modifiers, string text): Node(start, end, kind, modifiers) {
    this->text = text;
  }
  string text;
};


struct VariableDeclaration: public Node {
public:
  VariableDeclaration(int start, int end, SyntaxKind kind, vector<enum Modifier> modifiers, bool mutable_): Node(start, end, kind, modifiers) {
    this->mutable_ = mutable_;
  }
  struct Identifier* name;
  struct TypeAnnotation* type;
  bool mutable_;
};


struct TypeAnnotation: public Node {
public:
  TypeAnnotation(int start, int end, SyntaxKind kind, string name): Node(start, end, kind) {
    this->name = name;
  }
  string name;
};


struct SourceFile {
  string* source;
  vector<Node*> statements;
  string fileName;
  ~SourceFile() {
//    for (int i = 0; i < statements.size(); ++i) {
//      delete statements[i];
//    }
//    statements.clear();
  }
};


#endif