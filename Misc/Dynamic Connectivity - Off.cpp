// Offline O(nlog^2 n) dynamic connectivity structure
// based on persistent Union Find, for general graphs.
// Insert all operations with add / remove / query,
// then call process. Results will be in res
// Note: Do NOT call process with 0 queries

struct UnionFind {
	int n, comp;
	vector<int> p,s,c;
	UnionFind(int n = 0) : n(n), comp(n), p(n), s(n, 1) {
   	REP(i,0,n) p[i] = i; 
	}
   int find(int u){ return u==p[u] ? u : find(p[u]); }
	bool merge(int u, int v) {
		if((u=find(u))==(v=find(v))) return false;        
		if(s[u]<s[v]) swap(u, v);
		s[u]+=s[v], p[v]=u, comp--, c.pb(v);
		return true;
	}
	int snap(){ return sz(c); }
	void rollback(int snap){
		while(sz(c) > snap){
			int v = c.back(); c.pop_back();
			s[p[v]] -= s[v], p[v] = v, comp++;
		}
	}
};

enum {ADD,DEL,QUERY};
struct Query {
	int type,u,v;
	Query(int type, int u, int v) : type(type), u(u), v(v) { }
};
struct DynCon {
	vector<Query> q;
	UnionFind dsu;
	vector<int> match,res;
	map<ii,int> last;
	DynCon(int n=0) : dsu(n) {}

	void add(int u, int v) {
		if(u>v) swap(u,v);
		q.pb(Query(ADD, u, v)), match.pb(-1);
		last[mp(u,v)] = sz(q)-1;
	}
	void remove(int u, int v) {
		if(u>v) swap(u,v);
		q.pb(Query(DEL, u, v));
		int prev = last[ii(u,v)];
		match[prev] = sz(q)-1;
		match.pb(prev);
	}
	void query() {
		q.pb(Query(QUERY, -1, -1)), match.pb(-1);
	}
	void process() {
		REP(i,0,sz(q)) if (q[i].type == ADD && match[i] == -1) match[i] = sz(q);
		go(0,sz(q));
	}
	void go(int l, int r) {
		if(l+1==r){
			if (q[l].type == QUERY)
				res.pb(dsu.comp); // Answer query here
			return;
		}
		int s = dsu.snap(), m = (l+r) / 2;
		REP(i,m,r) if ( match[i]!=-1 && match[i]<l) dsu.merge(q[i].u, q[i].v);
		go(l,m);
		dsu.rollback(s);
		s = dsu.snap();
		REP(i,l,m) if ( match[i]!=-1 && match[i]>=r) dsu.merge(q[i].u, q[i].v);
		go(m,r);
		dsu.rollback(s);
	}
};
