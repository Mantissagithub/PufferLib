// ci only: hash nmmo3 terrain so x86 and arm64 maps can be compared
#include "nmmo3.h"
int main(int argc, char** argv) {
    int R = 512, C = 512;
    char* terrain = calloc(R*C, 1);
    unsigned char* rendered = calloc(R*C*3, 1);
    unsigned int rng = 42;
    generate_terrain(terrain, rendered, R, C, 16, 16, &rng);
    uint64_t h = 1469598103934665603ULL;
    int hist[256] = {0};
    for (int i = 0; i < R*C; i++) {
        h = (h ^ (unsigned char)terrain[i]) * 1099511628211ULL;
        hist[(unsigned char)terrain[i]]++;
    }
    int n = 0;
    for (int i = 0; i < 256; i++) {
        n += hist[i] != 0;
    }
    printf("%-28s hash=%016llx tile_types=%d\n", argc > 1 ? argv[1] : "",
        (unsigned long long)h, n);
}
