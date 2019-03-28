//Heavy Light Decomposition

struct SegmentTree{
  int n, t[2 * N];

  SegmentTree(int _n): n(_n){}
  int Op(int &u, int &v){ return max(u,v); }
  void build(){ IFR(i, n - 1, 1) t[i]=Op(t[i << 1], t[i << 1 | 1]); }
  void modify(int p, int val){ for(t[p+=n] = val ; p >>= 1;) t[p] = Op(t[p << 1], t[p << 1 | 1]); }
  int query(int l, int r){
    int ansl, ansr; 
    ansl = ansr = -1e9;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
        if(l&1) ansl = Op(ansl, t[l++]);
        if(r&1) ansr = Op(t[--r], ansr);
    }
    return Op(ansl, ansr);
  }
};

struct HeavyLight{
  int n, gid;
  SegmentTree st;
  vector<int> adj[N];
  //Parent, depth, subtree size, position on SegmentTree array, chain parent
  int p[N], d[N], tsz[N], id[N], rt[N];

  HeavyLight(int _n): n(_n), st(_n){}

  int Op(int a, int b) {
    return max(a, b); //Operation. Change if needed also in ST
  }

  int make(int u, int par, int depth){ //Build subtree sizes
      p[u] = par; d[u] = depth; tsz[u] = 1;
      for(auto v: adj[u]) if(v != p[u]) tsz[u] += make(v, u, depth + 1);
      return tsz[u];
  }

  void dfs(int u, int root){ //Build chains
      id[u] = gid++; rt[u] = root;
      int w = 0, wsz = low;
      for(auto v: adj[u]){
        if(v != p[u] && tsz[v] > wsz){
          w = v; wsz = tsz[v];
        }
      }
      if(w) dfs(w, root);
      for(auto v: adj[u]) if(v != p[u] && v != w) dfs(v, v);
  }

  void update(int u, int val){ //Update one position on the array
      st.modify(id[u], val);
  }

  int query(int u, int v){ //Query without lca, swapping elements
      int ans = 0; //Neutral
      while(u != -1){
          if(rt[u] == rt[v]){
              int a = id[u], b = id[v];
              if(a > b) swap(a, b);
              ans = Op(ans, st.query(a + 1, b+1)); //CHANGE HERE!!!!
              u = -1;
          }
          else{
    		  	  if(d[rt[u]] > d[rt[v]]) swap(u, v);
              ans = Op(ans, st.query(id[rt[v]], id[v]+1));
              v = p[rt[v]];
          }
      }
      return ans;
  }

  void build(){
      gid = 0; st.n = n;
      make(0,-1,0);
      dfs(0, 0);
      //Fill array and build Segment Tree if necessary
  }
};