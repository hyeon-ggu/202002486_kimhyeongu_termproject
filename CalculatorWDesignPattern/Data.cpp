#pragma once

#include<string>
#include<stack>
#include<list>
#include<cctype>
#include"hexadecimal.cpp"
#include"binary.cpp"
#include"op.cpp"
#include"NandOp.cpp"

using namespace std;

class Data : public Hexadecimal, public binary, public op {
protected:
	string midfix = "";
	string decimaled = "";
	int nLen = 0;
	int err = 0;

public:
	list<NandOp> postfix;

	Data() {}

	Data(string midfix) : midfix(midfix) {}

	void processData() {
		this->decimaled = parsing(midfix);
		this->postfix = convertToPostfix(this->decimaled);
		check_error_afterPostfix();
	}

	string parsing(string midfix) { //오류검사 x 다른 함수에서 구현
		check_error(midfix);
		if (err) {
			return "error";
		}
		string parsed;
		string temp;

		for (int i = 0; i < midfix.size(); i++) {
			char token = midfix.at(i);
			if (token == ' ') continue;
			if (token == '0') {
				this->nLen = 0;
				temp = toDecimal(midfix, i);
				parsed += temp;
				if (this->nLen == 0) continue;
				else {
					i += this->nLen + 1; //1은 뒤에 x or b값
				}
			}
			else {
				parsed += midfix.at(i);
			}
		}

		return parsed;
	}

	string toDecimal(string midfix, int i) { // 그냥 0일 수 도 있고 0b 0x 형식일 수도 있다
		if (i + 1 >= midfix.size() || midfix.at(i + 1) == '+' || midfix.at(i + 1) == '-' || midfix.at(i + 1) == '*' || midfix.at(i + 1) == '/') {
			this->nLen = 0;
			return "0";
		}

		int index = i;
		char next = midfix.at(i + 1);

		//count값 계산
		index += 2;
		this->nLen = 0;
		while (!(index >= midfix.size() || midfix.at(index) == '+' || midfix.at(index) == '-' || midfix.at(index) == '*' || midfix.at(index) == '/' || midfix.at(index) == ')')) {
			this->nLen++;
			index++;
		}

		int result = 0;
		if (midfix.at(i + 1) == 'b') { // binary to decimal
			result = binaryToDecimal(midfix.substr(i + 2, nLen));
		}
		else if (midfix.at(i + 1) == 'x') {
			result = hexadecimalToDecimal(midfix.substr(i + 2, nLen));
		}
		else {
			this->err = 3;
			cout << "유효하지 않은 16이나 2진수 태그 형식입니다." << endl;
		}

		if (getHexErr() || getBinaryErr()) {
			this->err = 6;
		}

		string dec_str = to_string(result);
		return dec_str;

	}

	list<NandOp> convertToPostfix(string decimaled) {
		if (this->err) {
			return this->postfix;
		}
		list<NandOp> postfix;
		stack<char> s;

		for (int i = 0; i < decimaled.length(); i++) {
			char token = decimaled.at(i);
			if (token == 0) {
				break;
			}
			int code = getOpPrec(token);

			if (code == -2) { //숫자
				NandOp obj = cutN(decimaled, i);
				postfix.push_back(obj);
				i += this->nLen - 1;
			}
			else if (code == 2 || code == 1) { // 사칙
				if (s.empty()) {
					s.push(token);
				}
				else {
					if (getOpPrec(s.top()) >= code) {
						NandOp obj("op", 0, token);
						postfix.push_back(obj);
						s.pop();
					}
					s.push(token);
				}
			}
			else if (code == 0) {
				s.push(token);
			}
			else if (code == -1) {
				while (!s.empty()) {
					if (s.top() == '(') {
						s.pop();
						break;
					}
					else {
						NandOp obj("op", 0, s.top());
						postfix.push_back(obj);
						s.pop();
					}
				}
			}
		}

		while (!s.empty()) {
			if (s.top() == '(' || s.top() == ')') continue;
			NandOp obj("op", 0, s.top());
			postfix.push_back(obj);
			s.pop();
		}

		return postfix;
	}

	NandOp cutN(string decimaled, int i) {
		int index = i;
		this->nLen = 0;
		string n = "";
		while (!(index >= decimaled.size() || decimaled.at(index) == '+' || decimaled.at(index) == '-' || decimaled.at(index) == '*' || decimaled.at(index) == '/' || decimaled.at(index) == ')')) {
			this->nLen++;
			n += decimaled.at(index);
			index++;
		}

		NandOp obj("n", stoi(n));
		return obj;
	}

	void check_error(string midfix) {
		this->err = 0;

		// err case 1: div by 0
		for (int i = 0; i < midfix.length(); i++) {
			if (i + 1 < midfix.length() && midfix.at(i) == '/' && midfix.at(i + 1) == '0') {
				cout << "0으로 나눌 수 없습니다." << endl;
				err = 1;
				return;
			}
		}

		// err case 2: unmatched parentheses '(', ')'
		int count = 0;
		for (int i = 0; i < midfix.length(); i++) {
			if (midfix.at(i) == '(') {
				count++;
			}
			else if (midfix.at(i) == ')') {
				count--;
			}
		}
		if (count > 0) {
			cout << "( 괄호가 더 많습니다." << endl;
			err = 2;
		}
		else if (count < 0) {
			cout << ") 괄호가 더 많습니다." << endl;
			err = 2;
		}

		//err case 3: exceptional char
		for (int i = 0; i < midfix.length(); i++) {
			if (midfix.at(i) == ' ') continue;
			if (midfix.at(i) == '(' || midfix.at(i) == ')') {
				continue;
			}
			else if (midfix.at(i) == '+' || midfix.at(i) == '-' || midfix.at(i) == '/' || midfix.at(i) == '*' || midfix.at(i) == 'b' || midfix.at(i) == 'x' || midfix.at(i) == 'A' || midfix.at(i) == 'B' || midfix.at(i) == 'C' || midfix.at(i) == 'D' || midfix.at(i) == 'E' || midfix.at(i) == 'F') {
				continue;
			}
			else if (('0' <= midfix.at(i) && midfix.at(i) <= '9')) {
				continue;
			} else {
				cout << "가능한 연산자, 수 이외의 다른 문자 입력." << endl;
				err = 3;
				break;
			}
		}
	}

	void check_error_afterPostfix() {
		if (this->err) {
			return;
		}
		list<NandOp> a = this->postfix;

		int nCnt = 0;
		int opCnt = 0;
		for (NandOp i : a) {
			if (i.getType() == "op" && (i.getOp() == '+' || i.getOp() == '-' || i.getOp() == '*' || i.getOp() == '/')) {
				opCnt++;
			}
			else if(i.getType() == "n") {
				nCnt++;
			}
		}

		//err case 5: unmatched operand and operator
		if (nCnt == 0 && opCnt == 0) {
			cout << "식을 다시 입력하세요" << endl;
			return;
		}
		if (nCnt <= opCnt) {
			cout << "n:" << nCnt << " op:" << opCnt << endl;
			cout << "연산자와 피연산자의 개수가 맞지 않습니다." << endl;
			this->err = 5;
		}
	}
};
	