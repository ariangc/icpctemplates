//Finds Biconnected Components

bool usd[1005];
int low[1005], d[1005], prev[1005], cnt;
vector <int> adj[1005];
stack <ii> S;

void Outcomp( int u , int v ){
	printf("New Component\n");
	ii e;
	do{
		e = S.top(); S.pop();
		cout << e.fst << " " << e.snd << endl;
	} while( e != mp( u , v ) );
}

void dfs( int u ){
	usd[u] = 1; cnt++;
	low[u] = d[u] = cnt;
	REP(i,0,sz(adj[u])){
		int v = adj[u][i];
		if( !usd[v] ){
			S.push( mp( u , v ) );
			prev[v] = u; dfs( v );
			if( low[v] >= d[u] ) Outcomp( u , v );
			low[u] = min( low[u] , low[v] );
		}
		else if( prev[u] != v and d[v] < d[u] ){
			S.push( mp( u , v ) );
			low[u] = min( low[u] , d[v] );
		}
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	REP(i,0,m){
		int a , b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	cnt = 0;
	memset(usd,0,sizeof(usd));
	memset(prev,-1,sizeof(prev));
	REP(i,0,n){
		if( !usd[i] ) dfs(i);
	}
	return 0;
}
