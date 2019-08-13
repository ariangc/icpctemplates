// Numerical Integration with Simpson's Rule
// Error is f^4(x) * (b-a)^5 / 2880

int n = 500; // n tiene que ser par
ld f( ld x ){ return sqrt( 1 + 1.0/x ) / x; }
int main(){
	int a , b ;
	while( cin >> a >> b ){
		ld dt = ( b - a )/(ld)n;
		ld I = 0 , pos = a;
		for( int i = 0 ; i < n ; i +=2 )
			I += dt * ( f( pos ) + 4*f( pos + dt ) + 
				f( pos = pos + dt + dt ));
		printf( "%.2f\n" , double( I/3.0 ) );
	}
}
