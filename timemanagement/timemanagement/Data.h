
#ifndef DATA_H                    //头文件保护，防止头文件重复包含
#define DATA_H                    //一般第一行会默认生成#pragma once 效果一样

#include <iostream>
#include <vector>                //动态数组
#include <string>
using namespace std;

struct User {
    int id;
    string name;
    string type;                //student or teacher
    string password;
};

struct Task {
    int id;
    int userId;
    string title;
    string userType;
    string category;      
    string status;        
    string startDate;
    string deadline;
    int priority;
    string remindRule;
    string semester;
    string remark;
};

extern vector<User> users;     //全局容器声明
extern vector<Task> tasks;

#endif