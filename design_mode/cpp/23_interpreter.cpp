 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 解释器模式

#include <iostream>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

class Content;

// 解释器接口
class Interpreter {
public:
  virtual void Interpret(Content* content) = 0;
};

class TerminalExpression : public Interpreter {
public:
  void Interpret(Content* content) {
    cout << "终端解释器" << endl;
  }
};

class NontermialExpression :public Interpreter {
public:
  void Interpret(Content* content) {
    cout << "非终端解释器" << endl;
  }
};

class Content {
private:
  string date_ = "";
};

int main()
{
  Content* content = new Content();
  vector<Interpreter*> interpre;
  interpre.push_back(new TerminalExpression());
  interpre.push_back(new NontermialExpression());
  interpre.push_back(new NontermialExpression());
  
  //for (vector<Interpreter*>::iterator i = interpre.begin(); i != interpre.end(); i++) {
  for (auto i = interpre.begin(); i != interpre.end(); i++) {
    (*i)->Interpret(content);
  }

  // delete interpre
  for (auto i = interpre.begin(); i != interpre.end(); i++) {
    SAFE_DELETE(*i);
  }
  interpre.clear();

  SAFE_DELETE(content);

	return 0;
}