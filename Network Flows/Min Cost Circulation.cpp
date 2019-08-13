struct Edge {
  int cap, flow;
  ll cost;
  Edge(int cap = 0, int flow = 0, ll cost = 0) :
    cap(cap), flow(flow), cost(cost) {}
};

struct MinCostCirculation{
	int s,t,n;
	ll maxFlow, minCost;
	vector<vector<Edge> > G; //nonexistent edge = Edge(0,0,0);
	vector<int> vis,parent;
	vector<ll> dist;
	MinCostCirculation (int _n = 0){
		n = _n;
		G.resize(n+1); dist.resize(n+1); vis.resize(n+1); parent.resize(n+1); //OK;
		REP(i,0,n+1) G[i].resize(n+1);
		minCost = 0;
	}
	void AddEdge(int from, int to, int cap, ll cost){
		G[from][to] = Edge(cap, 0, cost);
		G[to][from] = Edge(0, 0,-cost);
	}
	void updateEdge(int from, int to, int ncap){
		G[from][to].cap = ncap;
	}
	void Augment(int u){
   	REP(i,0,n+1) vis[i] = 0;
      while(!vis[u]){
      	vis[u] = 1;
         u = parent[u];
      }
      int aux = u;
      ll addedCost = 0;
      ll delta = INF;
      do{
      	int v = parent[u];
         addedCost += G[v][u].cost;
      	delta = min(delta,(ll) G[v][u].cap - G[v][u].flow);
         u = v;
      }while(u != aux);
      do{
      	int v = parent[u];
         G[v][u].flow += delta;
         G[u][v].flow -= delta;
         u = v;
		}while(u != aux);
      minCost += addedCost*delta;
	}

    bool negCycle(){
        /*Vertex n is a dummy vertex => |V| = n+1*/
        REP(i,0,n) dist[i] = INF;
        dist[n] = 0;
        parent[n] = -1;
        REP(k,0,n) REP(i,0,n+1) REP(j,0,n+1){
            if(G[i][j].flow == G[i][j].cap) continue;
            if(dist[i] + G[i][j].cost < dist[j]){
                dist[j] = dist[i] + G[i][j].cost;
                parent[j] = i;
            }
        }
        REP(i,0,n+1) REP(j,0,n+1){
            if(G[i][j].flow == G[i][j].cap) continue;
            if(dist[i] + G[i][j].cost < dist[j]){
                parent[j] = i;
                Augment(j);
                return true;
            }
        }
        return false;
    }

    ll GetMinCostCirculation(){
        while(negCycle());
        return minCost;
    }
};
