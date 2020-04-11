// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

class CGiveGift
{
public:
	virtual void GiveDolls() {}
	virtual void GiveFollows() {}
	virtual void GiveChocolates() {}
};

class SchoolGirl
{
public:
	void setname(string name) {
		_name = name;
	}

	string getname() {
		return _name;
	}

private:
	string _name;
};

class Pursuit : public CGiveGift {
public:
	Pursuit(SchoolGirl* schoolgirl) {
		_schoolgirl = schoolgirl;
	}

	void GiveDolls() {
		cout << "pursuit give dolls to "<< _schoolgirl->getname() << "\n";
	}

	void GiveFollows() {
		cout << "pursuit give follows to " << _schoolgirl->getname() << "\n";
	}

	void GiveChocolates() {
		cout << "pursuit give chocolates to " << _schoolgirl->getname() << "\n";
	}

private:
	SchoolGirl* _schoolgirl;
};

class Proxy : public CGiveGift {
public:
	Proxy(SchoolGirl* schoolgirl) {
		_pursuit = new Pursuit(schoolgirl);
	}
	
	void GiveDolls() {
		_pursuit->GiveDolls();
	}

	void GiveFollows() {
		_pursuit->GiveFollows();
	}

	void GiveChocolates() {
		_pursuit->GiveChocolates();
	}


private:
	Pursuit* _pursuit;
};


int main4()
{
	SchoolGirl* schoolgirl = new SchoolGirl();
	schoolgirl->setname("李娇娇");

	Proxy* proxy = new Proxy(schoolgirl);
	proxy->GiveDolls();
	proxy->GiveFollows();
	proxy->GiveChocolates();

	return 0;
}


