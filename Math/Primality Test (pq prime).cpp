// Primality test for [0,3*10^18] (Lucas97)
const ll MOD = 1e9 + 7;
const int MN = 1e6 + 2;
bool primos[MN * 5]; // 1 if is prime, 0 otherwise 
int cnt = 0;  // cnt denotes the number of primes
int prime[MN * 5];

ll mulmod(ll a, ll b, ll c) {
  ll x = 0, y = a % c;
  while (b) {
    if (b & 1) x = (x + y) % c;
    y = (y << 1) % c;
    b >>= 1;
  }
  return x % c;
}

ll fastPow(ll x, ll n, ll mod) {
  ll ret = 1;
  while (n) {
    if (n & 1) ret = mulmod(ret, x, mod);
    x = mulmod(x, x, mod);
    n >>= 1;
  }
  return ret;
}

bool isPrime(ll n) {
   // Verificar primero los casos pequeños (hasta 1e6)
  if(n <= 5 * MN - 10){
    if(!primos[n]) return 1;
    else return 0;
  }
  // Fin de verificacion
  ll d = n - 1;
  int s = 0;
  while (d % 2 == 0) {
    s++;
    d >>= 1;
  }
  // These values will work for any number smaller than 3*10^18 
  //(Only 9 are necessary)
  int a[11] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };
  for(int i = 0; i < 11; i++) {
    bool comp = fastPow(a[i], d, n) != 1;
    if(comp) for(int j = 0; j < s; j++) {
      ll fp = fastPow(a[i], (1LL << (ll)j)*d, n);
      if (fp == n - 1) {
        comp = false;
        break;
      }
    }
    if(comp) return false;
  }
  return true;
}
