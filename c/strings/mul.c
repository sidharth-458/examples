#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* mul_str(const char *a, const char *b) {
    int n = strlen(a), m = strlen(b);                 // lengths of input strings
    int len = n + m;                                  // max possible digits
    int *res = calloc(len, sizeof(int));              // result digit array

    for (int i = n-1; i >= 0; --i)                    // loop through digits of a
        for (int j = m-1; j >= 0; --j)                // loop through digits of b
            res[i+j+1] += (a[i]-'0') * (b[j]-'0');    // accumulate products

    for (int k = len-1; k > 0; --k) {                 // propagate carries
        res[k-1] += res[k] / 10;
        res[k] %= 10;
    }

    int start = 0;                                    // skip leading zeros
    while (start < len-1 && res[start] == 0) ++start;

    char *s = malloc(len - start + 1);                // allocate output string
    for (int i = start; i < len; ++i)                 // convert digits to chars
        s[i - start] = '0' + res[i];
    s[len - start] = '\0';                            // null-terminate

    free(res);                                        // free temporary buffer
    return s;                                         // return result string
}

int main(void) {
    char *r = mul_str("123456789123456789", "987654321987654321");
    puts(r);
    free(r);
}

