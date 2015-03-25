
#include <string>
#include "scanner.h"

using namespace std;

// Source text
string sourceText;

// Current index in source text
int idx = 0;

// Current character code
int ch;

string createScanner(string sourceText) {
  sourceText = sourceText;
  return sourceText;
}

void nextToken() {
  ch = (int)sourceText.at(idx);
  idx++;
}
