/*
ID: tzhan1
PROG: milk6
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

int zmaxc(vector<vector<pair<int, int>>> zb){
	int rt = 0, N = zb.size();
	
	while (1) {
		vector<int> qa(1), qb, pd(N, -1);
		
		pd[0] = 0;
		int tmpa = 1;
		while (1) {
			for (auto i = qa.begin(); i < qa.end(); ++i) {
				for (auto j = zb[*i].begin(); j < zb[*i].end(); ++j) {
					if ((*j).second > 0 && pd[(*j).first] == -1) {
						qb.push_back((*j).first);
						pd[(*j).first] = *i;
			}}}
			if (!qb.size() || pd[N - 1] != -1)		break;
			++tmpa;
			qa = qb;
			qb.clear();
		}
		if (pd[N - 1] == -1)		break;
		
		int i = N - 1, tmp = 2000001;
		while (i) {
			for (auto j = zb[pd[i]].begin(); j < zb[pd[i]].end(); ++j) {
				if ((*j).first == i) {
					if (tmp > (*j).second)		tmp = (*j).second;
					break;
			}}
			i = pd[i];
		}
		
		rt += tmp;
		i = N - 1;
		while (i) {
			for (auto j = zb[pd[i]].begin(); j < zb[pd[i]].end(); ++j) {
				if ((*j).first == i) {
					(*j).second -= tmp;
					break;
			}}
			auto j = zb[i].begin();
			for (; j < zb[i].end(); ++j) {
				if ((*j).first == pd[i]) {
					(*j).second += tmp;
					break;
			}}
			if (j == zb[i].end())
				zb[i].push_back(make_pair(pd[i], tmp));
			i = pd[i];
		}
	}
	
	return rt;
}

int zloop(vector<vector<pair<int, int>>>& zb,
		const vector<vector<int>>& za,
		vector<int> & kk,
		int cr, int stk, const int& mxstk, int mz) {
	for (int i = cr; i < za.size(); ++i) {
		if (za[i][2] > mz)		continue;
		int j = 0;
		for (; j < zb[za[i][0]].size(); ++j) {
			if (zb[za[i][0]][j].first == za[i][1]) {
				zb[za[i][0]][j].second -= za[i][2];
				if (zmaxc(zb) != mz - za[i][2]) {
					zb[za[i][0]][j].second += za[i][2];
					j = -1;
				}
				break;
		}}
		if (j == -1 || j == zb[za[i][0]].size())		continue;
		if (mz == za[i][2]) {
			kk.push_back(i + 1);
			return 1;
		}
		if (stk + 1 >= mxstk)		continue;
		kk.push_back(i + 1);
		if (zloop(zb, za, kk, i + 1, stk + 1, mxstk, mz - za[i][2]))
			return 1;
		kk.pop_back();
		zb[za[i][0]][j].second += za[i][2];
	}
	return 0;
}

int main() {
	ofstream fout("milk6.out");
	ifstream fin("milk6.in");
	int N, M, tmpa, i, j;
	
	fin >> N >> M;
	vector<vector<int>> za(M);
	vector<vector<pair<int, int>>> zb(N), zd(N);
	
	for (i = 0; i < M; ++i) {
		vector<int> tmp(3);
		fin >> tmp[0] >> tmp[1] >> tmp[2];
		--tmp[0]; --tmp[1];
		za[i] = tmp;
		if (tmp[0] == tmp[1] || tmp[0] == N - 1)		continue;
		
		for (j = 0; j < zb[tmp[0]].size(); ++j)
			if (tmp[1] == zb[tmp[0]][j].first) {
				zb[tmp[0]][j].second += tmp[2];
				zd[tmp[0]][j].second += tmp[2] + 1;
				break;
			}
		if (j == zb[tmp[0]].size()) {
			zb[tmp[0]].push_back(make_pair(tmp[1], tmp[2]));
			zd[tmp[0]].push_back(make_pair(tmp[1], tmp[2] + 1));
		}
	}
	
	int rz = zmaxc(zb), mxstk = zmaxc(zd) - rz;
	fout << rz << ' ' << mxstk << endl;
	
	vector<int> kk;
	zloop(zb, za, kk, 0, 0, mxstk, rz);
	
	for (int l = 0; l < mxstk; ++l)
		fout << kk[l] << endl;
	
	return 0;
}