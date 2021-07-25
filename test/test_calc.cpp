#include <gtest/gtest.h>
// #include <calculator.hpp>
#include "../src/calculator.hpp"

TEST(Calc, EvaluateExpression1)
{
	Calculator calc;
	calc.SetExpression("2 + 2 * 2");
	calc.Evaluate();
	ASSERT_EQ(calc.GetResult(), 6);
}

TEST(Calc, EvaluateExpression2)
{
	Calculator calc;
	calc.SetExpression("-1 + 5 - 3");
	calc.Evaluate();
	ASSERT_EQ(calc.GetResult(), 1);
}

TEST(Calc, EvaluateExpression3)
{
	Calculator calc;
	calc.SetExpression("-10 + (8 * 2.5) - (3 / 1,5)");
	calc.Evaluate();
	ASSERT_EQ(calc.GetResult(), 8);
}

TEST(Calc, EvaluateExpression4)
{
	Calculator calc;
	calc.SetExpression("1 + (2 * (2.5 + 2.5 + (3 - 2))) - (3 / 1.5)");
	calc.Evaluate();
	ASSERT_EQ(calc.GetResult(), 11);
}

TEST(Calc, EvaluateExpression5)
{
	Calculator calc;
	calc.SetExpression("-1 - 2 * 3");
	calc.Evaluate();
	ASSERT_EQ(calc.GetResult(), -7);
}