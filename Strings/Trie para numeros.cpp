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

int rem(ll x, int cur = 0, int pos = B){
	if(pos < 0){
		if(isEnd[cur]) isEnd[cur] --;
		if(!adj[cur][0] && !adj[cur][1] && isEnd[cur] == 0){
			return -1;
		}	
		return cur;
	}
	bool index = (1ll << pos) & x;
	int ret = rem(x, adj[cur][index], pos - 1);
	if(ret == -1) adj[cur][index] = 0;
	if(!adj[cur][0] && !adj[cur][1] && isEnd[cur] == 0){
		return -1;
	}
	return cur;
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
