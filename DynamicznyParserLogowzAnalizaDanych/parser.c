#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void writeLogs(int *localLines) {
    FILE *f = fopen("./log.txt", "w");
    if (!f) {
        perror("Nie można otworzyć log.txt do zapisu");
        return;
    }

    srand(time(0));
    int randomRows = (rand() % 50) + 1;
    *localLines = randomRows;

    for (int i = 0; i < randomRows; i++) {
        int randomLen = (rand() % 100) + 50;
        char *str = malloc((randomLen + 1) * sizeof(char));
        for (int j = 0; j < randomLen; j++) {
            str[j] = 'a' + rand() % 26;
        }
        str[randomLen] = '\0';
        fputs(str, f);
        fputs("\n", f);
        free(str);
    }

    fclose(f);
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