// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

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

class Facade {
public:
	void create() {
		_subsystemone->create();
		_subsystemtwo->create();
		_subsystemthree->create();
		_subsystemfour->create();
	}

	void clear() {
		_subsystemone->clear();
		_subsystemtwo->clear();
		_subsystemthree->clear();
		_subsystemfour->clear();
	}

private:
	subSystemOne* _subsystemone = new subSystemOne();
	subSystemTwo* _subsystemtwo = new subSystemTwo();
	subSystemThree* _subsystemthree = new subSystemThree();
	subSystemFour* _subsystemfour = new subSystemFour();
};

int main8()
{
	Facade* facade = new Facade();
	facade->create();
	facade->clear();

	return 0;
}


