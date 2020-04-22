// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式- 建造者模式

#include <iostream>

using namespace std;

class buildPerson {
public:
	virtual void createHead() {}
	virtual void createBody() {}
	virtual void createHand() {}
	virtual void createFoot() {}
};

class buildThinPerson: public buildPerson {
public:
	void createHead() {
		cout << "thin head" << endl;
	}
	void createBody() {
		cout << "thin body" << endl;
	}
	void createHand() {
		cout << "thin hand" << endl;
	}
	void createFoot() {
		cout << "thin foot" << endl;
	}
};

class buildFatPerson : public buildPerson {
public:
	void createHead() {
		cout << "fat head" << endl;
	}
	void createBody() {
		cout << "fat body" << endl;
	}
	void createHand() {
		cout << "fat hand" << endl;
	}
	void createFoot() {
		cout << "fat foot" << endl;
	}
};

class buildClass {
public:
	void construct(buildPerson* buildperson) {
		_buildperson = buildperson;
	}

	void constructPerson() {
		_buildperson->createHead();
		_buildperson->createBody();
		_buildperson->createHand();
		_buildperson->createFoot();
	}

private:
	buildPerson* _buildperson = new buildPerson();
};

int main9()
{
	buildClass* buildclass = new buildClass();

	buildThinPerson* buildthinperson = new buildThinPerson();
	buildclass->construct(buildthinperson);
	buildclass->constructPerson();

	buildFatPerson* buildfatperson = new buildFatPerson();
	buildclass->construct(buildfatperson);
	buildclass->constructPerson();

	return 0;
}


