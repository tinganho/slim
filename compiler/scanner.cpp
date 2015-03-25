
#include <string>
#include "scanner.h"
#include "types.cpp"

using namespace std;

// Source text
string sourceText;

// Current index in source text
int idx = 0;

// Current character code
char ch;

string createScanner(string sourceText) {
  sourceText = sourceText;
  return sourceText;
}

void nextToken() {
  ch = sourceText.at(idx);
  idx++;
}
