#include "calculator.hpp"
#include <string.h>
#include <errno.h>

int main()
{
	// std::string expression = { "1+(2*(2.5+2.5+(3-2)))-(3/1.5)" };
	// std::string expression = { "1+2+3" };
	// std::string expression
	Calculator calc;
	calc.ReadStdin();
	calc.Evaluate();
	calc.ShowResult();
}