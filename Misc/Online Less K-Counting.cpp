/*-------------------inversiones en un rango (online)----------------
 construccion amortizada a nlog(n);
 cada querie en log^2(n);*/

struct T{
  vi v;
  T () {}
  T (vi v): v(v){}
};
struct ST{
  ll n,ans;
  T t[2*N];
  inline T Op(T &val1, T &val2 ){
    vi v;
    REP(i,0,val1.v.size()) v.pb(val1.v[i]);
    REP(i,0,val2.v.size()) v.pb(val2.v[i]);
    sort(all(v));
    T ty;
    ty.v=v;
    return ty;
  }
  inline ll Op1( T &val1,ll &k){
    ans=0;
    //usar upper_bound para valores mayores a k
    //usar quitar el val1.v.size() para valores menores o iguales a k
    // usar lower_bound para valores estrictamente menoes a k(sin el val1.v.size())
    ans+=val1.v.size()-(upper_bound(all (val1.v),k)-val1.v.begin());
    return ans;
  }
  inline void build(){
    RREP(i,n-1,1) t[i]=Op(t[i<<1],t[i<<1|1]);
  }
  inline ll que(ll l, ll r, ll k){
    ll ans=0;
    for(l+=n,r+=n;l<r;l>>=1,r>>=1){
      if(l&1) ans+=Op1(t[l++],k);
      if(r&1) ans+=Op1(t[--r],k); 
    }
    return ans;
  }
}st;

int main(){fastio;
  ll n; cin>>n;
  st.n=n;
  REP(i,0,n) {
    ll x; cin>>x;
    st.t[i+n].v.push_back(x);
  } 
  st.build();
  ll q,ans=0,l,r,k; cin>>q;
  REP(i,0,q){
    cin>>l>>r>>k;// queries 1 base
    ans=st.que(l-1,r,k);
    cout<<ans<<endl;
  }
  return 0;
}