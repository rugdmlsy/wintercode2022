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
	cout << "�������û�����";
	userMsg* m = new userMsg;
	cin >> m->name;
	while (!ifUniqueName(m->name)) {
		cout << "�û������ظ������������룺";
		cin >> m->name;
	}
	cout << "���������룺";
	cin >> m->pswd;
	cout << "��������ϵ��ʽ��";
	cin >> m->contactInfo;
	cout << "�������ַ��";
	cin >> m->addr;
	userNode* p = new userNode;
	p->umsg = *m;
	p->next = NULL;
	totalState.addUser(p);
	cout << "ע��ɹ�����������������..." << endl << endl;
	return initMenu();
};

void userLogIn() {
	cout << "�������û�����";
	char tryname[11];
	cin >> tryname;
	if (totalState.userHead == NULL) {
		cout << "�û��������ڣ�����ע��" << endl;
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
		cout << "�û��������ڣ�����ע��" << endl << endl;
		return initMenu();
	}
	else {
		cout << "���������룺";
		char trypswd[21];
		cin >> trypswd;
		if (strcmp(p->umsg.pswd, trypswd) != 0) {
			cout << "������󣡼�������������..." << endl << endl;
			return initMenu();
		}
		else {
			totalState.userNow = &(p->umsg);
			cout << "��¼�ɹ���" << endl << endl;
			return userMenu();
		}
	}
}

void userMenu() {
	while (1) {
		cout << "===================================================" << endl;
		cout << "1.ע����¼ 2.������� 3.�������� 4.������Ϣ����" << endl;
		cout << "===================================================" << endl << endl;
		cout << "�����������";
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
		cout << "1.�����û������� 2.�޸���Ϣ 3.�鿴��Ϣ 4.��ֵ" << endl;
		cout << "===================================================" << endl << endl;
		cout << "�����������";
		int a = 0;
		while (a < 1 || a>4)
			cin >> a;
		switch (a) {
		case 1: return userMenu();
		case 2: 
			cout<<"��ѡ���޸ĵ����ԣ�1.�û��� 2.��ϵ��ʽ 3.��ַ����";
			cin >> a;
			switch (a) {
			case 1: 
				cout << "�������޸ĺ���û�����";
				char changedname[11];
				cin >> changedname;
				while (!ifUniqueName(changedname)) {
					cout << "�û����ظ������������룺";
					cin >> changedname;
				}
				strcpy(totalState.userNow->name, changedname);
				cout << "�޸ĳɹ���" << endl;
				break;
			case 2:
				cout << "�������޸ĺ����ϵ��ʽ��";
				char changed[21];
				cin >> changed;
				strcpy(totalState.userNow->contactInfo, changed);
				cout << "�޸ĳɹ���" << endl;
				break;
			case 3:
				cout << "�������޸ĺ�ĵ�ַ��";
				char changedaddr[21];
				cin >> changedaddr;
				strcpy(totalState.userNow->addr, changedaddr);
				cout << "�޸ĳɹ���" << endl;
				break;
			}
			break;
		case 3:
			cout << "***********************" << endl;
			cout << "�û�����" << totalState.userNow->name << endl;
			cout << "��ϵ��ʽ��" << totalState.userNow->contactInfo << endl;
			cout << "��ַ��" << totalState.userNow->addr << endl;
			cout << "Ǯ����";
			printf("%.1lf\n", totalState.userNow->balance);
			cout << "***********************" << endl;
			break;
		case 4: 
			cout<<"�������ֵ��Ŀ��";
			double amo;
			cin >> amo;
			totalState.userNow->balance += amo;
			cout << "***********************" << endl;
			cout << "��ֵ�ɹ���" << endl;
			cout << "��ǰ��";
			printf("%.1lf\n", totalState.userNow->balance);
			break;
		}
	}
}

void sellorMenu() {
	while (1) {
		cout << "====================================================================================" << endl;
		cout << "1.������Ʒ 2.�鿴������Ʒ 3.�޸���Ʒ��Ϣ 4.��/�¼���Ʒ 5.�鿴��ʷ���� 6.�����û�������" << endl;
		cout << "====================================================================================" << endl;
		cout << "���������";
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
	cout << "����ID  ��ƷID  ���׽��  ����ʱ��      ���ID\n";
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
	cout << "������Ҫ�޸ĵ���ƷID��";
	char tryid[7];
	cin >> tryid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "����Ʒ�����ڣ�" << endl;
		cout << "***************************" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, tryid) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "����Ʒ�����ڣ�" << endl;
			cout << "***************************" << endl;
			return sellorMenu();
		}
	}
	if (strcmp(p->imsg.sellorID, totalState.userNow->ID) != 0) {
		cout << "��������������Ʒ��" << endl;
		cout << "***************************" << endl;
		return sellorMenu();
	}
	cout << "������Ҫ�޸ĵ����ԣ�1.�۸� 2.��������";
	int i = 0;
	cin >> i;
	if (i != 1 && i != 2) {
		cout << "û�ж�Ӧ����Ʒ���ԣ��޸�ʧ�ܣ�" << endl;
		cout << "************************************" << endl;
		return sellorMenu();
	}
	char c = '\0';
	switch (i) {
	case 1: 
		cout << "�������޸ĺ�ļ۸�";
		double m;
		cin >> m;
		cout << "��ȷ���޸ĺ����Ʒ��Ϣ��" << endl <<endl;
		cout << "**************************" << endl;
		cout << "��ƷID��" << tryid << endl;
		cout << "��Ʒ���ƣ�" << p->imsg.name << endl;
		cout << "��Ʒ�۸�" << m << "Ԫ" << endl;
		cout << "��Ʒ������" << p->imsg.info << endl;
		cout << "**************************" << endl;
		cout << "ȷ���޸ģ���y/n��";
		cin >> c;
		while (c != 'y' && c != 'n') {
			cout << "������y��n��";
			cin >> c;
		}
		if (c == 'y') {
			p->imsg.price = m;
			cout << "�޸ĳɹ���" << endl;
			cout << "************************************" << endl;
		}
		else {
			cout << "ȡ���޸ģ�" << endl;
			cout << "************************************" << endl;
		}
		break;
	case 2:
		cout << "�������޸ĺ����Ʒ������";
		char d[101];
		cin >> d;
		cout << "��ȷ���޸ĺ����Ʒ��Ϣ��" << endl << endl;
		cout << "**************************" << endl;
		cout << "��ƷID��" << tryid << endl;
		cout << "��Ʒ���ƣ�" << p->imsg.name << endl;
		cout << "��Ʒ�۸�" << p->imsg.price << "Ԫ" << endl;
		cout << "��Ʒ������" << d << endl;
		cout << "**************************" << endl;
		cout << "ȷ���޸ģ���y/n��";
		char c1 = '\0';
		cin >> c1;
		while (c1 != 'y' && c1 != 'n') {
			cout << "������y��n��";
			cin >> c1;
		}
		if (c1 == 'y') {
			strcpy(p->imsg.info, d);
			cout << "�޸ĳɹ���" << endl;
			cout << "************************************" << endl;
		}
		else {
			cout << "ȡ���޸ģ�" << endl;
			cout << "************************************" << endl;
		}
		break;
	}
}

void seeItems() {
	itemNode* p = totalState.itemHead;
	cout << "����������Ʒ�嵥���£�" << endl;
	cout << "*****************************************************************************" << endl;
	cout << "ID      ����          �۸�      �ϼ�ʱ��      ��Ʒ״̬" << endl;
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
	p->state = "������";
	cout << "��������Ʒ���ƣ�";
	cin >> p->name;
	cout << "��������Ʒ�۸�";
	cin >> p->price;
	cout << "��������Ʒ������";
	cin >> p->info;
	strcpy(p->sellorID, totalState.userNow->ID);
	p->gettime();
	itemNode* nod = new itemNode;
	nod->imsg = *p;
	nod->next = NULL;
	totalState.addItem(nod);
	cout << "�ϼܳɹ���" << endl;
}

void remoItem() {
	cout << "������Ҫ��/�¼ܵ���ƷID��";
	char tryid[7];
	cin >> tryid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "����Ʒ�����ڣ���/�¼�ʧ�ܣ�" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, tryid) != 0 && strcmp(p->imsg.sellorID, totalState.userNow->ID) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "����Ʒ�����ڣ���/�¼�ʧ�ܣ�" << endl;
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
	cout << "��ѡ�������1.�¼� 2.�ϼ� 3.ȡ������";
	int i;
	cin >> i;
	while (i != 1 && i != 2 && i != 3) {
		cout << "������1��2��3��";
		cin >> i;
	}
	if (i == 1) {
		p->imsg.state = "���¼�";
		cout << "�¼ܳɹ���" << endl;
	}
	if (i == 2) {
		p->imsg.state = "������";
		cout << "�ϼܳɹ���" << endl;
	}
	if (i == 3)
		cout << "��ȡ����" << endl;
	return sellorMenu();
}
	
void buyerMenu() {
	while (1) {
		cout << "====================================================================================" << endl;
		cout << "1.�鿴��Ʒ�б� 2.������Ʒ 3.������Ʒ 4.�鿴��ʷ���� 5.�鿴��Ʒ��ϸ��Ϣ 6.�����û�������" << endl;
		cout << "====================================================================================" << endl;
		cout << "�����������";
		int i;
		cin >> i;
		while (i < 1 || i>6) {
			cout << "������һ��1~6���������";
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
	cout << "����ID  ��ƷID  ���׽��  ����ʱ��      ����ID\n";
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
	cout << "��������Ʒ���ƣ�";
	char tryname[11];
	cin >> tryname;
	itemMsg* p = sechItem(tryname);
	if (p == NULL || p->state != "������") {
		cout << "δ���ҵ���Ӧ��Ʒ" << endl;
		return;
	}
	cout << "*************************************************" << endl;
	cout << "ID      ����    �۸�   �ϼ�ʱ��         ����ID" << endl;
	cout << p->ID << "\t" << p->name << "\t";
	printf("%.1lf\t", p->price);
	cout << p->time << "\t" << p->sellorID << endl;
	cout << "*************************************************" << endl;
}

void seeDetail() {
	cout << "����������鿴����ƷID��\n";
	char tryid[7];
	cin >> tryid;
	itemMsg* p = searchItem(tryid);
	if (p == NULL) {
		cout << "��Ʒ�����ڣ�" << endl;
		return;
	}
	cout << "************************************" << endl;
	cout << "���ƣ�" << p->name << endl;
	cout << "������" << p->info << endl;
	cout << "�ϼ�ʱ�䣺" << p->time << endl;
	cout << "����ID��" << p->sellorID << endl;
	cout << "��Ʒ״̬��" << p->state << endl;
	cout << "************************************" << endl;
}

void buyerSeeItems() {
	itemNode* p = totalState.itemHead;
	cout << "*****************************************************************************" << endl;
	cout << "ID      ����            �۸�    ����ID  ����" << endl;
	if (p == NULL)
		return;
	while (p != NULL) {
		if (p->imsg.state == "������") {
			cout << p->imsg.ID << "\t";
			printf("%-10s\t%.1lf\t", p->imsg.name, p->imsg.price);
			cout << p->imsg.sellorID << "\t" << p->imsg.info << endl;
		}
		p = p->next;
	}
	cout << "*****************************************************************************" << endl << endl;
}

void buyitem() {
	cout << "������Ҫ�������ƷID��";
	char buyid[7];
	cin >> buyid;
	itemNode* p = totalState.itemHead;
	if (p == NULL) {
		cout << "����Ʒ�����ڣ�����ʧ�ܣ�" << endl;
		return sellorMenu();
	}
	while (strcmp(p->imsg.ID, buyid) != 0) {
		p = p->next;
		if (p == NULL) {
			cout << "����Ʒ�����ڣ�����ʧ�ܣ�" << endl;
			return sellorMenu();
		}
	}
	if (p->imsg.state == "���¼�")
		cout << "����Ʒ���¼ܣ�����ʧ�ܣ�" << endl;
	else if (p->imsg.state == "���۳�")
		cout << "����Ʒ���۳�������ʧ�ܣ�" << endl;
	else {
		cout << "��ȷ����Ʒ��Ϣ��" << endl;
		cout << "**************************" << endl;
		cout << "��ƷID��" << p->imsg.ID << endl;
		cout << "��Ʒ���ƣ�" << p->imsg.name << endl;
		cout << "��Ʒ�۸�";
		printf("%.1lfԪ\n", p->imsg.price);
		cout << "��Ʒ������" << p->imsg.info << endl;
		cout << "**************************" << endl;
		cout << "��ѡ�������1.���� 2.ȡ������";
		int i;
		cin >> i;
		while (i != 1 && i != 2) {
			cout << "������1��2��";
			cin >> i;
		}
		if (i == 1) {
			if (totalState.userNow->balance < p->imsg.price)
				cout << "���㣡����ʧ�ܣ�" << endl;
			else {
				
				p->imsg.state = "���۳�";
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
				cout << "�������ѣ�" << endl;
				char tim[11];
				timeNow(tim);
				cout << "����ʱ�䣺" << tim << endl;
				cout << "���׽�";
				printf("%.1lf\n", p->imsg.price);
				cout << "����״̬�����׳ɹ�" << endl;
				cout << "��";
				printf("%.1lfԪ\n", totalState.userNow->balance);
				cout << "*******************" << endl;
			}
			
		}
		if (i == 2)
			cout << "��ȡ������" << endl;
	}
	return buyerMenu();
}
