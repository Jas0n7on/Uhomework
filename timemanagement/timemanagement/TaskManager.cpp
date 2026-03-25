#include"TaskManager.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include <map>
#include <algorithm>
using namespace std;

string currentDate() {
    time_t now = time(0);            // 获取当前时间（自 1970 年 1 月 1 日以来的秒数）
    tm ltm;                          // 创建 tm 类型的对象
    localtime_s(&ltm, &now);          // 使用 localtime_s 获取本地时间

    // 构建日期字符串（格式为 yyyy-MM-dd）
    stringstream date;
    date << 1900 + ltm.tm_year << "-"  // tm_year 是从 1900 年开始的，所以需要加 1900
        << 1 + ltm.tm_mon << "-"      // tm_mon 是从 0 开始的，1 表示 1 月
        << ltm.tm_mday;               // tm_mday 是当前日期（1 到 31）

    return date.str();  // 返回格式为 yyyy-MM-dd 的日期字符串
}

void checkTaskReminders(int userId) {
    string today = currentDate();  // 获取当前日期
    cout << "------------------------" << endl;
    cout << "今天的日期是：" << today << endl;  // 调试输出

    // 遍历所有任务，检查当前用户的任务是否符合提醒规则
    for (auto& task : tasks) {
        // 只对当前用户的未完成任务进行提醒
        if (task.userId == userId && task.status != "done") {
            cout << "检查任务：" << task.title << ", 截止日期：" << task.deadline << endl;  // 调试输出任务信息

            // 检查截止日期是否是今天
            if (task.deadline == today) {
                cout << "提醒：任务 \"" << task.title << "\" 截止日期已到！" << endl;
            }
            // 检查提醒规则
            else if (task.deadline > today) {
                if (task.remindRule == "提前一天") {
                    cout << "提醒：任务 \"" << task.title << "\" 明天截止！" << endl;
                }
                // 可以根据需求添加其他提醒规则，如每周提醒
                else if (task.remindRule == "每周提醒") {
                    cout << "提醒：任务 \"" << task.title << "\" 每周提醒！" << endl;
                }
            }
        }
    }
}

void addTask(int userId, string userType) {
    Task t;
    t.userId = userId;
    t.userType = userType;

    cout << "------------------------" << endl;
    cout << "请输入任务编号：";
    cin >> t.id;
    cin.ignore();  // 清除输入缓冲区

    cout << "请输入任务名称：";
    getline(cin, t.title);

    // 任务类别选择
    cout << "请选择任务类别：" << endl;
    cout << "1. 一次性任务" << endl;
    cout << "2. 日常任务" << endl;
    cout << "3. 长期任务" << endl;
    int categoryChoice;
    cin >> categoryChoice;
    switch (categoryChoice) {
    case 1: t.category = "一次性任务"; break;
    case 2: t.category = "日常任务"; break;
    case 3: t.category = "长期任务"; break;
    default: t.category = "一次性任务"; cout << "无效选择，默认选择 '一次性任务'" << endl; break;
    }

    // 任务状态选择
    cout << "请选择任务状态：" << endl;
    cout << "1. 未完成" << endl;
    cout << "2. 进行中" << endl;
    cout << "3. 已完成" << endl;
    cout << "4. 延期" << endl;
    int statusChoice;
    cin >> statusChoice;
    switch (statusChoice) {
    case 1: t.status = "未完成"; break;
    case 2: t.status = "进行中"; break;
    case 3: t.status = "已完成"; break;
    case 4: t.status = "延期"; break;
    default: t.status = "未完成"; cout << "无效选择，默认选择 '未完成'" << endl; break;
    }

    // 任务优先级选择
    cout << "请选择任务优先级（1 - 低，5 - 高）：" << endl;
    cout << "1. 低" << endl;
    cout << "2. 中" << endl;
    cout << "3. 高" << endl;
    cout << "4. 非常高" << endl;
    cout << "5. 紧急" << endl;
    int priorityChoice;
    cin >> priorityChoice;
    switch (priorityChoice) {
    case 1: t.priority = 1; break;
    case 2: t.priority = 2; break;
    case 3: t.priority = 3; break;
    case 4: t.priority = 4; break;
    case 5: t.priority = 5; break;
    default: t.priority = 3; cout << "无效选择，默认选择 '中'" << endl; break;
    }

    cin.ignore();  // 清除输入缓冲区

    // 任务开始日期
    cout << "请输入开始日期（格式：yyyyMMdd）：";
    getline(cin, t.startDate);

    // 任务截止日期
    cout << "请输入截止日期（格式：yyyyMMdd）：";
    getline(cin, t.deadline);

    // 提醒规则输入
    cout << "请输入提醒规则：(没有则填无)";
    getline(cin, t.remindRule);

    // 学期信息输入
    cout << "请选择学期（1-8）：" << endl;
    cout << "1. 大一上" << endl;
    cout << "2. 大一下" << endl;
    cout << "以此类推" << endl;
    cout << "8. 大四下" << endl;
    int semesterChoice;
    cin >> semesterChoice;
    switch (semesterChoice) {
    case 1: t.semester = "大一上"; break;
    case 2: t.semester = "大一下"; break;
    case 3: t.semester = "大二上"; break;
    case 4: t.semester = "大二下"; break;
    case 5: t.semester = "大三上"; break;
    case 6: t.semester = "大三下"; break;
    case 7: t.semester = "大四上"; break;
    case 8: t.semester = "大四下"; break;
    default: t.semester = "大一上"; cout << "无效选择，默认选择 '大一上'" << endl; break;
    }

    cin.ignore();  // 清除输入缓冲区

    // 备注输入
    cout << "请输入备注：(没有则填无)";
    getline(cin, t.remark);

    // 将任务添加到任务列表
    tasks.push_back(t);
    cout << "任务添加成功！" << endl;
    cout << "------------------------" << endl;
}

void showAllTasks() {
    if (tasks.empty()) {
        cout << "------------------------" << endl;
        cout << "当前没有任务！" << endl;
        cout << "------------------------" << endl;
        return;
    }

    for (int i = 0; i < tasks.size(); i++) {
        cout << "------------------------" << endl;
        cout << "任务编号：" << tasks[i].id << endl;
        cout << "所属用户编号：" << tasks[i].userId << endl;
        cout << "任务名称：" << tasks[i].title << endl;
        cout << "用户类型：" << tasks[i].userType << endl;
        cout << "任务类别：" << tasks[i].category << endl;
        cout << "任务状态：" << tasks[i].status << endl;
        cout << "开始日期：" << tasks[i].startDate << endl;
        cout << "截止日期：" << tasks[i].deadline << endl;
        cout << "优先级：" << tasks[i].priority << endl;
        cout << "提醒规则：" << tasks[i].remindRule << endl;
        cout << "所属学期：" << tasks[i].semester << endl;
        cout << "备注：" << tasks[i].remark << endl;
        cout << "------------------------" << endl;
    }
}

void showTasksByUser(int userId) {
    bool found = false;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].userId == userId) {  // 只显示当前用户的任务
            found = true;
            cout << "------------------------" << endl;
            cout << "任务编号：" << tasks[i].id << endl;
            cout << "任务名称：" << tasks[i].title << endl;
            cout << "任务类别：" << tasks[i].category << endl;
            cout << "任务状态：" << tasks[i].status << endl;
            cout << "开始日期：" << tasks[i].startDate << endl;
            cout << "截止日期：" << tasks[i].deadline << endl;
            cout << "优先级：" << tasks[i].priority << endl;
            cout << "提醒规则：" << tasks[i].remindRule << endl;
            cout << "所属学期：" << tasks[i].semester << endl;
            cout << "备注：" << tasks[i].remark << endl;
            cout << "------------------------" << endl;
        }
    }

    if (!found) {
        cout << "------------------------" << endl;
        cout << "没有找到相关任务！" << endl;
        cout << "------------------------" << endl;
    }
}

void deleteTask(int taskId, int userId) {
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == taskId && tasks[i].userId == userId) {
            tasks.erase(tasks.begin() + i);         //erase()删除第一+i个元素 v自带
            cout << "------------------------" << endl;
            cout << "任务删除成功！" << endl;
            cout << "------------------------" << endl;
            return;
        }
    }
    cout << "------------------------" << endl;
    cout << "未找到该任务，或你无权删除！" << endl;
    cout << "------------------------" << endl;
}

void modifyTask(int taskId, int userId) {
    // 查找任务
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == taskId && tasks[i].userId == userId) {
            Task& t = tasks[i];  // 引用任务，直接修改

            cout << "请输入新的任务名称：";
            cin.ignore();  // 清空缓冲区
            getline(cin, t.title);

            // 任务类别选择
            cout << "请选择任务类别：" << endl;
            cout << "1. 一次性任务" << endl;
            cout << "2. 日常任务" << endl;
            cout << "3. 长期任务" << endl;
            int categoryChoice;
            cin >> categoryChoice;
            switch (categoryChoice) {
            case 1: t.category = "一次性任务"; break;
            case 2: t.category = "日常任务"; break;
            case 3: t.category = "长期任务"; break;
            default: t.category = "一次性任务"; cout << "无效选择，默认选择 '一次性任务'" << endl; break;
            }

            // 任务状态选择
            cout << "请选择任务状态：" << endl;
            cout << "1. 未完成" << endl;
            cout << "2. 进行中" << endl;
            cout << "3. 已完成" << endl;
            cout << "4. 延期" << endl;
            int statusChoice;
            cin >> statusChoice;
            switch (statusChoice) {
            case 1: t.status = "未完成"; break;
            case 2: t.status = "进行中"; break;
            case 3: t.status = "已完成"; break;
            case 4: t.status = "延期"; break;
            default: t.status = "未完成"; cout << "无效选择，默认选择 '未完成'" << endl; break;
            }

            // 任务优先级选择
            cout << "请选择任务优先级（1 - 低，5 - 高）：" << endl;
            cout << "1. 低" << endl;
            cout << "2. 中" << endl;
            cout << "3. 高" << endl;
            cout << "4. 非常高" << endl;
            cout << "5. 紧急" << endl;
            int priorityChoice;
            cin >> priorityChoice;
            switch (priorityChoice) {
            case 1: t.priority = 1; break;
            case 2: t.priority = 2; break;
            case 3: t.priority = 3; break;
            case 4: t.priority = 4; break;
            case 5: t.priority = 5; break;
            default: t.priority = 3; cout << "无效选择，默认选择 '中'" << endl; break;
            }

            cin.ignore();  // 清除输入缓冲区

            // 任务开始日期
            cout << "请输入开始日期（格式：yyyyMMdd）：";
            getline(cin, t.startDate);

            // 任务截止日期
            cout << "请输入截止日期（格式：yyyyMMdd）：";
            getline(cin, t.deadline);

            // 提醒规则输入
            cout << "请输入提醒规则：(没有则填无)";
            getline(cin, t.remindRule);

            // 学期信息输入
            cout << "请选择学期（1-8）：" << endl;
            cout << "1. 大一上" << endl;
            cout << "2. 大一下" << endl;
            cout << "以此类推" << endl;
            cout << "8. 大四下" << endl;
            int semesterChoice;
            cin >> semesterChoice;
            switch (semesterChoice) {
            case 1: t.semester = "大一上"; break;
            case 2: t.semester = "大一下"; break;
            case 3: t.semester = "大二上"; break;
            case 4: t.semester = "大二下"; break;
            case 5: t.semester = "大三上"; break;
            case 6: t.semester = "大三下"; break;
            case 7: t.semester = "大四上"; break;
            case 8: t.semester = "大四下"; break;
            default: t.semester = "大一上"; cout << "无效选择，默认选择 '大一上'" << endl; break;
            }

            cin.ignore();  // 清除输入缓冲区

            // 备注输入
            cout << "请输入备注：(没有则填无)";
            getline(cin, t.remark);

            cout << "任务修改成功！" << endl;
            return;  // 退出函数
            cout << "------------------------" << endl;
        }
    }
    cout << "未找到该任务，或者你没有权限修改该任务！" << endl;
}

void analyzeTaskBySemester(int userId) {
    cout << "------------------------" << endl;
    // 用于存储每个学期的任务统计
    map<string, pair<int, int>> semesterStats;  // 学期 -> (已完成任务数, 未完成任务数)

    // 遍历任务
    for (const auto& task : tasks) {
        if (task.userId == userId && !task.semester.empty()) {  // 只统计当前用户的任务
            // 根据任务的状态进行统计
            if (task.status == "done") {
                semesterStats[task.semester].first++;  // 已完成任务数
            }
            else {
                semesterStats[task.semester].second++; // 未完成任务数
            }
        }
    }

    // 输出每个学期的任务完成情况
    cout << "学期任务完成情况：" << endl;
    for (const auto& entry : semesterStats) {
        cout << entry.first << "学期：" << endl;
        cout << "  已完成任务：" << entry.second.first << endl;
        cout << "  未完成任务：" << entry.second.second << endl;
    }
}

void sortTasksByPriority(int userId) {
    cout << "------------------------" << endl;
    // 过滤出当前用户的任务
    vector<Task> userTasks;
    for (const auto& task : tasks) {
        if (task.userId == userId) {
            userTasks.push_back(task);
        }
    }

    // 根据优先级排序，优先级越高越排前
    sort(userTasks.begin(), userTasks.end(), [](const Task& a, const Task& b) {
        return a.priority > b.priority;  // 降序排列，优先级越高越靠前
        });

    // 输出排序后的任务
    cout << "排序后的任务（按优先级排序）：" << endl;
    for (const auto& task : userTasks) {
        cout << "任务名称：" << task.title << ", 截止日期：" << task.deadline
            << ", 优先级：" << task.priority << endl;
    }
}