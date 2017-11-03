/*
ID: tzhan1
PROG: ditch
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <stack>

using namespace std;

class Zl{
	public:
	int e;
	int l;
	short b[200];
	void giveval(int x, int y){
		e = x;	l = y;
	}
};

int main(){
	ofstream fout("ditch.out");
	ifstream fin("ditch.in");
	int N,M,tmpa,i,j,za[200],zb[200][200],zc[200][200]={0},k,l,rez,stm,*tpb,idc,idca[3],rtmp,mm;
	short zd[200],*tpc;
	stack<Zl> p;
	Zl zxa,zxb,zxc;
	
	(fin >> N >> M).get();
	
	rez = 0;
	for(i=0;i<N;++i){
		fin >> tmpa >> j >> k;
		--tmpa;	--j;
		if(!k || !j || tmpa == j)		continue;
		if(!tmpa && j == M - 1){
			rez += k;
			continue;
		}
		if(zc[tmpa][j])
			zc[tmpa][j] += k;
		else{
			zc[tmpa][j] = k;
			zb[tmpa][ za[tmpa]%M ] = j;
			++za[tmpa];
			if(j == M - 1)		za[tmpa] += M;
		}
	}
	
	for(i=0;i<*za%M;++i){
		zxa.giveval(zb[0][i], 1);
		zxa.b[0] = zb[0][i];
		p.push(zxa);
	}
	
	rtmp = 0;
	while(1){
		//cout << "@@\n";
		idc = 0;
		idca[0] = -2;
		while(!p.empty()){
			++rtmp;
			if(idc && idca[0] != -2){
				if(idca[0] == -1)		if(idca[2] == p.top().b[0]){
					//cout << (int)idca[2] << ' ' << (int)zc[0][idca[2]] << "^^\n";
					p.pop();
					continue;
				}
				else if(idca[0] < p.top().l - 1)	 if(idca[1] == p.top().b[idca[0]] && idca[2] == p.top().b[idca[0] + 1]){
					//cout << (int)idca[1] << ' ' << (int)idca[2] << ' ' << (int)zc[idca[1]][idca[2]] << "^^\n";
					p.pop();
					continue;
				}
			}
			
			i = p.top().e;
			j = p.top().l;
			memcpy(zd, p.top().b, sizeof(short) * j);
			p.pop();
			
			
			if(!idc || za[i] >= M){
				idc = 1;
				
				stm = zc[0][*zd];
				for(k = 0;k < j - 1;++k){
					//cout << (int)*tpc << ' '<<(int)*(tpc + 1) << ' '<<zc[*tpc][*(tpc + 1)]<<"@$#\n";
					if(stm > zc[zd[k]][zd[k + 1]])		stm = zc[zd[k]][zd[k + 1]];
					if(!stm){
						if(!zc[zd[k]][zd[k + 1]]){
							idca[0] = k;
							idca[1] = zd[k];
							idca[2] = zd[k + 1];
							//cout << (int)zd[k] << ' '<<(int)zd[k + 1] << ' '<<k<<"@$#\n";
						}
						else if(!zc[0][zd[0]]){
							idca[0] = -1;
							idca[1] = 0;
							idca[2] = zd[0];
							//cout << '0' << ' '<<(int)zd[0] << ' '<<"@$#\n";
						}
						else{
							cerr << "What?\n";
							return 0;
						}
						
						break;
					}
				}
				if(!stm)	continue;
				//cout<<"~~"<<stm<<"@#\n";
			}
			
			for(k=0;k<za[i]%M;++k){
				if(zb[i][k] == M - 1){
					if(stm > zc[zd[j - 1]][M - 1])		stm = zc[zd[j - 1]][M - 1];
					
					if(stm){
						rez += stm;
						for(mm = 0;mm < j;++mm)	cout<<zd[mm] << ' ';
						cout<<"~~~~"<<stm<<"@#\n";
						
						
						zxb.giveval(i,j);
						memcpy(zxb.b, zd, sizeof(short) * j);
						p.push(zxb);
					}
					//while(!p.empty())		p.pop();
					i = -1;
					break;
				}
				if(find(zd, zd + j, zb[i][k]) != zd + j)	continue;
				
				zxa.giveval(zb[i][k], j + 1);
				memcpy(zxa.b, zd, sizeof(short) * j);
				zxa.b[j] = zb[i][k];
				p.push(zxa);
				//if(p.size()>400)	cout<< p.size()<<"\n";
			}
			//cout << "@@2\n";
			idc = 0;
			idca[0] = -2;
			if(i == -1)	break;
		}
		//cout << "!!\n";
		if(p.empty())	break;
		
		
		if(stm)		for(i=0;i<=zxb.l;++i){
			j = i ? zxb.b[i-1] : 0;
			k = (i==zxb.l)? M - 1 : zxb.b[i];
			zc[j][k] -= stm;
			if(!zc[j][k]){
				tpb = find(zb[j], zb[j] + za[j]%M, k);
				if(tpb == zb[j] + za[j]%M)	continue;
				for(;tpb != zb[j] + za[j]%M - 1;tpb++)	*tpb = *(tpb + 1);
				--za[j];
				if(k == M - 1)	za[j] -= M;
			}
			
			if(!j || k == M - 1)	continue;
			zc[k][j] += stm;
			if(zc[k][j] == stm){
				zb[k][za[k]%M] = j;
				++za[k];
			}
		}
	}
	
	fout << rez << '\n';
	
	return 0;
}