

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
    string source = "let variable: int;";
    Parser parser;
    struct SourceFile* sourceFile = parser.parseSourceFile("file.s", &source);
    EXPECT_EQ(sourceFile->statements[0]->kind, SyntaxKind::VariableStatement);
//    EXPECT_EQ(static_cast<struct VariableDeclaration*>(sourceFile->statements[0])->name->text, "variable");
//    delete sourceFile;
  }
}
