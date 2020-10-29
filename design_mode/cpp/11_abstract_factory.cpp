// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 抽象工厂模式

// 各种工厂模式的区别：
// 简单工厂模式 ：由客户端通知，工厂创建具体产品的对象
// 工厂模式     ：由客户端选择创建具体产品的对象
// 抽象工厂模式 ：客户端不需要关心不同工厂的具体实现，只需要调用工厂提供的接口即可。

#include <iostream>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p){delete(p); (p)=NULL;} }
#endif

using namespace std;

// 具体的用户信息类
class User {
public:
	string getname() {
		return name_;
	}
	void setname(string name) {
		name_ = name;
	}

	int getid() {
		return id_;
	}

	void setid(int id) {
		id_ = id;
	}

private:
	string name_ = "";
	int id_ = 0;
};

// 操作用户信息的抽象类，作为接口
class IOperateUserDB {
public:
	virtual void insert(User* user) = 0;
	virtual User* select(int id) = 0;
};

// 操作用户信息的具体实现类
class SqlOperateUserDB :public IOperateUserDB {
public:
	void insert(User* user) {
		cout << "sql insert user " << user->getname() << endl;
	}

	User* select(int id) {
		cout << "sql select id " << id << "from user table" << endl;
		return nullptr;
	}
};

// 操作用户信息的具体实现类
class AccessOperateUserDB :public IOperateUserDB {
public:
	void insert(User* user) {
		cout << "access insert user " << user->getname() << endl;
	}

	User* select(int id) {
		cout << "access select id " << id << "from user table" << endl;
		return nullptr;
	}
};

// 具体的部门信息类
class Department {
public:
	void setid(int id) {
		id_ = id;
	}
	int getid() {
		return id_;
	}
private:
	int id_ = 0;
};

// 操作部门信息的抽象类，作为接口
class IOperatePartDB {
public:
	virtual void insert(Department* department) = 0;
	virtual Department* select(int id) = 0;
};

// 操作部门信息的具体实现类
class SqlOperatePartDB :public IOperatePartDB {
public:
	void insert(Department* department) {
		cout << "sql insert department " << department->getid() << endl;
	}

	Department* select(int id) {
		cout << "sql select id " << id << "from department table" << endl;
		return nullptr;
	}
};

// 操作部门信息的具体实现类
class AccessOperatePartDB :public IOperatePartDB {
public:
	void insert(Department* department) {
		cout << "access insert department " << department->getid() << endl;
	}

	Department* select(int id) {
		cout << "access select id " << id << "from department table" << endl;
		return nullptr;
	}
};

/*
// 工厂抽象接口
class IFactory {
public:
	virtual IOperateUserDB* CreateUser() {
		return nullptr;
	}
	virtual IOperatePartDB* CreateDepartment() {
		return nullptr;
	}
};

// 具体的工厂实现类，实现了创建操作用户/部门对象的方法
class SqlServerFactory : public IFactory{
public:
	IOperateUserDB* CreateUser() {
		return new SqlOperateUserDB();
	}
	IOperatePartDB* CreateDepartment() {
		return new SqlOperatePartDB();
	}
};

// 具体的工厂实现类，实现了创建操作用户/部门对象的方法
class AccessFactory : public IFactory {
public:
	IOperateUserDB* CreateUser() {
		return new AccessOperateUserDB();
	}
	IOperatePartDB* CreateDepartment() {
		return new AccessOperatePartDB();
	}
};
*/

// 根据配置创建不同的操作用户/部门的对象
class ControlDatabase {
public:
	IOperateUserDB* CreateUser() {
		IOperateUserDB* opera_user = nullptr;
		switch (dbtype_) {
			case 1:
				opera_user = new SqlOperateUserDB();
				break;
			case 2:
				opera_user = new AccessOperateUserDB();
				break;
			default:
				break;
		}
		return opera_user;
	}

	IOperatePartDB* CreateDepartmentr() {
		IOperatePartDB* idepartment = nullptr;
		switch (dbtype_) {
		case 1:
			idepartment = new SqlOperatePartDB();
			break;
		case 2:
			idepartment = new AccessOperatePartDB();
			break;
		default:
			break;
		}
		return idepartment;
	}

	void setDbtype(int id) {
		dbtype_ = id;
	}
private:
	int dbtype_ = 2; // 1 sql 2 access
};

int main11()
{
	/*
	IFactory* ifactory = new SqlServerFactory();
	//IFactory* ifactory = new AccessFactory();

	User* user = new User();
	user->setName("David");
	user->setId(27);
	Department* department = new Department();
	department->setId(297);

	IUser* usercurrent = ifactory->CreateUser();
	usercurrent->insert(user);
	usercurrent->select(27);
	IDepartment* departmentcurrent = ifactory->CreateDepartment();
	departmentcurrent->insert(department);
	departmentcurrent->select(297);
	*/

	ControlDatabase* dbbase = new ControlDatabase();
	dbbase->setDbtype(2);

	User* user = new User();
	user->setname("David");
	user->setid(27);
	Department* department = new Department();
	department->setid(297);

	// 用户和部门，不需要关心具体的数据库操作类的实现，只需要调用接口即可
	IOperateUserDB* usercurrent = dbbase->CreateUser();
	IOperatePartDB* departmentcurrent = dbbase->CreateDepartmentr();
	usercurrent->insert(user);
	usercurrent->select(27);
	departmentcurrent->insert(department);
	departmentcurrent->select(297);

	SAFE_DELETE(usercurrent);
	SAFE_DELETE(departmentcurrent);

	SAFE_DELETE(department);
	SAFE_DELETE(user);

	SAFE_DELETE(dbbase);

	return 0;
}