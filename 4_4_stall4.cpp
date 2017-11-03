/*
ID: tzhan1
PROG: stall4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

int main(){
	ofstream fout("stall4.out");
	ifstream fin("stall4.in");
	int N,M,tmpa,i,j,za[200]={0},zb[200]={0},zc[200][200]={0},zd[200][200]={0},k,rez,tmpb,tmpc;
	
	(fin >> N >> M).get();
	
	tmpa = 1;
	for(i=0;i<N;++i){
		fin >> za[i];
		for(j=0;j<za[i];++j){
			fin >> tmpa;
			++zb[--tmpa];
			zc[i][tmpa] = 1;
			tmpa = 0;
		}
	}
	if(tmpa){
		fout << "0\n";
		return 0;
	}
	
	rez = 0;
	tmpa = N * M;	tmpb = tmpc = 0;
	for(i=0;i<N;++i)	for(j=0;j<M;++j){
		if(zc[i][j]){
			zd[i][j] = za[i] + zb[j] - 1;
			if(zd[i][j] < tmpa){
				tmpa = zd[i][j];	tmpb = i;	tmpc = j;
			}
		}
	}
	za[tmpb] = 0;	zb[tmpc] = 0;
	for(i=0;i<N;++i){
		if(!za[i])		continue;
		for(j=0;j<N;++j){
			if(!zb[j])		continue;
			zd[i][j] -= zc[tmpb][j] + zc[i][tmpc];
		}
	}
	++rez;
	
	while(1){
		tmpa = N * M;
		for(i=0;i<N;++i){
			if(!za[i])		continue;
			for(j=0;j<N;++j){
				if(!zb[j])		continue;
				if(zc[i][j] && zd[i][j] < tmpa){
					tmpa = zd[i][j];	tmpb = i;	tmpc = j;
				}
			}
		}
		
		if(tmpa == N * M)		break;
		++rez;
		
		za[tmpb] = 0;	zb[tmpc] = 0;
		for(i=0;i<N;++i){
			if(!za[i])		continue;
			for(j=0;j<N;++j){
				if(!zb[j])		continue;
				zd[i][j] -= zc[tmpb][j] + zc[i][tmpc];
			}
		}
	}
	
	fout << rez << '\n';
	
	return 0;
}