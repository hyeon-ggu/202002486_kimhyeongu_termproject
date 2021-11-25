#pragma once
#include<iostream>

using namespace std;

class NandOp {
protected:
	int value;
	char op;
	string type; // "n" or "op"

public:
	NandOp(string type, int value = 0, char op = 0) : type(type), value(value), op(op) {

	}

	string getType() {
		return this->type;
	}

	char getOp() {
		return this->op;
	}

	int getValue() {
		return this->value;
	}
};