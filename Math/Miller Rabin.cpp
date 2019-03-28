//Miller-Rabin primality test

ll pow(ll a, ll b, ll c){
    ll ans = 1;
    while(b){
        if(b&1) ans = (1LL*ans*a)%c;
        a = (1LL*a*a)%c;
        b >>=1;
    }
    return ans;
}

bool miller(ll p, ll it = 10){
    if(p<2) return 0;
    if(p!=2 && (p&1) == 0) return 0;
    ll s=p-1;
    while((s&1) == 0) s>>=1;
    while(it--){
        ll a = rand()%(p-1)+1, temp = s;
        ll mod = pow(a,temp,p);
        while(temp!= p-1 && mod!=1 && mod!=p-1){
            mod = (1LL*mod*mod)%p;
            temp<<=1;
        }
        if(mod!=p-1 && (temp&1) == 0) return 0;
    }
    return 1;
}
