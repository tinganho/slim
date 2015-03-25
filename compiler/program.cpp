
#include <iostream>
#include <string>
#include "scanner.h"

using namespace std;

int main() {
  string source = "hello world";
  string result = createScanner(&source);
  cout << result << endl;
  return 0;
}
