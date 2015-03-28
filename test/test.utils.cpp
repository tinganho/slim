
#include "test.h"
#include "gtest/gtest.h"

void testToken(string* source, SyntaxKind token) {
  Scanner scanner(&source);
  SyntaxKind result = scanner.nextToken();
  EXPECT_EQ(result, SyntaxKind::WhitespaceTrivia);
}