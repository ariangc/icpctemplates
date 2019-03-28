//Lazy Propagation Segment Tree

struct SegmentTree{
	int arr[N], laz[4*N], t[4*N];
	int n;
	int OpId = 0, UpdId = 0;

	SegmentTree(){}
	int Op(int a, int b){ return a + b;}
	void build(int u, int a, int b){
		if(a+1 == b){
			t[u] = arr[a];
			return;
		}
		build(u << 1, a, (a + b) >> 1);
		build(u << 1 | 1, (a + b) >> 1, b);
		t[u] = Op(t[u << 1], t[u << 1 | 1]);
	}

	void push(int u, int a, int b){
		if(laz[u]){
			t[u] += (int)(b - a) * laz[u];
			if(a + 1 != b){
				laz[u << 1] += laz[u];
				laz[u << 1 | 1] += laz[u];
			}
		}
		laz[u] = UpdId;
	}

	void update(int u, int a, int b, int l, int r, int x){
		if(laz[u] != UpdId) push(u, a, b);
		if(b <= l || a >= r) return;
		if(a >= l && b <= r){
			laz[u] += x;
			push(u, a , b);
			return ;
		}
		update(u << 1, a, (a + b) >> 1, l, r, x);
		update(u << 1 | 1, (a + b) >> 1, b, l, r, x);
		t[u] = Op(t[u << 1], t[u << 1 | 1]);
	}

	int query(int u, int a, int b, int l, int r){
		if(laz[u] != UpdId) push(u, a, b);
		if(b <= l || a>=r) return 0;
		if(a >= l && b <= r) return t[u];
		int lch = query(u << 1, a, (a + b) >> 1, l, r);
		int rch = query(u << 1 | 1, (a + b) >> 1, b, l, r);
		return lch + rch;
	}

	inline void build(){ build(1, 0, n);}
	inline void update(int l, int r, int x){ update(1 ,0, n, l, r, x);}
	inline int query(int l, int r){ return query(1, 0, n, l, r);}
};