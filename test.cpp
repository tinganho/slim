

#include "parser.h"
#include "scanner.h"
#include "types.h"
#include <iostream>


int main() {
  string source = "let variable: int;";
  Parser parser;
  struct SourceFile* sourceFile = parser.parseSourceFile("file.s", &source);
//  delete sourceFile;
}