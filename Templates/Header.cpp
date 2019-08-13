#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
 
#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back
#define ff first
#define ss second
#define tm1 first
#define tm2 second.first
#define tm3 second.second
#define sz(x) ll(x.size())
#define fill(x,v) memset(x,v,sizeof(x))
#define all(v) (v).begin(),(v).end()
#define FER(i,a,b) for(ll i = ll(a); i < ll(b); ++i)
#define IFR(i,a,b) for(ll i = ll(a); i >= ll(b); --i)
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define sqr(x) (x)*(x)
#define bas 987625403
using namespace std;
typedef long double ld;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> tri;
typedef vector<ll> vi;
typedef vector<ii> vii;
#define trace(...) fff(#__VA_ARGS__,__VA_ARGS__)

template<typename t> void fff(const char *x, t&& val1){
	cout << x << " : " << val1 << endl; 
}

template<typename t1, typename... t2> void fff(const char *x, t1&& val1, t2&&... val2){
	const char *xd = strchr(x+1,',');
	cout.write(x,xd-x)<< " : " << val1 << " | ";
	fff(xd+1,val2...); 
}

int main(){
	fastio;
	return 0;
}
