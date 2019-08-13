// Divide and Conquer DP optimization.
// Problem: dp[i][j] = min{k>j} (func(j,k) + dp[i-1][k]).
// (That is, split n objects into k buckets with cost
// func per bucket). Necessary condition: argmin(dp[i][j]) <=
// argmin(dp[i][j+1]) (this is "opt")
// Naive complexity: O(kn^2)
// Improved complexity: O(knlog(n))
// Consider checking if opt[i+1][j] <= opt[i][j] <= opt[i][j+1]
// and using a knuth-like O(n^2) loop

const ll INF = 1e18;
int n, k;

ll c[8100];
ll s[8100];
ll dp[810][8100];

ll func(int i, int j){ return (s[j] - s[i])*(j-i); }

void go(int i, int l, int r, int optl, int optr){
	if (l >= r) return;
	int m = (l+r)/2;
	int opt = n;
	dp[i][m] = INF;
	for(int u = optr; u>= optl; u--){
		ll curr = dp[i-1][u] + func(m,u);
		if(curr < dp[i][m]){
			dp[i][m] = curr;
			opt = u;
		}
	}
	go(i,l,m,optl, opt);
	go(i,m+1,r,opt,optr);
}

int main(){
	fastio;
	cin >> n >> k;
	REP(i,0,n) cin >> c[i];
	s[0] = 0;
	REP(i,0,n+1) s[i] = s[i-1] + c[i-1];
	REP(i,1,k+1) dp[i][n] = INF;
	REP(i,0,n) dp[0][i] = INF;
	dp[0][n] = 0;
	REP(i,1,k+1) go(i,0,n,0,n);
	cout << dp[k][0] << endl;
	return 0;
}

//Divide and Conquer Trick by Ands

void compute(int cnt, int l, int r, int optl, int optr){
	if(l > r) return ;
	int mid = ( l + r ) >> 1 ; 	
	int opt = -1 ; 
	ll value = 1e18 ;
	int last = cnt^1 ;  
	for(int idx = optl ; idx <= min(mid-1,optr); ++idx){
		ll tmp = dp[last][idx] + C[idx][mid] ;
		if(tmp < value){
			value = tmp ; 
			opt = idx ; 
		} 
	}
	dp[cnt&1][mid] = value ;
	compute(cnt, l, mid-1, optl, opt); 
	compute(cnt, mid+1, r, opt, optr);
}


int main(){
	//casos base
	for(int cnt = 2; cnt <= m ; ++cnt) compute(cnt&1, 0, n-1, 0, n-1) ;
}
