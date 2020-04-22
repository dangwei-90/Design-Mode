// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 工厂方法模式

#include <iostream>

using namespace std;

// base
class Operation {
public:
	virtual int GetResult() = 0;

public:
	int first_num_ = 0;
	int second_num_ = 0;
};

// plus
class PlusOperation :public Operation {
public:
	int GetResult() {
		return first_num_ + second_num_;
	}
};

// Sub
class SubOperation :public Operation {
public:
	int GetResult() {
		return first_num_ - second_num_;
	}
};

// Mult
class MultOperation : public Operation {
public:
	int GetResult() {
		return first_num_ * second_num_;
	}
};

// interface
class CFactory {
public:
	virtual Operation* CreateOperation() = 0;
};

class PlusFactory : public CFactory {
public:
	Operation* CreateOperation() {
		return new PlusOperation();
	}
};

class SubFactory : public CFactory {
public:
	Operation* CreateOperation() {
		return new SubOperation();
	}
};

class MultFactory : public CFactory {
public:
	Operation* CreateOperation() {
		return new MultOperation();
	}
};

int main5()
{
	CFactory* factory = new MultFactory();
	Operation* op = factory->CreateOperation();
	op->first_num_ = 5;
	op->second_num_ = 3;
	cout << op->GetResult() << endl;

	return 0;
}
