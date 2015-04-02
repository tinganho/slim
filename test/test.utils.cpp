

#include <string>
#include "test.utils.h"
#include "scanner.h"
#include "gtest/gtest.h"


using namespace std;


Scanner expectStringToEqualToken(string source, SyntaxKind token) {
  Scanner scanner(&source);
  scanner.skipTrivia = false;
  EXPECT_EQ(scanner.scan(), token);
  return scanner;
}