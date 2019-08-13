// KMP algorithm for finding a pattern in a string in O(n+m).

const int MAX = 1000000;

int b[MAX]; // Fail function
char p[MAX]; // Pattern string
char t[MAX]; // Text string

int n; // Text string length
int m; // Pattern string length

void kmpPreprocess(){
    int i=0, j=-1;
    b[i]=j;
    while (i<m){
        while (j>=0 && p[i]!=p[j]) j=b[j];
        i++; j++;
        b[i]=j;
    }
}

void report(int x){
	cout << "Found on: " << x << endl;
}

void kmpSearch(){
    int i=0, j=0;
    while (i<n){
        while (j>=0 && t[i]!=p[j]) j=b[j];
        i++; j++;
        if (j==m){
            report(i-j);
            j=b[j];
        }
    }
}
