#include "Data.h"
#include "UserManager.h"
#include "TaskManager.h"
#include "FileManager.h"
#include <iostream>
#include <ctime>

vector<User> users;        //对Data.h里extern的定义
vector<Task> tasks;

int main() {
    loadUsersFromFile();
    loadTasksFromFile();

    cout << "--------系统启动成功--------" << endl;

    int userIndex = -1;
    string userType, userPassword;
    int userId;

    // 主菜单循环，直到用户选择退出
    while (true) {
        // 登录菜单循环
        while (userIndex == -1) {
            showLoginMenu();
            int choice;
            cin >> choice;
            cout << "------------------------" << endl;

            switch (choice) {
            case 1:
                userType = "student";
                break;
            case 2:
                userType = "teacher";
                break;
            case 3:
                registerUser();       // 调用注册函数
                continue;            // 注册后继续循环，允许登录
            case 4:
                cout << "退出系统！" << endl;
                return 0;  // 退出系统
            default:
                cout << "无效选择，请重新输入！" << endl;
                continue;
            }

            cout << "------------------------" << endl;
            cout << "请输入" << userType << "的编号：";
            cin >> userId;
            cout << "请输入密码：";
            cin >> userPassword;

            userIndex = login(userType, userId, userPassword);

            if (userIndex != -1) {
                cout << "登录成功！" << endl;
                break;  // 登录成功，跳出登录菜单，进入相应菜单
            }
            else {
                cout << "用户名或密码错误，请重新登录！" << endl;
            }
        }

        // 获取当前登录用户的姓名
        string userName = users[userIndex].name;

        checkTaskReminders(userId);

        // 学生菜单循环
        if (userType == "student") {
            while (true) {
                showStudentMenu(userName);  
                int studentChoice;
                cin >> studentChoice;

                switch (studentChoice) {
                case 1:
                    showTasksByUser(userId); 
                    break;
                case 2:
                    addTask(userId, userType); 
                    break;
                case 3:
                    int taskId;
                    cout << "请输入要修改的任务编号：";
                    cin >> taskId;
                    modifyTask(taskId, userId); 
                    break;
                case 4:
                    cout << "请输入要删除的任务编号：";
                    cin >> taskId;
                    deleteTask(taskId, userId); 
                    break;
                case 5:
                    cout << "查看学期任务完成情况！" << endl;
                    analyzeTaskBySemester(userId); 
                    break;
                case 6:
                    cout << "查看任务排序情况！" << endl;
                    sortTasksByPriority(userId); 
                    break;
                case 7:
                    cout << "退出学生菜单！" << endl;
                    userIndex = -1; 
                    break;
                default:
                    cout << "无效选择，请重新输入！" << endl;
                    continue;
                }
                if (userIndex == -1) break;  // 如果选择退出，跳出循环，回到主菜单
            }
        }
        // 教师菜单循环
        else if (userType == "teacher") {
            while (true) {
                showTeacherMenu(userName);  
                int teacherChoice;
                cin >> teacherChoice;

                switch (teacherChoice) {
                case 1:
                    showTasksByUser(userId); 
                    break;
                case 2:
                    addTask(userId, userType); 
                    break;
                case 3:
                    int taskId;
                    cout << "请输入要修改的任务编号：";
                    cin >> taskId;
                    modifyTask(taskId, userId); 
                    break;
                case 4:
                    cout << "请输入要删除的任务编号：";
                    cin >> taskId;
                    deleteTask(taskId, userId); 
                    break;
                case 5:
                    cout << "查看学期任务完成情况！" << endl;
                    analyzeTaskBySemester(userId);
                    break;
                case 6:
                    cout << "查看任务排序情况！" << endl;
                    sortTasksByPriority(userId); 
                    break;
                case 7:
                    cout << "退出教师菜单！" << endl;
                    userIndex = -1; 
                    break;
                default:
                    cout << "无效选择，请重新输入！" << endl;
                    continue;
                }
                if (userIndex == -1) break; 
            }
        }

        // 保存数据到文件
        saveUsersToFile();
        saveTasksToFile();
    }

    return 0;
}