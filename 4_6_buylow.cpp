/*
ID: tzhan1
PROG: buylow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
//#include <limits>

using namespace std;

const long long MAXX = 1000000000000000000; //std::numeric_limits<long long>::max() / 2 - 1;
const short LENM = 18;
class Bignum {
	vector<long long> v;
	bool isp = 1;
public:
	Bignum(){}
	Bignum(const long long &x);
	friend Bignum operator+(const Bignum &x, const Bignum &y);
	Bignum operator+(const long long &x);
	friend Bignum operator+(const long long &x, const Bignum &y){ return y + x; }
	friend Bignum operator-(const Bignum &x, const Bignum &y);
	Bignum operator-(const long long &x) { return *this + (-x); }
	friend Bignum operator-(const long long &x, const Bignum &y);
	Bignum & operator=(const Bignum &x) { v = x.v, isp = x.isp;	return *this; }
	Bignum & operator=(const long long &x);
	friend bool operator<(const Bignum &x, const Bignum &y);
	friend bool operator>(const Bignum &x, const Bignum &y) { return y < x; }
	friend bool operator==(const Bignum &x, const Bignum &y);
	friend bool operator!=(const Bignum &x, const Bignum &y) { return !(x == y); }
	friend ostream & operator<<(ostream &o, const Bignum &x);
};

Bignum operator+(const Bignum &x, const Bignum &y) {
	if (!x.isp) {
		Bignum z1 = x;
		z1.isp = 1;
		return y - z1;
	}
	if (!y.isp) {
		Bignum z1 = y;
		z1.isp = 1;
		return x - z1;
	}
	const Bignum *x1;
	Bignum z;
	int tmpa = 0;
	if (x > y)		z = x,	x1 = &y;
	else			z = y,	x1 = &x;
	
	for (int i = 0; i < z.v.size(); ++i) {
		if(i<x1->v.size())		z.v[i] += x1->v[i] + tmpa;
		else			z.v[i] += tmpa;
		if (z.v[i] > MAXX) {
			z.v[i] -= MAXX;
			tmpa = 1;
		}
		else	tmpa = 0;
		if (!tmpa&&i >= x1->v.size())		break;
	}
	if (tmpa)		z.v.push_back(1);
	return z;
}
Bignum Bignum::operator+(const long long &x) {
	Bignum y(x);
	return *this + y;
}

Bignum operator-(const Bignum &x, const Bignum &y) {
	if (!x.isp) {
		Bignum z1 = x;
		z1.isp = 1;
		Bignum z2 = z1 + y;
		z2.isp = 0;
		return z2;
	}
	if (!y.isp) {
		Bignum z1 = y;
		z1.isp = 1;
		return x + z1;
	}
	const Bignum *x1;
	Bignum z;
	int tmpa = 0;
	if (x == y) {
		Bignum z(0);
		return z;
	}
	else if (x > y) 	z = x, x1 = &y;
	else {
		z = y;
		z.isp = 0;
		x1 = &x;
	}

	for (int i = 0; i < z.v.size(); ++i) {
		if (i<x1->v.size())		z.v[i] -= x1->v[i] + tmpa;
		else			z.v[i] -= tmpa;
		if (z.v[i] < 0) {
			z.v[i] += MAXX;
			tmpa = 1;
		}
		else	tmpa = 0;
		if (!tmpa&&i >= x1->v.size())		break;
	}
	while (z.v.back() == 0 && z.v.size() > 1)	z.v.pop_back();
	return z;
}
Bignum operator-(const long long &x, const Bignum &y) {
	Bignum z = y;
	z.isp = !y.isp;
	return z + x;
}

Bignum::Bignum(const long long &x) { 
	long long tmpa = 0, y = x;
	if (y < 0) {
		isp = 0;
		y = -y;
	}
	while (y >= MAXX) {
		y -= MAXX;
		++tmpa;
	}
	v.push_back(y);
	if (tmpa)		v.push_back(tmpa);
}
Bignum & Bignum::operator=(const long long &x) {
	vector<long long>().swap(v);
	long long tmpa = 0, y = x;
	if (y < 0) {
		isp = 0;
		y = -y;
	}
	while (y >= MAXX) {
		y -= MAXX;
		++tmpa;
	}
	v.push_back(y);
	if (tmpa)		v.push_back(tmpa);
	return *this;
}

bool operator<(const Bignum & x, const Bignum &y)
{
	if (x.isp && !y.isp)	return false;
	if (!x.isp && y.isp)	return true;
	if (!x.isp && !y.isp) {
		Bignum z1 = x, z2 = y;
		z1.isp = 1;
		z2.isp = 1;
		return !(z1 < z2);
	}
	if (x.v.size()>y.v.size())	return false;
	if (x.v.size()<y.v.size())	return true;
	for (int i = x.v.size() - 1; i >= 0; --i) {
		if (x.v[i] > y.v[i])	return false;
		if (x.v[i] < y.v[i])	return true;
	}
	return false;
}

bool operator==(const Bignum &x, const Bignum &y) {
	if (x.isp != y.isp)		return false;
	if (x.v.size() != y.v.size())	return false;
	for (int i = x.v.size() - 1; i >= 0; --i)
		if (x.v[i] != y.v[i])	return false;
	return true;
}

ostream & operator<<(ostream &o, const Bignum &x) {
	if (!x.v.size())		return o;
	if (!x.isp)		o << '-';
	o << x.v.back();
	for (int i = x.v.size() - 2; i >= 0; --i) {
		o.width(LENM);
		o.fill('0');
		o << x.v[i];
	}
	return o;
}


int main() {
	ofstream fout("buylow.out");
	ifstream fin("buylow.in");
	int N, tmpa, i, j, tmpm, za[5000] = { 0 };
	short zb[5000];
	Bignum zc[5000], tmpi;
	
	(fin >> N).get();
	for (i = 0; i < N; ++i)		(fin >> zb[i]).get();
	
	za[N - 1] = 1;
	zc[N - 1] = 1;
	
	for (i = N - 2; i >= 0; --i) {
		tmpi = tmpm = 0;
		for (j = i + 1; j < N; ++j) {
			if (za[j] == 0)		continue;
			if (zb[j] > zb[i]) {
				if (tmpm >= za[j])		break;
				continue;
			}
			if (zb[j] == zb[i]) {
				if (za[j] - 1 > tmpm || !tmpm) {
					tmpm = -1;
					tmpi = 0;
					break;
				}
				else if (tmpm >= za[j])		break;
				else {		//tmpm == za[j] - 1.
					tmpi = tmpi + zc[j];
					zc[j] = za[j] = 0;
					break;
				}
			}
			if (za[j] < tmpm)		continue;
			else if (za[j] > tmpm) {
				tmpm = za[j];
				tmpi = zc[j];
			}
			else 	tmpi = tmpi + zc[j];
		}
		za[i] = tmpm + 1;
		zc[i] = tmpm ? tmpi : 1;
	}
	
	tmpi = tmpm = 0;
	for (j = 0; j < N; ++j) {
		if (za[j] < tmpm)		continue;
		else if (za[j] > tmpm) {
			tmpm = za[j];
			tmpi = zc[j];
		}
		else		tmpi = tmpi + zc[j];
	}

	fout << tmpm << ' ' << tmpi << endl;

	return 0;
}