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
	cout << "���������Ա������";
	cin >> adminName;
	cout << "���������룺";
	cin >> adminPSW;
	cout << endl;
	if (adminName != ADMINNAME || adminPSW != ADMINPSW) {
		cout << "****** ��¼ʧ�ܣ������������˵�... ******" << endl << endl;
		return initMenu();
	}
	cout << "****** ��¼�ɹ��� ******" << endl << endl;
	return adminMenu();
}

void adminMenu() {
	while (1) {
		cout << "=====================================================================================" << endl;
		cout << "1.�鿴������Ʒ 2.������Ʒ 3.�鿴���ж��� 4.�鿴�����û� 5.ɾ���û� 6.�¼���Ʒ 7.ע��" << endl;
		cout << "=====================================================================================" << endl;
		cout << endl;
		cout << "�����������";
		int ind;
		cin >> ind;
		while (ind < 1 || ind >7) {
			cout << "������һ��1~7��������";
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
			cout << "ע����..." << endl << endl;
			return initMenu();
		}
	};
}

void deleteUser() {
	cout << "��������Ҫɾ�����û�ID��";
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
			cout << "δ�ҵ����û���ɾ��ʧ�ܣ�" << endl;
			return;
		}
		deleUserItems(p->umsg.ID);
		delete p;
		cout << "ɾ���ɹ���\n";
		return;
	}
	else
		cout << "δ�ҵ����û���ɾ��ʧ�ܣ�" << endl;
}

void deleUserItems(char* userid) {
	itemNode* p = totalState.itemHead;
	while (p != NULL) {
		
	}
}

void removeItem() {
	cout << "������Ҫ�¼ܵ���ƷID��";
	char tryid[7];
	cin >> tryid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "����Ʒ�����ڣ��¼�ʧ�ܣ�" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, tryid) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "����Ʒ�����ڣ��¼�ʧ�ܣ�" << endl;
			return sellorMenu();
		}
	}
	cout << "��ȷ����Ʒ��Ϣ��" << endl;
	cout << "**************************" << endl;
	cout << "��ƷID��" << p->imsg.ID << endl;
	cout << "��Ʒ���ƣ�" << p->imsg.name << endl;
	cout << "��Ʒ�۸�";
	printf("%.1lfԪ\n", p->imsg.price);
	cout << "��Ʒ������" << p->imsg.info << endl;
	cout << "**************************" << endl;
	cout << "��ѡ�������1.�¼� 2.ȡ������";
	int i;
	cin >> i;
	while (i != 1 && i != 2 && i != 3) {
		cout << "������1��2��";
		cin >> i;
	}
	if (i == 1) {
		p->imsg.state = "���¼�";
		cout << "�¼ܳɹ���" << endl;
	}
	if (i == 2)
		cout << "��ȡ����" << endl;
	return sellorMenu();
}

void adminFindItems() {
	cout << "��������Ʒ���ƣ�";
	char tryname[11];
	cin >> tryname;
	itemMsg* p = sechItem(tryname);
	if (p == NULL) {
		cout << "δ���ҵ���Ӧ��Ʒ" << endl;
		return;
	}
	cout << "**********************************************************" << endl;
	cout << "ID      ����    �۸�   �ϼ�ʱ��         ����ID  ��Ʒ״̬" << endl;
	cout << p->ID << "\t" << p->name << "\t";
	printf("%.1lf\t", p->price);
	cout << p->time << "\t" << p->sellorID << "\t" << p->state << endl;
	cout << "**********************************************************" << endl;
}

void listAllOrders() {
	orderNode* p = totalState.orderHead;
	cout << "***************************************************************************\n";
	cout << "����ID  ��ƷID  ���׽��   ����ʱ��  ����ID  ���ID\n";
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
	cout << "�û�ID    �û���      ��ϵ��ʽ      Ǯ�����    ��ַ\n";
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
	cout << "ID      ����      �۸�  �ϼ�ʱ��    ����ID   ��Ʒ״̬\n";
	while (p != NULL) {
		cout << p->imsg.ID << "\t" << p->imsg.name << "\t";
		printf("%.1lf\t%s\t%s\t%s\n", p->imsg.price, p->imsg.time, p->imsg.sellorID, p->imsg.state);
		p = p->next;
	}
	cout << "***************************************************************************\n";
}