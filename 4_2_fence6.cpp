/*
ID: tzhan1
PROG: fence6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <queue>

using namespace std;

class Zl{
	public:
	int s;
	int e;
	int l;
	int b[4];
	void giveval(int x, int y, int z){
		s = x;	e = y;	l = z;
	}
};

int main(){
	ofstream fout("fence6.out");
	ifstream fin("fence6.in");
	int N,tmpa,i,j,za[100],zb[100][2],zc[100][2][8],zd[120],ze[120][9],zf[100][2],M,k,l,tmpb,tpa[4],st,ed,vl,rez;
	queue<Zl> p;
	Zl zxa,zxb;
	
	(fin >> N).get();
	
	for(i=0;i<N;++i){
		fin >> tmpa;
		--tmpa;
		fin >> za[tmpa];
		(fin >> zb[tmpa][0] >> zb[tmpa][1]).get();
		for(j=0;j<zb[tmpa][0];++j){
			fin >> zc[tmpa][0][j];
			--zc[tmpa][0][j];
		}
		sort(zc[tmpa][0],zc[tmpa][0] + zb[tmpa][0]);
		for(j=0;j<zb[tmpa][1];++j){
			fin >> zc[tmpa][1][j];
			--zc[tmpa][1][j];
		}
		sort(zc[tmpa][1],zc[tmpa][1] + zb[tmpa][1]);
	}
	
	j=0;
	for(i=0;i<N;++i){
		for(k=0;k<2;++k)	if(zb[i][k] <= 8){
			zd[j] = zb[i][k] + 1;
			ze[j][0] = i;
			for(l=1;l<zd[j];++l){
				ze[j][l] = zc[i][k][l-1];
				if(zc[ ze[j][l] ][0][0] == i){
					zb[ ze[j][l] ][0] += 8;
					zf[ ze[j][l] ][0] = j;
				}
				else{
					zb[ ze[j][l] ][1] += 8;
					zf[ ze[j][l] ][1] = j;
				}
			}
			zb[i][k] += 8;
			zf[i][k] = j;
			++j;
		}
	}
	M = j;
	
	rez = 0;
	for(i=0;i<M;++i){
		for(j=0;j<zd[i];++j){
			tmpa = ze[i][j];
			k = zf[tmpa][0]==i?1:0;
			k = zf[tmpa][k];
			if(k<i)		continue;
			zxa.giveval(0,k,za[tmpa]);
			memset(zxa.b, 0, sizeof(int) * 4);
			zxa.b[i / 30] |= 1 << (i%30);
			zxa.b[k / 30] |= 1 << (k%30);
			p.push(zxa);
		}
		
		while(!p.empty()){
			memcpy(tpa, p.front().b, sizeof(int) * 4);
			st = p.front().s;
			ed = p.front().e;
			vl = p.front().l;
			p.pop();
			
			for(j=0;j<zd[ed];++j){
				tmpa = ze[ed][j];
				k = zf[tmpa][0]==ed?1:0;
				k = zf[tmpa][k];
				if(k<i)		continue;
				if(k==i){
					if(!st)		continue;
					l = za[tmpa] + vl;
					if(!rez)	rez = l;
					else		rez = rez<l?rez:l;
					continue;
				}
				if( ( tpa[k / 30] >> (k%30) ) & 1 )		continue;
				
				tpa[k / 30] |= 1 << (k%30);
				zxa.giveval(st+1,k,vl + za[tmpa]);
				memcpy(zxa.b, tpa, sizeof(int) * 4);
				p.push(zxa);
			}
		}
	}
	
	fout << rez << '\n';
	
	return 0;
}