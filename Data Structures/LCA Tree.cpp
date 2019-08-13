const int MAX = 1e4;
const int LGMAX = 15;
//LCA construction in O(n*log(n)) with O(log(n)) queries.
struct LCATree{
	int n;
	vector<int> adj[MAX];
	int p[MAX][LGMAX];  // 2^j ancestor of node i
	int L[MAX];         // Depth of node i
	int q[MAX];         // (Queue used internally).

	LCATree(int N):n(N){}

	void dfs(int u, int h){
	    L[u] = h;
	    REP(i,0,sz(adj[u])){
	        int v = adj[u][i];
	        if (v != p[u][0]) {
	            p[v][0] = u;            
	            dfs(v, h+1);
	        }
	    }
	}
	void buildlca(int r){
		REP(i,0,n) REP(pw,0,LGMAX) p[i][pw] = -1;
	    dfs(r, 0);
		for (int pw = 1; (1<<pw) < n; pw++){
	        REP(i,0,n) if (p[i][pw-1] != -1) p[i][pw] = p[p[i][pw-1]][pw-1];
		}
	}
	int lca(int u, int v){
		if (L[u] < L[v]) swap(u,v);
		for (int pw = LGMAX-1; pw >= 0; pw--)
			if (L[u] - (1<<pw) >= L[v]) 
				u = p[u][pw];
		if (u == v) return u;
		for (int pw = LGMAX-1; pw >= 0; pw--){
			if (p[u][pw] != p[v][pw]) {
				u = p[u][pw];
				v = p[v][pw];
			}
		}
		return p[u][0];
	}
};

int main() {
	int n = 1e3;
    LCATree T(n);
    //Initialize n and the adj[] list
	T.buildlca(0); //Place the root instead of 0
	//Ready to answer queries
	return 0;
}
