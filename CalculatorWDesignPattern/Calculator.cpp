#pragma once
#include<iostream>
#include"Data.cpp"
#include"NandOp.cpp"

class Calculator :public Data{
public:
	Calculator(){}

	Calculator(string midfix) : Data(midfix) {};

	void setMidfix(string midfix) {
		Data::midfix = midfix;
		Data::processData();
	}

	int getErr() {
		return Data::err;
	}

	int calc() {
		stack<NandOp> s;
		list<NandOp> postfix = Data::postfix;

		for (NandOp token : postfix) {
			if (token.getType() == "n") {
				s.push(token);
			}
			else {
				NandOp n2 = s.top();
				s.pop();
				NandOp n1 = s.top();
				s.pop();

				//연산자에 맞는 계산
				char op = token.getOp();
				int result = 0;
				switch (op)
				{
				case '+':
					result = n1.getValue() + n2.getValue();
					break;
				case '-':
					result = n1.getValue() - n2.getValue();
					break;
				case '*':
					result = n1.getValue() * n2.getValue();
					break;
				case '/':
					result = n1.getValue() / n2.getValue();
					break;
				default:
					break;
				}
				NandOp resultObj("n", result);
				s.push(resultObj);
			}
		}

		if (!s.empty()) {
			NandOp result = s.top();
			s.pop();
			if (!s.empty()) {
				cout << "연산자의 갯수나 괄호 쌍이 맞지 않습니다." << endl;
				return NULL; // 오류
			}
			return result.getValue();
		}
	}
};