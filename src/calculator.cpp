#include "calculator.hpp"
#include <stdio.h>
#include <errno.h>
#include <string.h>

namespace
{
#define TokenOperandType -1
#define TokenOperationValue 0

	namespace StringUtil
	{
		std::string Trim( const std::string &str )
		{
			std::string s;
			char ch;
			for (size_t i = 0; i < str.length(); ++i)
			{
				ch = str[i];
				if (( ch == ' ' ) || ( ch == '\t' ))
				{
					continue;
				}
				s += ch;
			}
			return s;
		}
	}

}

bool Calculator::Calc( Operations &operations, Operands &operands )
{
	double op1, op2, opRes;
	op1 = operands.top().value;
	operands.pop();
	op2 = operands.top().value;
	operands.pop();
	Token token;
	switch (operations.top().type)
	{
		case '+':
			opRes = op2 + op1;
			token = { TokenOperandType, opRes };
			operands.push( token );
			operations.pop();
			break;
		case '-':
			opRes = op2 - op1;
			token = { TokenOperandType, opRes };
			operands.push( token );
			operations.pop();
			break;
		case '/':
			if (op1 == 0)
			{
				fprintf( stderr, "Divide by zero!\n" );
				return false;
			}
			opRes = op2 / op1;
			token = { TokenOperandType, opRes };
			operands.push( token );
			operations.pop();
			break;
		case '*':
			opRes = op2 * op1;
			token = { TokenOperandType, opRes };
			operands.push( token );
			operations.pop();
			break;

		default:
			fprintf( stderr, "Unknown operation!\n" );
			return false;
	}
	return true;
}

double Calculator::ParseDecimal( char *ch, size_t *index )
{
	double number = .0;
	*ch = expression[*index];
	while (( *ch >= '0' && *ch <= '9' ))
	{
		number = number * 10 + ( *ch - '0' );
		*ch = expression[++( *index )];
	}
	return number;
}

double Calculator::ParseFraction( char *ch, size_t *index )
{
	double number = .0;
	*ch = expression[++( *index )];
	while (( *ch >= '0' && *ch <= '9' ))
	{
		number = number * 10 + ( *ch - '0' ) * .1;
		*ch = expression[++( *index )];
	}
	return number;
}

Calculator::PriorityType Calculator::GetPriority( char ch ) const
{
	if (ch == '+' || ch == '-') return 2;
	if (ch == '/' || ch == '*') return 1;
	else return 3;
}

double Calculator::Evaluate()
{
	bool canBeNegative = true;
	bool isMinus = false;
	Token token;
	for (size_t i = 0; i < expression.length(); )
	{
		double number = .0;
		char ch = expression[i];
		if (ch == '\n') // end of expression
			break; // break cycle and process remaining expression

		if (( ch >= '0' && ch <= '9' ) || ( ch == '-' && canBeNegative == true ))
		{
			canBeNegative = false; // Now we'll read opeartion symbol 
			isMinus = false;
			if (ch == '-')
			{
				ch = expression[++i];
				isMinus = true;
			}
			number = ParseDecimal( &ch, &i );
			double fraction = .0;
			if (ch == '.' || ch == ',')
			{
				fraction = ParseFraction( &ch, &i );
			}
			number += fraction;
			number = isMinus ? -number : number;
			token = { TokenOperandType, number };
			operands.push( token );
			continue;
		}
		if (ch == '+' || ch == '-' && canBeNegative == 0 || ch == '/' || ch == '*')
		{
			if (operations.empty())
			{
				token = { ch, TokenOperandType };
				operations.push( token );
				++i;
				continue;
			}
			if (!operations.empty())
			{
				/** if the current type more important */
				if (GetPriority( ch ) < GetPriority( operations.top().type ))
				{
					token = { ch, TokenOperationValue };
					operations.push( token );
					++i;
					continue;
				}
				else
				{
					if (Calc( operations, operands ) == false) break;
					continue;
				}
			}
		}
		if (ch == '(')
		{
			canBeNegative = true;
			token = { ch, TokenOperationValue };
			operations.push( token );
			++i;
			continue;
		}
		if (ch == ')')
		{
			while (operations.top().type != '(')
			{
				if (Calc( operations, operands ) == false) break;
				continue;
			}
			operations.pop();
			++i;
			continue;
		}
		else
		{
			fprintf( stderr, "Invalid input. Input contains invalid expression: %.*s\n",
				( expression.length() - i - 1 ), ( expression.c_str() + i ) );
			isError = true;
			return result;
		}
	}
	while (!operations.empty())
	{
		if (Calc( operations, operands ) == false) break;
		continue;
	}

	result = operands.top().value;
	isError = false;
	return result;
}

double Calculator::GetResult() const
{
	if (isError)
	{
		fprintf( stderr, "An error occured. Error: Invalid result\n" );
	}
	return result;
}

void Calculator::SetExpression( std::string expr )
{
	std::string e = { ::StringUtil::Trim( expr ) };
	expression = std::move( e );
}

void Calculator::ShowResult() const
{
	if (isError)
	{
		fprintf( stderr, "An error occured. Error: Invalid result\n" );
	}
	printf( "%.2f", result );
}

bool Calculator::ReadStdin()
{
	char buffer[4096] = { 0 };
	printf( "Enter expression to evaluate.\nMax 4095 symbols.\n" );
	if (fgets( buffer, 4095, stdin ) == nullptr)
	{
		fprintf( stderr, "Encountered read error while reading expression\n" );
		return false;
	}

	std::string str = StringUtil::Trim( buffer );
	std::string expr = str;

	expression = std::move( expr );
	return true;
}
