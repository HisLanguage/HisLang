// generator.hpp - AST to C++ generator
#pragma once
#include "ast.hpp"
#include "lexer.hpp"
#include <string>

std::string generate_cpp(const AST& ast);