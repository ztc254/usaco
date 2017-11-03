/*
ID: tzhan1
PROG: ditch
LANG: C++
*/
//Key: find the MAXIMUM available path, instead of any path.
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

int main(){
	ofstream fout("ditch.out");
	ifstream fin("ditch.in");
	int N,M,tmpa,i,j,za[200]={0},zb[200][200],zc[200][200]={0},k,rez,stm,zd[200]={0},zf[200]={0},zg[200]={0},*tpa;
	
	(fin >> N >> M).get();
	
	rez = 0;
	for(i=0;i<N;++i){
		fin >> tmpa >> j >> k;
		--tmpa;	--j;
		if(!k || !j || tmpa == j || tmpa == M - 1)		continue;
		if(!tmpa && j == M - 1){
			rez += k;
			continue;
		}
		if(zc[tmpa][j])
			zc[tmpa][j] += k;
		else{
			zc[tmpa][j] = k;
			zb[tmpa][ za[tmpa] ] = j;
			++za[tmpa];
		}
	}
	
	while(1){
		for(i=0;i<M;++i)		zd[i] = 1;
		memset(zf, 0, sizeof(int) * M);
		memset(zg, 0, sizeof(int) * M);
		
		zd[0] = 1;
		j = zb[0][0];
		tmpa = zc[0][j];
		for(i=0;i<za[0];++i){
			zf[ zb[0][i] ] = zc[0][ zb[0][i] ];
			zg[ zb[0][i] ] = 0;
			if(zc[0][ zb[0][i] ] > tmpa)	j = zb[0][i];
		}
		
		while(j != M - 1 && zd[j]){
			zd[j] = 0;
			for(i=0;i<za[j];++i){
				tmpa = zc[j][ zb[j][i] ] < zf[j] ? zc[j][ zb[j][i] ] : zf[j];
				if(tmpa > zf[ zb[j][i] ]){
					zf[ zb[j][i] ] = tmpa;
					zg[ zb[j][i] ] = j;
				}
			}
			tmpa = 0;
			for(i=0;i<M;++i){	if(zd[i])	if(zf[i] > tmpa){
				tmpa = zf[i];
				j = i;
			}}
		}
		
		if(j != M - 1)		break;
		
		stm = zf[M - 1];
		rez += stm;
		
		i = M - 1;
		while(i){
			zc[ zg[i] ][i] -= stm;
			if(!zc[ zg[i] ][i]){
				tpa = find(zb[ zg[i] ], zb[ zg[i] ] + za[ zg[i] ], i);
				if(tpa == zb[ zg[i] ] + za[ zg[i] ])	cerr<<"Sigh...\n";
				*tpa = zb[ zg[i] ][ za[ zg[i] ] - 1];
				--za[ zg[i] ];
			}
			
			if(i != M - 1 && zg[i]){
				if(!zc[i][ zg[i] ]){
					zb[i][ za[i] ] = zg[i];
					++za[i];
				}
				zc[i][ zg[i] ] += stm;
			}
			i = zg[i];
		}
	}
	
	fout << rez << '\n';
	
	return 0;
}