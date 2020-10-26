// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 代理模式

#include <iostream>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif


// 代理模式
// 抽象类，包含功能接口
// 实现类，继承抽象类，并实现功能
// 代理类，集成抽象类，定义实现类的成员变量，通过实现类的对象，来调用具体实现功能的函数


// 该类仅为满足用例，可不存在
class SchoolGirl
{
public:
	void setname(string name) {
		name_ = name;
	}

	string getname() {
		return name_;
	}

private:
	string name_;
};

// 礼物接口
class CGiveGift
{
public:
	virtual void GiveDolls() = 0;
	virtual void GiveFollows() = 0;
	virtual void GiveChocolates() = 0;
};

// 追求者类，具体实现了礼物接口
class Pursuit : public CGiveGift {
public:
	Pursuit(SchoolGirl* schoolgirl) {
		schoolgirl_ = schoolgirl;
	}

	void GiveDolls() {
		if (schoolgirl_) {
			cout << "pursuit give dolls to " << schoolgirl_->getname() << "\n";
		}
	}

	void GiveFollows() {
		if (schoolgirl_) {
			cout << "pursuit give follows to " << schoolgirl_->getname() << "\n";
		}
	}

	void GiveChocolates() {
		if (schoolgirl_) {
			cout << "pursuit give chocolates to " << schoolgirl_->getname() << "\n";
		}
	}

private:
	SchoolGirl* schoolgirl_ = nullptr;
};

// 代理类，内部定义具体实现类的对象，在继承的函数中调用
class Proxy : public CGiveGift {
public:
	Proxy(SchoolGirl* schoolgirl) {
		pursuit_ = new Pursuit(schoolgirl);
	}

	~Proxy() {
		SAFE_DELETE(pursuit_);
	}
	
	void GiveDolls() {
		if (pursuit_) {
			pursuit_->GiveDolls();
		}
	}

	void GiveFollows() {
		if (pursuit_) {
			pursuit_->GiveFollows();
		}
	}

	void GiveChocolates() {
		if (pursuit_) {
			pursuit_->GiveChocolates();
		}
	}


private:
	Pursuit* pursuit_ = nullptr;
};


int main()
{
	SchoolGirl* schoolgirl = new SchoolGirl();
	schoolgirl->setname("李娇娇");

	// 代理对象
	Proxy* proxy = new Proxy(schoolgirl);
	// 代理对象中调用具体实现类的对象的实现方法
	proxy->GiveDolls();
	proxy->GiveFollows();
	proxy->GiveChocolates();

	SAFE_DELETE(proxy)
	SAFE_DELETE(schoolgirl)

	return 0;
}


