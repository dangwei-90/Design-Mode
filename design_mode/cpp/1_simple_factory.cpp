// 此文件包含 "main" 函数。程序执行将在此处开始并结束。

// 参考大话设计模式 - 简单工厂模式

#include <iostream>

using namespace std;

// base
class Operation {
public:
	virtual int GetResult() = 0;

public:
	int _first_num = 0;
	int _second_num = 0;
};

// plus
class PlusOperation :public Operation {
public:
	int GetResult() {
		return _first_num + _second_num;
	}
};

// Sub
class SubOperation :public Operation {
public:
	int GetResult() {
		return _first_num - _second_num;
	}
};

// simple factory
class SimpleFactory {
public:
	static Operation* CreateFactory(char sign);
};

Operation* SimpleFactory::CreateFactory(char sign) {
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


int main1()
{
    std::cout << "Hello Simple Factory!\n";
	int first_num = 0;
	int second_num = 0;
	cin >> first_num >> second_num;
	char sign;
	cin >> sign;
	Operation* op = SimpleFactory::CreateFactory(sign);
	op->_first_num = first_num;
	op->_second_num = second_num;

	cout << op->GetResult() << endl;
  
	return 0;
}
