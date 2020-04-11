// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

// base
class Operation {
public:
	virtual int GetResult() {
		int result = 0;
		return result;
	}

public:
	int first_num_ = 0;
	int second_num_ = 0;
};

// plus
class PlusOperation :public Operation {
public:
	virtual int GetResult() {
		return first_num_ + second_num_;
	}
};

// Sub
class SubOperation :public Operation {
public:
	virtual int GetResult() {
		return first_num_ - second_num_;
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
		op->first_num_ = first_num;
		op->second_num_ = second_num;

		cout << op->GetResult() << endl;
  
		return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
