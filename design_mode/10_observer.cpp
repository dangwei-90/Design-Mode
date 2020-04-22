// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 观察者模式

#include <iostream>
#include <vector> 

using namespace std;

class Secretary;

class Observer {
public:
	virtual void Notify() {
	}

private:
	string _name;
	Secretary* _secretary;
};

class Secretary{
public:
	void addObserver(Observer* observer) {
		_observers.push_back(observer);
	}

	void removeObserver(Observer* observer) {
		vector<Observer*>::iterator p = _observers.begin();
		while (p != _observers.end())
		{
			if ((*p) == observer) {
				_observers.erase(p);
				break;
			}
			p++;
		}
	}

	void Notify() {
		vector<Observer*>::iterator p = _observers.begin();
		while (p != _observers.end())
		{
			(*p)->Notify();
			p++;
		}
	}

private:
	vector<Observer*> _observers;
};

class WorkerAObserver : public Observer {
public:
	WorkerAObserver(string name, Secretary* secretary) {
		_name = name;
		_secretary = secretary;
	}

	void Notify() {
		cout << "secretary notify:" << _name << " boss come" << endl;
	}

private:
	string _name;
	Secretary* _secretary;
};

class WorkerBObserver : public Observer {
public:
	WorkerBObserver(string name, Secretary* secretary) {
		_name = name;
		_secretary = secretary;
	}

	void Notify() {
		cout << "secretary notify:" << _name << " boss come" << endl;
	}

private:
	string _name;
	Secretary* _secretary;
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
	secretary->Notify();

	return 0;
}


