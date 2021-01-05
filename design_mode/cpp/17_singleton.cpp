// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 单例模式

// 只创建一个实例，常见于读取配置文件等。
// 暂不考虑释放问题。代码过于丑陋，较难维护，且意义不大。

#include <iostream>
#include <vector>
#include <mutex>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;


/////////////////////C++ 11///////////////////
class SingletonStatic {
public:
  ~SingletonStatic() {}

  static SingletonStatic* GetInstance() {
    static SingletonStatic* singleton_static = new SingletonStatic();
    return singleton_static;
  }
};
//////////////////////////////////////////////


//////////////////加锁方式实现////////////////
// 加锁，保障线程安全
mutex g_mt_lock;

class Singleton {
public:
  ~Singleton() {
  }

  static Singleton* GetInstance() {
    if (singleton_ == nullptr) {
      g_mt_lock.lock();
      if (singleton_ == nullptr) {
        singleton_ = new Singleton();
      }
      g_mt_lock.unlock();
    }

    return singleton_;
  }

public:
  static Singleton* singleton_;
};
Singleton* Singleton::singleton_ = nullptr;
////////////////////////////////////////////


int main17()
{
  // C++ 11 的 static 特性，实现单例模式
  SingletonStatic* test_a_static = SingletonStatic::GetInstance();
  SingletonStatic* test_b_static = SingletonStatic::GetInstance();
  if (test_a_static == test_b_static) {
    cout << "static same singleton" << endl;
  }
  else {
    cout << "static not same singleton" << endl;
  }

  // 加锁的方式实现单例模式
  Singleton* test_a = Singleton::GetInstance();
  Singleton* test_b = Singleton::GetInstance();
  if (test_a == test_b) {
    cout << "same singleton" << endl;
  }
  else {
    cout << "not same singleton" << endl;
  }


  /* 暂不考虑释放问题。代码过于丑陋，较难维护，且意义不大。
  //delete Singleton::GetInstance();
  delete test_a;
  test_a = nullptr;

  Singleton* test_c = Singleton::GetInstance();
  test_c->testfun();
  test_a->testfun();
  */

  return 0;
}