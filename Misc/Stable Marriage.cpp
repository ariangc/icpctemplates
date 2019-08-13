// Stable Marriage Problem
#define N 505
int n;
int pref_men[N][N], pref_women[N][N], inv[N][N];
int cont[N], husband[N], wife[N];
void stable_marriage(){
	REP(i,0,n) REP(j,0,n) inv[i][pref_women[i][j]] = j;
	clr(cont, 0);
	clr(husband, -1);
	int m, w, dumped;
	REP(i,0,n){
		m = i;
		while(m >= 0){
			while(1){
				w = pref_men[m][cont[m]];
				++cont[m];
				if(husband[w] < 0 || inv[w][m] < inv[w][husband[w]])
					break;
			}
			dumped = husband[w];
			husband[w] = m;
			wife[m]=  w;
			m = dumped;
		}
	}
}
