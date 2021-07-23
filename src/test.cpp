#include "calculator.hpp"

int main()
{
	std::string expression = { "1+(2*(2.5+2.5+(3-2)))-(3/1.5)" };
	// std::string expression = { "1+2+3" };
	// std::string expression
	Calculator calc;
	printf("%f\n", calc.Evaluate(expression));
}