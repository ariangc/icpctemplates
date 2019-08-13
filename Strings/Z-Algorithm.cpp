//Zfun(i) devuelve la longitud del maximo prefijo que empieza en i
vi Zfun(string s){
	vi Z(s.sz,0);
	int l = 0, r = 0;
	REP(i,1,sz(s)){
		if ( i<=r ) Z[i] = min(Z[i-l], r-i+1);
		while ( i+Z[i]<s.sz and s[i+Z[i]]==s[Z[i]] ) Z[i]++;
		if ( i+Z[i]-1>r ) l = i, r = i+Z[i]-1;
	}
	return Z;
}
