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

  void testfun() {
    test_num_++;
    cout << "test object" << endl;
  }

public:
  static Singleton* singleton_;
  int test_num_ = 0;
};

Singleton* Singleton::singleton_ = nullptr;

int main17()
{
  Singleton* test_a = Singleton::GetInstance();
  Singleton* test_b = Singleton::GetInstance();
  if (test_a == test_b) {
    cout << "same singleton" << endl;
  }

  test_a->testfun();

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