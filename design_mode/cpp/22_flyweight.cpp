// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 享元模式

#include <iostream>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 方法接口 抽象类
class Flyweight {
public:
  virtual void Operation(int num) = 0;
};

// 可共用的方法实现
class ConreteFlyweight : public Flyweight {
public:
  void Operation(int num) {
    cout << "flyweight , num: " << num << endl;
  }
};

// 不可共用的方法实现
class UnsharedConreteFlyweight : public Flyweight {
public:
  void Operation(int num) {
    cout << "unshared flyweight , num: " << num << endl;
  }
};

class FlyweightFactory {
public:
  FlyweightFactory() {
    // 写法不好，不易内存管理
    flyweight_.push_back(new ConreteFlyweight());
  }

  ~FlyweightFactory()
  {
    for (auto it = flyweight_.begin(); it != flyweight_.end(); it++)
    {
      SAFE_DELETE(*it);
    }
    flyweight_.clear();
  }

  Flyweight* GetFlyweight() {
    vector<Flyweight*>::iterator p = flyweight_.begin();
    return *p;
  }

private:
  vector<Flyweight*> flyweight_;
};

int main22()
{
  FlyweightFactory* flyweight_factory = new FlyweightFactory();

  Flyweight* concrete_flyweight = flyweight_factory->GetFlyweight();
  concrete_flyweight->Operation(12);

  Flyweight* concrete_flyweight_2 = flyweight_factory->GetFlyweight();
  concrete_flyweight_2->Operation(13);

  UnsharedConreteFlyweight* unshared_concrete_flyweight = new UnsharedConreteFlyweight();
  unshared_concrete_flyweight->Operation(16);

  SAFE_DELETE(unshared_concrete_flyweight);
  SAFE_DELETE(flyweight_factory);

	return 0;
}