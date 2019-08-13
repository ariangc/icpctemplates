// FFT adapted from the MIT ACM Reference
// Usage: call init for size 2^pw
// Then fill the data array and call transform()
// WARNING: DECLARE FFT INSTANCES ONLY GLOBALLY

double PI = acos(-1);
struct cpx {
	double a, b;
	cpx() : a(0), b(0) { }
	cpx(double a, double b) : a(a), b(b) { }
	const cpx operator+(const cpx &c) const
		{return cpx(a + c.a, b + c.b);}
	const cpx operator-(const cpx &c) const
		{return cpx(a - c.a, b - c.b);}
	const cpx operator*(const cpx &c) const
		{return cpx(a*c.a - b*c.b, a*c.b + b*c.a);}
};

const int FMAX = 140000;
struct FFT {
	cpx data[FMAX];
	cpx roots[FMAX];
	int rev[FMAX];
	int s, n;

	void init(int pw){
		s = pw;
		n = (1 << s);
		REP(i,0,n) REP(j,0,s) 
			if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s-j-1));
		roots[0] = cpx(1, 0);
		cpx mult = cpx(cos(2*PI/n), sin(2*PI/n));
		REP(i,1,n+1) roots[i] = roots[i-1] * mult;
	}

	cpx temp[FMAX];
	void transform(bool inverse = false){
		REP(i,0,n) temp[i] = data[rev[i]];
		REP(i,0,n) data[i] = temp[i];
		REP(i,1,s+1){
			int m = (1 << i), md2 = m / 2;
			int start = 0, increment = (1 << (s-i));
			if (inverse) {
				start = n;
				increment *= -1;
			}
			cpx t, u;
			for (int k = 0; k < n; k += m) {
				int index = start;
				REP(j,k,md2+k){
					t = roots[index] * data[j+md2];
					index += increment;
					data[j+md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}
		if (inverse) REP(i,0,n){
			data[i].a /= n;
			data[i].b /= n;
		}
	}
};

const int MAX = 140000;

FFT pga,pgb;
int main(){
	int n = 3;
	vector<int> a = {2,3,9};
	vector<int> b = {5,7,2};
	vector<int> c = {0,0,0};

	int pw = 0;
	while ((1<<pw) < max(sz(a),sz(b))) pw++;

	pga.init(pw);
	pgb.init(pw);
	int k = (1<<pw);
	a.resize(k);
	b.resize(k);
	c.resize(k);
	REP(i,n,k) a[i] = b[i] = c[i] = 0;

	REP(i,0,k) pga.data[i] = cpx(a[i], 0);
	pga.transform();
	REP(i,0,k) pgb.data[i] = cpx(b[i], 0);
	pgb.transform();
	REP(i,0,k) pga.data[i] = pga.data[i] * pgb.data[i];
	pga.transform(true);

	REP(i,0,k) c[i] = (int) (pga.data[i].a + 0.5);
	REP(i,0,n) cout << c[i] << " "; 
			
	return 0;
}
