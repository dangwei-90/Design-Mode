// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

class Work;
class FornoonState;

class State {
public:
	virtual void writeProgram(Work* work) = 0;
};

class Work {
public:
	Work();

	void setHour(int hour) {
		_hour = hour;
	}
	int getHour() {
		return _hour;
	}

	void setFinish(bool finish) {
		_finish = finish;
	}
	int getFinish() {
		return _finish;
	}

	void setState(State* state) {
		_state = state;
	}

	void getCurrentState() {
		_state->writeProgram(this);
	}

private:
	int _hour = 0;
	bool _finish = false;
	State* _state = nullptr;
};

class SleeptimeState : public State {
public:
	void writeProgram(Work* work) {
		cout << "time: " << work->getHour() << ", can not work ,need sleep" << endl;
	}
};

class GohomeState : public State {
public:
	void writeProgram(Work* work) {
		work->setFinish(true);
	}
};

class NigthtimeState : public State {
public:
	void writeProgram(Work* work) {
		if (work->getFinish()) {
			cout << "time: " << work->getHour() << ", work done, go home" << endl;
			work->setState(new GohomeState());
		}
		else {
			if (work->getHour() < 21) {
				cout << "time: " << work->getHour() << ", work very tired." << endl;
			}
			else {
				work->setState(new SleeptimeState());
				work->getCurrentState();
			}
		}
	}
};

class AfternoonState : public State {
public:
	void writeProgram(Work* work) {
		if (work->getHour() < 19) {
			cout << "time: " << work->getHour() << ", work tired." << endl;
		}
		else {
			work->setState(new NigthtimeState());
			work->getCurrentState();
		}
	}
};

class NoontimeState : public State {
public:
	void writeProgram(Work* work) {
		if (work->getHour() < 14) {
			cout << "time: " << work->getHour() << ", work hungry." << endl;
		}
		else {
			work->setState(new AfternoonState());
			work->getCurrentState();
		}
	}
};

class FornoonState : public State {
public:
	void writeProgram(Work* work) {
		if (work->getHour() < 12) {
			cout << "time: " << work->getHour() << ", work wonderful." << endl;
		} else {
			work->setState(new NoontimeState());
			work->getCurrentState();
		}
	}
};

Work::Work() {
	_state = new FornoonState();
}

int main()
{
	Work* work = new Work();

	work->setHour(8);
	work->getCurrentState();

	work->setHour(9);
	work->getCurrentState();

	work->setHour(12);
	work->getCurrentState();

	work->setHour(15);
	work->getCurrentState();

	work->setHour(17);
	work->getCurrentState();

	work->setHour(19);
	work->getCurrentState();

	work->setFinish(true);
	work->getCurrentState();

	work->setHour(21);
	work->getCurrentState();

	return 0;
}


