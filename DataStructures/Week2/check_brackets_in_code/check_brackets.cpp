#include <iostream>
#include <stack>
#include <string>

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
            // Process opening bracket, write your code here
            opening_brackets_stack.emplace(Bracket(next, position +1));
        }

        if (next == ')' || next == ']' || next == '}') {
            if(opening_brackets_stack.empty()) {
              std::cout << position + 1 << "\n";
              return 0;
            } else if(!opening_brackets_stack.top().Matchc(next)) {
              std::cout << position + 1 << "\n";
              return 0;
            } else {
              opening_brackets_stack.pop();
            }
        }
    }

    if(opening_brackets_stack.empty()) {
      std::cout << "Success\n";
    } else {
      std::cout << opening_brackets_stack.top().position << "\n";
    }

    return 0;
}
