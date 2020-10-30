// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 状态模式

#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

// 状态模式：存在多种状态，用if else逻辑较为繁琐时，可采用状态模式进行管控
// 
// 注意：内存泄露问题

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
	~Work() {
		SAFE_DELETE(state_);
	}

	void setHour(int hour) {
		hour_ = hour;
	}
	int getHour() {
		return hour_;
	}

	void setFinish(bool finish) {
		finish_ = finish;
	}
	int getFinish() {
		return finish_;
	}

	// 此处注意内存泄露
	void setState(State* state) {
		SAFE_DELETE(state_);
		state_ = state;
	}

	void getCurrentState() {
		state_->writeProgram(this);
	}

private:
	int hour_ = 0;
	bool finish_ = false;
	State* state_ = nullptr;
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
	state_ = new FornoonState();
}

int main12()
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

	SAFE_DELETE(work);

	return 0;
}


