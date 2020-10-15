 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

mutex g_mt_lock;

class Singleton {
public:
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

int main()
{
  Singleton* test_a = Singleton::GetInstance();
  Singleton* test_b = Singleton::GetInstance();
  if (test_a == test_b) {
    cout << "same singleton" << endl;
  }

	return 0;
}


