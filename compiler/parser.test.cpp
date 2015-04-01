

#include <string>
#include "parser.h"
#include "types.h"
#include "test.utils.h"
#include "gtest/gtest.h"


class ParserTest: public testing::Test {
protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};


namespace WhiteSpaceTests {
  TEST_F(ParserTest, Newline) {
    string source = "int main() {}";
    Parser parser;
    struct SourceFile sourceFile = parser.parseSourceFile("file.s", &source);
    EXPECT_EQ(sourceFile.statements[0].kind, SyntaxKind::CallExpression);
  }
}
