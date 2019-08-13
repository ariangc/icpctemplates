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

//Criba para phi
int phi[MAX];

void CribaEuler(){
	REP(i,0, MAX) primo[i] = 1, phi[i] = 1;
	primo[0] = primo[1] = false;
	REP(i,2,MAX){
		if(primo[i]){
			phi[i] = i - 1;
			for(int j = i+i; j < MAX; j += i){
				primo[j] = false;
				int pot = 1, aux = j/i;
				while( aux % i == 0 ){
					aux /= i, pot *= i;
				}
				phi[j] *= (i-1)*pot ;
			}
		}
	}
}