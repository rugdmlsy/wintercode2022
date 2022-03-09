#pragma once
#include <iostream>
#include <cstdio>
#include <ctime>
#pragma warning(disable:4996)
using namespace std;


class userMsg {
	char ID[7];
	char name[11];
	char pswd[21];
	char contactInfo[21];
	char addr[21];
	float balance;
public:
	friend void listAllUsers();
	userMsg() {
		strcpy(ID, "U00000");
		strcpy(name, "_testuser_"); 
		strcpy(pswd, "__testpswd__");
		strcpy(contactInfo, "__testinfo__");
		strcpy(addr, "__testaddr__");
		balance = 0;
	}
	void read() {
		cin.getline(ID, 7, ',');
		cin.getline(name, 11, ',');
		cin.getline(pswd, 21, ',');
		cin.getline(contactInfo, 21, ',');
		cin.getline(addr, 21, ',');
		cin >> balance;
	};
	friend void userSignUp();
	friend bool ifUniqueName(char* userId);
	friend void userLogIn();
	friend void PIMMenu();
	friend void remoItem();
	friend void deleteUser();
	void setID(int i) {
		sprintf(ID, "U%05d", i);
	}
	friend void seeItems();
	friend void releItem();
	friend void modiItem();
	friend void buyitem();
	friend void buyerOrderHist();
	friend void sellorOrderHist();
};
class itemMsg {
	char ID[7];
	char name[11];
	double price;
	char info[101];
	char sellorID[7];
	char time[11];
	string state;
public:
	friend void deleUserItems(char* userid);
	friend void removeItem();
	friend void listAllItems();
	friend void adminFindItems();
	void setID(int i) {
		sprintf(ID, "M%05d", i);
	}
	void rem() {
		cout << "您确认要下架该商品吗？" << endl;
		cout << "***********************" << endl;
		cout << "商品ID：" << ID << endl;
		cout << "商品名称：" << name << endl;
		cout << "商品金额：";
		printf("%.1lf\n", price);
		cout << "商品描述：" << info << endl;
		cout << "***********************" << endl;
		cout << "请选择（y/n）：";
		char cho = '\0';
		while (cho != 'y' && cho != 'n')
			cin >> cho;
		if (cho == 'y') {
			state = "已下架";
			cout << "下架成功！" << endl;
		}
		else if (cho == 'n')
			cout << "下架取消" << endl;
	}
	friend void remoItem();
	friend void releItem();
	void gettime() {
		time_t now = std::time(0);
		tm* ltm = localtime(&now);
		char yyyy[5], mm[3], dd[3];
		itoa(ltm->tm_year + 1900, yyyy, 10);
		itoa(ltm->tm_mon + 1, mm, 10);
		itoa(ltm->tm_mday, dd, 10);
		sprintf(time, "%s-%s-%s", yyyy, mm, dd);
	}
	friend void seeItems();
	friend void modiItem();
	friend void buyerSeeItems();
	friend void buyitem();
	friend itemMsg* searchItem(char* tryid);
	friend void seeDetail();
	friend itemMsg* sechItem(char* trynm);
	friend void findItem();
};
class orderMsg {
	char ID[7];
	char itemID[7];
	char time[11];
	char sellorID[7];
	char buyerID[7];
	double amt;
public:
	void setID(int i) {
		sprintf(ID, "O%05d", i);
	}
	friend void buyitem();
	friend void buyerOrderHist();
	friend void sellorOrderHist();
	friend void listAllOrders();
};

extern userMsg tstmsg;

struct userNode {
	userMsg umsg = tstmsg;
	userNode* next = NULL;
};
struct itemNode {
	itemMsg imsg;
	itemNode* next = NULL;
};
struct orderNode {
	orderMsg omsg;
	orderNode* next = NULL;
};

class totalstate {
	userNode* userHead;
	userMsg* userNow;
	itemNode* itemHead;
	orderNode* orderHead;
	int maxUID;
	int maxMID;
	int maxOID;
public:
	totalstate() { 
		userHead = NULL;
		userNow = NULL;
		itemHead = NULL;
		orderHead = NULL;
		maxUID = 0;
		maxMID = 0;
		maxOID = 0;
	}
	~totalstate() {
		if (userHead != NULL) {
			while (userHead->next != NULL) {
				userNode* p = userHead;
				userHead = userHead->next;
				delete p;
			}
			delete userHead;
		}
		if (itemHead != NULL) {
			while (itemHead->next != NULL) {
				itemNode* q = itemHead;
				itemHead = itemHead->next;
				delete q;
			}
			delete itemHead;
		}
		if (orderHead != NULL) {
			while (orderHead->next != NULL) {
				orderNode* r = orderHead;
				orderHead = orderHead->next;
				delete r;
			}
			delete orderHead;
		}
	}
	friend void deleUserItems(char* userid);
	friend void deleteUser();
	friend void removeItem();
	friend void listAllItems();
	friend void listAllUsers();
	friend itemMsg* sechItem(char* trynm);
	friend itemMsg* searchItem(char* tryid);
	void addUser(userNode* nod) {
		userNode* p = userHead;
		maxUID += 1;
		nod->umsg.setID(maxUID);
		if (p == NULL)
			userHead = nod;
		else {
			while (p->next != NULL)
				p = p->next;
			p->next = nod;
		}
	}
	void addItem(itemNode* nod) {
		itemNode* p = itemHead;
		maxMID += 1;
		nod->imsg.setID(maxMID);
		if (p == NULL)
			itemHead = nod;
		else {
			while (p->next != NULL)
				p = p->next;
			p->next = nod;
		}
	}
	void addOrder(orderNode* nod) {
		orderNode* p = orderHead;
		maxOID += 1;
		nod->omsg.setID(maxOID);
		if (p == NULL)
			orderHead = nod;
		else {
			while (p->next != NULL)
				p = p->next;
			p->next = nod;
		}
	}
	friend void userSignUp();
	friend bool ifUniqueName(char* userId);
	friend void deleteUserHead();
	friend void userLogIn();
	friend void PIMMenu();
	friend void remoItem();
	friend void releItem();
	friend void seeItems();
	friend void modiItem();
	friend void buyerSeeItems();
	friend void buyitem();
	friend void buyerOrderHist();
	friend void sellorOrderHist();
	friend void listAllOrders();
};

extern totalstate totalState;

itemMsg* searchItem(char* tryid);
itemMsg* sechItem(char* trynm);
bool ifUniqueName(char* userId);
void userSignUp();
void userLogIn();
void userMenu();
void PIMMenu();
void sellorMenu();
void sellorOrderHist();
void modiItem();
void seeItems();
void releItem();
void remoItem();
void buyerMenu();
void buyerOrderHist();
void findItem();
void seeDetail();
void buyerSeeItems();
void buyitem();
void listAllOrders();
void listAllUsers();
