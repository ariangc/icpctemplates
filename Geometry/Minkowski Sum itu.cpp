//Calcula suma de Minkowski en O(n + m)
//A y B deben estar en sentido antihorario
inline bool compare(PT a, PT b){
	// mas abajo, mas a la izquierda
	if(a.y < b.y) return 1;
	if(a.y == b.y) return a.x < b.x;
	return 0;
}

vector<PT> minkow_sum(const vector<PT>& a, const vector<PT>& b){
	vector< PT > out;
	out.clear();
	int lena = int(a.size());
	int lenb = int(b.size());
	int i = 0, j = 0;
	for(int q = 0; q < lena; ++q) if(compare(a[q], a[i])) i = q;
	for(int q = 0; q < lenb; ++q) if(compare(b[q], b[j])) j = q;
	ll pr;
	int nxti, nxtj;	
	do{
		out.pb(a[i] + b[j]);
		nxti = (i + 1) % lena;
		nxtj = (j + 1) % lenb; 
		pr = cross(a[nxti] - a[i], b[nxtj] - b[j]);
		if(pr > 0) i = nxti;
		else if(pr < 0) j = nxtj;
		else i = nxti, j = nxtj; // paralelas, subo en ambas
	}while((a[i] + b[j]) != out[0]);
	return out;
}

