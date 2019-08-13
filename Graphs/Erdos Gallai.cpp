//Erdos-Gallai Theorem

bool erdosgallai(vector<int> d) {
	sort(all(d), greater<int>());
	vector<ll> pd(sz(d));
	int n = sz(d), p = n-1;
	FER(i, 0, n) pd[i] = d[i] + (i > 0 ? pd[i-1] : 0);
	FER(k, 1, n + 1){
		while(p >= 0 && d[p] < k) p--;
		ll sum;
		if (p >= k-1) sum = (p-k+1)*1ll*k + pd[n-1] - pd[p];
		else sum = pd[n-1] - pd[k-1];
		if (pd[k-1] > k*(k-1LL) + sum) return false;
	}
	return (pd[n-1] % 2 == 0);
}