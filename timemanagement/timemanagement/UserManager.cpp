#include "UserManager.h"
#include "FileManager.h"

int login(string type, int id, string password) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].type == type &&
			users[i].id == id &&
			users[i].password == password) {
			return i;
		}
	}
	return -1;
}

void registerUser() {
	User newUser;
	int typeChoice;

	cout << "------------------------" << endl;

	cout << "请选择您的用户类型：" << endl;
	cout << "1. 学生" << endl;
	cout << "2. 教师" << endl;
	cout << "请输入选择（1 或 2）：";
	cin >> typeChoice;

	if (typeChoice == 1) {
		newUser.type = "student";
	}
	else if (typeChoice == 2) {
		newUser.type = "teacher";
	}
	else {
		cout << "无效的选择，注册失败！" << endl;
		return; 
	}

	cout << "请输入用户编号：";
	cin >> newUser.id;

	for (const auto& user : users) {
		if (user.id == newUser.id) {
			cout << "用户编号已存在！" << endl;
			return;
		}
	}

	cout << "请输入密码：";
	cin >> newUser.password;

	cout << "请输入用户名：";
	cin >> newUser.name;

	users.push_back(newUser); 
	cout << "注册成功！" << endl;
	cout << "------------------------" << endl;

	saveUsersToFile();
}

int findUserById(int id) {
	for (int i = 0; i < users.size(); i++) {
		if (users[i].id == id) {
			return i;
		}
	}
	return -1;
}

void showUserInfo(int index) {
	if (index < 0 || index >= users.size()) {
		cout << "用户不存在！" << endl;
		return;
	}

	cout << "用户编号：" << users[index].id << endl;
	cout << "用户名：" << users[index].name << endl;
	cout << "用户类型：" << users[index].type << endl;
}


void showLoginMenu() {
	cout << "------------------------" << endl;
	cout << "欢迎进入时间管理系统！" << endl;
	cout << "------------------------" << endl;
	cout << "请选择登录方式：" << endl;
	cout << "1. 学生登录" << endl;
	cout << "2. 教师登录" << endl;
	cout << "3. 注册账号" << endl;
	cout << "4. 退出" << endl;
	cout << "请输入选择（1/2/3/4）: ";
}

void showStudentMenu(string userName) {
	cout << "------------------------" << endl;
	cout << userName << "的学生菜单" << endl;
	cout << "1. 查看任务" << endl;
	cout << "2. 添加任务" << endl;
	cout << "3. 修改任务" << endl;
	cout << "4. 删除任务" << endl;
	cout << "5. 学期任务分析" << endl;
	cout << "6. 任务排序" << endl;
	cout << "7. 退出菜单" << endl;
	cout << "请输入选择: ";
}

void showTeacherMenu(string userName) {
	cout << "------------------------" << endl;
	cout << userName << "的教师菜单" << endl;
	cout << "1. 查看所有任务" << endl;
	cout << "2. 添加任务" << endl;
	cout << "3. 修改任务" << endl;
	cout << "4. 删除任务" << endl;
	cout << "5. 学期任务分析" << endl;
	cout << "6. 任务排序" << endl;
	cout << "7. 退出菜单" << endl;
	cout << "请输入选择: ";
}