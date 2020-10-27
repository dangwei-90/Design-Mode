// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式- 建造者模式

#include <iostream>

// 建造者模式：通过统一的规范的抽象类，子类集成后实现不同的功能。
//             所以子类都必须满足基类的纯虚函数方法。

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

// 抽象基类，包括多个子类必须实现的方法
class buildPerson {
public:
	virtual void createHead() = 0;
	virtual void createBody() = 0;
	virtual void createHand() = 0;
	virtual void createFoot() = 0;
};

// 具体的实现类
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

// 建造者类，负责根据不同的对象，调用不同的已规范好的实现
class buildClass {
public:
	void construct(buildPerson* buildperson) {
		buildperson_ = buildperson;
	}

	void constructPerson() {
		if (buildperson_) {
			buildperson_->createHead();
			buildperson_->createBody();
			buildperson_->createHand();
			buildperson_->createFoot();
		}
	}

private:
	buildPerson* buildperson_ = nullptr;
};

int main9()
{
	// 建造者对象
	buildClass* buildclass = new buildClass();

	// 具体的person对象，传入建造者，由建造者调用已规范好的方法。
	buildThinPerson* buildthinperson = new buildThinPerson();
	buildclass->construct(buildthinperson);
	buildclass->constructPerson();

	SAFE_DELETE(buildthinperson);

	buildFatPerson* buildfatperson = new buildFatPerson();
	buildclass->construct(buildfatperson);
	buildclass->constructPerson();

	SAFE_DELETE(buildfatperson);
	SAFE_DELETE(buildclass);

	return 0;
}


