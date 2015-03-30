
#include <string>
#include "gtest/gtest.h"
#include "scanner.h"
#include "types.h"
#include "test.utils.h"

  
// The fixture for testing class Foo.
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
    expectStringToEqualToken("!", SyntaxKind::ExclamationEqualsToken);
  }
}


int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}