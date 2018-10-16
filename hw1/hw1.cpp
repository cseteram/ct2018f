#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int, int> pii;

#define NMAX 128
#define MMAX 128

int n, m;
char text[NMAX][NMAX], pattern[MMAX][MMAX];
int re[NMAX], r[NMAX];

class KMP {
public:
    string text, pattern;
    int n, m, p;
    vector<int> fail;

    /* initialize */
    void clear() {
        n = m = p = 0;
        text.clear();
        pattern.clear();
        fail.clear();
    }

    /* set x as pattern */
    void set(string &x) {
        pattern = x;
        m = (int)pattern.size();
        fail.clear();
        fail.resize(m);

        fail[0] = 0;
        int p = 0;
        for (int i = 1; i < m; ++i) {
            while (p > 0 && pattern[p] != pattern[i])
                p = fail[p - 1];
            if (pattern[p] == pattern[i]) ++p;
            fail[i] = p;
        }
    }

    /* push c to text and perform KMP (only last iteration) */
    bool push(char c) {
        text.push_back(c);

        while (p > 0 && pattern[p] != c)
            p = fail[p - 1];
        if (pattern[p] == c) ++p;
        if (p == m) {
            p = fail[p - 1];
            return true;
        }
        return false;
    }
};

class AC {
public:
    string text;
    vector<string> patterns;
    int n, m, t;

    vector<vector<int> > trie;
    vector<int> fail;
    vector<int> out;

    /* initialize */
    void clear() {
        text.clear();
        patterns.clear();
        n = m = t = 0;

        trie.clear();
        fail.clear();
        out.clear();
    }

    /* set x as patterns
     * 1) make trie
     * 2) make failure function
     * 3) make output function */
    void set(vector<string> &x) {
        patterns = x;
        m = (int)patterns.size();
        trie.push_back(vector<int>(26, 0));
        fail.push_back(0);
        out.push_back(0);

        t = 0;
        for (int i = 0; i < m; ++i) {
            int p = 0, mi = (int)patterns[i].size();
            for (int j = 0; j < mi; ++j) {
                char c = patterns[i][j] - 'a';
                if (!trie[p][c]) {
                    trie[p][c] = ++t;
                    trie.push_back(vector<int>(26, 0));
                    fail.push_back(0);
                    out.push_back(0);
                }
                p = trie[p][c];
            }
            out[p] = 1 + i;
        }

        queue<int> que; /* queue for BFS */
        for (int j = 0; j < 26; ++j) {
            if (trie[0][j]) que.push(trie[0][j]);
        }
        while (!que.empty()) {
            int here = que.front();
            que.pop();

            for (int i = 0; i < 26; ++i) {
                int there = trie[here][i];
                if (!there) continue;

                int p = fail[here];
                while (p && !trie[p][i]) p = fail[p];
                p = trie[p][i];
                fail[there] = p;
                if (out[p]) out[there] = out[p];
                que.push(there);
            }
        }
    }

    /* find patterns in text and return the location */
    vector<pii> find(string &t) {
        vector<pii> ret;
        text = t;
        n = (int)text.size();

        int p = 0;
        for (int i = 0; i < n; ++i) {
            char c = text[i] - 'a';
            while (p && !trie[p][c]) p = fail[p];
            p = trie[p][c];
            if (out[p]) ret.push_back(pii(i, out[p]));
        }

        return ret;
    }
};

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s [input] [output]\n", argv[0]);
        printf("Example: %s sample/bb_in.txt bb_out.txt\n", argv[0]);
        return 0;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");

    fscanf(input, "%d%d", &m, &n);
    for (int i = 0; i < m; ++i)
        fscanf(input, "%s", pattern[i]);
    for (int i = 0; i < n; ++i)
        fscanf(input, "%s", text[i]);

    int t = 0;
    string s;
    vector<string> patterns;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < i; ++j) {
            if (strcmp(pattern[i], pattern[j]) == 0)
                re[i] = re[j];
        }
        if (!re[i]) {
            patterns.push_back(string(pattern[i]));
            re[i] = ++t;
        }

        s.push_back(re[i]);
    }
    
    KMP kmp[NMAX];
    for (int i = 0; i < n; ++i) {
        kmp[i].clear();
        kmp[i].set(s);
    }

    vector<pii> ans;
    for (int i = 0; i < n; ++i) {
        string s(text[i]);

        /* initialize r[i] to 0 */
        for (int j = 0; j < n; ++j)
            r[j] = 0;

        /* compute R[i] using Aho-Corasick */
        AC ac;
        ac.set(patterns);
        vector<pii> ret = ac.find(s);
        for (int j = 0; j < (int)ret.size(); ++j) {
            pii x = ret[j];
            r[x.first] = x.second;
        }

        /* run j-th KMP one more step */
        for (int j = 0; j < n; ++j) {
            bool chk = kmp[j].push(r[j]);
            if (chk) ans.push_back(pii(i, j));
        }
    }

    sort(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        pii x = ans[i];
        fprintf(output, "%d %d\n", x.first, x.second);
    }

    return 0;
}
