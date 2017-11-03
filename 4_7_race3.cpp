/*
ID: tzhan1
PROG: race3
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

int main() {
	ofstream fout("race3.out");
	ifstream fin("race3.in");
	int N, tmpa, i, j, dis;
	vector<int> za[51];
	vector<int>::iterator iz;
	
	i = 0;
	while (1) {
		while (1) {
			fin >> tmpa;
			if (tmpa == i)	continue;
			if (tmpa < 0)	break;
			za[i].push_back(tmpa);
		}
		if (tmpa == -1)		break;
		++i;
	}
	N = i;

	vector<int> zc(N), zd(N), ze, zf;
	i = 2; ze.push_back(0); zc[0] = 1;
	while (1) {
		for (int k = 0; k < ze.size(); ++k)
			for (int l = 0; l < za[ze[k]].size(); ++l)
				if (!zc[za[ze[k]][l]] || zc[za[ze[k]][l]] > i) {
					zc[za[ze[k]][l]] = i;
					zd[za[ze[k]][l]] = ze[k];
					zf.push_back(za[ze[k]][l]);
		}
		ze = zf;
		zf.clear();
		if (!ze.size())		break;
		++i;
	}
	dis = i - 1;

	vector<int> zg;
	i = N - 1;
	while (zd[i]) {
		zg.push_back(zd[i]);
		i = zd[i];
	}
	zg.push_back(0);
	reverse(zg.begin(), zg.end());

	tmpa = 0;
	for (i = 1; i < zg.size(); ++i) {
		vector<bool> zb(N);
		ze.clear();		zf.clear();
		ze.push_back(zg[i - 1]);	zb[zg[i - 1]] = 1;
		while (1) {
			for (int k = 0; k < ze.size(); ++k) 
				for (int l = 0; l < za[ze[k]].size(); ++l)
					if (!zb[za[ze[k]][l]] && za[ze[k]][l] != zg[i]) {
						zb[za[ze[k]][l]] = 1;
						zf.push_back(za[ze[k]][l]);
			}
			ze = zf;
			zf.clear();
			if (!ze.size()) {
				tmpa = 0;
				break;
			}
			for (int k = i + 1; k < zg.size(); ++k)
				if (zb[zg[k]]) {
					tmpa = 1;
					zg.erase(zg.begin() + i);
					--i;
					break;
			}
			if (zb[N - 1] && !tmpa) {
				tmpa = 1;
				zg.erase(zg.begin() + i);
				--i;
			}
			if (tmpa == 1) {
				tmpa = 0;
				break;
			}
		}
	}

	cout << zg.size() - 1;
	for (iz = zg.begin() + 1; iz < zg.end(); ++iz) {
		cout << ' ' << *iz;
	}
	cout << endl;

	vector<int> zh(zg);
	zc = vector<int>(N);
	zh.push_back(N - 1);
	zc[N - 1] = zh.size();
	for (i = zh.size() - 2; i >= 0; --i) {
		tmpa = 0;
		ze.clear();		zf.clear();
		ze.push_back(zh[i]);
		if (zc[zh[i]] > i + 2) {
			int l = zc[zh[i]];
			zh.erase(zh.begin() + i + 1, zh.begin() + l - 1);
			for (int k = 0; k < zc.size(); ++k) {
				if (zc[k] > i + 2 && zc[k] <= l)
					zc[k] = i + 2;
				else if (zc[k] > l) {
					zc[k] -= l - i - 2;
				}
			}
		}
		zc[zh[i]] = i + 1;
		while (1) {
			for (int k = 0; k < ze.size(); ++k) {
				for (int l = 0; l < za[ze[k]].size(); ++l) {
					if (!zc[za[ze[k]][l]]) {
						zc[za[ze[k]][l]] = i + 2;
						zf.push_back(za[ze[k]][l]);
					}
					if (zc[za[ze[k]][l]] > i + 2) {
						j = zc[za[ze[k]][l]];
						tmpa = 1;
					}
				}
			}
			ze = zf;
			zf.clear();
			if (!ze.size())		break;
		}
		if (tmpa) {
			tmpa = 0;
			zh.erase(zh.begin() + i + 1, zh.begin() + j - 1);
			for (int k = 0; k < zc.size(); ++k) {
				if (zc[k] > i + 2 && zc[k] <= j)		zc[k] = i + 2;
				else if (zc[k] > j)		zc[k] -= j - i - 2;
			}
		}
	}

	sort(zg.begin(), zg.end());
	sort(zh.begin(), zh.end());
	fout << zg.size() - 1;
	for (iz = zg.begin() + 1; iz < zg.end(); ++iz) {
		fout << ' ' << *iz;
	}
	fout << endl << zh.size() - 2;
	for (iz = zh.begin() + 1; iz < zh.end() - 1; ++iz) {
		fout << ' ' << *iz;
	}
	fout << endl;

	return 0;
}