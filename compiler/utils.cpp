

#include "types.h"
#include <string>
#include <sstream>


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


string charCodeToString(int charCode) {
  stringstream ss;
  string s;
  ss << (char)charCode;
  ss >> s;
  return s;
}