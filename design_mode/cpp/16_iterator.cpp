 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 迭代器模式

// 类似C++已经实现的迭代器

#include <iostream>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 迭代器接口
class Iterator {
public:
  virtual string First() = 0;
  virtual string Next() = 0;
  virtual bool IsEnd() = 0;
  virtual string GetCurrent() = 0;
};

// 操作一组数据的接口
class Aggregate {
public:
  virtual void Push(const string& str) = 0;
  virtual string Pop(size_t index) = 0;
  virtual size_t Count() = 0;
  virtual Iterator* CreateIterator() = 0;
};

// 迭代器接口的具体实现
// 调用数据接口，进行数据的操作
class ConcreteIterator : public Iterator {
public:
  ConcreteIterator(Aggregate* aggregate) {
    aggregate_ = aggregate;
  }

  string First() {
    return aggregate_->Pop(0);
  }

  string Next() {
    if (current_ + 1 < aggregate_->Count()) {
      current_++;
      return aggregate_->Pop(current_);
    }
    else {
      return "";
    }
  }

  bool IsEnd() {
    if (current_ + 1 == aggregate_->Count()) {
      return true;
    }
    else {
      return false;
    }
  }

  string GetCurrent() {
    return aggregate_->Pop(current_);
  }

private:
  Aggregate* aggregate_ = nullptr;
  size_t current_ = 0;
};

// 数据的具体实现
class ConcreteAggregate : public Aggregate {
public:
  ConcreteAggregate() {}
  ~ConcreteAggregate () {
    SAFE_DELETE(iterator_);
  }

  void Push(const string& str) {
    vec_str_.push_back(str);
  }
  
  string Pop(size_t index) {
    return vec_str_[index];
  }

  size_t Count() {
    return vec_str_.size();
  }

  Iterator* CreateIterator() {
    if (iterator_ == nullptr) {
      iterator_ = new ConcreteIterator(this);
    }
    return iterator_;
  }

private:
  vector<string> vec_str_;
  Iterator* iterator_ = nullptr;
};

int main16()
{
  // ConcreteAggregate成员变量vector进行处理。 
  // 该类CreateIterator方法实现了调用迭代器接口，并将将this传给迭代器。
  ConcreteAggregate* concrete_aggregate = new ConcreteAggregate();
  concrete_aggregate->Push("a");
  concrete_aggregate->Push("b");
  concrete_aggregate->Push("c");
  concrete_aggregate->Push("d");

  Iterator* iterator = concrete_aggregate->CreateIterator();

  cout << iterator->First() << endl;
  while (!iterator->IsEnd()) {
    cout << iterator->Next() << endl;
  }

  SAFE_DELETE(concrete_aggregate);

	return 0;
}


