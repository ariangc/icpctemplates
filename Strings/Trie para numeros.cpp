const int N = 4e6 + 2;
const int B = 40;

int adj[N][2];
int isEnd[N];
int gid;
ll val[N];

void init(int p){
	adj[p][0] = adj[p][1] = 0;
	isEnd[p] = 0;
}

void add(ll x){
	int cur = 0;
	IFR(i, B, 0){
		bool dig = (1ll << i) & (x);
		if(adj[cur][dig] == 0){
			adj[cur][dig] = ++gid;
			init(gid);
		}
		cur = adj[cur][dig];
	}
	isEnd[cur] ++;
	val[cur] = x;
}

ll getval(ll x){
	int cur = 0;
	IFR(i, B, 0){
		bool dig = (1ll << i) & x;
		if(adj[cur][1 - dig]) cur = adj[cur][1 - dig];
		else if(adj[cur][dig]) cur = adj[cur][dig];
	}
	return x ^ val[cur];
}
