#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

enum TokenType {
    NUMBER,
    OPERATOR,
    LPAREN,
    RPAREN,
    END
};

struct Token {
    TokenType type;
    string value;
};

class Parser {
public:
    Parser(const vector<Token>& tokens) : tokens(tokens), current_token_idx(0) {}

    int parse() {
        return parseExpression();
    }

private:
    vector<Token> tokens;
    size_t current_token_idx;

    Token getCurrentToken() {
        if (current_token_idx >= tokens.size()) {
            return {END, ""};
        }
        return tokens[current_token_idx];
    }

    void consumeToken() {
        current_token_idx++;
    }

    int parseExpression() {
        int result = parseTerm();
        while (true) {
            Token token = getCurrentToken();
            if (token.type == OPERATOR && (token.value == "+" || token.value == "-")) {
                consumeToken();
                int term = parseTerm();
                if (token.value == "+") {
                    result += term;
                } else {
                    result -= term;
                }
            } else {
                break;
            }
        }
        return result;
    }

    int parseTerm() {
        int result = parseFactor();
        while (true) {
            Token token = getCurrentToken();
            if (token.type == OPERATOR && (token.value == "*" || token.value == "/")) {
                consumeToken();
                int factor = parseFactor();
                if (token.value == "*") {
                    result *= factor;
                } else {
                    if (factor == 0) {
                        throw invalid_argument("Division by zero");
                    }
                    result /= factor;
                }
            } else {
                break;
            }
        }
        return result;
    }

    int parseFactor() {
        Token token = getCurrentToken();
        if (token.type == NUMBER) {
            consumeToken();
            return stoi(token.value);
        } else if (token.type == LPAREN) {
            consumeToken();
            int result = parseExpression();
            token = getCurrentToken();
            if (token.type != RPAREN) {
                throw invalid_argument("Unmatched parenthesis");
            }
            consumeToken();
            return result;
        } else {
            throw invalid_argument("Invalid token");
        }
    }
};

int main() {
    vector<Token> tokens = {
        {NUMBER, "5"},
        {OPERATOR, "+"},
        {NUMBER, "3"},
        {OPERATOR, "*"},
        {NUMBER, "2"},
    };

    Parser parser(tokens);
    try {
        int result = parser.parse();
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
