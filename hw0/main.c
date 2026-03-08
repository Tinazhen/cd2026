#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ch;
    int count;
    struct Node* next;
} Node;

Node* head = NULL;

Node* findChar(char c) {
    Node* cur = head;

    while (cur != NULL) {
        if (cur->ch == c) {
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}

void insertChar(char c) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("memory allocation failed\n");
        exit(1);
    }

    newNode->ch = c;
    newNode->count = 1;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
}

void printList() {
    Node* cur = head;

    while (cur != NULL) {

        if (cur->ch == '\n') {
            printf("\\n : %d\n", cur->count);
        }
        else if (cur->ch == ' ') {
            printf("' ' : %d\n", cur->count);
        }
        else if (cur->ch == '\t') {
            printf("\\t : %d\n", cur->count);
        }
        else {
            printf("%c : %d\n", cur->ch, cur->count);
        }

        cur = cur->next;
    }
}

void freeList() {
    Node* cur = head;
    Node* temp;

    while (cur != NULL) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
}

int main() {

    FILE* fp;
    int c;
    Node* found;

    fp = fopen(__FILE__, "r");

    if (fp == NULL) {
        printf("cannot open file\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {

        found = findChar((char)c);

        if (found != NULL) {
            found->count++;
        }
        else {
            insertChar((char)c);
        }
    }

    fclose(fp);

    printList();

    freeList();

    return 0;
}
