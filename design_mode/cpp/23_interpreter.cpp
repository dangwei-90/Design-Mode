 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>
#include <vector>

using namespace std;

class Content;

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
  
  for (vector<Interpreter*>::iterator i = interpre.begin(); i != interpre.end(); i++) {
    (*i)->Interpret(content);
  }

	return 0;
}