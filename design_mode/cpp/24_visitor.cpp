// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 访问者模式

#include <iostream>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

//#define USE_SHARED_PTR
#define USE_UNIQUE_PTR
//#define USE_NEW_CLASS


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
#if defined (USE_UNIQUE_PTR) || defined(USE_NEW_CLASS)
  virtual void Accept(Action* action) = 0;
#endif

#ifdef USE_SHARED_PTR
  virtual void Accept(std::shared_ptr<Action> action) = 0;
#endif // USE_SHARED_PTR
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
#if defined (USE_UNIQUE_PTR) || defined(USE_NEW_CLASS)
  void Accept(Action* action) {
#endif
#if defined (USE_SHARED_PTR)
  void Accept(std::shared_ptr<Action> action) {
#endif
    action->GetManConclusion(this);
  }
};

class Women :public Person {
public:
#if defined (USE_UNIQUE_PTR) || defined(USE_NEW_CLASS)
  void Accept(Action* action) {
#endif
#if defined (USE_SHARED_PTR)
  void Accept(std::shared_ptr<Action> action) {
#endif
    action->GetWomenConlusion(this);
  }
};

#if defined (USE_UNIQUE_PTR)
// use unique_ptr
void display(vector<std::unique_ptr<Person>>& person, Action* action) {
  for (auto it = person.begin(); it != person.end(); it++) {
    (*it)->Accept(action);
  }
}
#endif

int main24()
{
  // use shared_ptr or unique_ptr instead of new point.

#if defined(USE_NEW_CLASS)
  vector<Person*> person;
  person.push_back(new Man());
  person.push_back(new Women());
#endif

#if defined(USE_SHARED_PTR)
  vector<std::shared_ptr<Person>> person;
  person.push_back(std::shared_ptr<Man>(new Man()));
  person.push_back(std::shared_ptr<Women>(new Women()));
#endif

#if defined(USE_UNIQUE_PTR)
  vector<std::unique_ptr<Person>> person;
  person.push_back(std::unique_ptr<Man>(new Man()));
  person.push_back(std::unique_ptr<Women>(new Women()));
#endif

#if defined(USE_NEW_CLASS)
  Success* success = new Success();
#endif

#if defined(USE_SHARED_PTR)
  std::shared_ptr<Success> success(new Success());
#endif

#if defined(USE_UNIQUE_PTR)
  std::unique_ptr<Success> success(new Success());
  // can also use display.
  // display(person, success.get());
#endif

#if defined(USE_UNIQUE_PTR)
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(success.get());
  }
#endif

#if defined(USE_SHARED_PTR) || defined(USE_NEW_CLASS)
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(success);
  }
#endif

#if defined(USE_NEW_CLASS)
  Fail* fail = new Fail();
#endif

#if defined(USE_SHARED_PTR)
  std::shared_ptr<Fail> fail(new Fail());
#endif

#if defined(USE_UNIQUE_PTR)
  std::unique_ptr<Fail> fail(new Fail());
#endif

#if defined(USE_UNIQUE_PTR)
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(fail.get());
  }
#endif

#if defined(USE_SHARED_PTR) || defined(USE_NEW_CLASS)
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(fail);
  }
#endif

#if defined(USE_NEW_CLASS)
  Amtiveness* amtiveness = new Amtiveness();
#endif

#if defined(USE_SHARED_PTR)
  std::shared_ptr<Amtiveness> amtiveness(new Amtiveness());
#endif

#if defined(USE_UNIQUE_PTR)
  std::unique_ptr<Amtiveness> amtiveness(new Amtiveness());
#endif

#if defined(USE_UNIQUE_PTR)
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(amtiveness.get());
  }
#endif

#if defined(USE_SHARED_PTR) || defined(USE_NEW_CLASS)
  for (auto it = person.begin(); it != person.end(); it++)
  {
    (*it)->Accept(amtiveness);
  }
#endif

#if defined(USE_NEW_CLASS)
  // use shared_ptr. we need not delete vector.
  // delete person
  for (auto it = person.begin(); it != person.end(); it++) {
    SAFE_DELETE(*it);
  }

  SAFE_DELETE(success);
  SAFE_DELETE(fail);
  SAFE_DELETE(amtiveness);
#endif

	return 0;
}
