 // Simple Hull
struct HullSimple { // Upper envelope for Maximum.
    // Special case: strictly increasing slope in insertions,
    // increasing value in queries.
    deque<pair<ll, ll> > dq;
    ld cross(pair<ll, ll> l1, pair<ll, ll> l2){
        return (ld)(l2.snd - l1.snd) / (ld)(l1.fst - l2.fst);
    }
    void insert_line(ll m, ll b){
        pair<ll,ll> line = mp(m,b);
        while (sz(dq) > 1 && cross(line, dq[sz(dq)-1]) <=
               cross(dq[sz(dq)-1], dq[sz(dq)-2])) dq.pop_back();
        dq.pb(mp(m,b));
    }
    
    ll eval(pair<ll, ll> line, ll x){
        return line.fst * x + line.snd;
    }
    
    ll eval(ll x){
        while (sz(dq) > 1 && eval(dq[0], x) < eval(dq[1],x))
            dq.pop_front();
        return eval(dq[0],x);
    }
};

// Dynamic Hull
// Compile with g++ -std=c++11 file.cpp -o file 
typedef long double ld;
const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
// Upper envelope for Maximum
struct HullDynamic : public multiset<Line> { 
     bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b)*(z->m - y->m) >= 
					(y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0: &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};