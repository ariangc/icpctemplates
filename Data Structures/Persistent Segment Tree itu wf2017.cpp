// Persistent segment tree implemented with pointers.
// Consider using a map<int, node*> which represents
// the segment tree at time t.
const int MAX = 1e6;
typedef int T;
T arr[MAX];
struct node {
	T val;
	node *l, *r;
	node(T val) : val(val), l(NULL), r(NULL) {} 
	node(T val, node* l, node* r) : val(val), l(l), r(r) {}
};
// Identity element of Op()
const T OpId = 0;
// Associative query operation
T Op(T val1, T val2){
	return val1 + val2;
}
node* build(int a, int b) {
  	if (a+1 == b) return new node(arr[a]);
	node* l = build(a, (a+b)/2);
	node* r = build((a+b)/2, b);	
	return new node(Op(l->val, r->val), l, r);
}
// Branch and increment position p by val
node* update(node* u, int a, int b, int p, T val) {
	if (a > p || b <= p) return u;
	if (a+1 == b) return new node(Op(u->val, val));
	node* l = update(u->l, a, (a+b)/2, p, val);
	node* r = update(u->r, (a+b)/2, b, p, val);
	return new node(Op(l->val, r->val), l, r);
}
// Query t to get sum of values in range [i, j)
T query(node* u, int a, int b, int i, int j) {
	if (a >= j || b <= i) return OpId;
	if (a >= i && b <= j) return u->val;
	T q1 = query(u->l, a, (a+b)/2, i, j);
	T q2 = query(u->r, (a+b)/2, b, i, j); 
	return Op(q1, q2);
}
map<int, node*> m;
node* st;
T val;
int n, p; 
int main() {
	REP(i,0,n) arr[i] = 0;	// Any starting values
	m.clear();
	st = build(0,n);
	m[0] = st;
	REP(i,0,n){
		// Modify position p with value val at time t
		st = update(st, 0, n, p, val);
		m[i] = st;
	}	
	// Consider for example rectangular queries:
	// Sum of all nodes in [a,b]x[c,d] using one
	// coordinate as time and another as values
}
