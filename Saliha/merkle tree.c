#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int hash(char *str) {
    int h = 0;
    for (int i = 0; str[i]; i++)
        h = h * 31 + str[i];
    return h;
}
void intToStr(int num, char *str) {
    sprintf(str, "%d", num);
}
void buildMerkleTree(char data[][10], int n) {
    int levelSize = n;
    int hashes[100];
    for (int i = 0; i < n; i++) {
        hashes[i] = hash(data[i]);
    }
    while (levelSize > 1) {
        int j = 0;

        for (int i = 0; i < levelSize; i += 2) {
            char combined[50];
            if (i + 1 < levelSize) {
                sprintf(combined, "%d%d", hashes[i], hashes[i + 1]);
            } else {
                sprintf(combined, "%d%d", hashes[i], hashes[i]);
            }

            hashes[j++] = hash(combined);
        }

        levelSize = j;
    }

    printf("Merkle Root: %d\n", hashes[0]);
}

int main() {
    char data[4][10] = {"A", "B", "C", "D"};

    buildMerkleTree(data, 4);

    return 0;
}
