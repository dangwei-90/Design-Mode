// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

class Person {
public:
	Person() {}
	Person(string* name) {
		_strname = name;
	}

	virtual void show() {
		cout << "装扮的" << _strname << "\n";
	}

private:
	string _strname = "";
};


// 服饰类
class Finery : public Person{
public:
	virtual void decorate(Person * person) {
		_person = person;
	}

	void show() {
		if (_persion != nullptr) {
			_persion.show();
		}
	}

protected:
	Person* _person;
};

// 运动鞋
class Sneaker : public Finery {
public:
	void show() {
		cout << "运动鞋";
	}
};

// 垮裤
class BigTrouser : public Finery {
public:
	void show() {
		cout << "垮裤";
	}
};

// T恤
class TShirt : public Finery {
public:
	void show() {
		cout << "T恤";
	}
};

// 皮鞋
class LeatherShoes : public Finery {
public:
	void show() {
		cout << "皮鞋";
	}
};

// 领带
class Tie : public Finery {
public:
	void show() {
		cout << "领带";
	}
};

// 西装
class Suit : public Finery {
public:
	void show() {
		cout << "西装";
	}
};
int main()
{
	Person person = new Person("link");

	cout << "first decorator: \n";

	Sneaker* sneaker = new Sneaker();
	BigTrouser* bigtrouser = new BigTrouser();
	TShirt* tshirt = new TShirt();

	sneaker->decorate(person);
	bigtrouser->decorate(sneaker);
	tshirt->decorate(bigtrouser);

	tshirt->show();

	return 0;
}


