#include <string>
#include <iostream>
#include <vector>
using namespace std;

#include <string>

enum TokenType {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_LITERAL,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATION,
    TOKEN_COMMENT
};

struct Token {
    TokenType type;
    std::string lexeme;
};

vector<string> Lexer(string lexeme){
    vector<string> expression;
    for(int i = 0; i < lexeme.length(); i++){
        if(isdigit(lexeme[i])){
            cout << lexeme[i] << 1 << endl;
            string temp;
            while(i < lexeme.length() && isdigit(lexeme[i])){
                temp += lexeme[i];
                i++;
            }
            expression.push_back(temp);
            i--;
        }
        else if(isalpha(lexeme[i])){
            cout << lexeme[i] << 2 << endl;
            string temp;
            while(i < lexeme.length() && isalpha(lexeme[i])){
                temp += lexeme[i];
                i++;
            }
            expression.push_back(temp);
            i--;
        }
        else if(lexeme[i] == '+' || lexeme[i] == '-' || lexeme[i] == '*' || lexeme[i] == '/' || lexeme[i] == '(' || lexeme[i] == ')' || lexeme[i] == '%' || lexeme[i] == '^'){
            cout << lexeme[i] << 3 << endl;
            expression.push_back(string(1, lexeme[i]));
        }
    }
    return expression;
}

int main(){
    vector<string> expression;
    string lexeme = "print 56+4";
    expression = Lexer(lexeme);
    Analyser(expression);
    return 0;
}