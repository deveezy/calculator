#include "calculator.hpp"

namespace
{
#define TokenOperandType -1
#define TokenOperationValue 0
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
	*ch = expression[++(*index)];
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

double Calculator::Evaluate( std::string expression_ )
{
	expression = std::move( expression_ );
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
	}
	while (!operations.empty())
	{
		if (Calc( operations, operands ) == false) break;
		continue;
	}

	result = operands.top().value;
	return result;
	// printf( "%f\n", operands.top().value );
}
