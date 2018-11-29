#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;
typedef unsigned char uchar;
typedef pair<int, int> pii;

#define TMAX (1 << 17)
#define CMAX 128

int cnt = 0;
map<char, int> m;

class Trie {
public:
	vector<vector<int>> trie; /* trie graph */
	vector<int> out; /* indicate which is terminal node */
	int t, p;

	/* initializer */
	Trie() : t(0), p(0) {
		trie.push_back(vector<int>(CMAX, 0));
		out.push_back(0);
	}

	/* insert x to the trie graph */
	void insert(string &x) {
		if (t >= TMAX - 1) return;
		int p = 0;
		for (auto &ch : x) {
			int c = m[ch];
			if (!trie[p][c]) {
				trie[p][c] = ++t;
				trie.push_back(vector<int>(CMAX, 0));
				out.push_back(0);
			}
			p = trie[p][c];
		}
		out[p] = 1;
	}

	/* find x in trie graph and return its node index
	 * if there is no such string, return -1 */
	int find(string &x) {
		int p = 0;
		for (auto &ch : x) {
			int c = m[ch];
			if (!trie[p][c]) return -1;
			p = trie[p][c];
		}
		return p;
	}

	/* similar to find(x), but only perform last character */
	int next(string &x) {
		int c = m[x.back()];
		if (!trie[p][c]) {
			p = 0;
			return -1;
		}
		return p = trie[p][c];
	}
};

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Usage: %s [input] [output]\n", argv[0]);
		printf("Example: %s sample/infile.txt encoding.txt\n", argv[0]);
		return 0;
	}

	FILE *in = fopen(argv[1], "rb");
	FILE *out = fopen(argv[2], "wb");

	fseek(in, 0, SEEK_END);
	int n = (int)ftell(in);
	rewind(in);

    char *text = (char*)malloc((n + 1) * sizeof(char));
	fread(text, sizeof(char), n, in);
	text[n] = '\0';

	Trie trie;
	vector<pii> enc;

    /* make the dictionary from the text */
	int t = 0;
	string phrase;
	for (int i = 0; i < n; ++i) {
		char c = text[i];
		phrase.push_back(c);
		if (!m.count(c)) m[c] = ++cnt;

		// int here = trie.find(phrase);
		int here = trie.next(phrase);
		if (here == -1 || i == n - 1) { /* EOF handling */
			trie.insert(phrase);
			enc.push_back({ t, c });
			phrase.clear();
			t = 0;
		}
		else {
			t = here;
		}
	}

    /* generate the bitstream from the dictionary */
    for (auto &here : enc) {
        int index = here.first;
        char ch = here.second;
        
        uchar ch1, ch2, ch3;
        ch3 = (uchar)(((index & 0x01) << 7) + (ch & 0x7F));
        ch2 = (uchar)((index >> 1) & 0xFF);
        ch1 = (uchar)((index >> 9) & 0xFF);

        fwrite(&ch1, sizeof(uchar), 1, out);
        fwrite(&ch2, sizeof(uchar), 1, out);
        fwrite(&ch3, sizeof(uchar), 1, out);
    }

    free(text);
    fclose(in);
	fclose(out);

	return 0;
}
