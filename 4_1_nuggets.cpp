/*
ID: tzhan1
PROG: nuggets
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int ZGCD(const int *p, const int &N){
	int a=*p,i,b,c;
	for(i=1;i<N;++i){
		b = a<*(p+i)?a:*(p+i);
		c = a>*(p+i)?a:*(p+i);
		while(b){
			c %= b;
			b ^= c;	c ^= b;	b ^= c;
		}
		a = c;
	}
	return a;
}

int ZGCD(int a, int b){
	if(a > b){	a ^= b;	b ^= a;	a ^= b;	}
	while(a){
		b %= a;
		a ^= b;	b ^= a;	a ^= b;
	}
	return b;
}

int main()
{
	ofstream fout("nuggets.out");
	ifstream fin("nuggets.in");
	int N,tmpa,i,j,za[10],zmod[256],zp[256],M,*p,rez;
	
	(fin >> N).get();
	
	for(i=0;i<N;++i)	fin >> za[i];
	sort(za, za + N);
	M = *za;
	
	if(N == 1 || M == 1 || ZGCD(za,N) - 1){
		fout << "0\n";
		return 0;
	}
	
	*zmod = *zp = 0;
	for(i=1;i<M;++i)	zmod[i] = zp[i] = 0x7fffffff;
	
	for(i=1;i<N;++i){
		if(!(*(za + i)%M))		continue;
		
		for(j=0;j<M;++j){
			if(zp[j] == 0x7fffffff)		break;
			
			tmpa = zp[j] + za[i];
			if(zmod[tmpa%M] > tmpa){
				p = find(zp, zp + M, zmod[tmpa%M]);
				*p = zmod[tmpa%M] = tmpa;
				sort(zp, zp + M);
			}
		}
	}
	
	fout << zp[M - 1] - M << "\n";
	
	return 0;
}