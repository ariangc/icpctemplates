//Finding bridges and articulation points

int low[N],id[N],parent[N];
bool art[N];
vi adj[N];
vi bridge[N];
int curr_id =0;
int root, rootchild;

void dfs(int u) {
	low[u] = id[u] = curr_id++;
	REP(j,0,sz(adj[u])) {
		int v = adj[u][j];
		if (id[v] == -1) {
			parent[v] = u;
			if (u == root) rootchild++;
			dfs(v);
			if (low[v] >= id[u]) art[u] = true;
			if (low[v] > id[u]){
				bridge[u].pb(v);
				bridge[v].pb(u); //store bridges in a sub graph
			}
			low[u] = min(low[u], low[v]);
		}
		else if (v != parent[u]) low[u] = min(low[u], id[v]);
	} 
}

//inside int main()
REP(i,0,n){
	if (id[i] == -1) {
		root = i; rootchild = 0; dfs(i);
		art[root] = (rootchild > 1); 
	} 
}
