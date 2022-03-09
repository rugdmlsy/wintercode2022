#include <iostream>
#include <ctime>
#include "admin.h"
#include "user.h"
using namespace std;


void initMenu() {
	cout << "=============================================" << endl;
	cout << "1.�û���¼ 2.�û�ע�� 3.����Ա��¼ 4.�˳�����" << endl;
	cout << "=============================================" << endl << endl;
	cout << "���������";
	int ind;
	cin >> ind;
	while (ind < 1 || ind >4) {
		cout << "������һ��1~4��������";
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
