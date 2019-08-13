// adamant's palindromic tree online O(n*log(|E|)) construction
// Tutorial: http://adilet.org/blog/25-09-14/
// Add/Delete operation can be supported in O(logn) by doing
// check(link[v]), v = slink[v] in get_link
// (periodicity -> same initial char)
const int maxn = 5e5, sigma = 26, INF = 1e9;
int s[maxn], len[maxn], link[maxn], to[maxn][sigma];
int n, last, sz;
// All these optional (palindromic factoring)
int d[maxn], slink[maxn], dpe[maxn], dpo[maxn];
int anse[maxn], anso[maxn], prve[maxn], prvo[maxn];

void init(){ // Call with n=0
	s[n++] = -1;
	link[0] = 1;
	len[1] = -1;
	sz = 2;	
	anse[0] = 0;
	anso[0] = INF;
}

int get_link(int v){
	while(s[n - len[v] - 2] != s[n - 1]) v = link[v];
	return v;
}

ii getmin(int v, int* ans, int* dp, int* prv){
	dp[v] = ans[n - (len[slink[v]] + d[v]) - 1];
	int best = n - (len[slink[v]] + d[v]) - 1;
	if (d[v] == d[link[v]]){
		if (dp[v] > dp[link[v]]){
			dp[v] = dp[link[v]];
			best = prv[n-1-d[v]];
		}
	}
	return mp(dp[v] + 1, best);
}	

void add_letter(int c){
	s[n++] = c;
	last = get_link(last);
	if(!to[last][c]) {
		len [sz] = len[last] + 2;
		link[sz] = to[get_link(link[last])][c];
		d[sz] = len[sz] - len[link[sz]];
		if (d[sz] == d[link[sz]]) slink[sz] = slink[link[sz]];
		else slink[sz] = link[sz];
		to[last][c] = sz++;	
	}
	last = to[last][c];
	
	anse[n-1] = INF;
	for (int v = last; len[v] > 0; v = slink[v]){
		ii acte = getmin(v, anso, dpe, prve);
		if (act.fst < anse[n-1]){
			anse[n-1] = act.fst;
			prve[n-1] = act.snd;
		}
	}
	
	anso[n-1] = INF;
	for (int v = last; len[v] > 0; v = slink[v]){
		ii act = getmin(v, anse, dpo, prvo);
		if (act.fst <= anso[n-1]){
			anso[n-1] = act.fst;
			prvo[n-1] = act.snd;
		}
	}
}
