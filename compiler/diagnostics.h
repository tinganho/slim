//
//  diagnostics.h
//  Slim
//
//  Created by Tingan Ho on 3/30/15.
//
//

#ifndef __Slim__diagnostics__
#define __Slim__diagnostics__


#include <map>
#include <string>
#include "types.h"


using namespace std;


enum Diagnostic {
  UnexpectEndOfInput,
  UnterminatedStringLiteral
};


struct DiagnosticObject {
  unsigned int code;
  string message;
};


DiagnosticObject getDiagnostic(Diagnostic diagnostic);


#endif /* defined(__Slim__diagnostics__) */
