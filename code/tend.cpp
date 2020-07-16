#include <iostream>
int main() {
	int ind = 10;
	// tend operator, just a joke
	// in fact: `--`operator and `>` operator
	while(ind --> 0) {
		std::cout << ind << " ";
	}
	return 0;
}
