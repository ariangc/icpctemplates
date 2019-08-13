// Bron-Kerbosch algorithm for finding all the
// maximal cliques of a graph in O(3^(n/3))
// 3 ^ 13 = 1.6e6

// Call them using clique(0, (1LL << n) - 1, 0)
// n vertexs
ll adj[65];
// This algorithm finds all the maximal cliques containing an edge
// The cliques are found explicitly (the vertex of the cliques)
void clique(ll r, ll p, ll x) {
    if (p == 0 && x == 0) {
        /* r is a maximal clique */
        /* Every 1 in r is a vertex of the clique
        Then, __builtin_popcountll(r) is the size of the clique*/
        return;
        }
    int pivot = -1;
    int menor = INF;
    for (int i = 0; i < n; i++) {
        if ( ((1LL << i) & p) || ((1LL << i) & x) ) {
            int x = __builtin_popcountll(p & (~(adj[i])));
            if (x < menor) {
                pivot = i;
                menor = x;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if ((1LL << i) & p) {
            if (pivot != -1 && adj[pivot] & (1LL << i)) continue;
            clique(r | (1LL << i), p & adj[i], x & adj[i]);
            p = p ^ (1LL << i);
            x = x | (1LL << i);
        }
    }
}

// This one has the same idea, but is faster
// However, it only finds the size of the cliques
void clique2(int r, ll p, ll x){
    if(p == 0 && x == 0){
        // r is the size of the clique
    }
    if(p == 0) return;
    int u = __builtin__ctzll(p | x);
    ll c = p & ~ adj[u];
    while(c){
        int v = __builint_ctzll(c); //Number of trailing zeros
        clique(r + 1, p & adj[v], x & adj[v]);
        p ^= (1LL << v);
        x |= (1LL << v);
        c ^= (1LL << v);
    }
}
