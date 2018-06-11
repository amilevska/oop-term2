#include"Stack.h"
#include<conio.h>

/*int main() {
	Stack<int> stack;
	std::cout << "1 - Push\n2 - Pop\n3 - Read\n";
	int answer;
	int item;
	int read_item;
	do {
		std::cin >> answer;
		switch (answer) {
		case 1:
			std::cout << "Enter the item\n";
			std::cin >> item;
			try {
				stack.push(item);
			}
			catch (const std::out_of_range& exception) {
				std::cerr << exception.what() << "\n";
			}
			break;
		case 2:
			try {
				stack.pop();
			}
			catch (const std::out_of_range& exception) {
				std::cerr << exception.what() << "\n";
			}
			break;
		case 3:
			try {
				read_item = stack.read();
			}
			catch (const std::out_of_range& exception) {
				std::cerr << exception.what() << "\n";
				break;
			}
			std::cout << "Item = " << read_item << "\n";
			break;
		}
		stack.print_array();
	} while (_getch() != 27);
}*/

