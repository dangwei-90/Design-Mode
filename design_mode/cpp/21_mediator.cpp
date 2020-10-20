 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>
#include <vector>

using namespace std;

class Colleague;

class Mediator {
public:
  virtual void Send(string str, Colleague* colleague) = 0;
};

class Colleague {
public:
  virtual void Notify() = 0;

  void SetMediator(Mediator* mediator) {
    mediator_ = mediator;
  }

protected:
  Mediator* mediator_ = nullptr;
};

class ConcreteColleagueA : public Colleague{
public:
  void SetMediatorA(Mediator* mediator) {
    mediator_ = mediator;
  }

  void Send(string str) {
    mediator_->Send(str, this);
  }

  void Notify() {
    cout << "A get a msg" << endl;
  }
};

class ConcreteColleagueB : public Colleague {
public:
  void SetMediatorB(Mediator* mediator) {
    mediator_ = mediator;
  }

  void Send(string str) {
    mediator_->Send(str, this);
  }

  void Notify() {
    cout << "B get a msg" << endl;
  }
};

class ConcreteMediator : public Mediator {
public:
  void SetColleagueA(ConcreteColleagueA* colleague) {
    colleague_a_ = colleague;
  }

  void SetColleagueB(ConcreteColleagueB* colleague) {
    colleague_b_ = colleague;
  }

  void Send(string str, Colleague* colleague) {
    cout << str << endl;
    if (colleague == colleague_a_) {
      colleague_b_->Notify();
    }
    else {
      colleague_a_->Notify();
    }
  }

private:
  ConcreteColleagueA* colleague_a_ = nullptr;
  ConcreteColleagueB* colleague_b_ = nullptr;
};

int main()
{
  ConcreteMediator* mediator = new ConcreteMediator();

  ConcreteColleagueA* colleague_a = new ConcreteColleagueA();
  ConcreteColleagueB* colleague_b = new ConcreteColleagueB();

  colleague_a->SetMediator(mediator);
  colleague_b->SetMediator(mediator);

  mediator->SetColleagueA(colleague_a);
  mediator->SetColleagueB(colleague_b);

  colleague_a->Send("a , send a msg");
  colleague_b->Send("b , send a msg");

	return 0;
}