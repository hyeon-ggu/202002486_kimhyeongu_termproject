#include "Calculator.cpp"
#include "View.cpp"

class Controller {
private:
	Calculator calculator;

	View view;

public:
	Controller(Calculator calculator, View view) : calculator(calculator), view(view){}

	void setMidfix(string midfix) {
		this->calculator.setMidfix(midfix);
	}

	void updateViewAndCalc() {
		if (calculator.getErr()) {
			return;
		}
		else {
			view.printResult(calculator.calc());
		}
	}
};