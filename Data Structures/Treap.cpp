// Implicit cartesian tree: Array with O(log(n)) 
// split, access, merge
// Remember to srand(time(NULL))
typedef int T;		// Type of the node information
struct node{
	T x;
	int y, cnt;		// y: random Priority Queue key
	node *l, *r;	// cnt: number of nodes in subtreap
	node() {}		// l,r: left and right children.
	node(T x): x(x), y(rand()), cnt(1), l(NULL), r(NULL){}
};
node* treap;

inline int cnt(node* &it){ return it ? it->cnt : 0; }
inline void upd_cnt(node* &it){
	if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
}
inline void push(node*& it){
	if (it) { /* Push the lazy update */ }
}
 
// Split tree at the kth element
void split(node* t, node* &l, node* &r, int k){
    if (!t) l = r = NULL;
    else{
		push(t); // lazy push
        int cntL = cnt(t->l);
        if (k <= cntL)
            split (t->l, l, t->l, k), r = t;
        else
            split (t->r, t->r, r, k - cntL - 1), l = t;
        upd_cnt(t);
    }
}
 
// Merge trees l, r in order
void merge(node* &t, node* l, node* r){
    if (!l) t = r;
    else if(!r) t = l;
    else {
		push(l);
		push(r);
		if (l->y > r->y) merge (l->r, l->r, r), t = l;
    	else merge (r->l, l, r->l), t = r;	
	}
    upd_cnt(t);
}

// Find the kth element in the treap
node* findkth(node* &t, int k){
	if (!t) return NULL;
	int cntl = cnt(t->l);
	if (k < cntl) return findkth(t->l, k);
	if (k == cntl) return t;
	if (k > cntl) return findkth(t->r, k-cntl-1);
}
