#include <stack>
#include <string>

class Calculator
{
public:
	double Evaluate( std::string expression_ );
	double GetResult() const;

public:
	Calculator() = default;
	~Calculator() = default;

private:
	struct Token
	{
		char type;
		double value;
	};

private:
	using Operations = std::stack<Token>;
	using Operands = std::stack<Token>;
	using PriorityType = int;

private:
	PriorityType GetPriority( char ch ) const;
	bool Calc( Operations &operations, Operands &operands );
	double ParseDecimal( char *ch, size_t *index );
	double ParseFraction( char *ch, size_t *index );

private:
	std::string expression;
	Operations operations;
	Operands operands;
	double result = .0;
};