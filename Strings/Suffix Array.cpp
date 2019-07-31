/*
    Suffix Array built in O(nlog^2(n))
    Call functions and members as SA::<function name>
    
    sa[i]: i-th suffix starting position in the sorted array
    lcp[i]: Longest common prefix size between suffix on sa[i] and sa[i+1]
 
*/

const int MAXN = 5e4 + 2;

namespace SA{
    string S;
    int N, gap;
    int sa[MAXN], pos[MAXN], tmp[MAXN], lcp[MAXN];

    bool sufCmp(int i, int j){
        if (pos[i] != pos[j])
            return pos[i] < pos[j];
        i += gap;
        j += gap;
        return (i < N && j < N) ? pos[i] < pos[j] : i > j;
    }

    void buildSA(){
        N = sz(S);
        FER(i,0, N) sa[i] = i, pos[i] = S[i];
        for (gap = 1;; gap *= 2){
            sort(sa, sa + N, sufCmp);
            FER(i, 0, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
            FER(i, 0, N) pos[sa[i]] = tmp[i];
            if (tmp[N - 1] == N - 1) break;
        }
    }

    void buildLCP(){
        for (int i = 0, k = 0; i < N; ++i) if (pos[i] != N - 1){
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
            ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }
};

// O(nlog^2n) fast suffix array, 0.6s for N = 10^6
const int N = 1000010;  

// sa is the list of sorted suffixes.
// rnk is the position of i in the sorted list
int n,t;
int rnk[N],sa[N], bc[256], lcp[N];
char s[N];

void fix_index(int b, int e){
    int lastpk, pk, d;
    lastpk = rnk[sa[b]+t];
    d = b;
    FER(i,b,e){
        if (((pk = rnk[sa[i]+t]) != lastpk) 
            && (b > lastpk || pk >= e)){
            lastpk = pk;
            d = i;
        }
        rnk[sa[i]]= d;
    }
}

void suff_arr(){
    FER(i,0,256) bc[i]=0;
    FER(i,0,n) bc[(int)s[i]]++;
    FER(i,1,256) bc[i] += bc[i-1];
    for (int i = n-1; i >= 0; i--) sa[--bc[(int)s[i]]] = i;
    for (int i = n-1; i >= 0; i--) rnk[i] = bc[(int)s[i]];
    for (t = 1; t < n; t<<=1){
        for (int i = 0, j = 1; i < n; i = j++){
            while (j < n && rnk[sa[j]] == rnk[sa[i]]) ++j;
            if (j-i > 1){
                sort(sa+i, sa+j, [&](const int& i, const int& j){
                    return rnk[i+t] < rnk[j+t];
                });
                fix_index(i, j);        
            }
        }
    }
}
