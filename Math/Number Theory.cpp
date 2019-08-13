// return a % b (positive value)
int mod(int a, int b) {
  return ((a%b)+b)%b;
}

// returns d = gcd(a,b); finds x,y such that d = ax + by
int extended_euclid(int a, int b, int &x, int &y) {  
  int xx = y = 0;
  int yy = x = 1;
  while (b) {
    int q = a/b;
    int t = b; b = a%b; a = t;
    t = xx; xx = x-q*xx; x = t;
    t = yy; yy = y-q*yy; y = t;
  }
  return a;
}

// finds all solutions to ax = b (mod n)
vi modular_linear_equation_solver(int a, int b, int n) {
  int x, y;
  vi solutions;
  int d = extended_euclid(a, n, x, y);
  if (!(b%d)) {
    x = mod (x*(b/d), n);
    for (int i = 0; i < d; i++)
      solutions.push_back(mod(x + i*(n/d), n));
  }
  return solutions;
}

// computes b such that ab = 1 (mod n), returns -1 on failure
int mod_inverse(int a, int n) {
  int x, y;
  int d = extended_euclid(a, n, x, y);
  if (d > 1) return -1;
  return mod(x,n);
}

// Chinese remainder theorem: find z such that
// z % x[i] = a[i] for all i.  Note that the solution is
// unique modulo M = lcm_i (x[i]).  Return (z,M).  On 
// failure, M = -1.  Note that we do not require the a[i]'s
// to be relatively prime.
// Note that it's NOT necessary that x[i] > 0
// But if they are postive, it makes MODULO > 0 (convenient)
ii chinese_remainder(int x, int a, int y, int b) {
  int s, t;
  x = abs(x) , y = abs(y); // x and y NEED to be positive here
  int d = extended_euclid(x, y, s, t);
  if (a%d != b%d) return make_pair(0, -1);
  return make_pair(mod(s*b*x+t*a*y,x*y)/d, x*y/d);
}
ii chinese_remainder(const vi &x, const vi &a) {
  ii ret = make_pair(a[0], abs(x[0]));
  for (int i = 1; i < x.size(); i++) {
    ret = chinese_remainder(ret.second, ret.first, x[i], a[i]);
    if (ret.second == -1) break;
  }
  return ret;
}

// Criba en O(n)
// p[i] indica el valor del primo i-esimo 
// A[i] indica que el menor factor primo de i 
//			es el primo A[i] - esimo 
#define MAXN 100000
int A[MAXN + 1], p[MAXN + 1], pc = 0;  
void sieve()  
{ 
    for(int i=2; i<=MAXN; i++){ 
        if(!A[i]) p[A[i] = ++pc] = i; 
        for(int j=1; j<=A[i] && i*p[j]<=MAXN; j++) 
            A[i*p[j]] = j; 
    } 
} 

// Lucas Teorem 
// Cuando n y m son grandes y se pide comb(n,m)%MOD, donde 
// MOD es un numero primo, se puede usar el Teorema de Lucas.
ll comb( ll n, ll k ){
	ll ans = 1;
    while( n > 0 ){
        ll ni = n%MOD,ki = k%MOD;
        n /= MOD; k /= MOD;
        if( ni - ki < 0 )return 0;
        ll temp = (FP[ki]*FP[ni-ki])%MOD;
        temp = (temp*F[ni])%MOD;
        ans = (ans*temp)%MOD;
    }
    return ans;
}
