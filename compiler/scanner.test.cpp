

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


namespace StringLiterals {
  TEST_F(ScannerTest, SingleQuote) {
    Scanner scanner = expectStringToEqualToken("\'hej\'", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "hej");
  }

  TEST_F(ScannerTest, DoubleQuote) {
    Scanner scanner = expectStringToEqualToken("\"hej\"", SyntaxKind::StringLiteral);
    EXPECT_EQ(scanner.getTokenValue(), "hej");
  }
}
