//Biconnected Components Benq

vector<ii> st;
int par[N];
int cnt, num[N], low[N];
vector<int> adj[N];
vector< vector<ii> > bcc;

void tarjan(int u, bool root = 0){
	num[u] = low[u] = cnt++;
	int child = 0;
	for(int v : adj[u]) if(v != par[u]){
		if(num[v] == -1){
			child++, par[v] = u;
			st.push_back(ii(u,v));
			tarjan(v);
			low[u] = min(low[u],low[v]);
			if((root && child > 1) || (!root && num[u] <= low[v])){
				vector<ii> tmp;
				while(st.back() != ii(u,v)) tmp.pb(st.back()), st.pop_back();
				tmp.pb(st.back()), st.pop_back();
				bcc.pb(tmp);
			}
		}else if(num[v] < num[u]){
			low[u] = min(low[u],num[v]);
			st.pb(ii(u,v));
		}
	}
}