// Iterative, 2d, commutative segment tree.
// Read into t[n,2*n)*[m,2*m), call build().
typedef int T;
const int MAX = 1e3;
const T OpId = 0; // Identity element
// Associative, conmutative operation
T Op(T val1, T val2){
    return val1 + val2;
}
T t[2*MAX][2*MAX];
int n, m;   

void build(){
   for( int i = n-1 ; i > 0 ; i-- )
		for ( int j = 2*m ; j >= m; j-- ) 
			t[i][j] = Op(t[i<<1][j], t[i<<1|1][j]);
	for ( int i = 2*n ; i > 0 ; i-- ) 
		for ( int j = m-1 ; j > 0 ; j-- ) 
			t[i][j] = Op(t[i][j<<1], t[i][j<<1|1])
}

void mody( int x, int y ){
	int q = y;
	while (q >>= 1)
		t[x][q] = Op(t[x][q<<1], t[x][q<<1|1]);
}

void modify( int x , int y , T val ){
	t[x+=n][y+=m] = val;
	mody(x,y);
	while (x >>= 1) {
		t[x][y] = Op(t[x<<1][y], t[x<<1|1][y]);
		mody(x, y);
	}
}

T gety(int x, int yl, int yr){
	T ans = OpId;
	for ( yl += m, yr += m ; yl < yr ; yl >>= 1, yr >>= 1){
		if (yl&1) ans = Op(ans, t[x][yl++]);
		if (yr&1) ans = Op(ans, t[x][--yr]);
	}
	return ans;
}

T get(int xl, int xr, int yl, int yr){ // [xl,xr)*[yl,yr)
	T ans = OpId;
	for ( xl += n, xr += n ; xl < xr ; xl >>= 1, xr >>= 1){
		if (xl&1) ans = Op(ans, gety(xl++, yl, yr));
		if (xr&1) ans = Op(ans, gety(--xr, yl, yr));
	}
	return ans;
}
