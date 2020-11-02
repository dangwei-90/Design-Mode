 // 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 组合模式

#include <iostream>
#include <vector>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

class Component {
public:
	Component() {}
	Component(string name) {
		name_ = name;
	}

	virtual void Add(Component* component) = 0;
	virtual void Remove(Component* component) = 0;
	virtual void Display(int depth) = 0;

public:
	string name_ = "";
};

// 叶子结点
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

// 结点
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

	// 遍历该结点，以及该结点拥有的子节点
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
	// 根节点及两个叶子结点
	Composite* root = new Composite("root");
	root->Add(new Leaf("leaf_a"));
	root->Add(new Leaf("leaf_b"));

	// 子结点一，及两个叶子结点
	Composite* comp_1 = new  Composite("comp_1");
	comp_1->Add(new Leaf("comp1_a"));
	comp_1->Add(new Leaf("comp1_b"));

	// 子结点一挂在根节点上
	root->Add(comp_1);
	
	// 子结点二，及两个叶子结点
	Composite* comp_2 = new  Composite("comp_2");
	comp_2->Add(new Leaf("comp2_a"));
	comp_2->Add(new Leaf("comp2_b"));

	// 子结点二挂在子结点一上
	comp_1->Add(comp_2);

	// 子结点三，及两个叶子结点
	Composite* comp_3 = new  Composite("comp_3");
	comp_3->Add(new Leaf("comp3_a"));
	comp_3->Add(new Leaf("comp3_b"));

	// 子结点三挂在根节点上
	root->Add(comp_3);

	// 从根节点开始遍历
	root->Display(1);

	SAFE_DELETE(comp_3);
	SAFE_DELETE(comp_2);
	SAFE_DELETE(comp_1);
	SAFE_DELETE(root);

	return 0;
}