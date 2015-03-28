
#include <string>
#include "gtest/gtest.h"
#include "scanner.h"
#include "types.h"

  
// The fixture for testing class Foo.
class ScannerTest: public testing::Test {
protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(ScannerTest, scan) {
  string source = "\n";
  Scanner scanner(&source);
  SyntaxKind result = scanner.nextToken();
  EXPECT_EQ(result, SyntaxKind::NewLineTrivia);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}