 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式

#include <iostream>
#include <vector>

using namespace std;

class Component {
public:
	Component() {}
	Component(string name) {
		name_ = name;
	}

	virtual void Add(Component* component) {};
	virtual void Remove(Component* component) {};
	virtual void Display(int depth) {};

public:
	string name_;
};

class Leaf : public Component {
public:
	Leaf(string name) {
		name_ = name;
	}

	void Add(Component* component) {
		cout << "not have a component" << endl;
	}

	void Remove(Component* component) {
		cout << "not have a component" << endl;
	}

	void Display(int depth) {
		for (int n = 0; n < depth; n++) {
			cout << "-";
		}
		cout << name_ << endl;
	}; 
};

class Composite : public Component {
public:
	Composite(string name) {
		name_ = name;
	}

	void Add(Component* component) {
		component_vector_.push_back(component);
	}

	void Remove(Component* component) {
		component_vector_.emplace_back(component);
	}

	void Display(int depth) {
		for (int n = 0; n < depth; n++) {
			cout << "-";
		}
		cout << name_ << endl;

		for (auto iter = component_vector_.begin(); iter != component_vector_.end(); iter++) {
			(*iter)->Display(depth + 2);
		}
	}

private:
	vector<Component*> component_vector_;
};

int main15()
{
	Composite* root = new Composite("root");
	root->Add(new Leaf("leaf_a"));
	root->Add(new Leaf("leaf_b"));

	Composite* comp_1 = new  Composite("comp_1");
	comp_1->Add(new Leaf("comp1_a"));
	comp_1->Add(new Leaf("comp1_b"));

	root->Add(comp_1);
	
	Composite* comp_2 = new  Composite("comp_2");
	comp_2->Add(new Leaf("comp2_a"));
	comp_2->Add(new Leaf("comp2_b"));

	comp_1->Add(comp_2);

	Composite* comp_3 = new  Composite("comp_3");
	comp_3->Add(new Leaf("comp3_a"));
	comp_3->Add(new Leaf("comp3_b"));

	root->Add(comp_3);

	root->Display(1);

	return 0;
}


