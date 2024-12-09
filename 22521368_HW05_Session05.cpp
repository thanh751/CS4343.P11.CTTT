//Name: Trần Tịnh Đan Thanh
//Student's ID: 22521368
//Session 05 - Homework 05
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <memory>
#include <stdexcept>

// Abstract Syntax Tree Node
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual double evaluate() const = 0;
};

// Number Node
struct NumberNode : public ASTNode {
    double value;
    NumberNode(double val) : value(val) {}
    double evaluate() const override { return value; }
};

// Binary Operation Node
struct BinOpNode : public ASTNode {
    char op;
    std::unique_ptr<ASTNode> left, right;
    BinOpNode(char oper, std::unique_ptr<ASTNode> lhs, std::unique_ptr<ASTNode> rhs)
        : op(oper), left(std::move(lhs)), right(std::move(rhs)) {}
    double evaluate() const override {
        double l = left->evaluate();
        double r = right->evaluate();
        switch(op) {
            case '+': return l + r;
            case '-': return l - r;
            case '*': return l * r;
            case '/': 
                if (r == 0) throw std::runtime_error("Division by zero");
                return l / r;
            default: throw std::runtime_error("Unknown operator");
        }
    }
};

// Parser
class Parser {
public:
    Parser(const std::string& expr) : expression(expr), pos(0) {}
    std::unique_ptr<ASTNode> parse() { return parseExpression(); }
private:
    std::string expression;
    size_t pos;

    std::unique_ptr<ASTNode> parseExpression() {
        auto node = parseTerm();
        while (match('+') || match('-')) {
            char op = expression[pos - 1];
            auto right = parseTerm();
            node = std::make_unique<BinOpNode>(op, std::move(node), std::move(right));
        }
        return node;
    }

    std::unique_ptr<ASTNode> parseTerm() {
        auto node = parseFactor();
        while (match('*') || match('/')) {
            char op = expression[pos - 1];
            auto right = parseFactor();
            node = std::make_unique<BinOpNode>(op, std::move(node), std::move(right));
        }
        return node;
    }

    std::unique_ptr<ASTNode> parseFactor() {
        skipWhitespace();
        if (match('(')) {
            auto node = parseExpression();
            if (!match(')')) throw std::runtime_error("Expected ')'");
            return node;
        }
        return parseNumber();
    }

    std::unique_ptr<ASTNode> parseNumber() {
        skipWhitespace();
        size_t start = pos;
        while (pos < expression.size() && (isdigit(expression[pos]) || expression[pos] == '.')) pos++;
        if (start == pos) throw std::runtime_error("Expected number");
        double value = std::stod(expression.substr(start, pos - start));
        return std::make_unique<NumberNode>(value);
    }

    bool match(char expected) {
        skipWhitespace();
        if (pos < expression.size() && expression[pos] == expected) {
            pos++;
            return true;
        }
        return false;
    }

    void skipWhitespace() {
        while (pos < expression.size() && isspace(expression[pos])) pos++;
    }
};

int main() {
    std::string expr;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, expr);

    try {
        Parser parser(expr);
        auto ast = parser.parse();
        double result = ast->evaluate();
        std::cout << "Result: " << result << std::endl;
    }
    catch(const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}