// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 原型模式

// 原型模式，通过默认拷贝构造函数，通过clone接口，new一个新的对象

#include <iostream>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

class Prototype {
public:
	Prototype() {}

	virtual void SetID(string id) = 0;

	virtual string GetID() = 0;

	virtual Prototype* Clone() = 0;

protected:
	string id_ = "";
};

class ConcreatePrototype : Prototype {
public :
	ConcreatePrototype(string id){
		id_ = id;
	}

	void SetID(string id) {
		id_ = id;
	}

	string GetID() {
		return id_;
	}

	Prototype* Clone() {
		// 根据当前对象 拷贝构造一个新对象(浅拷贝)
		return new ConcreatePrototype(*this);

		/*
		ConcreatePrototype* prototype = new ConcreatePrototype("p");
		*prototype = *this;
		return prototype;
		*/
	}
};

int main6()
{
	ConcreatePrototype* p1 = new ConcreatePrototype("p1");
	ConcreatePrototype* p2 = (ConcreatePrototype*)p1->Clone();

	// 此处p2对象的成员变量均为p1对象的成员变量的值
	cout << "p1: " << p1 << endl;
	cout << "p1 id: " << p1->GetID() << endl;
	cout << "p2: " << p2 << endl;
	cout << "p2 id: " << p2->GetID() << endl;

	cout << "--------------------\n";
	// P1和P2各自调用自己的方法
	p1->SetID("p1 set");
	p2->SetID("p2 set");
	cout << "p1 id: " << p1->GetID() << endl;
	cout << "p2 id: " << p2->GetID() << endl;

	SAFE_DELETE(p2)
	SAFE_DELETE(p1)

	return 0;
}


