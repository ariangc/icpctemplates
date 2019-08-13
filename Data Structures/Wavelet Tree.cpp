/*
  Wavelet Tree Implementation
  Construction in O(nlogn)
  Queries in O(log(MAX))

  1 - based array!
*/



typedef vector<int> vi;

struct WT{
  int lo, hi;
  WT *l, *r; vi b;
  WT(int *from, int *to, int x, int y){
    lo = x, hi = y;
    if(lo == hi or from >= to) return;
    int mid = (lo+hi)/2;
    auto f = [mid](int x){
      return x <= mid;
    };
    b.reserve(to-from+1);
    b.pb(0);
    for(auto it = from; it != to; it++) b.pb(b.back() + f(*it));
    auto pivot = stable_partition(from, to, f);
    l = new WT(from, pivot, lo, mid);
    r = new WT(pivot, to, mid+1, hi);
  }
  //kth en [l,r] 
  int kth(int l, int r, int k){
    if(l > r) return 0;
    if(lo == hi) return lo;
    int inLeft = b[r] - b[l-1]; //cantidad en los a primeros b[a]
    int lb = b[l-1];  
    int rb = b[r]; 
    if(k <= inLeft) return this->l->kth(lb+1, rb , k);
    return this->r->kth(l-lb, r-rb, k-inLeft);
  }
 
  //cantidad de numeros menoes a K en [l,r]
  int LTE(int l, int r, int k) {
    if(l > r or k < lo) return 0;
    if(hi <= k) return r - l + 1;
    int lb = b[l-1], rb = b[r];
    return this->l->LTE(lb+1, rb, k) + this->r->LTE(l-lb, r-rb, k);
  }
 
  //cantidad de numeros en [l,r] iguales a k
  int count(int l, int r, int k) {
    if(l > r or k < lo or k > hi) return 0;
    if(lo == hi) return r - l + 1;
    int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
    if(k <= mid) return this->l->count(lb+1, rb, k);
    return this->r->count(l-lb, r-rb, k);
  }
  ~WT(){
    delete l;
    delete r;
  }
};
