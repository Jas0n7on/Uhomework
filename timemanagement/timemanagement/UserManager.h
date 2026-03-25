#pragma once

#include "Data.h"

int login(string type, int id, string password);
int findUserById(int id);
void showUserInfo(int index);

void showLoginMenu();
void showStudentMenu(string userName);
void showTeacherMenu(string userName);

void registerUser();