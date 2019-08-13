ll comb[105][105];

//Devuleve la comb(n,k) % m para n,k grandes y m pequeno

ll lucas( ll n , ll k , ll m ){
	//Se puede precalcular la combinatoria afuera
	REP(i,0,52) REP(j,0,52){
		if( j == 0 ) comb[i][0] = 1;
		else if( j > i ) comb[i][j] = 0;
		else comb[i][j] = ( comb[i-1][j] + comb[i-1][j-1] ) % m;
	}

	ll ans = 1, x, y;
	
	while( n ){
		x = n % m, y = k % m;
		ans = ( ans * comb[x][y] ) % m;
		n /= m, k /= m;
	}
	return ans;
}
