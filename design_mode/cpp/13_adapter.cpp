// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

// demo one
class Target {
public:
	void Request() {
		cout << "normal request" << endl;
	}
};

class Adaptee {
public:
	void SpecialRequest() {
		cout << "special request" << endl;
	}
};

class Adapter : public Target {
public:
	void Request() {
		adaptee->SpecialRequest();
	}

private:
	Adaptee* adaptee = new Adaptee();
};

// demo two
class CPlayer {
public:
	CPlayer() {}

	CPlayer(string name) {
		name_ = name;
	}

	virtual void attack() {};

	virtual void stop() {};

public:
	string name_;
};

class CForwards : public CPlayer {
public:
	CForwards(string name) {
		name_ = name;
	}

	void attack() {
		cout << name_ << ", attack!" << endl;
	}

	void stop() {
		cout << name_ << ", stop!" << endl;
	}
};

class CCenters : public CPlayer {
public:
	CCenters(string name) {
		name_ = name;
	}

	void attack() {
		cout << name_ << ", attack!" << endl;
	}

	void stop() {
		cout << name_ << ", stop!" << endl;
	}
};

class CGuards : public CPlayer {
public:
	CGuards(string name) {
		name_ = name;
	}

	void attack() {
		cout << name_ << ", attack!" << endl;
	}

	void stop() {
		cout << name_ << ", stop!" << endl;
	}
};

class ForeignCenter {
public:
	void SetForeignName(string name) {
		name_ = name;
	}

	void attack() {
		cout << name_ << ", attack!" << endl;
	}

	void stop() {
		cout << name_ << ", stop!" << endl;
	}

public:
	string name_;
};

class Translator : public CPlayer {
public:
	Translator(string name) {
		foreign->SetForeignName(name);
	}

	void attack() {
		foreign->attack();
	}

	void stop() {
		foreign->stop();
	}

public:
	ForeignCenter* foreign = new ForeignCenter();
};

int main()
{
	Adapter* adapter = new Adapter();
	adapter->Request();

	CPlayer* forward = new CForwards("前锋1号");
	forward->attack();
	forward->stop();

	CPlayer* center = new CCenters("中锋3号");
	center->attack();
	center->stop();

	CPlayer* guard = new CGuards("后卫1号");
	guard->attack();
	guard->stop();

	CPlayer* translator = new Translator("姚明");
	translator->attack();
	translator->stop();

	return 0;
}


