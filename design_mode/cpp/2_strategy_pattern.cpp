// simple_factory.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 策略模式

#include <iostream>

using namespace std;


class CashSuper {
public:
	virtual double acceptCash(double money) = 0;
};


// 正常收费子类
class CashNormal : public CashSuper {
public:
	double acceptCash(double money) {
		return money;
	}
};


// 打折收费子类
class CashRebate : public CashSuper {
public:
	CashRebate(double moneyRebate) {
		_moneyRebate = moneyRebate;
	}

	double acceptCash(double money) {
		return money * _moneyRebate;
	}
private:
	double _moneyRebate = 0;
};


// 返利收费子类
class CashReturn : public CashSuper {
public:
	CashReturn(double total, double ret) {
		_total = total;
		_return = ret;
	}

	double acceptCash(double money) {
		if (money > _total) {
			return money - _return;
		}
		else {
			return money;
		}
	}

private:
	double _total = 0;
	double _return = 0;
};

// strategy
class CashContext {
public:
	CashContext(int ntype) {
		switch (ntype) {
		case 1:
		{
			_cashSuper = new CashNormal();
			break;
		}
		case 2:
		{
			_cashSuper = new CashRebate(0.8);
			break;
		}
		case 3:
		{
			_cashSuper = new CashReturn(500, 300);
			break;
		}
		default:
			break;
		}
	}

	double GetCashResult(double money) {
		return _cashSuper->acceptCash(money);
	}

private:
	CashSuper* _cashSuper = nullptr;
};

int main2()
{
	int ntype = 3;
	CashContext* cashContext = new CashContext(ntype);
	cout << cashContext->GetCashResult(1000) << "\n";

	return 0;
}


