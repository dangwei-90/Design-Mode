// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 外观模式

#include <iostream>

// 外观模式：对子类中的系列接口，提供各种各种组合的统一接口，用于上层调用

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

class subSystemOne {
public:
	void create() {
		cout << "sub system one create\n";
	}

	void clear() {
		cout << "sub system one clear\n";
	}
};

class subSystemTwo {
public:
	void create() {
		cout << "sub system two create\n";
	}

	void clear() {
		cout << "sub system two clear\n";
	}
};

class subSystemThree {
public:
	void create() {
		cout << "sub system three create\n";
	}

	void clear() {
		cout << "sub system three clear\n";
	}
};

class subSystemFour {
public:
	void create() {
		cout << "sub system four create\n";
	}

	void clear() {
		cout << "sub system four clear\n";
	}
};

// 具体的提供接口的类。
// 客户端只关心调用哪个组合的接口方法，而不需要关心具体的实现
class Facade {
public:
	Facade() {
		subsystemone_ = new subSystemOne();
		subsystemtwo_ = new subSystemTwo();
		subsystemthree_ = new subSystemThree();
		subsystemfour_ = new subSystemFour();
	}

	~Facade() {
		SAFE_DELETE(subsystemone_);
		SAFE_DELETE(subsystemtwo_);
		SAFE_DELETE(subsystemthree_);
		SAFE_DELETE(subsystemfour_);
	};

	void one_and_two_create() {
		subsystemone_->create();
		subsystemtwo_->create();
	}

	void three_and_four_clear() {
		subsystemthree_->clear();
		subsystemfour_->clear();
	}

private:
	subSystemOne* subsystemone_ = nullptr;
	subSystemTwo* subsystemtwo_ = nullptr;
	subSystemThree* subsystemthree_ = nullptr;
	subSystemFour* subsystemfour_ = nullptr;
};

int main()
{
	Facade* facade = new Facade();
	facade->one_and_two_create();
	facade->three_and_four_clear();

	SAFE_DELETE(facade)

	return 0;
}


