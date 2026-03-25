#pragma once

#include "Data.h"

void addTask(int userId, string userType);
void showAllTasks();
void showTasksByUser(int userId);
void deleteTask(int taskId, int userId);
void modifyTask(int taskId, int userId);
void checkTaskReminders(int userId);
string currentDate();
void analyzeTaskBySemester(int userId);
void sortTasksByPriority(int userId);