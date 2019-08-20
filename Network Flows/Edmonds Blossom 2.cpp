// Maximum general matching (not necessarily bipartite)
// Make sure to set N in main()
// Claimed O(N^4) running time

int N; // the number of vertices in the graph
typedef vector<int> vi;
typedef vector< vector<int> > vvi;
vi match;
vi vis;
 
void couple(int n, int m) { match[n]=m; match[m]=n; }
 
// True if augmenting path or a blossom (if blossom is non-empty).
// the dfs returns true from the moment the stem of the flower is
// reached and thus the base of the blossom is an unmatched node.
// blossom should be empty when dfs is called and 
// contains the nodes of the blossom when a blossom is found.
bool dfs(int n, vvi &conn, vi &blossom) {
  vis[n]=0;
  REP(i, 0, N) if(conn[n][i]) {
    if(vis[i]==-1) {
      vis[i]=1;
      if(match[i]==-1 || dfs(match[i], conn, blossom)) { 
			couple(n,i); 
			return true; 
		}
    }
    if(vis[i]==0 || SZ(blossom)) {  // found flower
      blossom.pb(i); blossom.pb(n);
      if(n==blossom[0]) { match[n]=-1; return true; }
      return false;
    }
  }
  return false;
}
 
// search for an augmenting path.
// if a blossom is found build a new graph (newconn) where the
// (free) blossom is shrunken to a single node and recurse.
// if a augmenting path is found it has already been augmented
// except if the augmented path ended on the shrunken blossom.
// in this case the matching should be updated along the 
// appropriate direction of the blossom.
bool augment(vvi &conn) {
	REP(m, 0, N) if(match[m]==-1) {
		vi blossom;
		vis=vi(N,-1);
		if(!dfs(m, conn, blossom)) continue;
		if(SZ(blossom)==0) return true; // augmenting path found
 
// blossom is found so build shrunken graph
		int base=blossom[0], S=SZ(blossom);
		vvi newconn=conn;
		REP(i, 1, S-1) REP(j, 0, N) 
			newconn[base][j]=newconn[j][base]|=conn[blossom[i]][j];
		REP(i, 1, S-1) REP(j, 0, N) 
			newconn[blossom[i]][j]=newconn[j][blossom[i]]=0;
		newconn[base][base]=0; // is now the new graph
		if(!augment(newconn)) return false;
		int n=match[base];
 
// if n!=-1 the augmenting path ended on this blossom
    if(n!=-1) REP(i, 0, S) if(conn[blossom[i]][n]) {
      couple(blossom[i], n);
      if(i&1) for(int j=i+1; j<S; j+=2) 
			couple(blossom[j],blossom[j+1]);
      else for(int j=0; j<i; j+=2) 
			couple(blossom[j],blossom[j+1]);
      break;
    }
    return true;
  }
  return false;
}
 
// conn is the NxN adjacency matrix
// returns the number of edges in a max matching.
int edmonds(vvi &conn) {
  int res=0;
  match=vi(N,-1);
  while(augment(conn)) res++;
  return res;
}

/****************************************************/
set<pair<int,int> > used;
int main(){
  int n;
  cin >> n;
  N = n;
  vvi conn;
  vi tmp;
  tmp.assign(n,0);
  REP(i, 0, n) conn.push_back(tmp);
  int u, v;
  while(cin >> u >> v){
    u--; v--;
    if(u > v) swap(u,v);
    if(used.count(make_pair(u,v))) continue;
    used.insert(make_pair(u,v));
    conn[u][v] = conn[v][u] = 1;
  }
  int res = edmonds(conn);
  cout<<res*2<<endl;
  REP(i, 0, n) {
    if(match[i] > i){
      cout<<i+1<<" "<<match[i] + 1<<endl;
    }
  }
  return 0;
}
