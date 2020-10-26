// simple_factory.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 策略模式

#include <iostream>

using namespace std;

// 不同策略的接口
class CashSuper {
public:
	virtual double acceptCash(double money) = 0;
};

// 具体的策略实现子类
// 正常收费
class CashNormal : public CashSuper {
public:
	double acceptCash(double money) {
		return money;
	}
};

// 具体的策略实现子类
// 打折收费
class CashRebate : public CashSuper {
public:
	CashRebate(double moneyRebate) {
		moneyRebate_ = moneyRebate;
	}

	double acceptCash(double money) {
		return money * moneyRebate_;
	}

private:
	double moneyRebate_ = 0;
};

// 具体的策略实现子类
// 返利收费
class CashReturn : public CashSuper {
public:
	CashReturn(double total, double ret) {
		total_ = total;
		return_ = ret;
	}

	double acceptCash(double money) {
		if (money > total_) {
			return money - return_;
		}
		else {
			return money;
		}
	}

private:
	double total_ = 0;
	double return_ = 0;
};

// 根据具体不同的策略，创建不同的对象，包含策略的具体算法
class CashContext {
public:
	CashContext(int ntype) {
		switch (ntype) {
		case 1:
		{
			cashSuper_ = new CashNormal();
			break;
		}
		case 2:
		{
			cashSuper_ = new CashRebate(0.8);
			break;
		}
		case 3:
		{
			cashSuper_ = new CashReturn(500, 300);
			break;
		}
		default:
			break;
		}
	}

	~CashContext() {
		if (cashSuper_ != nullptr) {
			delete cashSuper_;
			cashSuper_ = nullptr;
		}
	}

	double GetCashResult(double money) {
		return cashSuper_->acceptCash(money);
	}

private:
	CashSuper* cashSuper_ = nullptr;
};

int main2()
{
	// 客户端只关心调用策略类型，而不关心策略的具体实现
	int ntype = 3;
	CashContext* cashContext = new CashContext(ntype);
	cout << cashContext->GetCashResult(1000) << "\n";

	delete cashContext;
	cashContext = nullptr;

	ntype = 2;
	cashContext = new CashContext(ntype);
	cout << cashContext->GetCashResult(1000) << "\n";

	delete cashContext;
	cashContext = nullptr;

	return 0;
}


