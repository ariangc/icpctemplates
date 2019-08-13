//Cada query esta en (low[i], high[i]] 
//Tocheck tiene los valores acutales a verificar
//en el bsearch 

//Solved puede tener 1, -1
//1: el unico valor posible cumple
//-1: no hay respuesta  
 
int low[MAXN]; 
int high[MAXN]; 
char solved[MAXN]; 
vector< int > tocheck[MAXN]; 
 
int main(){	
	// Leer n, m
	// Leer a[i], b[i] (i en [1, m]) 
	// Leer q: queries
	// Leer x[i], y[i], z[i] (i en [0, q])
	
	for(int i = 0; i < q; ++i)
	low[i] = 0, high[i] = m;
	
	bool done = 0;
	DSU uf(n); // DSU structure
	int curvis;
	while(!done){
		done = 1;
		for(int i = 0; i < q; ++i){
			int mid = (low[i] + high[i]) >> 1;
			tocheck[mid].pb(i); 
		}	
		uf.clear(n); 
		int last = -1;
		for(int value = 0; value <= m; ++value){
			if(tocheck[value].empty()) continue;
			for(int i = last + 1; i <= value; ++i) 
				uf.join(a[i], b[i]); 
			last = value; 
			while(!tocheck[value].empty()){
				int id = tocheck[value].back();
				tocheck[value].pop_back();
				int u = x[id], v = y[id];
				int visited = z[id]; 
				if(low[id] + 1 == high[id]) solved[id] = 1;
				if(uf.connected(u, v)) curvis = uf.size(u);
				else curvis = uf.size(u) + uf.size(v);
				if(curvis >= visited) high[id] = value; 
				else low[id] = value;
				if(low[id] == high[id]) solved[id] = -1; 
			}
		}
		for(int i = 0; i < q; ++i) 
			if(solved[i] == 0) done = 0;
	}
	for(int i = 0; i < q; ++i) 
		if(solved[i] == -1) cout << -1 << endl; 
		else cout << high[i] << endl;  
}
