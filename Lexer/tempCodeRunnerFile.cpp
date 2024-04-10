#include <string>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    LITERAL,
    OPERATOR,
    PUNCTUATION,
    COMMENT,
    NUMBER
};

struct Token {
    TokenType type;
    std::string lexeme;
};

vector<Token> Lexer(string lexeme){
    vector<Token> expression;
    for(int i = 0; i < lexeme.length(); i++){
        if(isdigit(lexeme[i])){
            string temp;
            while(i < lexeme.length() && isdigit(lexeme[i])){
                temp += lexeme[i];
                i++;
            }
            expression.push_back({NUMBER, temp});
            i--;
        }
        else if(isalpha(lexeme[i])){
            string temp;
            while(i < lexeme.length() && isalpha(lexeme[i])){
                temp += lexeme[i];
                i++;
            }
            expression.push_back({IDENTIFIER, temp});
            i--;
        }
        else if(lexeme[i] == '+' || lexeme[i] == '-' || lexeme[i] == '*' || lexeme[i] == '/' || lexeme[i] == '(' || lexeme[i] == ')' || lexeme[i] == '%' || lexeme[i] == '^'){
            expression.push_back({OPERATOR, string(1, lexeme[i])});
        }
    }
    return expression;
}

int main(){
    vector<Token> expression;
    string lexeme = "print 56+4\n64-6";
    stringstream ss(lexeme);
    string token;
    while (getline(ss, token, '\n')) {
        vector<Token> tokens = Lexer(token);
        expression.insert(expression.end(), tokens.begin(), tokens.end());
    cout<<tokens[0];
    }
    return 0;
}
