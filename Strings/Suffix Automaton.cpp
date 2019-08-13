// O(n) Online suffix automaton construction
// len[u]: Max length of a string accepted by u
// link[u]: Suffix link of u
// Link edges give the suffix tree of reverse(s)
// Terminal nodes can be obtained by
// 	traversing last's links

const int MAX = 1000000;
int len[MAX*2];
int link[MAX*2];
map<char,int> adj[MAX*2];
int sz, last;

// To reuse, clear adj[]
void sa_init() {
	sz = last = 0;
	len[0] = 0;
	link[0] = -1;
	sz++;
}

void sa_extend (char c) {
	int cur = sz++;
	len[cur] = len[last] + 1;
	int p;
	for (p=last; p!=-1 && !adj[p].count(c); p = link[p])
		adj[p][c] = cur;
	if (p == -1)
		link[cur] = 0;
	else {
		int q = adj[p][c];
		if (len[p] + 1 == len[q])
			link[cur] = q;
		else {
			int clone = sz++;
			len[clone] = len[p] + 1;
			adj[clone] = adj[q];
			link[clone] = link[q];
			for (; p != -1 && adj[p][c] == q; p = link[p])
				adj[p][c] = clone;
			link[q] = link[cur] = clone;
		}
	}
	last = cur;
}
