#include <cstdio>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int, int> pii;

#define NMAX 128
#define MMAX 128

int n, m;
char text[NMAX][NMAX], pattern[MMAX][MMAX];

vector<pii> naive() {
    vector<pii> ret;
    for (int i = 0; i < n - m + 1; ++i) {
        for (int j = 0; j < n - m + 1; ++j) {
            bool chk = true;
            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (pattern[r][c] != text[i + r][j + c]) {
                        chk = false;
                        break;
                    }
                }
                if (!chk) break;
            }
            if (chk) ret.push_back(pii(i + m - 1, j + m - 1));
        }
    }
    return ret;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s [user_input] [user_output] [checker_output]\n", argv[0]);
        printf("Example: %s sample/bb_in.txt bb_out.txt bb_check.txt\n", argv[0]);
        return 0;
    }
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "r");
    FILE *c_output = fopen(argv[3], "w");

    fscanf(input, "%d%d", &m, &n);
    for (int i = 0; i < m; ++i)
        fscanf(input, "%s", pattern[i]);
    for (int i = 0; i < n; ++i)
        fscanf(input, "%s", text[i]);

    vector<pii> answer = naive();
    vector<pii> result;
    int x, y;
    while (fscanf(output, "%d%d", &x, &y) != EOF)
        result.push_back(pii(x, y));

    bool chk = (answer == result);
    if (chk)
        fprintf(c_output, "yes\n");
    else
        fprintf(c_output, "no\n");

    fclose(input);
    fclose(output);
    fclose(c_output);

    return 0;
}
