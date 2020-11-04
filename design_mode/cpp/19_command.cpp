// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 命令模式

#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 接收者 类
class Receiver {
public:
  void Action() {
    cout << "receive do action." << endl;
  }
};

// 命令者 抽象类
class Command {
public:
  virtual void SetReceiver(Receiver* receiver) = 0;
  virtual void Execute() = 0;

protected:
  Receiver* receiver_ = nullptr;
};

// 实现命令者 类
class ConcreteCommand : public Command {
public:
  void SetReceiver(Receiver* receiver) {
    receiver_ = receiver;
  }

  void Execute() {
    if (receiver_) {
      receiver_->Action();
    }
  }
};

// 调用者 类
class Invoker {
public:
  void SetCommand(Command* command) {
    command_ = command;
  }

  void ExecuteCommand() {
    command_->Execute();
  }

private:
  Command* command_ = nullptr;
};


int main19()
{
  Receiver* receiver = new Receiver();
  Command* command = new ConcreteCommand();
  command->SetReceiver(receiver);
  Invoker* invoker = new Invoker();
  invoker->SetCommand(command);

  invoker->ExecuteCommand();

  SAFE_DELETE(invoker);
  SAFE_DELETE(command);
  SAFE_DELETE(receiver);

	return 0;
}


