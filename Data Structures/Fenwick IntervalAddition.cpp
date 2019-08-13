// Interval Addition queries done with Fenwick Tree
const int MAXN = 1e5 + 1;
int n,c;
ll fenwick_add[MAXN + 1] , fenwick_mul[MAXN +1] ; 

void internal_update(int idx, ll mul, ll add){
	while( idx <= n ){
		fenwick_mul[idx] += mul; 
		fenwick_add[idx] += add; 
		idx |= (idx + 1); 
	}
}

void update_interval(int le, int ri, ll val){
	internal_update(le,val, -val*(le-1));
	internal_update(ri,-val, val*ri); 
}	


ll Recover_interval(int idx){
	ll mul = 0 , add = 0; 
	int start = idx; 
	while(idx >= 0){
		mul += fenwick_mul[idx]; 
		add += fenwick_add[idx];
		idx = (idx & (idx + 1) ) - 1;
	} 
	return mul*start + add; 
}

int main(){
	fast_io();
	int tc; cin >> tc; 
	int tipo,p,q; 	
	ll v;
	for(int tt = 0; tt < tc ; ++tt){
		cin >> n >> c; 
		for(int i = 0 ; i <= n ; ++i) 
			fenwick_mul[i] = fenwick_add[i] = 0;
		for(int i = 0; i<c ; ++i){
			cin >> tipo >> p >> q;
			if(tipo) {
				ll z = Recover_interval(q) - Recover_interval(p-1);
				cout << z << endl;
			}
			else cin >> v, update_interval(p,q,v);
		}
	}
	return 0;
}
