#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *fp;
    int c;
    int table[256];

    int i;

    for(i = 0; i < 256; i++)
        table[i] = 0;

    fp = fopen(__FILE__, "r");

    if(fp == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    while((c = fgetc(fp)) != EOF) {
        table[c]++;
    }

    fclose(fp);

    for(i = 0; i < 256; i++) {

        if(table[i] > 0) {

            if(i == '\n')
                printf("\\n : %d\n", table[i]);

            else if(i == ' ')
                printf("' ' : %d\n", table[i]);

            else if(i == '\t')
                printf("\\t : %d\n", table[i]);

            else
                printf("%c : %d\n", i, table[i]);
        }
    }

    return 0;
}
