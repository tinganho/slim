

#include <string>
#include "test.utils.h"
#include "scanner.h"
#include "gtest/gtest.h"


using namespace std;


void expectStringToEqualToken(string source, SyntaxKind token) {
  Scanner scanner(&source);
  EXPECT_EQ(scanner.nextToken(), token);
}