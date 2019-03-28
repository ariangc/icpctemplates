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
        REP(i,0, N) sa[i] = i, pos[i] = S[i];
        for (gap = 1;; gap *= 2){
            sort(sa, sa + N, sufCmp);
            REP(i, 0, N - 1) tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
            REP(i, 0, N) pos[sa[i]] = tmp[i];
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