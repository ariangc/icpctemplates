// Fenwick tree: O(log(n)) accumulated sum queries.

ll bitadd[N] ; 
ll bitsub[N] ; 
int n ; 

void update( int idx, ll val1, ll val2 ){
	while( idx <=n ) {
		bitadd[idx] += val1 ; 
		bitsub[idx] += val2 ; 
		idx += idx & -idx ;
	}
}

void updaterange( int l , int r , ll val ){
	update( l , val , (l-1)*val ) ;
	update( r+1 , -val , -r*val) ;
}

ll get( int idx ){
	ll add = 0 , sub = 0, aux = idx ;
	while ( idx > 0 ){
		add += bitadd[idx] ;
		sub += bitsub[idx] ;	
		idx -= idx & -idx ;
	}
	return aux*add - sub ;
}

