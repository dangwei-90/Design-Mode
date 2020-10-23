 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>
#include <vector>

using namespace std;

class Person;
class Man;
class Women;

class Action {
public:
  virtual void GetManConclusion(Man* man) = 0;
  virtual void GetWomenConlusion(Women* women) = 0;
};

class Person {
public:
  virtual void Accept(Action* action) = 0;
};

class Success : public Action {
public:
  void GetManConclusion(Man* man) {
    cout << "男人成功时，背后...." << endl;
  }

  void GetWomenConlusion(Women* women) {
    cout << "女人成功时，背后...." << endl;
  }
};

class Fail : public Action {
public:
  void GetManConclusion(Man* man) {
    cout << "男人失败时，背后...." << endl;
  }

  void GetWomenConlusion(Women* women) {
    cout << "女人失败时，背后...." << endl;
  }
};

class Amtiveness : public Action {
public:
  void GetManConclusion(Man* man) {
    cout << "男人恋爱时，背后...." << endl;
  }

  void GetWomenConlusion(Women* women) {
    cout << "女人恋爱时，背后...." << endl;
  }
};

class Man :public Person {
public:
  void Accept(Action* action) {
    action->GetManConclusion(this);
  }
};

class Women :public Person {
public:
  void Accept(Action* action) {
    action->GetWomenConlusion(this);
  }
};

int main24()
{
  vector<Person*> person;
  person.push_back(new Man());
  person.push_back(new Women());
  
  Success* success = new Success();
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(success);
  }

  Fail* fail = new Fail();
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(fail);
  }

  Amtiveness* amtiveness = new Amtiveness();
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(amtiveness);
  }
	return 0;
}
