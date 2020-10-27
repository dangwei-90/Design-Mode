// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 模板方法模式

#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 基类：提供按照某个流程的具体实现方法。
//       流程内的具体步骤，由子类可定制。
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

// 子类仅实现自己定制的具体步骤。步骤组合后的流程，由基类实现。
class aBoy : public AbstractClass {
public:
  void doSomething() {
		cout << "A boy do something and ";
	}

	void doOtherthing() {
		cout << " do otherthing about :";
	}
};

// 子类仅实现自己定制的具体步骤。步骤组合后的流程，由基类实现。
class aGirl : public AbstractClass {
public:
	void doSomething() {
		cout << "A girl do something and ";
	}

	void doOtherthing() {
		cout << "do otherthing about :";
	}
};

int main()
{
	aBoy* aboy = new aBoy();
	aboy->someDoIt();
	SAFE_DELETE(aboy);

	aGirl* agirl = new aGirl();
	agirl->someDoIt();
	SAFE_DELETE(agirl);

	return 0;
}


