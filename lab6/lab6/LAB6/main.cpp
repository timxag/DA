#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include "TLongNumber.h"



int main(void) {

	const int base = 10000; 
	
	std::string x, y;
	char z;

	while (std::cin >> x >> y >> z) {

		TLongNumber a(x, base);
		TLongNumber b(y, base);

		TLongNumber err("-1", base);

		TLongNumber res;

		bool compare = false;
		bool answerOnQuestion;

		switch(z) {
			case '+': {
				res = a + b;
				break;
			}
			case '-': {
				res = a - b;
				break;
			}
			case '*': {
				res = a * b;
				break;
			}
			case '/': {
				res = a / b;
				break;
			}
			case '^': {
				res = a ^ b;
				break;
			}
			case '>': {
				answerOnQuestion =  a > b ;
				compare = true;
				break;
			}
			case '<': {
				answerOnQuestion =  a < b ;
				compare = true;
				break;
			}
			case '=': {
				answerOnQuestion = a == b ;
				compare = true;
				break;
			}
		}

		if (compare) {
			std::cout << (answerOnQuestion ? "true" : "false");
		} else
		if (res == err) {
			std::cout << "Error";
		} else {
			std::cout << res;
		}

		std::cout << std::endl;
	}

	return 0;
}
