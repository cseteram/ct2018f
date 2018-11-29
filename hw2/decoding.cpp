#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
typedef unsigned char uchar;

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Usage: %s [input] [output]\n", argv[0]);
		printf("Example: %s encoding.txt outfile.txt\n", argv[0]);
		return 0;
	}

	FILE *in = fopen(argv[1], "rb");
	FILE *out = fopen(argv[2], "wb");

    /* decode the bitstream and make the dictionary */
    vector<pii> dict;
    while (true) {
        uchar buf[3];
        size_t rc;
        rc = fread(buf, sizeof(uchar), 3, in);
        if (rc < 3 * sizeof(uchar)) break;
        
        int idx = 0;
        idx += buf[0]; idx = (idx << 8);
        idx += buf[1]; idx = (idx << 1);
        idx += (buf[2] & 0x80) >> 7;

        int ch = (buf[2] & 0x7f);
        dict.push_back({idx, ch});
    }
    
    /* restore the text from the dictionary */
    for (int i = 0; i < (int)dict.size(); ++i) {
        string phrase;
        int j = i;
        while (j >= 0) {
            phrase.push_back(dict[j].second);
            j = dict[j].first - 1;
        }
        reverse(phrase.begin(), phrase.end());
        fwrite(phrase.c_str(), sizeof(char), phrase.size(), out);
    }

    fclose(in);
	fclose(out);

	return 0;
}
