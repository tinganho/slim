

#include "test.utils.h"
#include "gtest/gtest.h"


class ScannerTest: public testing::Test {
protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};


namespace WhiteSpaceTests {
  TEST_F(ScannerTest, Newline) {
    expectStringToEqualToken("\n", SyntaxKind::NewLineTrivia);
  }

  TEST_F(ScannerTest, Space) {
    expectStringToEqualToken(" ", SyntaxKind::WhitespaceTrivia);
  }

  TEST_F(ScannerTest, Tab) {
    expectStringToEqualToken("\t", SyntaxKind::WhitespaceTrivia);
  }

  TEST_F(ScannerTest, FormFeed) {
    expectStringToEqualToken("\f", SyntaxKind::WhitespaceTrivia);
  }

  TEST_F(ScannerTest, VerticalTab) {
    expectStringToEqualToken("\v", SyntaxKind::WhitespaceTrivia);
  }

  TEST_F(ScannerTest, EndOfFile) {
    expectStringToEqualToken("", SyntaxKind::EndOfFileToken);
  }
}


namespace ExclamationTests {
  TEST_F(ScannerTest, Exclamation) {
    expectStringToEqualToken("!", SyntaxKind::ExclamationToken);
  }

  TEST_F(ScannerTest, ExclamationEqual) {
    expectStringToEqualToken("!=", SyntaxKind::ExclamationEqualsToken);
  }
}


namespace IdentifierTests {
  TEST_F(ScannerTest, Identifier) {
    Scanner scanner = expectStringToEqualToken("identifier", SyntaxKind::Identifier);
    EXPECT_EQ(scanner.getTokenValue(), "identifier");
  }
}


namespace StringLiterals {
  TEST_F(ScannerTest, SingleQuote) {
    Scanner scanner = expectStringToEqualToken("\'hej\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\'");
  }

  TEST_F(ScannerTest, DoubleQuote) {
    Scanner scanner = expectStringToEqualToken("\"hej\"", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\"hej\"");
  }

  TEST_F(ScannerTest, Zero) {
    Scanner scanner = expectStringToEqualToken("\'hej\0\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\0\'");
  }

  TEST_F(ScannerTest, Tab) {
    Scanner scanner = expectStringToEqualToken("\'hej\b\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\b\'");
  }

  TEST_F(ScannerTest, Backspace) {
    Scanner scanner = expectStringToEqualToken("\'hej\b\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\b\'");
  }

  TEST_F(ScannerTest, VerticalTab) {
    Scanner scanner = expectStringToEqualToken("\'hej\v\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\v\'");
  }

  TEST_F(ScannerTest, FormFeed) {
    Scanner scanner = expectStringToEqualToken("\'hej\f\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\f\'");
  }

  TEST_F(ScannerTest, CarriageReturn) {
    Scanner scanner = expectStringToEqualToken("\'hej\\r\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\\\r\'");
  }

  TEST_F(ScannerTest, LineFeed) {
    Scanner scanner = expectStringToEqualToken("\'hej\\n\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "\'hej\\\n\'");
  }
}


namespace Punctuations {
  TEST_F(ScannerTest, Plus) {
    expectStringToEqualToken("+", SyntaxKind::PlusToken);
  }

  TEST_F(ScannerTest, PlusEquals) {
    expectStringToEqualToken("+=", SyntaxKind::PlusEqualsToken);
  }

  TEST_F(ScannerTest, PlusPlus) {
    expectStringToEqualToken("++", SyntaxKind::PlusPlusToken);
  }

  TEST_F(ScannerTest, OpenBrace) {
    expectStringToEqualToken("{", SyntaxKind::OpenBraceToken);
  }

  TEST_F(ScannerTest, CloseBrace) {
    expectStringToEqualToken("}", SyntaxKind::CloseBraceToken);
  }

  TEST_F(ScannerTest, OpenParen) {
    expectStringToEqualToken("(", SyntaxKind::OpenParenToken);
  }

  TEST_F(ScannerTest, CloseParen) {
    expectStringToEqualToken(")", SyntaxKind::CloseParenToken);
  }
}