// Fast number input
#define getcx getchar_unlocked
inline void read(int &number) {
	number = 0;
	int ch = getcx();
	while (ch < '0' || ch > '9')
		ch = getcx();
	while(ch >= '0' && ch <= '9'){
		number = (number << 3) + (number << 1) + ch - '0';
		ch = getcx();
	}
}

int main(){
    cout << setprecision(5) << fixed; // Amount of decimal
    cout.setf(ios::showpoint); // Show decimal point
    cout.setf(ios::showpos); // Show + in positiv  
    cout << hex << dec << endl; // Hexadecimal / Normal
}
