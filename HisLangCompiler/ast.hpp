// ast.hpp - AST structure for MyLang
#pragma once
#include "lexer.hpp"
#include <string>
#include <vector>
#include <memory>

struct Statement {
    virtual ~Statement() = default;
};

class SayStatement : public Statement {
public:
    std::vector<std::string> args;
    std::vector<bool> is_vars;
    std::string end;

    SayStatement(const std::vector<std::string>& args,
        const std::vector<bool>& is_vars,
        const std::string& end)
        : args(args), is_vars(is_vars), end(end) {}
};


struct SetStatement : public Statement {
    std::string var;
    SetStatement(const std::string& var) : var(var) {}
};

struct FunctionCall : Statement {
    std::string name;
    std::string arg;
    TokenType arg_type;
    FunctionCall(const std::string& n, const std::string& a, TokenType t = TokenType::EOFToken)
        : name(n), arg(a), arg_type(t) {}
};


struct FunctionDef : public Statement {
    std::string name;
    std::string param;
    std::vector<std::shared_ptr<Statement>> body;
    FunctionDef(const std::string& name, const std::string& param,
        const std::vector<std::shared_ptr<Statement>>& body)
        : name(name), param(param), body(body) {}
};

struct StartBlock : public Statement {
    std::vector<std::shared_ptr<Statement>> body;
    StartBlock(const std::vector<std::shared_ptr<Statement>>& body)
        : body(body) {}
};

struct AST {
    std::vector<std::shared_ptr<Statement>> statements;
};
