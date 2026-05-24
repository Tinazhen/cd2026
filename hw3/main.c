#include <stdio.h>
#include <string.h>

#define MAX_INPUT 1000

#define TOKEN_LPAREN 1
#define TOKEN_RPAREN 2
#define TOKEN_PLUS 3
#define TOKEN_ONE 4
#define TOKEN_END 5
#define TOKEN_INVALID 6

char input[MAX_INPUT];
int pos = 0;
int currentToken;

/* ---------- Scanner ---------- */

int getToken() {
    while (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '\t') {
        pos++;
    }

    if (input[pos] == '\0') {
        return TOKEN_END;
    }

    if (input[pos] == '(') {
        pos++;
        return TOKEN_LPAREN;
    }

    if (input[pos] == ')') {
        pos++;
        return TOKEN_RPAREN;
    }

    if (input[pos] == '+') {
        pos++;
        return TOKEN_PLUS;
    }

    if (input[pos] == '1') {
        pos++;
        return TOKEN_ONE;
    }

    pos++;
    return TOKEN_INVALID;
}

void nextToken() {
    currentToken = getToken();
}

/* ---------- Output helper ---------- */

void printIndent(int level) {
    int i;
    for (i = 0; i < level; i++) {
        printf("  ");
    }
}

/* ---------- Parser functions ---------- */

int parse_S(int level);
int parse_S_prime(int level);
int parse_E(int level);

/*
Grammar:
S -> E S'
*/
int parse_S(int level) {
    printIndent(level);
    printf("S -> E S'\n");

    if (!parse_E(level + 1)) {
        return 0;
    }

    if (!parse_S_prime(level + 1)) {
        return 0;
    }

    return 1;
}

/*
Grammar:
S' -> + S | epsilon
*/
int parse_S_prime(int level) {
    if (currentToken == TOKEN_PLUS) {
        printIndent(level);
        printf("S' -> + S\n");

        printIndent(level + 1);
        printf("+\n");

        nextToken();

        if (!parse_S(level + 1)) {
            return 0;
        }

        return 1;
    }

    printIndent(level);
    printf("S' -> epsilon\n");

    return 1;
}

/*
Grammar:
E -> ( S ) | 1
*/
int parse_E(int level) {
    if (currentToken == TOKEN_LPAREN) {
        printIndent(level);
        printf("E -> ( S )\n");

        printIndent(level + 1);
        printf("(\n");

        nextToken();

        if (!parse_S(level + 1)) {
            return 0;
        }

        if (currentToken != TOKEN_RPAREN) {
            printf("Syntax Error: missing ')'\n");
            return 0;
        }

        printIndent(level + 1);
        printf(")\n");

        nextToken();

        return 1;
    }

    if (currentToken == TOKEN_ONE) {
        printIndent(level);
        printf("E -> 1\n");

        printIndent(level + 1);
        printf("1\n");

        nextToken();

        return 1;
    }

    printf("Syntax Error: expected '(' or '1'\n");
    return 0;
}

/* ---------- Main ---------- */

int main() {
    printf("Input: ");
    fgets(input, MAX_INPUT, stdin);

    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
    }

    pos = 0;
    nextToken();

    printf("\nParse Tree:\n");

    if (parse_S(0) && currentToken == TOKEN_END) {
        printf("\nAccepted\n");
    } else {
        printf("\nRejected\n");
    }

    return 0;
}