// parser.hpp - MyLang parser interface
#pragma once
#include "ast.hpp"
#include "lexer.hpp"
#include <vector>

AST parse(const std::vector<Token>& tokens);
