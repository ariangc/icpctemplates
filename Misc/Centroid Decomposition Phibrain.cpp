#define N 100002

inline ll ma(ll a, ll b){ return ((a-b>0)? a:b);}
inline ll mi(ll a, ll b){return ((a-b>0)? b:a);}

struct CD{
	vector< int > graph[N];
	int sub[N],p[N];
	//sub[i]: size del nodo i luego de descomponer el tree
	//p[i]: padre del nodo i luego de descomponer el tree
	//notar que el padre del centroid es -2
	// el tree es 1 ó 0 base
	//para inicializar addEddge(a,b);
	//para construir el centroid tree, solo llamar init(root); root: root del tree
	void addEdge(int &a, int &b){
		graph[a].pb(b);
		graph[b].pb(a);
	}
	inline void dfs(int cur, int parent){
		sub[cur] = 1;
		for(int i = 0; i < sz(graph[cur]); ++i){
			int to = graph[cur][i];
			if(to != parent && p[to] == -1){
				dfs(to, cur);
				sub[cur] += sub[to];
			}
		}
	}
	inline void decompose(int cur, int parent, int sb, int prevc){
		for(int i = 0; i < sz(graph[cur]); ++i){
			int to = graph[cur][i];
			if(to != parent && p[to] == -1 && (2 * sub[to] > sb)){
				decompose(to, cur, sb, prevc);
				return;
			}
		}
		p[cur] = prevc;
		for(int i = 0; i < sz(graph[cur]); ++i){
			int to = graph[cur][i];
			if(p[to] == -1){
				dfs(to, - 1);
				decompose(to, cur, sub[to], cur);
			}
		}
	}	
	inline void init(int start){
		for(int i = 0; i < N; ++i) p[i] = -1;
		dfs(start, - 1);
		decompose(start, -1, sub[start], -2);
	}
};
int cnt=1;
vi adj[N];
int d[N];
inline void make(int &u, int x, int depth){
	d[u]=depth;
	for(auto v :adj[u]) if(v!=x) make(v,u,depth+1);
}
int main() {
	fastio;
	int n; cin>>n;
	CD cd; //cd.n=n;
	REP(i,0,n-1) {
		ll a,b; cin>>a>>b;
		cd.addEdge(a,b);
	}
	cd.init(1);
	int pa, root;
	REP(i,1,n+1) {
		pa=cd.p[i];
		if(pa==-2) root=i;
		if(pa!=-2) { 
			adj[i].pb(pa);
			adj[pa].pb(i);
		}
	}
	make(root,0,1);
	char is;map<int, string> m;int k=1,flag=1;
	for(is='A'; is<='Z'; is++) m[k++]=is;
	REP(i,1,n+1) if(d[i]>26) flag=0;
	if(flag==0) cout<<"Impossible!"<<endl;
	if(flag==1) {
		REP(i,1,n+1) cout<<m[d[i]]<<endl;
	}	
	return 0;
}