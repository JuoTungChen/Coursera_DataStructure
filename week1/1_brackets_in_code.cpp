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

	int result_pos = 0;

    std::stack <Bracket> opening_brackets_stack;
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        if (next == '(' || next == '[' || next == '{') {
		opening_brackets_stack.push(Bracket(next, position+1));       

       	}
	else if (next == ')' || next == ']' || next == '}') {
		if(!opening_brackets_stack.empty()){
			if(opening_brackets_stack.top().Matchc(next))
				opening_brackets_stack.pop();
		
			else{
				opening_brackets_stack.push(Bracket(next, position+1));       
				break;
			}
		}
		else{
			opening_brackets_stack.push(Bracket(next, position+1));       
			break;
		}
       	}
    }

    // Printing answer, write your code here
    	if(opening_brackets_stack.empty())
    		std::cout<< "Success" <<std::endl;
	else
    		std::cout<< opening_brackets_stack.top().position <<std::endl;

    return 0;
}
