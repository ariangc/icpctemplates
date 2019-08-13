// O(V*E) maximum bipartite matching
int p[MAX];		// Parent of right-node v in the matching
int vis[MAX];	// Whether left-node u has been visited 
vi adj[MAX];	// Standard adjacency list

int match(int u) {
	if (vis[u]) return 0;
	vis[u] = 1;
	REP(i,0,adj[u].size()){
		int v = adj[u][i];
		if (p[v] == -1 || match(p[v])) {
			p[v] = u; 
			return 1;
		} 
	}
   return 0;
}

int main(){
	// build adj here with n left nodes
    // and V total nodes
	int n = 1000000;
    int V = 2000000; 
	int maxMatch = 0;
	REP(i,0,V) p[i] = -1;
	REP(u,0,n){
		REP(i,0,n) vis[i] = 0;
		maxMatch += match(u);
	}
	printf("Found %d matchings\n", maxMatch)
}
