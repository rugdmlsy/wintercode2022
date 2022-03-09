#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "init.h"
#include "user.h"
#pragma warning(disable:4996)
using namespace std;

userMsg tstmsg;
totalstate totalState;
void userMenu();
void PIMMenu();
void sellorMenu();
void remoItem();
void releItem();
void seeItems();
void buyerSeeItems();
void modiItem();
void seeDetail();
void buyerMenu();
void buyitem();
void findItem();

itemMsg* searchItem(char* tryid) {
	itemNode* p = totalState.itemHead;
	while (p != NULL) {
		if (strcmp(p->imsg.ID, tryid) == 0)
			return &(p->imsg);
		p = p->next;
	}
	return NULL;
}

itemMsg* sechItem(char* trynm) {
	itemNode* p = totalState.itemHead;
	while (p != NULL) {
		if (strcmp(p->imsg.name, trynm) == 0)
			return &(p->imsg);
		p = p->next;
	}
	return NULL;
}

bool ifUniqueName(char* userId) {
	if (totalState.userHead == NULL)
		return true;
	userNode* p = totalState.userHead;
	if (strcmp(p->umsg.name, userId) == 0) 
		return false;
	while (p->next != NULL) {
		p = p->next;
		if (strcmp(p->umsg.name, userId) == 0)
			return false;
	} 
	return true;
}

void userSignUp() {
	cout << "请输入用户名：";
	userMsg* m = new userMsg;
	cin >> m->name;
	while (!ifUniqueName(m->name)) {
		cout << "用户名已重复！请重新输入：";
		cin >> m->name;
	}
	cout << "请输入密码：";
	cin >> m->pswd;
	cout << "请输入联系方式：";
	cin >> m->contactInfo;
	cout << "请输入地址：";
	cin >> m->addr;
	userNode* p = new userNode;
	p->umsg = *m;
	p->next = NULL;
	totalState.addUser(p);
	cout << "注册成功！即将返回主界面..." << endl << endl;
	return initMenu();
};

void userLogIn() {
	cout << "请输入用户名：";
	char tryname[11];
	cin >> tryname;
	if (totalState.userHead == NULL) {
		cout << "用户名不存在！请先注册" << endl;
		return initMenu();
	}
	userNode* p = totalState.userHead;
	while (p->next != NULL) {
		if (strcmp(p->umsg.name, tryname) == 0)
			break;
		else
			p = p->next;
	}
	if (strcmp(p->umsg.name, tryname) != 0) {
		cout << "用户名不存在！请先注册" << endl << endl;
		return initMenu();
	}
	else {
		cout << "请输入密码：";
		char trypswd[21];
		cin >> trypswd;
		if (strcmp(p->umsg.pswd, trypswd) != 0) {
			cout << "密码错误！即将返回主界面..." << endl << endl;
			return initMenu();
		}
		else {
			totalState.userNow = &(p->umsg);
			cout << "登录成功！" << endl << endl;
			return userMenu();
		}
	}
}

void userMenu() {
	while (1) {
		cout << "===================================================" << endl;
		cout << "1.注销登录 2.我是买家 3.我是卖家 4.个人信息管理" << endl;
		cout << "===================================================" << endl << endl;
		cout << "请输入操作：";
		int a = 0;
		while (a < 1 || a>4)
			cin >> a;
		cout << endl;
		switch (a) {
		case 1: 
			return initMenu();
		case 2: 
			return buyerMenu();
		case 3:
			return sellorMenu();
		case 4: 
			return PIMMenu();
		}
	}
	
};

void PIMMenu() {
	while (1) {
		cout << "===================================================" << endl;
		cout << "1.返回用户主界面 2.修改信息 3.查看信息 4.充值" << endl;
		cout << "===================================================" << endl << endl;
		cout << "请输入操作：";
		int a = 0;
		while (a < 1 || a>4)
			cin >> a;
		switch (a) {
		case 1: return userMenu();
		case 2: 
			cout<<"请选择修改的属性（1.用户名 2.联系方式 3.地址）：";
			cin >> a;
			switch (a) {
			case 1: 
				cout << "请输入修改后的用户名：";
				char changedname[11];
				cin >> changedname;
				while (!ifUniqueName(changedname)) {
					cout << "用户名重复，请重新输入：";
					cin >> changedname;
				}
				strcpy(totalState.userNow->name, changedname);
				cout << "修改成功！" << endl;
				break;
			case 2:
				cout << "请输入修改后的联系方式：";
				char changed[21];
				cin >> changed;
				strcpy(totalState.userNow->contactInfo, changed);
				cout << "修改成功！" << endl;
				break;
			case 3:
				cout << "请输入修改后的地址：";
				char changedaddr[21];
				cin >> changedaddr;
				strcpy(totalState.userNow->addr, changedaddr);
				cout << "修改成功！" << endl;
				break;
			}
			break;
		case 3:
			cout << "***********************" << endl;
			cout << "用户名：" << totalState.userNow->name << endl;
			cout << "联系方式：" << totalState.userNow->contactInfo << endl;
			cout << "地址：" << totalState.userNow->addr << endl;
			cout << "钱包余额：";
			printf("%.1lf\n", totalState.userNow->balance);
			cout << "***********************" << endl;
			break;
		case 4: 
			cout<<"请输入充值数目：";
			double amo;
			cin >> amo;
			totalState.userNow->balance += amo;
			cout << "***********************" << endl;
			cout << "充值成功！" << endl;
			cout << "当前余额：";
			printf("%.1lf\n", totalState.userNow->balance);
			break;
		}
	}
}

void sellorMenu() {
	while (1) {
		cout << "====================================================================================" << endl;
		cout << "1.发布商品 2.查看发布商品 3.修改商品信息 4.上/下架商品 5.查看历史订单 6.返回用户主界面" << endl;
		cout << "====================================================================================" << endl;
		cout << "输入操作：";
		int i = 0;
		while (i < 1 || i>6)
			cin >> i;
		switch (i) {
		case 1: 
			releItem(); break;
		case 2:
			seeItems(); break;
		case 3: 
			modiItem(); break;
		case 4:
			remoItem(); break;
		case 5: 
			sellorOrderHist(); break;
		case 6:
			return userMenu();
		}
	}
}

void sellorOrderHist() {
	cout << "*********************************************************\n";
	cout << "订单ID  商品ID  交易金额  交易时间      买家ID\n";
	orderNode* p = totalState.orderHead;
	while (p != NULL) {
		if (strcmp(p->omsg.sellorID, totalState.userNow->ID) == 0) {
			cout << p->omsg.ID << "\t" << p->omsg.itemID << "\t";
			printf("%.1lf\t", p->omsg.amt);
			cout << p->omsg.time << "\t" << p->omsg.buyerID << endl;
		}
		p = p->next;
	}
	cout << "*********************************************************\n";
}

void modiItem() {
	cout << "***************************" << endl;
	cout << "请输入要修改的商品ID：";
	char tryid[7];
	cin >> tryid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "该商品不存在！" << endl;
		cout << "***************************" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, tryid) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "该商品不存在！" << endl;
			cout << "***************************" << endl;
			return sellorMenu();
		}
	}
	if (strcmp(p->imsg.sellorID, totalState.userNow->ID) != 0) {
		cout << "不是您发布的商品！" << endl;
		cout << "***************************" << endl;
		return sellorMenu();
	}
	cout << "请输入要修改的属性（1.价格 2.描述）：";
	int i = 0;
	cin >> i;
	if (i != 1 && i != 2) {
		cout << "没有对应的商品属性，修改失败！" << endl;
		cout << "************************************" << endl;
		return sellorMenu();
	}
	char c = '\0';
	switch (i) {
	case 1: 
		cout << "请输入修改后的价格：";
		double m;
		cin >> m;
		cout << "请确认修改后的商品信息！" << endl <<endl;
		cout << "**************************" << endl;
		cout << "商品ID：" << tryid << endl;
		cout << "商品名称：" << p->imsg.name << endl;
		cout << "商品价格：" << m << "元" << endl;
		cout << "商品描述：" << p->imsg.info << endl;
		cout << "**************************" << endl;
		cout << "确认修改？（y/n）";
		cin >> c;
		while (c != 'y' && c != 'n') {
			cout << "请输入y或n：";
			cin >> c;
		}
		if (c == 'y') {
			p->imsg.price = m;
			cout << "修改成功！" << endl;
			cout << "************************************" << endl;
		}
		else {
			cout << "取消修改！" << endl;
			cout << "************************************" << endl;
		}
		break;
	case 2:
		cout << "请输入修改后的商品描述：";
		char d[101];
		cin >> d;
		cout << "请确认修改后的商品信息！" << endl << endl;
		cout << "**************************" << endl;
		cout << "商品ID：" << tryid << endl;
		cout << "商品名称：" << p->imsg.name << endl;
		cout << "商品价格：" << p->imsg.price << "元" << endl;
		cout << "商品描述：" << d << endl;
		cout << "**************************" << endl;
		cout << "确认修改？（y/n）";
		char c1 = '\0';
		cin >> c1;
		while (c1 != 'y' && c1 != 'n') {
			cout << "请输入y或n：";
			cin >> c1;
		}
		if (c1 == 'y') {
			strcpy(p->imsg.info, d);
			cout << "修改成功！" << endl;
			cout << "************************************" << endl;
		}
		else {
			cout << "取消修改！" << endl;
			cout << "************************************" << endl;
		}
		break;
	}
}

void seeItems() {
	itemNode* p = totalState.itemHead;
	cout << "您发布的商品清单如下：" << endl;
	cout << "*****************************************************************************" << endl;
	cout << "ID      名称          价格      上架时间      商品状态" << endl;
	if (p == NULL)
		return;
	while (p != NULL) {
		if (strcmp(p->imsg.sellorID, totalState.userNow->ID) == 0) {
			cout << p->imsg.ID << "\t";
			printf("%-10s\t%.1lf\t", p->imsg.name, p->imsg.price);
			cout << p->imsg.time << "\t" << p->imsg.state << endl;
		}
		p = p->next;
	}
	cout << "*****************************************************************************" << endl << endl;
}

void releItem() {
	itemMsg* p = new itemMsg;
	p->state = "销售中";
	cout << "请输入商品名称：";
	cin >> p->name;
	cout << "请输入商品价格：";
	cin >> p->price;
	cout << "请输入商品描述：";
	cin >> p->info;
	strcpy(p->sellorID, totalState.userNow->ID);
	p->gettime();
	itemNode* nod = new itemNode;
	nod->imsg = *p;
	nod->next = NULL;
	totalState.addItem(nod);
	cout << "上架成功！" << endl;
}

void remoItem() {
	cout << "请输入要上/下架的商品ID：";
	char tryid[7];
	cin >> tryid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "该商品不存在！上/下架失败！" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, tryid) != 0 && strcmp(p->imsg.sellorID, totalState.userNow->ID) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "该商品不存在！上/下架失败！" << endl;
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
	cout << "请选择操作（1.下架 2.上架 3.取消）：";
	int i;
	cin >> i;
	while (i != 1 && i != 2 && i != 3) {
		cout << "请输入1或2或3：";
		cin >> i;
	}
	if (i == 1) {
		p->imsg.state = "已下架";
		cout << "下架成功！" << endl;
	}
	if (i == 2) {
		p->imsg.state = "销售中";
		cout << "上架成功！" << endl;
	}
	if (i == 3)
		cout << "已取消。" << endl;
	return sellorMenu();
}
	
void buyerMenu() {
	while (1) {
		cout << "====================================================================================" << endl;
		cout << "1.查看商品列表 2.购买商品 3.搜索商品 4.查看历史订单 5.查看商品详细信息 6.返回用户主界面" << endl;
		cout << "====================================================================================" << endl;
		cout << "请输入操作：";
		int i;
		cin >> i;
		while (i < 1 || i>6) {
			cout << "请输入一个1~6间的整数：";
			cin >> i;
		}
		switch (i) {
		case 1: 
			buyerSeeItems();
			break;
		case 2:
			buyitem();
			break;
		case 3:
			findItem();
			break;
		case 4:
			buyerOrderHist();
			break;
		case 5:
			seeDetail();
			break;
		case 6:
			return userMenu();
		}
	}
}

void buyerOrderHist() {
	cout << "*********************************************************\n";
	cout << "订单ID  商品ID  交易金额  交易时间      卖家ID\n";
	orderNode* p = totalState.orderHead;
	while (p != NULL) {
		if (strcmp(p->omsg.buyerID, totalState.userNow->ID) == 0) {
			cout << p->omsg.ID << "\t" << p->omsg.itemID << "\t";
			printf("%.1lf\t", p->omsg.amt);
			cout << p->omsg.time << "\t" << p->omsg.sellorID << endl;
		}
		p = p->next;
	}
	cout << "*********************************************************\n";
}

void findItem() {
	cout << "请输入商品名称：";
	char tryname[11];
	cin >> tryname;
	itemMsg* p = sechItem(tryname);
	if (p == NULL || p->state != "销售中") {
		cout << "未查找到相应商品" << endl;
		return;
	}
	cout << "*************************************************" << endl;
	cout << "ID      名称    价格   上架时间         卖家ID" << endl;
	cout << p->ID << "\t" << p->name << "\t";
	printf("%.1lf\t", p->price);
	cout << p->time << "\t" << p->sellorID << endl;
	cout << "*************************************************" << endl;
}

void seeDetail() {
	cout << "请输入您想查看的商品ID：\n";
	char tryid[7];
	cin >> tryid;
	itemMsg* p = searchItem(tryid);
	if (p == NULL) {
		cout << "商品不存在！" << endl;
		return;
	}
	cout << "************************************" << endl;
	cout << "名称：" << p->name << endl;
	cout << "描述：" << p->info << endl;
	cout << "上架时间：" << p->time << endl;
	cout << "卖家ID：" << p->sellorID << endl;
	cout << "商品状态：" << p->state << endl;
	cout << "************************************" << endl;
}

void buyerSeeItems() {
	itemNode* p = totalState.itemHead;
	cout << "*****************************************************************************" << endl;
	cout << "ID      名称            价格    卖家ID  描述" << endl;
	if (p == NULL)
		return;
	while (p != NULL) {
		if (p->imsg.state == "销售中") {
			cout << p->imsg.ID << "\t";
			printf("%-10s\t%.1lf\t", p->imsg.name, p->imsg.price);
			cout << p->imsg.sellorID << "\t" << p->imsg.info << endl;
		}
		p = p->next;
	}
	cout << "*****************************************************************************" << endl << endl;
}

void buyitem() {
	cout << "请输入要购买的商品ID：";
	char buyid[7];
	cin >> buyid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "该商品不存在！购买失败！" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, buyid) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "该商品不存在！购买失败！" << endl;
			return sellorMenu();
		}
	}
	if (p->imsg.state == "已下架")
		cout << "该商品已下架！购买失败！" << endl;
	else if (p->imsg.state == "已售出")
		cout << "该商品已售出！购买失败！" << endl;
	else {
		cout << "请确认商品信息！" << endl;
		cout << "**************************" << endl;
		cout << "商品ID：" << p->imsg.ID << endl;
		cout << "商品名称：" << p->imsg.name << endl;
		cout << "商品价格：";
		printf("%.1lf元\n", p->imsg.price);
		cout << "商品描述：" << p->imsg.info << endl;
		cout << "**************************" << endl;
		cout << "请选择操作（1.购买 2.取消）：";
		int i;
		cin >> i;
		while (i != 1 && i != 2) {
			cout << "请输入1或2：";
			cin >> i;
		}
		if (i == 1) {
			if (totalState.userNow->balance < p->imsg.price)
				cout << "余额不足！购买失败！" << endl;
			else {
				
				p->imsg.state = "已售出";
				totalState.userNow->balance -= p->imsg.price;
				userNode* q = totalState.userHead;
				while (strcmp(q->umsg.ID, p->imsg.sellorID) != 0)
					q = q->next;
				q->umsg.balance += p->imsg.price;
				
				orderMsg* om = new orderMsg;
				strcpy(om->itemID, p->imsg.ID);
				timeNow(om->time);
				strcpy(om->sellorID, q->umsg.ID);
				strcpy(om->buyerID, totalState.userNow->ID);
				om->amt = p->imsg.price;
				orderNode* nod = new orderNode;
				nod->omsg = *om;
				nod->next = NULL;
				totalState.addOrder(nod);

				cout << "*******************" << endl;
				cout << "交易提醒：" << endl;
				char tim[11];
				timeNow(tim);
				cout << "交易时间：" << tim << endl;
				cout << "交易金额：";
				printf("%.1lf\n", p->imsg.price);
				cout << "交易状态：交易成功" << endl;
				cout << "余额：";
				printf("%.1lf元\n", totalState.userNow->balance);
				cout << "*******************" << endl;
			}
			
		}
		if (i == 2)
			cout << "已取消购买。" << endl;
	}
	return buyerMenu();
}
