#include "FileManager.h"
#include <fstream>
#include <sstream>

void loadUsersFromFile() {
	ifstream fin("users.txt");
	if (!fin.is_open()) {
		cout << "文件无法打开！" << endl;
		return;
	}

	users.clear();        //清除旧数据
	string line;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        User u;
        string temp;
        stringstream ss(line);    //line = "1|张三|student|123456"

        getline(ss, temp, '|');   //从 ss 里读取内容，遇到 | 就停，把前面的内容存进 temp
        u.id = stoi(temp);         //stoi() 把字符1变成int 1
        getline(ss, u.name, '|');
        getline(ss, u.type, '|');
        getline(ss, u.password, '|');

        users.push_back(u);
    }

    fin.close();
}

void loadTasksFromFile() {
    ifstream fin("tasks.txt");
    if (!fin.is_open()) {
        cout << "文件无法打开！" << endl;
        return;
    }

    tasks.clear();
    string line;

    while (getline(fin, line)) {
        if (line.empty()) continue;

        Task t;
        string temp;
        stringstream ss(line);

        getline(ss, temp, '|');
        t.id = stoi(temp);

        getline(ss, temp, '|');
        t.userId = stoi(temp);

        getline(ss, t.title, '|');
        getline(ss, t.userType, '|');
        getline(ss, t.category, '|');
        getline(ss, t.status, '|');
        getline(ss, t.startDate, '|');
        getline(ss, t.deadline, '|');

        getline(ss, temp, '|');
        t.priority = stoi(temp);

        getline(ss, t.remindRule, '|');
        getline(ss, t.semester, '|');
        getline(ss, t.remark, '|');

        tasks.push_back(t);
    }
    fin.close();
}

void saveUsersToFile() {
    ofstream fout("users.txt");                //User u = {1, "张三", "student", "123456"};

    for (int i = 0; i < users.size(); i++) {
        fout << users[i].id << "|"
             << users[i].name << "|"
             << users[i].type << "|"
             << users[i].password << endl;
    }                                          //1|张三|student|123456
    fout.close();
}

void saveTasksToFile() {
    ofstream fout("tasks.txt");

    for (int i = 0; i < tasks.size(); i++) {
        fout << tasks[i].id << "|"
            << tasks[i].userId << "|"
            << tasks[i].title << "|"
            << tasks[i].userType << "|"
            << tasks[i].category << "|"
            << tasks[i].status << "|"
            << tasks[i].startDate << "|"
            << tasks[i].deadline << "|"
            << tasks[i].priority << "|"
            << tasks[i].remindRule << "|"
            << tasks[i].semester << "|"
            << tasks[i].remark << endl;
    }

    fout.close();
}


