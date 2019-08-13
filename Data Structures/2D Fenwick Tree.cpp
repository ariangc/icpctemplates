// 2D Fenwick Tree with the normal operations.
const int MAX = 1000;
int tree[MAX+1][MAX+1]; /*Starts at 1, not 0!*/

int query(int x, int y) {
	int sum=0,yy=y;
	if (x==0 || y==0) return 0;
	while (x) {
		while (y) {
			sum+=tree[x][y];
			y -= y & (-y);
		}
		x -= x & (-x);
		y = yy;
	}
	return sum;
}

void update(int x, int y, int v) {
	int yy = y;
	if ( x==0 || y==0 ) return;
	while (x<=MAX) {
		while (y<=MAX) {
			tree[x][y]+=v;
			y+=y & (-y);
		}
		x+=x & (-x);
		y=yy;
	}
}

int main(){
	REP(i,0,MAX) REP(j,0,MAX) tree[i][j] = 0;
	return 0;
}
