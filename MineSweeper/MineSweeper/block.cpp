#include <iostream>
using namespace std;

class grid {
	int state;
	int x, y;
	bool isMined = false;
	bool isSigned = false;
public:
	void sign() {
		isSigned = !isSigned;
	};
	void uncover() {
		if (isSigned) cout << "����ȡ�����" << endl;
		else {
			if (!isMined) {
				uncover()
			}
		}
	}
};

grid g[1][1];