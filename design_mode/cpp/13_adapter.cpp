// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 适配器模式

// 适配器模式：作为两个不兼容的接口之间的桥梁

#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 用例一
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
	~Adapter() {
		SAFE_DELETE(adaptee_);
	}

	void Request() {
		adaptee_->SpecialRequest();
	}

private:
	Adaptee* adaptee_ = new Adaptee();
};

// 用例二
class CPlayer {
public:
	CPlayer() {}

	virtual void attack() = 0;

	virtual void stop() = 0;

public:
	string name_ = "";
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

// 适配器模式，用户翻译 ForeignCenter 的方法
class Translator : public CPlayer {
public:
	Translator(string name) {
		foreign_->SetForeignName(name);
	}

	~Translator() {
		SAFE_DELETE(foreign_);
	}

	void attack() {
		foreign_->attack();
	}

	void stop() {
		foreign_->stop();
	}

public:
	ForeignCenter* foreign_ = new ForeignCenter();
};

int main()
{
	// 示例一
	Adapter* adapter = new Adapter();
	adapter->Request();
	SAFE_DELETE(adapter);

	// 示例二
	CPlayer* forward = new CForwards("前锋1号");
	forward->attack();
	forward->stop();
	SAFE_DELETE(forward);

	CPlayer* center = new CCenters("中锋3号");
	center->attack();
	center->stop();
	SAFE_DELETE(center);

	CPlayer* guard = new CGuards("后卫1号");
	guard->attack();
	guard->stop();
	SAFE_DELETE(guard);

	// 通过适配器翻译官，进行翻译，调用对应的方法
	CPlayer* translator = new Translator("姚明");
	translator->attack();
	translator->stop();
	SAFE_DELETE(translator);

	return 0;
}


