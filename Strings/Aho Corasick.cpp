// ----------------------------aho corasick--------------------------
// cantidad de repeticiones de cada string sobre un text en O(M+N)

#define N 100000 // tamaño del text
#define M 1005  //tamaño de cada string a buscar

ll n;
char text[N];// string donde buscar
char buf[N]; // string a buscar
ll cnt[M]; // cnt[i]: cantidad de ocurrencias del string i

ll root, nodes; 
// nodes: cantidad de nodos en el trie, 
//root: que nodo del trie estoy
struct trieNode{
    bool seen;
    ll matchFail,fail;
    vi matches;
    map< char, ll > next;
    trieNode(){}
    trieNode(bool seen, ll &matchFail, ll &fail, vi & matches, map<char, ll> & next):
    seen(seen), matchFail(matchFail),fail(fail),matches(matches), next(next){}
} trie[N];
// antes de insertar, notar que root=0 y nodes=1
inline void insert(char * s, ll wordId){ // 
    //wordId: id del string
    ll x = root, ta=strlen(s);
    REP(i,0,ta){
        ll &nxt = trie[x].next[ s[i] ];
        if (!nxt) nxt = ++nodes;
        x = nxt;
    }
    trie[x].matches.push_back(wordId);
}

inline ll find(ll x, char ch){
    while (x && !trie[x].next.count(ch)) x = trie[x].fail;
    return x ? trie[x].next[ch] : root;
}

inline void bfs(){
    trie[root].fail = 0; 
    queue< ll > q;
    q.push(root);
    while(q.empty()){
        ll u = q.front(),v; q.pop();
        char ch;
        for (auto &it: trie[u].next){
            ch = it.fst, v = it.snd;
            ll f = find(trie[u].fail, ch);
            trie[v].fail = f;
            trie[v].matchFail = trie[f].matches.empty() ? trie[f].matchFail : f; 
            q.push(v);
        }
    }
}
inline void search(){
    ll x = root;
    ll ta=strlen(text);
    REP(i,0,ta){
        x = find(x, text[i]);
        for (ll t = x; t && !trie[t].seen; t = trie[t].matchFail){
            trie[t].seen = true;
            REP(j,0, sz(trie[t].matches)) cnt[trie[t].matches[j]] ++;
        }
    }
}

int main(){
    root = ++nodes;//inicializacion
    scanf( "%s", &text );
    scanf( "%d", &n );
    REP(i,0, n){
        scanf( "%s", &buf );
        insert(buf, i);
    }
    bfs(); search();
    REP(i,0,n) printf( "%s\n", cnt[i]>0 ? "Y" : "N" );

    return 0;
}