// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 模板方法模式

#include <iostream>

using namespace std;

class AbstractClass {
public:
	virtual void doSomething() = 0;

	virtual void doOtherthing() = 0;

public:
	void someDoIt() {
		doSomething();
		doOtherthing();
		cout << "do job" << endl;
	}
};

class aBoy : public AbstractClass {
public:
  void doSomething() {
		cout << "A boy do something and ";
	}

	void doOtherthing() {
		cout << " do otherthing about :";
	}
};

class aGirl : public AbstractClass {
public:
	void doSomething() {
		cout << "A girl do something and ";
	}

	void doOtherthing() {
		cout << "do otherthing about :";
	}
};

int main7()
{
	aBoy* aboy = new aBoy();
	aboy->someDoIt();

	aGirl* agirl = new aGirl();
	agirl->someDoIt();

	return 0;
}


