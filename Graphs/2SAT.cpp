//2-SAT
//Conditions from 0 to 2*number of nodes, i and i^1 are reciprocal
//That means, ~0 is 1, ~1 is 0, ~2 is 3, ~3 is 2, etc
//When adding an edge, make sure to fix values
//For example, node from a to b (a,b >= 1)
//aa = (a-1)*2, bb = (b-1)*2, then a has "aa" as true and aa^1 as false
//Same to b
//To return to the main state, divide by 2 and sum 1

struct TwoSAT{
   int n;
   vector< vi> g, adj;
   vi d, low, scc, ans, lev;
   vector<bool> stacked, ok;
   stack<int> s;
   int ticks, current_scc;

   TwoSAT(int N):
      n(N),ticks(0), current_scc(0), g(N), adj(N), d(N), low(N), scc(N), ans(N), lev(N),
      stacked(N), ok(N){}

   void initialize(){
      REP(i,0,n){
         stacked[i] = false;
         d[i] = -1;
         scc[i] = -1;
         ok[i] = false;
         current_scc = ticks = 0;
      }
   }

   void addEdge(int a, int b){
      g[a].pb(b);
   }

   void tarjan(int u){
     d[u] = low[u] = ticks++;
     s.push(u);
     stacked[u] = true;
     const vector<int> &out = g[u];
     for (int k=0, m=out.size(); k<m; ++k){
       const int &v = out[k];
       if (d[v] == -1){
         tarjan(v);
         low[u] = min(low[u], low[v]);
       }else if (stacked[v]){
         low[u] = min(low[u], low[v]);
       }
     }
     if (d[u] == low[u]){
       int v;
       do{
         v = s.top();
         s.pop();
         stacked[v] = false;
         scc[v] = current_scc;
       }while (u != v);
       current_scc++;
     }
   }

   bool consistent(){
      for(int i = 0; i < n; i+=2){
         if(scc[i] == scc[i^1]){
            return false;
         }
      }
      return true;
   }

   void build(){
      REP(i,0,n){
         REP(j,0,sz(g[i])){
            int v = g[i][j];
            if(scc[i] != scc[v]){
               adj[i].pb(v); lev[v]++;
            }
         }
      }
   }

   void toposort(){
      queue<int> q;
      REP(i,0,current_scc){
         if(lev[i] == 0) q.push(i);
      }
      int x = 1;
      while(!q.empty()){
         int u = q.front(); q.pop();
         ans[u] = x ++;
         REP(i,0,sz(adj[u])){
            int v = adj[u][i];
            lev[v]--;
            if(lev[v] == 0) q.push(v);
         }
      }
   }

   void solve(){
      for(int i = 0; i<n; i+=2){
         if(ans[scc[i]] < ans[scc[i^1]]){
            ok[i] = false; ok[i^1] = true;
         }
         else{
            ok[i] = true; ok[i^1] = false;
         }
      }
   }

   bool go(){
      REP(i,0,n){
         if(scc[i] == -1) tarjan(i);
      }
      if(!consistent()) return false;
      else{
         build();
         toposort();
         solve();
         return true;
      }
   }

};

int main(){
   fastio;
   int n,m; cin >> n >> m;
   TwoSAT TS = TwoSAT(2*n);
   TS.initialize();

   //TO DO: ADD EDGES

   bool res = TS.go();
   if(!res) cout << "Impossible" << endl;
   else{
      for(int i = 0; i < 2*n; i+=2){
         int state = i/2 + 1;
         if(TS.ok[i]) //state is true
         else //state is false 
      }
   return 0;
}
