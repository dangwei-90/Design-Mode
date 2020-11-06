// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 访问者模式

#include <iostream>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

class Person;
class Man;
class Women;

// 接口
class Action {
public:
  virtual void GetManConclusion(Man* man) = 0;
  virtual void GetWomenConlusion(Women* women) = 0;
};

class Person {
public:
  virtual void Accept(std::shared_ptr<Action> action) = 0;
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
  void Accept(std::shared_ptr<Action> action) {
    action->GetManConclusion(this);
  }
};

class Women :public Person {
public:
  void Accept(std::shared_ptr<Action> action) {
    action->GetWomenConlusion(this);
  }
};

// use unique_ptr, not support our demo.
void display(vector<std::unique_ptr<Person>>& person, std::unique_ptr<Action> action) {
  for (auto it = person.begin(); it != person.end(); it++) {
    (*it)->Accept(std::move(action));
  }
}

int main()
{
  // use shared_ptr instead of new point.
  //vector<Person*> person;
  //person.push_back(new Man());
  //person.push_back(new Women());

  vector<std::shared_ptr<Person>> person;
  person.push_back(std::shared_ptr<Man>(new Man()));
  person.push_back(std::shared_ptr<Women>(new Women()));
  
  // Success* success = new Success();
  std::shared_ptr<Success> success(new Success());
  //display(person, std::move(success));

  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(success);
  }

  // Fail* fail = new Fail();
  std::shared_ptr<Fail> fail(new Fail());
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(fail);
  }

  // Amtiveness* amtiveness = new Amtiveness();
  std::shared_ptr<Amtiveness> amtiveness(new Amtiveness());
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(amtiveness);
  }

  // use shared_ptr. we need not delete vector.
  // delete person
  //for (auto it = person.begin(); it != person.end(); it++) {
  //  SAFE_DELETE(*it);
  //}

  // SAFE_DELETE(success);
  // SAFE_DELETE(fail);
  // SAFE_DELETE(amtiveness);

	return 0;
}
