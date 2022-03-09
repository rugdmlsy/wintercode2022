#define ADMINNAME "admin"
#define ADMINPSW "123456"
#include <iostream>
#include "init.h"
#include <cstdio>
#include <string>
#include "user.h"
#pragma warning(disable:4996)
using namespace std;

void adminMenu();

void adminLogin() {
	string adminName, adminPSW;
	cout << "请输入管理员姓名：";
	cin >> adminName;
	cout << "请输入密码：";
	cin >> adminPSW;
	cout << endl;
	if (adminName != ADMINNAME || adminPSW != ADMINPSW) {
		cout << "****** 登录失败！即将返回主菜单... ******" << endl << endl;
		return initMenu();
	}
	cout << "****** 登录成功！ ******" << endl << endl;
	return adminMenu();
}

void adminMenu() {
	while (1) {
		cout << "=====================================================================================" << endl;
		cout << "1.查看所有商品 2.搜索商品 3.查看所有订单 4.查看所有用户 5.删除用户 6.下架商品 7.注销" << endl;
		cout << "=====================================================================================" << endl;
		cout << endl;
		cout << "请输入操作：";
		int ind;
		cin >> ind;
		while (ind < 1 || ind >7) {
			cout << "请输入一个1~7间整数：";
			cin >> ind;
		}
		switch (ind) {
		case 1: 
			listAllItems(); break;
		case 2: 
			adminFindItems(); break;
		case 3: 
			listAllOrders(); break;
		case 4: 
			listAllUsers(); break;
		case 5:
			deleteUser(); break;
		case 6: 
			removeItem(); break;
		case 7:
			cout << "注销中..." << endl << endl;
			return initMenu();
		}
	};
}

void deleteUser() {
	cout << "请输入想要删除的用户ID：";
	char tryid[7];
	cin >> tryid;
	userNode* p = totalState.userHead;
	int i = 0;
	if (p != NULL) {
		if (strcmp(p->umsg.ID, tryid) == 0) 
			totalState.userHead = totalState.userHead->next;
		else {
			while (p->next != NULL && i != 1) {
				if (strcmp(p->next->umsg.ID, tryid) == 0) {
					i = 1;
					p->next = p->next->next;
					p = p->next;
				}
				else
					p = p->next;
			}
		}
		if (p == NULL) {
			cout << "未找到该用户，删除失败！" << endl;
			return;
		}
		deleUserItems(p->umsg.ID);
		delete p;
		cout << "删除成功！\n";
		return;
	}
	else
		cout << "未找到该用户，删除失败！" << endl;
}

void deleUserItems(char* userid) {
	itemNode* p = totalState.itemHead;
	while (p != NULL) {
		
	}
}

void removeItem() {
	cout << "请输入要下架的商品ID：";
	char tryid[7];
	cin >> tryid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "该商品不存在！下架失败！" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, tryid) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "该商品不存在！下架失败！" << endl;
			return sellorMenu();
		}
	}
	cout << "请确认商品信息！" << endl;
	cout << "**************************" << endl;
	cout << "商品ID：" << p->imsg.ID << endl;
	cout << "商品名称：" << p->imsg.name << endl;
	cout << "商品价格：";
	printf("%.1lf元\n", p->imsg.price);
	cout << "商品描述：" << p->imsg.info << endl;
	cout << "**************************" << endl;
	cout << "请选择操作（1.下架 2.取消）：";
	int i;
	cin >> i;
	while (i != 1 && i != 2 && i != 3) {
		cout << "请输入1或2：";
		cin >> i;
	}
	if (i == 1) {
		p->imsg.state = "已下架";
		cout << "下架成功！" << endl;
	}
	if (i == 2)
		cout << "已取消。" << endl;
	return sellorMenu();
}

void adminFindItems() {
	cout << "请输入商品名称：";
	char tryname[11];
	cin >> tryname;
	itemMsg* p = sechItem(tryname);
	if (p == NULL) {
		cout << "未查找到相应商品" << endl;
		return;
	}
	cout << "**********************************************************" << endl;
	cout << "ID      名称    价格   上架时间         卖家ID  商品状态" << endl;
	cout << p->ID << "\t" << p->name << "\t";
	printf("%.1lf\t", p->price);
	cout << p->time << "\t" << p->sellorID << "\t" << p->state << endl;
	cout << "**********************************************************" << endl;
}

void listAllOrders() {
	orderNode* p = totalState.orderHead;
	cout << "***************************************************************************\n";
	cout << "订单ID  商品ID  交易金额   交易时间  卖家ID  买家ID\n";
	while (p != NULL) {
		cout << p->omsg.ID << "\t" << p->omsg.itemID << "\t";
		printf("%.1lf\t%s\t%s\t%s\n", p->omsg.amt, p->omsg.time, p->omsg.sellorID, p->omsg.buyerID);
		p = p->next;
	}
	cout << "***************************************************************************\n";
}

void listAllUsers() {
	userNode* p = totalState.userHead;
	cout << "***************************************************************************\n";
	cout << "用户ID    用户名      联系方式      钱包余额    地址\n";
	while (p != NULL) {
		cout << p->umsg.ID << "\t" << p->umsg.name << "\t" << p->umsg.contactInfo << "\t";
		printf("%.1lf\t%s\n", p->umsg.balance, p->umsg.addr);
		p = p->next;
	}
	cout << "***************************************************************************\n";
}

void listAllItems() {
	itemNode* p = totalState.itemHead;
	cout << "***************************************************************************\n";
	cout << "ID      名称      价格  上架时间    卖家ID   商品状态\n";
	while (p != NULL) {
		cout << p->imsg.ID << "\t" << p->imsg.name << "\t";
		printf("%.1lf\t%s\t%s\t%s\n", p->imsg.price, p->imsg.time, p->imsg.sellorID, p->imsg.state);
		p = p->next;
	}
	cout << "***************************************************************************\n";
}