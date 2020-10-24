// 此文件包含 "main" 函数。程序执行将在此处开始并结束。

// 参考大话设计模式 - 简单工厂模式

#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 实现业务需求的接口
// 包含必要的具有共性的成员函数及成员变量
class Operation {
public:
	virtual int GetResult() = 0;

public:
	void SetNums(int first_num, int second_num) {
		first_num_ = first_num;
		second_num_ = second_num;
	}

protected:
	int first_num_ = 0;
	int second_num_ = 0;
};

// 具体的实现功能的类
// 根据特定标识，进行具体的实现
// Add
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

// 简单工厂类
// 根据具体不同的标识，返回符合该标识的业务对象
class SimpleFactory {
public:
	static Operation* CreateFactory(char sign) {
		Operation* oper_ret = nullptr;
		switch (sign)
		{
		case '+':
			oper_ret = new PlusOperation();
			break;
		case '-':
			oper_ret = new SubOperation();
			break;
		default:
			// do nothing
			break;
		}

		return oper_ret;
	}
};

int main1()
{
	int first_num = 3;
	int second_num = 6;
	char sign = '+';
	Operation* op = SimpleFactory::CreateFactory(sign);
	op->SetNums(first_num, second_num);
	cout << op->GetResult() << endl;
	SAFE_DELETE(op);

	sign = '-';
	op = SimpleFactory::CreateFactory(sign);
	op->SetNums(first_num, second_num);
	cout << op->GetResult() << endl;
	SAFE_DELETE(op);

	return 0;
}
