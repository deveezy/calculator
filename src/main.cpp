// #include <stdio.h>
// #include <stack>
// #include <string>

// #define TokenOperandType -1
// #define TokenOperationValue 0

// double ParseDecimal( const std::string &expression, char *ch, size_t *index )
// {
// 	double number = .0;
// 	*ch = expression[*index];
// 	while (( *ch >= '0' && *ch <= '9' ))
// 	{
// 		number = number * 10 + ( *ch - '0' );
// 		*ch = expression[++( *index )];
// 	}
// 	return number;
// }

// double ParseFraction( const std::string &expression, char *ch, size_t *index )
// {
// 	double number = .0;
// 	*ch = expression[++(*index)];
// 	while (( *ch >= '0' && *ch <= '9' ))
// 	{
// 		number = number * 10 + ( *ch - '0' ) * .1;
// 		*ch = expression[++( *index )];
// 	}
// 	return number;
// }

// using PriorityType = int;

// struct Token
// {
// 	char type;
// 	double value;
// };

// using Operations = std::stack<Token>;
// using Operands = std::stack<Token>;

// // 1 - highest priority
// PriorityType GetPriority( char ch )
// {
// 	if (ch == '+' || ch == '-') return 2;
// 	if (ch == '/' || ch == '*') return 1;
// 	else return 3;
// }

// bool Calc( Operations &operations, Operands &operands )
// {
// 	double op1, op2, opRes;
// 	op1 = operands.top().value;
// 	operands.pop();
// 	op2 = operands.top().value;
// 	operands.pop();
// 	Token token;
// 	switch (operations.top().type)
// 	{
// 		case '+':
// 			opRes = op2 + op1;
// 			token = { TokenOperandType, opRes };
// 			operands.push( token );
// 			operations.pop();
// 			break;
// 		case '-':
// 			opRes = op2 - op1;
// 			token = { TokenOperandType, opRes };
// 			operands.push( token );
// 			operations.pop();
// 			break;
// 		case '/':
// 			if (op1 == 0)
// 			{
// 				fprintf( stderr, "Divide by zero!\n" );
// 				return false;
// 			}
// 			opRes = op2 / op1;
// 			token = { TokenOperandType, opRes };
// 			operands.push( token );
// 			operations.pop();
// 			break;
// 		case '*':
// 			opRes = op2 * op1;
// 			token = { TokenOperandType, opRes };
// 			operands.push( token );
// 			operations.pop();
// 			break;

// 		default:
// 			fprintf( stderr, "Unknown operation!\n" );
// 			return false;
// 	}
// 	return true;
// }

// int main()
// {
// 	// std::string expression = { "-10+(8*2.5)-(3/1.5)\n" };
// 	// std::string expression = { "(2+2)*(2+3)*(-1)\n" };
// 	std::string expression = { "1+(2*(2.5+2.5+(3-2)))-(3/1.5)" };
// 	Operations operations;
// 	Operands operands;
// 	Token token;
// 	bool canBeNegative = true;
// 	bool isMinus = false;
// 	for (size_t i = 0; i < expression.length(); )
// 	{
// 		double number = .0;
// 		char ch = expression[i];
// 		if (ch == '\n') // end of expression
// 			break; // break cycle and process remaining expression

// 		if (( ch >= '0' && ch <= '9' ) || ( ch == '-' && canBeNegative == true ))
// 		{
// 			canBeNegative = false; // Now we'll read opeartion symbol 
// 			isMinus = false;
// 			if (ch == '-')
// 			{
// 				ch = expression[++i];
// 				isMinus = true;
// 			}
// 			number = ParseDecimal( expression, &ch, &i );
// 			double fraction = .0;
// 			if (ch == '.' || ch == ',')
// 			{
// 				fraction = ParseFraction( expression, &ch, &i );
// 			}
// 			number += fraction;
// 			number = isMinus ? -number : number;
// 			token = { TokenOperandType, number };
// 			operands.push( token );
// 			continue;
// 		}
// 		if (ch == '+' || ch == '-' && canBeNegative == 0 || ch == '/' || ch == '*')
// 		{
// 			if (operations.empty())
// 			{
// 				token = { ch, TokenOperandType };
// 				operations.push( token );
// 				++i;
// 				continue;
// 			}
// 			if (!operations.empty())
// 			{
// 				/** if the current type more important */
// 				if (GetPriority( ch ) < GetPriority( operations.top().type ))
// 				{
// 					token = { ch, TokenOperationValue };
// 					operations.push( token );
// 					++i;
// 					continue;
// 				}
// 				else
// 				{
// 					if (Calc( operations, operands ) == false) break;
// 					continue;
// 				}
// 			}
// 		}
// 		if (ch == '(')
// 		{
// 			canBeNegative = true;
// 			token = { ch, TokenOperationValue };
// 			operations.push( token );
// 			++i;
// 			continue;
// 		}
// 		if (ch == ')')
// 		{
// 			while (operations.top().type != '(')
// 			{
// 				if (Calc( operations, operands ) == false) break;
// 				continue;
// 			}
// 			operations.pop();
// 			++i;
// 			continue;
// 		}
// 	}
// 	while (!operations.empty())
// 	{
// 		if (Calc( operations, operands ) == false) break;
// 		continue;
// 	}

// 	printf( "%f\n", operands.top().value );
// 	return 0;
// }