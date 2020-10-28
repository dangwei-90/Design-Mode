// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 工厂方法模式

// 各种工厂模式的区别：
// 简单工厂模式 ：由客户端通知，工厂创建具体产品的对象
// 工厂模式     ：由客户端选择创建具体产品的对象
// 抽象工厂模式 ：客户端不需要关心不同工厂的具体实现，只需要调用工厂提供的接口即可。

#include <iostream>

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

// 抽象类，功能的接口
class Operation {
public:
	virtual int GetResult() = 0;

public:
	int first_num_ = 0;
	int second_num_ = 0;
};

// 抽象类的具体实现：加法功能
class PlusOperation :public Operation {
public:
	int GetResult() {
		return first_num_ + second_num_;
	}
};

// 抽象类的具体实现：减法功能
class SubOperation :public Operation {
public:
	int GetResult() {
		return first_num_ - second_num_;
	}
};

// 抽象类的具体实现：乘法功能
class MultOperation : public Operation {
public:
	int GetResult() {
		return first_num_ * second_num_;
	}
};

// 工厂抽象类，创建具体功能对象的接口
class CFactory {
public:
	virtual Operation* CreateOperation() = 0;
};

// 工厂类的具体实现，创建加法功能类的对象
class PlusFactory : public CFactory {
public:
	Operation* CreateOperation() {
		return new PlusOperation();
	}
};

// 工厂类的具体实现，创建减法功能类的对象
class SubFactory : public CFactory {
public:
	Operation* CreateOperation() {
		return new SubOperation();
	}
};

// 工厂类的具体实现，创建乘法功能类的对象
class MultFactory : public CFactory {
public:
	Operation* CreateOperation() {
		return new MultOperation();
	}
};

int main5()
{
	// 由客户端决定，创建具体功能的工厂
	CFactory* factory = new MultFactory();
  // 根据具体的工厂，创建具体的功能类
	Operation* op = factory->CreateOperation();
	op->first_num_ = 5;
	op->second_num_ = 3;
	cout << op->GetResult() << endl;

	SAFE_DELETE(op)
	SAFE_DELETE(factory)

	return 0;
}
