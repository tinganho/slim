

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


namespace VariableDeclarationTest {
  TEST_F(ParserTest, VariableDeclaration) {
    string source = "let variable = 1";
    Parser parser;
    struct SourceFile* sourceFile = parser.parseSourceFile("file.s", &source);
    EXPECT_EQ(sourceFile->statements[0]->kind, SyntaxKind::VariableStatement);
    delete sourceFile;
  }
}
