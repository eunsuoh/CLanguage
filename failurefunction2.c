int pmatch(char *string, char *pat, int *fail) {
    int i = 0, j = 0;
    int lens = strlen(string);
    int lenp = strlen(pat);

    while (i < lens && j < lenp) {
        if (string[i] == pat[j]) {
            i++;
            j++;
        } else if (j == 0) {
            i++;
        } else {
            j = fail[j - 1] + 1;
        }
    }

    return (j == lenp) ? i - lenp : -1;
}
