//
//  diagnostics.cpp
//  Slim
//
//  Created by Tingan Ho on 3/30/15.
//
//

#include "diagnostics.h"

DiagnosticObject getDiagnostic(Diagnostic diagnostic) {
  switch (diagnostic) {
    case Diagnostic::UnexpectEndOfInput:
      return DiagnosticObject { 1001, "Unexpeted end of input." }
    case Diagnostic::UnterminatedStringLiteral:
      return DiagnosticObject { 1002, "Unterminated string literal." }
    case Diagnostic::ExpectedIdentifier:
      return DiagnosticObject { 1003, "Expected identifier." }
    default:
      break;
  }
}