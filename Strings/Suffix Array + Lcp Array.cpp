// O(nlog^2n) fast suffix array, 0.6s for N = 10^6
const int MAXN = 1000010;  
const int MAXLG = 25;

// r is the list of sorted suffixes.
// p is the position of i in the sorted list
int n,t;
int p[MAXN],r[MAXN],h[MAXN];    
char s[MAXN];                   
int rmq[MAXLG][MAXN];
int flog2[MAXN];

void fix_index(int b, int e){
	int lastpk, pk, d;
	lastpk = p[r[b]+t];
	d = b;
	REP(i,b,e){
		if (((pk = p[r[i]+t]) != lastpk) 
			&& (b > lastpk || pk >= e)){
			lastpk = pk;
			d = i;
		}
		p[r[i]]= d;
	}
}

// Computes the r and p in O(n*log^2(n))
void suff_arr(){
	int bc[256];
	REP(i,0,256) bc[i]=0;
	REP(i,0,n) bc[(int)s[i]]++;
	REP(i,1,256) bc[i] += bc[i-1];
	for (int i = n-1; i >= 0; i--) r[--bc[(int)s[i]]] = i;
	for (int i = n-1; i >= 0; i--) p[i] = bc[(int)s[i]];
	for (t = 1; t < n; t<<=1){
		for (int i = 0, j = 1; i < n; i = j++){
			while (j < n && p[r[j]] == p[r[i]]) ++j;
			if (j-i > 1){
				sort(r+i, r+j, [&](const int& i, const int& j){
					return p[i+t] < p[j+t];
				});
				fix_index(i, j);        
			}
		}
	}
}

// Computes the LCP array in O(n) by Kasai-LCP
void initlcp(){
	int tam = 0, j;
	REP(i,0,n-1){
		j = r[p[i]-1];
		while(s[i+tam] == s[j+tam]) ++tam;
		h[p[i]-1] = tam;
		if (tam > 0) --tam;
	}
}

// Creates the full LCP by RMQ in O(n*log(n))
void makelcp(){
	initlcp();
	REP(i,0,n-1) rmq[0][i] = h[i];
	int lg = 0, pw = 1;
	do{
		REP(i,pw,pw*2) flog2[i] = lg;
		lg++; pw*=2;
		REP(i,0,n-1){
			if (i+pw/2 < n-1) 
				rmq[lg][i] = min(rmq[lg-1][i], rmq[lg-1][i+pw/2]);
			else 
				rmq[lg][i] = rmq[lg-1][i];
		}
	}while(pw < n);
}

// LCP in interval [i,j] of the suffix array
int lcp(int i, int j){
	if (i == j) return n - r[i] - 1;
	int lg = flog2[j-i], pw = (1<<lg);
	return min(rmq[lg][i], rmq[lg][j-pw]);
}

int main(){
	scanf("%s%n", s, &n);
	s[n++] = '$';
	suff_arr();
	makelcp();
	return 0;
}
