// Aho Corasick automaton. O(n) in size of Trie.
// Allows searching for a dictionary of patterns in a string. 
// Consider using DP[u, pos], for instance.

const int MAXN = 500000; // Sum of words*length
const int SZA = 26;		 // Alphabet size

map<int,int> adj[MAXN];	// Trie
int isEnd[MAXN];	// Example: How many words end at node u
int gid;				// Id of last node set
int f[MAXN];		// Aho Corasick failure function

void init(int id){
	isEnd[id] = 0;
	adj[id].clear();
}

void add(string s){
	int u = 0;	// Current node
	REP(p,0,sz(s)){
		int id = s[p] - 'a';
		if (!adj[u].count(id)){
			adj[u][id] = ++gid;	// Lazy initialization
			init(gid);
		}
		u = adj[u][id];
	}
	isEnd[u]++;
}

void build(){
   // BFS-DP Aho Corasick construction
	queue<int> q;
	f[0] = 0;
	REPIT(it, adj[0]){
		int u = it->snd;
		q.push(u);
		f[u] = 0;
	}
	while (!q.empty()){
		int e = q.front();
		q.pop();
		REPIT(it, adj[e]){
			int i = it->fst;
			int u = it->snd;	
			q.push(u);
			int v = f[e];
			while (v && !adj[v].count(i)) v = f[v];
			f[u] = (adj[v].count(i) ? adj[v][i] : 0);
			// Aggregate necessary information here
			// In general, S[u] += S[f[u]]
			isEnd[u] += isEnd[f[u]];
		}
	}
}

// Search string s for all strings in trie
ll search(string s){
	ll ans = 0;
	int u = 0;
	REP(p,0,sz(s)){
		int id = s[p] - 'a';
		while (u && !adj[u].count(id)) u = f[u];
		if (adj[u].count(id)) u = adj[u][id];
		ans += isEnd[u];
	}
	return ans;
}

int main(){
	gid = 0;
	init(0);
	// Ready for add(s), build(), search(t)	
	return 0;
}

