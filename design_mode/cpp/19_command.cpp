 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>

using namespace std;

class Receiver {
public:
  void Action() {
    cout << "receive do action." << endl;
  }
};

class Command {
public:
  virtual void SetReceiver(Receiver* receiver) = 0;
  virtual void Execute() = 0;

protected:
  Receiver* receiver_ = nullptr;
};

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

  delete invoker;
  invoker = nullptr;

  delete command;
  command = nullptr;

  delete receiver;
  receiver = nullptr;

	return 0;
}


