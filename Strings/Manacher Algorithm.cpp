// Manacher's algorithm for finding all palindromes
// in a string in O(n).

int n;
char s[200200];
char aux[100100];
int p[200200];

int main(){
	scanf("%s%n", aux, &n);
	s[0] = '^';
	s[1] = '#';
	REP(i,0,n){
		s[2*i+2] = aux[i];
		s[2*i+3] = '#';
	}
	s[2*n+2] = '\0';
	int c = 0, r = 0;
	REP(i,0,2*n+2){
		if (i > r) p[i] = 0;
		else p[i] = min(r-i, p[2*c-i]);
		while (s[i+p[i]+1] == s[i-p[i]-1]) p[i]++;
		if (i + p[i] > r){
			c = i;
			r = i + p[i];
		}
	}

	printf("%s\n", s);
	REP(i,0,2*n+2) {
		printf("%d", p[i]);
	}
	printf("\n");
	return 0;
}
