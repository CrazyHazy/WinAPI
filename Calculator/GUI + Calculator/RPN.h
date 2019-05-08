#pragma once
#include<stack>
#include<vector>
#include<iostream>
#include<string>
#include<execution>

std::vector<std::string> Split(std::string str, char separator)
{
	std::vector<std::string> ans;
	int last = 0;

	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] == separator)
		{
			if (str[last] != separator)
			{
				ans.push_back(str.substr(last, i - last));
			}

			last = i + 1;
		}
	}

	if (last != 0)
	{
		ans.push_back(str.substr(last, str.length() - last));
	}
	else
	{
		ans.push_back(str);
	}

	return ans;
}

int GetPriority(char ch)
{
	switch (ch)
	{
	case '+': return 1; break;
	case '-': return 1; break;
	case 'x': return 2; break;
	case '/': return 2; break;
	case '(': return 3; break;
	case ')': return -1; break;
	default: return 0; break;
	}
}
std::string GetRPN(std::string exp) {

	std::stack<char> stack;
	std::string ans;


	for (unsigned i = 0; i < exp.length(); i++) {
		int p = GetPriority(exp[i]);
		if (p == 0)
		{
			ans += exp[i];
		}
		else if (p == -1)
		{
			while (!stack.empty() && GetPriority(stack.top()) != 3)
			{
				ans.append(" ");
				ans += stack.top();
				stack.pop();
			}

			if (stack.empty())
			{
				throw std::logic_error("not correct");
			}
			else
			{
				stack.pop();
			}
		}
		else if (!stack.empty() && (GetPriority(stack.top()) <= p || GetPriority(stack.top()) == 3))
		{
			stack.push(exp[i]);
		}
		else
		{
			while (!stack.empty() && GetPriority(stack.top()) > p)
			{

				ans.append(" ");
				ans += stack.top();
				stack.pop();
			}
			stack.push(exp[i]);
		}
	}

	while (!stack.empty())
	{
		ans.append(" ");
		ans += stack.top();
		stack.pop();
	}

	return ans;
}

double CountRPN(std::string rpn) {

	std::vector<std::string> v_rpn = Split(rpn, ' ');

	std::stack<double> operands;

	for (unsigned i = 0; i < v_rpn.size(); i++)
	{
		try
		{
			double temp = stod(v_rpn[i]);
			operands.push(temp);
		}
		catch (std::invalid_argument&)
		{
			double op2 = operands.top();
			operands.pop();

			double op1 = operands.top();
			operands.pop();

			//GODDAMN I cant use standard switch/case with strings i'll fix it but not today 

			if (v_rpn[i] == "x") operands.push(op1*op2);
			else if (v_rpn[i] == "/") operands.push(op1 / op2);
			else if (v_rpn[i] == "+") operands.push(op1 + op2);
			else if (v_rpn[i] == "-") operands.push(op1 - op2);
			else throw std::logic_error("not correct");

		}
	}

	return operands.top();
}