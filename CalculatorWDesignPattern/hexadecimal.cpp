#pragma once

#include<iostream>
#include<string>

using namespace std;

class Hexadecimal {
protected:
    int err = 0;

public:
    int getHexErr() {
        return this->err;
    }

	int hexadecimalToDecimal(string n) {
        this->err = 0;
		string num = n;
		int dec_value = 0;
		int base = 1;
		int len = num.length();
		for (int i = len - 1; i >= 0; i--) {
            if (num[i] == ' ')continue;
            int check = ctoi(num[i]);
            if (check == -1) { //err case 6: ��ȿ���� ���� 16���� ����
                cout << "Ʋ�� 16���� �����Դϴ�." << endl;
                this->err = 6;
                break;
            }
            else {
                dec_value += base * ctoi(num[i]);
                base *= 16;
            }
		}

		return dec_value;
	}

    int ctoi(char _cChar) {
        char cChar = _cChar;
        int iConverted = -1;        

        if ('0' <= cChar && cChar <= '9')
        {
            iConverted = cChar - '0';
        }
        else if ('A' <= cChar && cChar <= 'F')
        {                                        
            iConverted = 10 + cChar - 'A';
        }

        return iConverted;
    }
};