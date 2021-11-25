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
	
	cout << "���� �Դϴ�. ��Ģ����� ��ȣ ����� �����մϴ�." << endl;
	cout << "-------------------------------------------------" << endl;
	cout << endl;

	while (EOF) {
		cout << endl;
		cout << "����� ������ �Է��� �ּ��� : ";
		getline(cin, midfix);

		controller.setMidfix(midfix);
		controller.updateViewAndCalc();
	}
}