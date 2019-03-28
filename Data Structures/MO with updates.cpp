#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define sz(v) ((ll)v.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define trace(x) cout << #x << " = " << x << endl
#define FER(i,x,y) for(int (i)=(x);(i)<(y); (i) ++)
#define IFR(i,x,y) for(ll (i)=(x);(i)>=(y); (i) --)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;
typedef pair<ll, ll> ii;

const ll N = 2e5 + 2;

ll b[N]; //b[i] = Block of elemnt in position i

struct Query{
	ll l, r, t, id;
	Query(ll a, ll b, ll c, ll d):l(a), r(b), t(c), id(d){}
	bool operator < (const Query &x){
		if(b[l] < b[x.l]) return true;
		if(b[l] == b[x.l] && b[r - 1] < b[x.r - 1]) return true;
		if(b[l] == b[x.l] && b[r - 1] == b[x.r - 1] && t < x.t) return true;
		return false;
	}
};

struct Update{
	ll idx, pre, cur;
	Update(ll a, ll b, ll c):idx(a), pre(b), cur(c){}
};

vector<Query> que;
vector<Update> upd;
ll curR, curL, updId;
ll ans[N], a[N], f[N], cont[N], dp[N];

void add(ll x){ cont[f[x]] --; cont[++f[x]] ++;}
void rem(ll x){ cont[f[x]] --; cont[--f[x]] ++;}

void push(ll p, ll cur){
	if(p >= curL && p < curR) add(cur), rem(a[p]);
	a[p] = cur;
}

ll query(ll l, ll r, ll curupd){
	while(updId < curupd) {
		push(upd[updId].idx, upd[updId].cur); updId ++;
	}
	while(updId > curupd){
		updId --; push(upd[updId].idx, upd[updId].pre);
	}
	while(curL < l) rem(a[curL ++]);
	while(curL > l) add(a[--curL]);
	while(curR > r) rem(a[--curR]);
	while(curR < r) add(a[curR++]);
	ll mex = 1; while(cont[mex]) mex ++;
	return mex;
}

map<ll, ll> m; ll gid = 1;

void foo(ll &x){
	if(m[x] == 0) m[x] = gid ++;
	x = m[x];
}

int main(){
	fastio;
	ll n, q; cin >> n >> q;
	ll blsz = pow(n, 2.0 / 3.0);
	FER(i, 0, n){
		b[i] = i / blsz;
		cin >> a[i]; foo(a[i]);
		dp[i] = a[i];
	}
	FER(i, 0, q){
		ll t; cin >> t;
		if(t == 1){
			ll l, r; cin >> l >> r; l --;
			que.pb(Query(l, r, sz(upd), sz(que))); 
		}
		else{
			ll p, x; cin >> p >> x; foo(x);
			p --;
			upd.pb(Update(p, dp[p], x));
			dp[p] = x;
		}
	}
	sort(que.begin(), que.end());
	FER(i, 0, sz(que)){
		ans[que[i].id] = query(que[i].l, que[i].r, que[i].t);
	}
	FER(i, 0, sz(que)) cout << ans[i] << endl;
	return 0;
}
