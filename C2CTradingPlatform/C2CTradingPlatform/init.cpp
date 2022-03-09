#include <iostream>
#include <ctime>
#include "admin.h"
#include "user.h"
using namespace std;


void initMenu() {
	cout << "=============================================" << endl;
	cout << "1.用户登录 2.用户注册 3.管理员登录 4.退出程序" << endl;
	cout << "=============================================" << endl << endl;
	cout << "输入操作：";
	int ind;
	cin >> ind;
	while (ind < 1 || ind >4) {
		cout << "请输入一个1~4间整数：";
		cin >> ind;
	}
	switch (ind) {
	case 1: userLogIn(); break;
	case 2: userSignUp(); break;
	case 3: adminLogin(); break;
	case 4: exit(0);
	}
}

void timeNow(char* buf) {
	time_t now = time(0);
	tm* ltm = localtime(&now);
	char yyyy[5], mm[3], dd[3];
	itoa(ltm->tm_year + 1900, yyyy, 10);
	itoa(ltm->tm_mon + 1, mm, 10);
	itoa(ltm->tm_mday, dd, 10);
	sprintf(buf, "%s-%s-%s", yyyy, mm, dd);
}
