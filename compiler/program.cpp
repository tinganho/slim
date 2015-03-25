
#include <iostream>
#include <string>
#include "scanner.h"

using namespace std;

int main() {
  string result = createScanner("hello world");
  cout << (int)result.at(1) << endl;
  return 0;
}
