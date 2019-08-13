// ----------------------------Suffix array--------------------------
// construccion en nlog^2(n)
//usa lcp(x,y)=mi[lcp(x,x+1),lcp(x+1,x+2)....lcp(y-1,y)]
//construye el lcp(x,y) con sparce table, notar que los indices son 0 base 
//s=ababa
//s1[0]=ababa,s1[1]=baba,s1[2]=aba, s1[3]=ba,s1[4]=a, s1[5]='$'
//s2={$,a,aba,ababa,ba,baba}={5,4,2,0,3,1}=r
//r[i] lista de los sufijos ordenados en 0 base
//indice de s1={ababa,baba,aba,ba,a,$}={3,5,2,4,1,0}=p  
//p[i] posicion del i substring en el suffix array (s1) en 0 base

#define N 100010  
#define M 20
inline ll ma(ll a, ll b){ return ((a-b>0)? a:b);}
inline ll mi(ll a, ll b){return ((a-b>0)? b:a);}

struct SA{
  //asignar s:string(char), n tamaño del string
  ll n,t;
  ll p[N],r[N],h[N];    
  char s[N];                   
  ll rmq[M][N];
  ll flog2[N];
  inline void fix_index(ll b, ll e){
    ll lastpk, pk, d;
    lastpk = p[r[b]+t];
    d = b;
    REP(i,b,e){
      if (((pk = p[r[i]+t]) != lastpk) && (b > lastpk || pk >= e)){
        lastpk = pk;
        d = i;
      }
      p[r[i]]= d;
    }
  }
  //calculo de r y p 
  inline void suff_arr(){ 
    s[n++] = '$';
    ll bc[256];
    REP(i,0,256) bc[i]=0;
    REP(i,0,n) bc[(ll)s[i]]++;
    REP(i,1,256) bc[i] += bc[i-1];
    RREP(i,n-1,0) r[--bc[(ll)s[i]]] = i;
    RREP(i,n-1,0) p[i] = bc[(ll)s[i]];
    for (t = 1; t < n; t<<=1){
      for (ll i = 0, j = 1; i < n; i = j++){
        while (j < n && p[r[j]] == p[r[i]]) ++j;
        if (j-i > 1){
          sort(r+i, r+j, [&](const ll &i, const ll &j){return p[i+t] < p[j+t];});
          fix_index(i, j);        
        }
      }
    }
  }
  //calcula h[i] en O(n) usando Kasai algorithm
  inline void initlcp(){
    ll tam = 0, j;
    REP(i,0,n-1){
      j = r[p[i]-1];
      while(s[i+tam] == s[j+tam]) ++tam;
      h[p[i]-1] = tam;
      if (tam > 0) --tam;
    }
  }
  //construccion del RMQ para hallar lcp en un rango
  inline void makelcp(){
    initlcp();
    REP(i,0,n-1) rmq[0][i] = h[i];
    ll lg = 0, pw = 1;
    do{
      REP(i,pw,pw*2) flog2[i] = lg;
      lg++; pw*=2;
      REP(i,0,n-1){
        if (i+pw/2 < n-1) rmq[lg][i] = mi(rmq[lg-1][i], rmq[lg-1][i+pw/2]);
        else rmq[lg][i] = rmq[lg-1][i];
      }
    } while(pw < n);
  }
  //calcula el lcp en [i,j] de s1(suffix array);
  inline ll lcp(ll i, ll j){
    if (i == j) return n - r[i] - 1;
    ll lg = flog2[j-i], pw = (1<<lg);
    return mi(rmq[lg][i], rmq[lg][j-pw]);
  }
  //limpia y construye
  inline void build(){
    memset(p,0,sizeof(p));
    memset(r,0,sizeof(r));
    memset(h,0,sizeof(h));
    memset(rmq,0,sizeof(rmq));
    memset(flog2,0,sizeof(flog2));
    suff_arr();
    makelcp();
  }
};
int main(){
  //ejemplo, hallar la cantidad de diferentes substrings para t1 strings;
  ll t1; scanf("%lld", &t1);
  REP(ik,0,t1){
    SA sa; scanf("%s", &sa.s);
    ll ta=strlen(sa.s);
    sa.n=ta; sa.build();
    ll ans=0;
    REP(i,1,ta){
        ans+=sa.lcp(i,i+1);
    }
    ll xd=(ta*(ta+1)/2)-ans;
    printf("%lld\n",xd);
  }
  return 0;
}