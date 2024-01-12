#include <bits/stdc++.h>
using namespace std;

// Define macros for loops and common elements
#define loop(var, start, end) for (int var = start; var < end; ++var)
#define rloop(var, start, end) for (int var = start; var >= end; --var)
#define ll long long
#define endl "\n"
#define all(s) s.begin(), s.end()
#define PI 3.141592653589793
#define se second
#define fi first

// Define 5 Token types
enum TokenType { TYPE_INT, TYPE_PLUS, TYPE_MINUS, TYPE_MULTI, TYPE_DIV };

// Define a structure to represent tokens
struct Token {
  TokenType Type;
  string Text;
};

// Lexer class for tokenizing the input string
class Lexer {
  string text;
  int n;
  queue<Token> tokenQueue;

public:
  // Constructor taking an input string
  Lexer(string input) : text(input), n(input.length()) {}

  // Tokenize the input string
  void tokenize() {
    loop(i, 0, n) {
      if (isdigit(text[i])) {
        // If the character is a digit, create a token for an integer
        string num = "";
        while (isdigit(text[i])) {
          num += text[i];
          ++i;
        }
        tokenQueue.push({TYPE_INT, num});
      } 
      // Check for operators and create corresponding tokens
      if (text[i] == '+') {
        tokenQueue.push({TYPE_PLUS, "+"});
      } else if (text[i] == '-') {
        tokenQueue.push({TYPE_MINUS, "-"});
      } else if (text[i] == '*') {
        tokenQueue.push({TYPE_MULTI, "*"});
      } else if (text[i] == '/') {
        tokenQueue.push({TYPE_DIV, "/"});
      } else if (text[i] != ' ' && text[i] != '\0') {
        // Handle unknown characters
        cout << "Error!! Unknown character at pos " << i << "\n";
      }
    }
  }

  // Get the tokenized list
  queue<Token> getList() const {
    return tokenQueue;
  }
};

// Parser class for converting token stream to a postfix expression
class Parser {
  stack<Token> opStack;
  vector<Token> output;
  queue<Token> inputQueue;

public:
  // Constructor taking a Lexer object
  Parser(Lexer lexer) : inputQueue(lexer.getList()) {}

  // Parse the token stream
  void parseLexer() {
    while (!inputQueue.empty()) {
      Token next = peekNextToken();
      if (!isOperator(next)) {
        // If token is not an operator, add it to the output
        output.push_back(getNextToken());
      } else {
        // Handle operators and precedence
        while (!opStack.empty() && !isLess(opStack.top(), next)) {
          output.push_back(opStack.top());
          opStack.pop();
        }
        opStack.push(getNextToken());
      }
    }
    // Pop any remaining operators from the stack to the output
    while (!opStack.empty()) {
      output.push_back(opStack.top());
      opStack.pop();
    }
    // Print the postfix expression
    printTree();
  }

  // Print the postfix expression
  void printTree() const {
    for (const auto& token : output) {
      cout << token.Text << " ";
    }
  }

private:
  // Check if a token is an operator
  bool isOperator(Token next) const {
    return (next.Type == TYPE_PLUS || next.Type == TYPE_MINUS ||
            next.Type == TYPE_MULTI || next.Type == TYPE_DIV);
  }

  // Check precedence of operators
  bool isLess(Token top, Token next) const {
    return ((top.Type == TYPE_PLUS || top.Type == TYPE_MINUS) &&
            (next.Type == TYPE_MULTI || next.Type == TYPE_DIV));
  }

  // Get the next token from the input queue
  Token getNextToken() {
    Token temp = inputQueue.front();
    inputQueue.pop();
    return temp;
  }

  // Peek at the next token without removing it from the queue
  Token peekNextToken() const {
    return inputQueue.front();
  }
};

int main() {
  // Set up input/output stream optimizations
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  // Open the input file
  ifstream in("C:/Users/Mohamed/Desktop/Coding Stuff/C++ Stuff/C++/input.txt");
  if (!in.is_open()) {
    cout << "Error opening file\n";
    return 1;
  }

  string line, input;
  // Read the input file line by line
  while (getline(in, line)) {
    input += line;
  }
  in.close();

  // Tokenize the input string
  Lexer lexer(input);
  lexer.tokenize();

  // Parse the token stream and print the postfix expression
  Parser parser(lexer);
  parser.parseLexer();

  return 0;
}
