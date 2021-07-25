#include <stack>
#include <string>

class Calculator
{
public:
	bool ReadStdin();
	double Evaluate();
	double GetResult() const;
	void SetExpression( const std::string &expr );
	void ShowResult() const;

public:
	Calculator() = default;
	~Calculator() = default;
	Calculator( const Calculator & ) = delete;
	Calculator &operator=( const Calculator & ) = delete;
	Calculator( Calculator && ) = default;
	Calculator &operator=( Calculator && ) = default;

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
	float  RoundUp(double value);

private:
	std::string expression;
	Operations operations;
	Operands operands;
	double result = .0;
	bool isError = false;
};