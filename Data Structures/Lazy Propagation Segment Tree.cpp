// lazy propagation con propagacion y el update
//ejemplo de update en [l,r> la serie de fibonaci con a y b como primeros numeros (f[1]=a,f[2]=b)
//notar la forma de updatepro y proh; 
//made preprocess y find el fib de posicion n con a y b como primeros numeros

inline ll ss(ll val) {return val%MOD;}

ll dpf[N];

inline void made(){
  dpf[1]=1 ; dpf[2]=1;
  REP(i,3,N) dpf[i]=ss(dpf[i-1]+dpf[i-2]);
}
inline ll find(ll a, ll b, ll n) {
  if(n<3) return n==1? a:b; 
  return ss(a*dpf[n-2]+b*dpf[n-1]);
}

struct ST{
  ii lazy[4*N]; 
  ll tree[4*N], ar[N];
  ll n;
  inline void updatepro(ii laz,ll id, ll l,ll r){
    ll ta=r-l, sum=(find(laz.fst,laz.snd,ta+2)-laz.snd+MOD)%MOD;
    tree[id]=ss(tree[id]+sum);
    lazy[id].fst=ss(lazy[id].fst+laz.fst);
    lazy[id].snd=ss(lazy[id].snd+laz.snd);
  }
  inline void proh(ll id, ll l,ll r){
    ll mid=(l+r)>>1, ta=mid-l;
    updatepro(lazy[id],2*id,l,mid);
    ii laz; 
    laz.fst=find(lazy[id].fst,lazy[id].snd,ta+1);
    laz.snd=find(lazy[id].fst,lazy[id].snd,ta+2);
    updatepro(laz,2*id+1,mid,r);
    lazy[id]={0LL,0LL};
  }
  inline void updateRange(ll x, ll y, ll a, ll b, ll id, ll l,ll r){
    if(x>=r || y<=l) return;
    if(x<=l && r<=y){
      ll ta=l-x; ii laz;
      laz.fst=find(a,b,ta+1); laz.snd=find(a,b,ta+2);
      updatepro(laz,id,l,r);
      return;
    } 
    proh(id,l,r);ll mid=(l+r)>>1;
    updateRange(x,y,a,b,2*id,l,mid);
    updateRange(x,y,a,b,2*id+1,mid,r);
    tree[id]=ss(tree[2*id]+tree[2*id+1]);
  }
  inline ll getSum(ll x,ll y,ll id,ll l,ll r){
    if(x>=r || l>=y) return 0;
    if(x<=l && r<=y) return tree[id];
    proh(id,l,r);ll mid=(l+r)>>1;
    ll ez,ez1,ez2;
    ez1=getSum(x,y,2*id,l,mid);
    ez2=getSum(x,y,2*id+1,mid,r);ez=ss(ez1+ez2);
    return ez;
  }
  inline void build1( ll id, ll l, ll r){
    if (l > r) return ;
    if (r-l<2){tree[id] = ar[l];return;}
    ll mid = (l + r)>>1;
    build1(2*id, l,mid); build1(2*id+1, mid, r);
    tree[id] = ss(tree[id*2 ] + tree[id*2 + 1]);
  }
  inline void upd(ll x, ll y, ll a, ll b){
    updateRange(x,y,a,b,1,0,n);
  }
  inline void build(){
    build1(1,0,n);
  }
  inline ll que(ll x, ll y){
    return getSum(x,y,1,0,n);
  }
};
