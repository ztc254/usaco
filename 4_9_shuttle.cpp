/*
ID: tzhan1
PROG: shuttle
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

vector<int> dt(25);
int zl, N, hd = 0, tl;

int znxt(int i) {
	if (!i) {
		if (zl < 2)		return 0;
		if (dt[zl - 2] != -1 || dt[zl - 1] != 1)		return 0;
		if (tl > zl + 1)		if (dt[zl + 1] == -1)		return 0;
		dt[zl] = -1; zl -= 2; dt[zl] = 0;
		if (hd == zl)		hd += 2;
	}
	else if (i == 1) {
		if (zl < 1)		return 0;
		if (dt[zl - 1] != -1)		return 0;
		if (tl > zl + 1)		if (dt[zl + 1] == -1)		return 0;
		dt[zl] = -1; dt[--zl] = 0;
		if (hd == zl)		++hd;
	}
	else if (i == 2) {
		if (zl > 2 * N - 1)		return 0;
		if (dt[zl + 1] != 1)			return 0;
		if (hd < zl - 1)		if (dt[zl - 1] == 1)		return 0;
		dt[zl] = 1; dt[++zl] = 0;
		if (tl == zl)		--tl;
	}
	else {
		if (zl > 2 * N - 2)		return 0;
		if (dt[zl + 2] != 1 || dt[zl + 1] != -1)		return 0;
		if (hd < zl - 1)		if (dt[zl - 1] == 1)		return 0;
		dt[zl] = 1; zl += 2; dt[zl] = 0;
		if (tl == zl)		tl -= 2;
	}
	return 1;
}

void zbck(int i) {
	if (!i) {
		dt[zl] = -1; zl += 2; dt[zl] = 0;
		if (hd == zl)		hd -= 2;
	}
	if (i == 1) {
		dt[zl] = -1; dt[++zl] = 0;
		if (hd == zl)		--hd;
	}
	if (i == 2) {
		dt[zl] = 1; dt[--zl] = 0;
		if (tl == zl)		++tl;
	}
	if (i == 3) {
		dt[zl] = 1; zl -= 2; dt[zl] = 0;
		if (tl==zl)		tl += 2;
	}
}

int main() {
	ofstream fout("shuttle.out");
	ifstream fin("shuttle.in");
	int tmpa, i, j;
	
	fin >> N;
	fin.close();
	zl = N, tl = 2 * N;
	vector<int> nd(dt);
	for (i = 0; i < N; ++i) {
		dt[i] = -1; nd[i] = 1;
		dt[i + N + 1] = 1; nd[i + N + 1] = -1;
	}
	
	int M = N*(N + 2);
	vector<int> rt(M), ori(1);

	rt[0] = N - 2;
	while (1) {
		while (!znxt(ori.back())) {
			while (++ori.back() > 3 && ori.size()) {
				ori.pop_back();
				zbck(ori.back());
			}
		}
		rt[ori.size() - 1] = zl + 1;
		if (ori.size() == M)		break;
		ori.push_back(0);
	}

	for (i = 0; i < M - 1; ++i) {
		fout << rt[i];
		if (i % 20 == 19)		fout << endl;
		else		fout << ' ';
	}
	fout << rt[i] << endl;

	return 0;
}