#include"vector.h"
#include<iostream>
using namespace std;
int main()
{
	vector a(2, 3, 5);//构造函数  (依次为向量的x坐标,y坐标,z坐标)
	vector b;//默认构造
	vector c(a);//拷贝构造

	cout << "Enter a vector ：" << endl;
	cin >> c;//输入符号的重载
	cout << "c is" << c << endl;//(输出格式（2，3，5）)
	cout << "a+c is" << a + c << endl;//加法重载
	cout << "a-c is" << a - c << endl;//减号的重载
	cout << "-5*a is" << -5 * a << endl;//向量的数乘
	cout << "a*(-5)" << a * (-5) << endl;
	cout << "a*c" << a * c << endl;//向量的点乘
	cout << "a^c" << (a ^ c) << endl;//向量的叉乘
	cout << "a == c?:" << (a == c) << endl; //实现“==”重载
}
