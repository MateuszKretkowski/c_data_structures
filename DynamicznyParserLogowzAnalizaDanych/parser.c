#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void writeLogs(int *localLines) {
    FILE *f = fopen("./log.txt", "w");
    srand(time(0));
    int randomRows = (rand() % 2000) + 1;
    *localLines = randomRows;
    for (int i = 0; i < randomRows; i++) {
        int randomLen = (rand() % 200) + 1;
        char *str = malloc((randomLen) * sizeof(char));
        for (int j = 0; j < randomLen; j++) {
            str[j] = 'a' + rand() % 26;
        }
        fwrite(str, sizeof(char), randomLen, f);
        fputs("\n", f);
        free(str);
    }
}

char *pickLongestLine() {
    FILE *f = fopen("./log.txt", "r");
    if (!f) {
        perror("Nie można otworzyć pliku");
        return NULL;
    }

    char line[1024];
    char *longest = NULL;

    while (fgets(line, sizeof(line), f)) {
        size_t len = strlen(line);
        if (!longest || len > strlen(longest)) {
            char *temp = realloc(longest, (len + 1) * sizeof(char));
            if (!temp) {
                perror("Błąd realloc");
                free(longest);
                fclose(f);
                return NULL;
            }
            longest = temp;
            strcpy(longest, line);
        }
    }

    fclose(f);
    return longest;
}

int main() {
    int lines;
    writeLogs(&lines);
    char *actstr = pickLongestLine();

    if (actstr) {
        printf("Longest Line in the entire file: %s", actstr);
        free(actstr);
    }

    return 0;
}