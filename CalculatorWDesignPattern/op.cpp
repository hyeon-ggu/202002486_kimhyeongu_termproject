#pragma once

class op {
public:
	int getOpPrec(char op)
	{
		switch (op)
		{
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		case '(':
			return 0;
		case ')':
			return -1;
		default: // 0 ~ 9
			return -2;
		}
	}
};