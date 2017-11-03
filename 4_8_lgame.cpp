/*
ID: tzhan1
PROG: lgame
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

const int dicti[26] = { 2,5,4,4,1,6,5,5,1,7,
6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7 };

bool zcomp(char &x, char &y) {
	if(dicti[x - 'a'] != dicti[y - 'a'])
		return dicti[x - 'a'] < dicti[y - 'a'];
	return x < y;
}

bool zchksub(int x, int y, int* zc, const int &N) {
	for (int i = N - 1; i >= 0; --i) {
		if (y%(zc[i] + 1) > x%(zc[i] + 1))		return false;
		x /= zc[i] + 1; y /= zc[i] + 1;
	}
	return true;
}

int zclc(int x, int *zb, int *zc, const int &N) {
	int rt = 0;
	for (int i = N - 1; i >= 0; --i) {
		rt += x % (zc[i] + 1) * dicti[zb[i] - 'a'];
		x /= zc[i] + 1;
	}
	return rt;
}

int main() {
	ofstream fout("lgame.out");
	ifstream fin("lgame.in"), gin("lgame.dict");
	int N, M, tmpa, i, j, zb[7] = { 0 }, zc[7] = { 0 }, arl;
	string za;
	
	fin >> za;
	M = za.length();
	sort(za.begin(), za.end(), zcomp);
	
	j = 0; arl = 1;
	zb[0] = za[0]; ++zc[0];
	for (i = 1; i < M; ++i) {
		if (za[i] != zb[j]) {
			arl *= zc[j] + 1;
			zb[++j] = za[i];
		}
		++zc[j];
	}
	arl *= zc[j] + 1;
	N = j + 1;
	tmpa = 1;
	
	i = 0;
	string s;
	vector<string> vdc;
	vector<vector<int>> mdc(arl);
	vector<bool> zd(arl);
	while (1) {
		gin >> s;
		if (s == ".")		break;
		if (s.length() > M)		continue;
		int tmp[7] = { 0 }, tp = 0, tx = 0;
		for (int k = 0; k < N; ++k) {
			tmpa = count(s.begin(), s.end(), zb[k]);
			if (tmpa > zc[k]) {
				tmpa = -1;
				break;
			}
			tmp[k] = tmpa;
			tp += tmpa;
			if (k > 0)		tx *= zc[k] + 1;
			tx += tmpa;
		}
		if (tmpa == -1 || tp != s.length())		continue;
		vdc.push_back(s);
		mdc[tx].push_back(vdc.size() - 1);
		zd[tx] = 1;
	}
	
	vector<vector<vector<int>>> mp(arl);
	for (i = 0; i < arl; ++i)	if (zd[i])
		mp[i].push_back(vector<int>(1, i));

	int mxx = 0;
	vector<int> mxi;
	for (i = 1; i < arl; ++i) {
		for (j = 1; j <= i / 2; ++j) {
			if (!zchksub(i, j, zc, N) || !zd[j] || !zd[i - j])
				continue;
			zd[i] = 1;
			for (int k = 0; k < mp[j].size(); ++k)
				for (int l = 0; l < mp[i - j].size(); ++l) {
					vector<int> tmp = mp[j][k];
					tmp.insert(tmp.end(), mp[i - j][l].begin(), mp[i - j][l].end());
					sort(tmp.begin(),tmp.end());
					mp[i].push_back(tmp);
			}
			sort(mp[i].begin(), mp[i].end());
			mp[i].erase(unique(mp[i].begin(), mp[i].end()), mp[i].end());
		}
		if (zd[i]) {
			int tmp = zclc(i, zb, zc, N);
			if (tmp > mxx) {
				mxi.clear();
				mxx = tmp;
				mxi.push_back(i);
			}
			else if (tmp == mxx)	mxi.push_back(i);
		}
	}

	fout << mxx << endl;
	vector<string> rz;
	for (const auto& mx : mxi) {
		for (const auto& v : mp[mx]) {
			vector<string> tmp;
			vector<int> tp(v.size());
			while (1) {
				tmp.clear();
				tmp.push_back(vdc[mdc[v[0]][tp[0]]]);
				for (i = 1; i < v.size(); ++i)
					tmp.push_back(vdc[mdc[v[i]][tp[i]]]);
				sort(tmp.begin(), tmp.end());
				string tq(tmp[0]);
				for (vector<string>::iterator k = tmp.begin() + 1; k < tmp.end(); ++k)
					tq = tq + ' ' + *k;
				rz.push_back(tq);

				i = v.size() - 1;
				while (1) {
					if (++tp[i] < mdc[v[i]].size())		break;
					tp[i--] = 0;
					if (i < 0)		break;
				}
				if (i < 0)		break;
			}
		}
	}
	sort(rz.begin(), rz.end());
	for (vector<string>::iterator k = rz.begin(); k < rz.end(); ++k)
		fout << *k << endl;

	return 0;
}