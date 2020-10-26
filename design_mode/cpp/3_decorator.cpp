// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 装饰模式

#include <iostream>

using namespace std;

// 装饰模式
// Person 为抽象类接口，譬如人，人分为男人和女人
// Man是Person的实现子类，实现男人
// Finery继承Man，表示男款衣服的统称，包含Man的成员变量对象
// Sneaker是具体的Finery的实现子类，实现了运动鞋，调用man->show

// 人的接口
class PersonDecorator {
public:
	virtual void show() = 0;
};

// 男人的具体实现类
class ManDecorator : PersonDecorator {
public:
	ManDecorator() {}
	ManDecorator(string name) {
		strname_ = name;
	}

	virtual void show() {
		cout << "装扮的" << strname_ << "\n";
	}

private:
	string strname_ = "";
};

// 服饰类，服饰的统称
class Finery : public ManDecorator {
public:
	void decorate(ManDecorator* man) {
		man_ = man;
	}

	void show() {
		man_->show();
	}

protected:
	ManDecorator* man_ = nullptr;
};

// 运动鞋，继承服饰类的具体服饰实现，之后皆同
class Sneaker : public Finery {
public:
	void show() {
		cout << "运动鞋 ";
		man_->show();
	}
};

// 垮裤
class BigTrouser : public Finery {
public:
	void show() {
		cout << "垮裤 ";
		man_->show();
	}
};

// T恤
class TShirt : public Finery {
public:
	void show() {
		cout << " T恤 ";
		man_->show();
	}
};

// 皮鞋
class LeatherShoes : public Finery {
public:
	void show() {
		cout << "皮鞋 ";
		man_->show();
	}
};

// 领带
class Tie : public Finery {
public:
	void show() {
		cout << "领带 ";
		man_->show();
	}
};

// 西装
class Suit : public Finery {
public:
	void show() {
		cout << "西装 ";
		man_->show();
	}
};
int main()
{
	// 具体的人 link
	ManDecorator* man = new ManDecorator("link");

	// 具体的衣服实现
	Sneaker* sneaker = new Sneaker();
	BigTrouser* bigtrouser = new BigTrouser();
	TShirt* tshirt = new TShirt();
	sneaker->decorate(man);
	bigtrouser->decorate(sneaker);
	tshirt->decorate(bigtrouser);

	// 统一展示Link的装饰
	tshirt->show();


	Tie* tie = new Tie();
	LeatherShoes* leathershoe = new LeatherShoes();
	//Sneaker* sneaker = new Sneaker();
	tie->decorate(man);
	leathershoe->decorate(tie);
	sneaker->decorate(leathershoe);
	sneaker->show();

	return 0;
}


