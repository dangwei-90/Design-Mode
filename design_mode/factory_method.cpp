// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

// base
class Operation {
public:
	virtual int GetResult() {
		return 0;
	}

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
	virtual Operation* CreateOperation() {
		return nullptr;
	};
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

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
