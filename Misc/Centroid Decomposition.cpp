const int MAXCD = 1e5 + 5;
struct CentroidD{
	//MAXCD: tamanho maximo del grafo
	vector< int > graph[MAXCD]; 
	int sub[MAXCD];//size de subtree en CD tree
	int cpar[MAXCD];//padre en el centroid tree
	//la raiz tiene padre -2 

	void add_edge(int a, int b){
		graph[a].pb(b);
		graph[b].pb(a);
	}

	void dfs(int cur, int parent){
		sub[cur] = 1;
		for(int i = 0; i < sz(graph[cur]); ++i){
			int to = graph[cur][i];
			if(to != parent && cpar[to] == -1){
				dfs(to, cur);
				sub[cur] += sub[to];
			}
		}
	}

	void decompose(int cur, int parent, int sb, int prevc){
		for(int i = 0; i < sz(graph[cur]); ++i){
			int to = graph[cur][i];
			if(to != parent && cpar[to] == -1 && (2 * sub[to] > sb)){
				decompose(to, cur, sb, prevc);
				return;
			}
		}
		cpar[cur] = prevc;
		for(int i = 0; i < sz(graph[cur]); ++i){
			int to = graph[cur][i];
			if(cpar[to] == -1){
				dfs(to, - 1);
				decompose(to, cur, sub[to], cur);
			}
		}
	}
	
	void init(int start){
		for(int i = 0; i < MAXCD; ++i) cpar[i] = -1;
		dfs(start, - 1);
		decompose(start, -1, sub[start], -2);
	}
};
