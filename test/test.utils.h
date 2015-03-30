//
//  test.h
//  Slim
//
//  Created by Tingan Ho on 3/28/15.
//
//

#ifndef __Slim__test__
#define __Slim__test__


#include <string>
#include "types.h"
#include "scanner.h"

using namespace std;


Scanner expectStringToEqualToken(string source, SyntaxKind token);


#endif /* defined(__Slim__test__) */
