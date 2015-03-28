
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

TEST_F(ScannerTest, Newline) {
  expectStringToEqualToken("\n", SyntaxKind::NewLineTrivia);
}

TEST_F(ScannerTest, Space) {
  string source = " ";
  Scanner scanner(&source);
  SyntaxKind result = scanner.nextToken();
  EXPECT_EQ(result, SyntaxKind::WhitespaceTrivia);
}

TEST_F(ScannerTest, Tab) {
  string source = "\t";
  Scanner scanner(&source);
  SyntaxKind result = scanner.nextToken();
  EXPECT_EQ(result, SyntaxKind::WhitespaceTrivia);
}

TEST_F(ScannerTest, FormFeed) {
  string source = "\f";
  Scanner scanner(&source);
  SyntaxKind result = scanner.nextToken();
  EXPECT_EQ(result, SyntaxKind::WhitespaceTrivia);
}

TEST_F(ScannerTest, VerticalTab) {
  string source = "\v";
  Scanner scanner(&source);
  SyntaxKind result = scanner.nextToken();
  EXPECT_EQ(result, SyntaxKind::WhitespaceTrivia);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}