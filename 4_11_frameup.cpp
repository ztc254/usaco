/*
ID: tzhan1
PROG: frameup
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

void zloop(const vector<vector<int>>& zd, 
	vector<int>& kk, 
	vector<vector<int>>& vkk,
	vector<bool>& tp,
	const int &L) {
	if (kk.size() == L) {
		vkk.push_back(kk);
		return;
	}
	vector<bool> aa(L);
	for (int i = 0; i < L; ++i) {
		if (tp[i])		continue;
		for (int v : zd[i])
			aa[v] = 1;
	}
	for (int i = 0; i < L; ++i) {
		if (aa[i] || tp[i])		continue;
		kk.push_back(i);
		tp[i] = 1;
		zloop(zd, kk, vkk, tp, L);
		tp[i] = 0;
		kk.pop_back();
	}
}

int main() {
	ofstream fout("frameup.out");
	ifstream fin("frameup.in");
	int N, M, L = 0, tmpa, i, j, za[30][30], zb[26][4], zcx[26] = { 0 };
	
	(fin >> N >> M).get();
	vector<int> zc;
	
	for (i = 0; i < 26; ++i) {
		zb[i][0] = N;
		zb[i][1] = 0;
		zb[i][2] = M;
		zb[i][3] = 0;
	}
	
	for (i = 0; i < N; ++i) {
		for (j = 0; j < M; ++j) {
			int tmp = fin.get() - 'A';
			za[i][j] = tmp;
			if (za[i][j] == '.' - 'A') {
				za[i][j] = -1;
				continue;
			}
			if (!zcx[tmp]) {
				zcx[tmp] = 1;
				zc.push_back(tmp);
				++L;
			}
			if (zb[tmp][0] > i)		zb[tmp][0] = i;
			if (zb[tmp][1] < i)		zb[tmp][1] = i;
			if (zb[tmp][2] > j)		zb[tmp][2] = j;
			if (zb[tmp][3] < j)		zb[tmp][3] = j;
		}
		fin.get();
	}
	
	sort(zc.begin(), zc.end());
	for (i = 0; i < L; ++i)
		zcx[zc[i]] = i;
	vector<vector<int>> zd(L);
	
	for (int i = 0; i < L; ++i) {
		for (j = zb[zc[i]][0]; j <= zb[zc[i]][1]; ++j) {
			if (za[j][zb[zc[i]][2]] != zc[i])
				if (find(zd[i].begin(), zd[i].end(), zcx[za[j][zb[zc[i]][2]]]) == zd[i].end())
					zd[i].push_back(zcx[za[j][zb[zc[i]][2]]]);
			if (za[j][zb[zc[i]][3]] != zc[i])
				if (find(zd[i].begin(), zd[i].end(), zcx[za[j][zb[zc[i]][3]]]) == zd[i].end())
					zd[i].push_back(zcx[za[j][zb[zc[i]][3]]]);
		}
		for (j = zb[zc[i]][2] + 1; j < zb[zc[i]][3]; ++j) {
			if (za[zb[zc[i]][0]][j] != zc[i])
				if (find(zd[i].begin(), zd[i].end(), zcx[za[zb[zc[i]][0]][j]]) == zd[i].end())
					zd[i].push_back(zcx[za[zb[zc[i]][0]][j]]);
			if (za[zb[zc[i]][1]][j] != zc[i])
				if (find(zd[i].begin(), zd[i].end(), zcx[za[zb[zc[i]][1]][j]]) == zd[i].end())
					zd[i].push_back(zcx[za[zb[zc[i]][1]][j]]);
		}
	}
	
	vector<int> kk;
	vector<vector<int>> vkk;
	vector<bool> tp(L);
	zloop(zd, kk, vkk, tp, L);
	
	for (auto v : vkk) {
		for (auto vv : v)
			fout << char(zc[vv] + 'A');
		fout << endl;
	}
	
	return 0;
}