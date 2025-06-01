// generator.cpp - AST to C++ generator
#include "generator.hpp"
#include "ast.hpp"
#include <sstream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <iostream>


static std::string indent(int level) {
    return std::string(level * 4, ' ');
}

static std::string escape_string(const std::string& s) {
    std::string out;
    for (char c : s) {
        if (c == '\"') out += "\\\"";
        else if (c == '\\') out += "\\\\";
        else out += c;
    }
    return out;
}

static void gen_stmt(std::ostringstream& out, const std::shared_ptr<Statement>& stmt, int indent_level = 1) {
    std::string ind = indent(indent_level);

    if (auto say = dynamic_cast<SayStatement*>(stmt.get())) {
        out << ind << "std::cout";
        for (size_t i = 0; i < say->args.size(); ++i) {
            out << " << ";
            if (say->is_vars[i]) {
                out << say->args[i];
            }
            else {
                out << "\"" << escape_string(say->args[i]) << "\"";
            }
        }

        if (say->end == "\\n")
            out << " << std::endl;\n";
        else
            out << " << \"" << escape_string(say->end) << "\";\n";
    }
    else if (auto set = dynamic_cast<SetStatement*>(stmt.get())) {
        out << ind << "auto " << set->var << " = 0;\n";
    }
    else if (auto func = dynamic_cast<FunctionDef*>(stmt.get())) {
        if (!func->param.empty()) {
            out << "void " << func->name << "(auto " << func->param << ") {\n";
        }
        else {
            out << "void " << func->name << "() {\n";
        }

        for (auto& s : func->body) gen_stmt(out, s, indent_level + 1);
        out << "}\n";
    }
    else if (auto call = dynamic_cast<FunctionCall*>(stmt.get())) {
        out << ind << call->name << "(";
#if _DEBUG
        std::cerr << "[DEBUG] function call arg in gen " << escape_string(call->arg) << " ";
        switch (call->arg_type) {
        case TokenType::Keyword:        std::cerr << "Keyword    "; break;
        case TokenType::Identifier:     std::cerr << "Identifier "; break;
        case TokenType::StringLiteral:  std::cerr << "String     "; break;
        case TokenType::Newline:        std::cerr << "Newline    "; break;
        case TokenType::EOFToken:       std::cerr << "EOF        "; break;
        case TokenType::Symbol:         std::cerr << "Symbol     "; break;
        }
        std::cerr << std::endl;
#endif
        if (!call->arg.empty()) {
            if (call->arg_type == TokenType::StringLiteral) {
                out << "\"" << escape_string(call->arg) << "\"";
            }
            else {
                out << call->arg;
            }
        }
        out << ");\n";
    }
    else if (auto main = dynamic_cast<StartBlock*>(stmt.get())) {
        out << "int main() {\n#ifdef _WIN32\nSetConsoleOutputCP(CP_UTF8);\n#endif\n\n";
        for (auto& s : main->body) gen_stmt(out, s, indent_level + 1);
        out << indent(indent_level + 1) << "return 0;\n";
        out << "}\n";
    }
}

std::string generate_cpp(const AST& ast) {
    std::ostringstream out;
    out << "#include <iostream>\n#include <string>\n\n#ifdef _WIN32\n#include <windows.h>\n#endif\n\n";

    for (auto& stmt : ast.statements) {
        if (dynamic_cast<FunctionDef*>(stmt.get())) {
            gen_stmt(out, stmt, 0);
            out << '\n';
        }
    }

    for (auto& stmt : ast.statements) {
        if (dynamic_cast<StartBlock*>(stmt.get())) {
            gen_stmt(out, stmt, 0);
            out << '\n';
        }
    }

    return out.str();
}
