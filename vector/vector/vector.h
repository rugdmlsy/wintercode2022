#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class vector {
	int x, y, z;
public:
	vector(int x1, int y1, int z1) : x(x1), y(y1), z(z1) {};
	vector() : x(0), y(0), z(0) {};
	friend istream& operator>> (istream& in, vector& vec);
	friend ostream& operator<< (ostream& out, const vector& vec);
	vector operator+ (vector& vec);
	vector operator- (vector& vec);
	vector operator* (int a);
	friend vector operator* (int a, vector& vec);
	int operator* (vector& vec);
	vector operator^ (vector& vec);
	bool operator== (vector& vec);
};

istream& operator>> (istream& in, vector& vec) {
	string s;
	getline(in, s);
	int a = s.find(",");
	vec.x = atoi(s.substr(1, a - 1).c_str());
	int b = s.find(",", a + 1);
	vec.y = atoi(s.substr(a + 1, b).c_str());
	int c = s.find(")", b + 1);
	vec.z = atoi(s.substr(b + 1, c).c_str());
	return in;
}

ostream& operator<< (ostream& out, const vector& vec) {
	out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
	return out;
}

vector vector::operator+ (vector& vec) {
	return vector(x + vec.x, y + vec.y, z + vec.z);
}

vector vector::operator- (vector& vec) {
	return vector(x - vec.x, y - vec.y, z - vec.z);
}

vector vector::operator* (int a) {
	return vector(x * a, y * a, z * a);
}

vector operator* (int a, vector& vec) {
	return vec * a;
}

int vector::operator* (vector& vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}

vector vector::operator^ (vector& vec) {
	return vector(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}

bool vector::operator== (vector& vec) {
	return (x == vec.x && y == vec.y && z == vec.z) ? true : false;
}

#endif // !VECTOR_H