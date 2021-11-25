#include"Calculator.cpp"
#include"View.cpp"
#include"Controller.cpp"
#include<iostream>

using namespace std;



int main(void) {
	string midfix;
	Calculator calculator;
	View view;

	Controller controller(calculator, view);
	
	cout << "계산기 입니다. 사칙연산과 괄호 계산이 가능합니다." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << endl;

	while (EOF) {
		cout << endl;
		cout << "계산할 수식을 입력해 주세요 : ";
		getline(cin, midfix);

		controller.setMidfix(midfix);
		controller.updateViewAndCalc();
	}
}