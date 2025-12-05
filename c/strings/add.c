#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* addStrings(const char *a, const char *b) {
    int n = strlen(a);
    int m = strlen(b);
    int i = n - 1, j = m - 1, carry = 0;
    
    // Result can be at most max(n, m) + 1
    
    char *res = malloc(n>m? n+1:m+1);
    int k = 0;

    while (i >= 0 || j >= 0 || carry) {
        int da = (i >= 0) ? a[i] - '0' : 0;
        int db = (j >= 0) ? b[j] - '0' : 0;

        int sum = da + db + carry;
        res[k++] = (sum % 10) + '0';
        carry = sum / 10;

        i--;
        j--;
    }

    // Reverse the result
    for (int left = 0, right = k - 1; left < right; left++, right--) {
        char tmp = res[left];
        res[left] = res[right];
        res[right] = tmp;
    }

    res[k] = '\0';
    return res;
}

int main() {
    char *sum = addStrings("1122334455", "12");
    printf("%s\n", sum);
    free(sum);
    return 0;
}

