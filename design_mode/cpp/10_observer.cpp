// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 观察者模式

#include <iostream>
#include <vector> 

// 观察者模式：通过 AddObserver 把对象放进vector中。
//             当有消息通知时，对vector所有的Observer进行通知。常见用于消息通知派发等。

using namespace std;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

class Secretary;

class Observer {
public:
	virtual void Notify() = 0;

protected:
	string name_ = "";
	Secretary* secretary_ = nullptr;
};

// 具体的观察者实现类
class Secretary{
public:
	// 用于添加观察者
	void addObserver(Observer* observer) {
		observers_.push_back(observer);
	}

	// 用于移除观察者
	void removeObserver(Observer* observer) {
		vector<Observer*>::iterator p = observers_.begin();
		while (p != observers_.end())
		{
			if ((*p) == observer) {
				observers_.erase(p);
				break;
			}
			p++;
		}
	}

	// 对所有观察者进行消息派发
	// 可以通过消息返回值进行派发中断。
	void Notify() {
		vector<Observer*>::iterator p = observers_.begin();
		while (p != observers_.end())
		{
			(*p)->Notify();
			p++;
		}
	}

private:
	vector<Observer*> observers_;
};

// 具体的待观察者的实现
class WorkerAObserver : public Observer {
public:
	WorkerAObserver(string name, Secretary* secretary) {
		name_ = name;
		secretary_ = secretary;
	}

	void Notify() {
		cout << "secretary notify:" << name_ << " boss come" << endl;
	}
};

class WorkerBObserver : public Observer {
public:
	WorkerBObserver(string name, Secretary* secretary) {
		name_ = name;
		secretary_ = secretary;
	}

	void Notify() {
		cout << "secretary notify:" << name_ << " boss come" << endl;
	}
};


int main10()
{
	Secretary* secretary = new Secretary();

	WorkerAObserver* workerA = new WorkerAObserver("David", secretary);
	WorkerBObserver* workerB = new WorkerBObserver("Tom", secretary);
	secretary->addObserver(workerA);
	secretary->addObserver(workerB);

	secretary->Notify();

	cout << "remove workerA" << endl;
	secretary->removeObserver(workerA);
	SAFE_DELETE(workerA);

	secretary->Notify();

	SAFE_DELETE(secretary);
  SAFE_DELETE(workerB)

	return 0;
}


