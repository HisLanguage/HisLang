// warnings.cpp - Indentation warning analyzer
#include "warnings.hpp"
#include "utils.hpp"
#include <sstream>
#include <iostream>
#include <stack>

void check_indentation(const std::string& source) {
    std::istringstream in(source);
    std::string line;
    int lineno = 1;

    std::stack<int> indent_stack;

    while (std::getline(in, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#') {
            lineno++;
            continue;
        }

        int indent = 0;
        for (char c : line) {
            if (c == ' ') indent++;
            else break;
        }

        if (trimmed == "end") {
            if (indent_stack.empty()) {
                std::cerr << "[Warning] Line " << lineno << ": 'end' without matching block start.\n";
            }
            else {
                int expected_indent = indent_stack.top();
                if (indent != expected_indent) {
                    std::cerr << "[Warning] Line " << lineno << ": 'end' indentation mismatch. Expected "
                        << expected_indent << " spaces but got " << indent << ".\n";
                }
                indent_stack.pop();
            }
        }
        else if (trimmed.find("function") == 0 || trimmed.find("start:") == 0 ||
            trimmed.find("if") == 0 || trimmed.find("elif") == 0 || trimmed.find("else") == 0) {
            indent_stack.push(indent);
        }
        else {
            if (!indent_stack.empty()) {
                int expected_indent = indent_stack.top();
                if (indent <= expected_indent) {
                    std::cerr << "[Warning] Line " << lineno << ": Inconsistent indentation. Expected greater than "
                        << expected_indent << " spaces but got " << indent << ".\n";
                }
            }
        }
        lineno++;
    }

    if (!indent_stack.empty()) {
        std::cerr << "[Warning] EOF: Some blocks not closed properly (missing 'end').\n";
    }
}
