//Why 860?
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define sz(v) ((ll)v.size())
#define fill(x, v) memset(x, v, sizeof(x))
#define trace(x) cout << #x << " = " << x << endl
#define FER(i,x,y) for(ll (i)=(x);(i)<(y); (i) ++)
#define IFR(i,x,y) for(ll (i)=(x);(i)>=(y); (i) --)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;

const int L = 8002, G = 802;
const ll oo = 1e18;

ll psum[L], dp[G][L], c[L];

ll f(ll a, ll b){
	return (b - a + 1) * (psum[b] - (a > 0 ? psum[a - 1] : 0));
}

void go(ll i, ll l, ll r, ll optl, ll optr){
	if(l >= r) return;
	ll m = (l + r) >> 1;
	ll opt = -1;
	dp[i][m] = oo;
	FER(k, optl, min(optr, m) + 1){
		ll curr = dp[i - 1][k] + f(k + 1, m);
		if(curr < dp[i][m]){
			dp[i][m] = curr;
			opt = k;
		}
	}
	go(i, l, m, optl, opt);
	go(i, m + 1, r, opt, optr);
}

int main(){
	fastio;
	int l, g; cin >> l >> g;
	FER(i, 0, l) cin >> c[i];
	psum[0] = c[0]; FER(i, 1, l) psum[i] = psum[i - 1] + c[i];
	FER(i, 0, l) dp[0][i] = psum[i] * (i + 1);
	FER(i, 1, g) go(i, 0, l, 0, l);
	cout << dp[g - 1][l - 1] << endl;
	return 0;
}