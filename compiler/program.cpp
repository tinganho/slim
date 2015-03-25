
#include <iostream>
#include <string>
#include "scanner.h"

using namespace std;

int main() {
  string result = createScanner("hello world");
  cout << result << endl;
  return 0;
}
