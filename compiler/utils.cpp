

#include "types.h"
#include <string>


bool isModifier(SyntaxKind* token) {
  switch (*token) {
    case SyntaxKind::PublicKeyword:
    case SyntaxKind::PrivateKeyword:
    case SyntaxKind::ProtectedKeyword:
    case SyntaxKind::StaticKeyword:
    case SyntaxKind::ExportKeyword:
    case SyntaxKind::DeclareKeyword:
    case SyntaxKind::ConstKeyword:
    case SyntaxKind::DefaultKeyword:
      return true;
    default:
      return false;
  }
}