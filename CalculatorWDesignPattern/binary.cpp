#pragma once
#include<iostream>

using namespace std;

class binary {
protected:
	int err = 0;

public:
	int binaryToDecimal(string n) {
		this->err = 0;
		string num = n;
		int dec_value = 0;
		int base = 1;
		int len = num.length();
		for (int i = len - 1; i >= 0; i--) {
			if (num[i] == ' ')continue;
			if (!(num[i] == '1' || num[i] == '0')) { // err case 6: ��ȿ���� ���� 2���� ����
				err = 6;
				cout << "��ȿ���� ���� 2���� �����Դϴ�." << endl;
				break;
			}
			if (num[i] == '1')
				dec_value += base;
			base *= 2;
		}

		return dec_value;
	}

	int getBinaryErr() {
		return this->err;
	}
};