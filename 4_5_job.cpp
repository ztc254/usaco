/*
ID: tzhan1
PROG: job
LANG: C++
*/
/* Missed an EXTREMELY simple method:
minimize the result on each adding-up step. */

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <cmath>

int z_calc1(int x, int * za, const int& M1) {
	int tmpa = 0, i = 0;
	for (; i<M1; ++i) {
		if (!za[i]) { std::cerr << "OMG y!\n";	return -1; }
		tmpa += x / za[i];
	}
	return tmpa;
}

using namespace std;

int main() {
	ofstream fout("job.out");
	ifstream fin("job.in");
	int N, M1, M2, tmpa, i, j, za[30], zb[30], zc[20001] = { 0 }, zd[30], ze[30][4] = { 0 }, rez, ren, ra, rb, tmpb, cntr;

	(fin >> N >> M1 >> M2).get();

	for (i = 0; i<M1; ++i)		(fin >> za[i]).get();
	for (i = 0; i<M2; ++i)		(fin >> zb[i]).get();
	sort(za, za + M1);
	sort(zb, zb + M2);

	for (i = 0; i<M2; ++i)	zd[i] = -1;

	ra = ceil(1.0 * N / M1) * za[M1 - 1];
	rb = ra / 2;

	if (z_calc1(ra, za, M1) - N) {
		while ((tmpa = z_calc1(rb, za, M1)) >= N) {
			if (tmpa == N)	break;
			ra = rb;
			rb = ra / 2;
		}
		if (tmpa == N)	ra = rb;
		else {
			while ((tmpa = (ra + rb) / 2) != rb) {
				if (z_calc1(tmpa, za, M1) < N)	rb = tmpa;
				else	ra = tmpa;
			}
		}
	}

	fout << ra << ' ' << flush;

	rb = z_calc1(ra, za, M1) - N;
	for (i = 0; i<M1; ++i) {
		for (j = 1; j <= ra / za[i]; ++j) {
			++zc[j * za[i]];
		}
	}
	zc[ra] -= rb;

	cntr = 0;
	for (i = za[0]; i <= ra; ++i) {
		cntr += zc[i];
		for (j = 0; j<M2; ++j) {
			if (zd[j] + 1)		++zd[j];
			if (zd[j] == zb[j]) {
				ze[j][0] = i;
				zd[j] = cntr ? 0 : -1;
				if (cntr) {
					--cntr;
					++ze[j][2];
				}
			}
			if (zd[j] == -1 && cntr) {
				--cntr;
				zd[j] = 0;
				ze[j][1] = ze[j][0];
				ze[j][0] = i;
				ze[j][2] = 1;
			}
		}
	}
	
	if (cntr)	for (; i<40001; ++i) {
		for (j = 0; j<M2; ++j) {
			if (zd[j] + 1)		++zd[j];
			if (zd[j] == zb[j]) {
				ze[j][0] = i;
				++ze[j][2];
				zd[j] = 0;
				--cntr;
			}
			if (!cntr) {
				i = 40002;
				break;
			}
		}
	}
	
	rez = 0;
	for (i = 0; i < M2; ++i) {
		if (zd[i] + 1) 		ze[i][0] += zb[i];
		ze[i][3] = ze[i][0] - ze[i][2] * zb[i];
		if (ze[i][0] > rez) {
			ren = i;
			rez = ze[i][0];
		}
	}
	
	while (1) {
		i = ren;
		for (j = 0; j < M2; ++j) {
			if (j == i)		continue;
			tmpa = ze[j][0] - ze[j][3];
			tmpb = ze[i][0] - ze[i][3];
			if (tmpa < tmpb && ze[j][3]<ze[i][3] && ze[j][3]>ze[i][1] && 
				max(ze[j][3] + tmpb, ze[i][3] + tmpa) < min(ze[j][0] + zb[j], ze[i][0])) {
				
				swap(ze[i][3], ze[j][3]);
				swap(ze[i][2], ze[j][2]);
				ze[i][0] = ze[i][3] + ze[i][2] * zb[i];
				ze[j][0] = ze[j][3] + ze[j][2] * zb[j];
				break;
			}
			else if (ze[j][0] + zb[j] < ze[i][0] && ze[i][2] > 1) {
				ze[j][0] += zb[j];
				++ze[j][2];
				ze[i][0] -= zb[i];
				--ze[i][2];
				break;
			}
		}
		if (j == M2)		break;
		rez = 0;
		for (i = 0; i < M2; ++i)	if (ze[i][0] > rez) {
			rez = ze[i][0];
			ren = i;
		}
	}

	fout << rez << "\n";

	return 0;
}