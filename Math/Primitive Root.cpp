// If a primitive root exists, there are phi(phi(n)) of them */

//Primitive root modulo p(prime p>=2) 
//Complexity: O(plog²p)
int generator(int p){
		int phi = p - 1, np = phi ;
		vector<int>fact;
		for(int i = 2; i*i<=np ; ++i){
			if(np%i == 0){
				fact.pb(i);
				while(np%i == 0) np/=i;
			}
		}
		if(np > 1) fact.pb(np);
		for(int ret = 1; ret < p ; ++ret){
			bool ok = 1;
			for(int i = 0; i<fact.size(); ++i){
				if( binpow(ret,phi/fact[i],p) == 1LL){
				ok = 0; break;
				}	
			}
			if(ok) return ret;
		}
		return -1;
}		
		
//Probabilistic method , Complexity: O(loglogp *  p)
ll prob_generator(ll p){
	ll g , order; 
        while(1){
        	g = rand() % (p - 1) + 1;
        	ll G = 1;
        	for(order = 1 ;; ++order){
          	  G = (G * g) % p;
          	  if(G == 1) break;
        	}
       	        if(order == p-1) break;
     	}
	return g;
}
