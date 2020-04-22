// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 参考大话设计模式 - 抽象工厂模式

#include <iostream>

using namespace std;

class User {
public:
	string getName() {
		return _name;
	}
	void setName(string name) {
		_name = name;
	}

	int getId() {
		return _id;
	}

	void setId(int id) {
		_id = id;
	}

private:
	string _name = "";
	int _id = 0;
};

class IUser {
public:
	virtual void insert(User* user) {}
	virtual User* select(int id) {
		return nullptr;
	}
};

class SqlUser :public IUser {
public:
	void insert(User* user) {
		cout << "sql insert user " << user->getName() << endl;
	}

	User* select(int id) {
		cout << "sql select id " << id << "from user table" << endl;
		return nullptr;
	}
};

class AccessUser :public IUser {
public:
	void insert(User* user) {
		cout << "access insert user " << user->getName() << endl;
	}

	User* select(int id) {
		cout << "access select id " << id << "from user table" << endl;
		return nullptr;
	}
};

class Department {
public:
	void setId(int id) {
		_id = id;
	}
	int getId() {
		return _id;
	}
private:
	int _id = 0;
};

class IDepartment {
public:
	virtual void insert(Department* department) {}
	virtual Department* select(int id) {
		return nullptr;
	}
};

class SqlDepartment :public IDepartment {
public:
	void insert(Department* department) {
		cout << "sql insert department " << department->getId() << endl;
	}

	Department* select(int id) {
		cout << "sql select id " << id << "from department table" << endl;
		return nullptr;
	}
};

class AccessDepartment :public IDepartment {
public:
	void insert(Department* department) {
		cout << "access insert department " << department->getId() << endl;
	}

	Department* select(int id) {
		cout << "access select id " << id << "from department table" << endl;
		return nullptr;
	}
};

class IFactory {
public:
	virtual IUser* CreateUser() {
		return nullptr;
	}
	virtual IDepartment* CreateDepartment() {
		return nullptr;
	}
};

class SqlServerFactory : public IFactory{
public:
	IUser* CreateUser() {
		return new SqlUser();
	}
	IDepartment* CreateDepartment() {
		return new SqlDepartment();
	}
};

class AccessFactory : public IFactory {
public:
	IUser* CreateUser() {
		return new AccessUser();
	}
	IDepartment* CreateDepartment() {
		return new AccessDepartment();
	}
};

class ControlDatabase {
public:
	IUser* CreateUser() {
		IUser* iuser = nullptr;
		switch (_dbtype) {
			case 1:
				iuser = new SqlUser();
				break;
			case 2:
				iuser = new AccessUser();
				break;
			default:
				break;
		}
		return iuser;
	}

	IDepartment* CreateDepartmentr() {
		IDepartment* idepartment = nullptr;
		switch (_dbtype) {
		case 1:
			idepartment = new SqlDepartment();
			break;
		case 2:
			idepartment = new AccessDepartment();
			break;
		default:
			break;
		}
		return idepartment;
	}

	void setDbtype(int id) {
		_dbtype = id;
	}
private:
	int _dbtype = 2; // 1 sql 2 access
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
	User* user = new User();
	user->setName("David");
	user->setId(27);
	Department* department = new Department();
	department->setId(297);

	IUser* usercurrent = dbbase->CreateUser();
	IDepartment* departmentcurrent = dbbase->CreateDepartmentr();
	usercurrent->insert(user);
	usercurrent->select(27);
	departmentcurrent->insert(department);
	departmentcurrent->select(297);

	return 0;
}


