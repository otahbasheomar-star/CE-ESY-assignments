#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    int size;
    int head; // write
    int tail; // read
    int count;
} CircularBuffer;

// Initialization
void initBuffer(CircularBuffer *cb, int size) {
    cb->data = (char *)malloc(size * sizeof(char));
    cb->size = size;
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Free memory
void freeBuffer(CircularBuffer *cb) {
    free(cb->data);
}

// Is full?
int isFull(CircularBuffer *cb) {
    return cb->count == cb->size;
}

// Is empty?
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// Write one character
int writeChar(CircularBuffer *cb, char c) {
    if (isFull(cb)) {
        return 0;
    }
    cb->data[cb->head] = c;
    cb->head = (cb->head + 1) % cb->size;
    cb->count++;
    return 1;
}

// Read one character
int readChar(CircularBuffer *cb, char *c) {
    if (isEmpty(cb)) {
        return 0;
    }
    *c = cb->data[cb->tail];
    cb->tail = (cb->tail + 1) % cb->size;
    cb->count--;
    return 1;
}

// Write string
void writeString(CircularBuffer *cb, const char *str) {
    while (*str) {
        if (!writeChar(cb, *str)) {
            printf("Buffer Full! Stopped writing.\n");
            return;
        }
        str++;
    }
}

// Read all data
void readAll(CircularBuffer *cb, char *output) {
    int i = 0;
    char c;
    while (readChar(cb, &c)) {
        output[i++] = c;
    }
    output[i] = '\0';
}

// Single test
void testBuffer(int size, const char *input) {
    printf("\n ---Testing Buffer Size = %d ---\n", size);

    CircularBuffer cb;
    initBuffer(&cb, size);

    printf("Writing: %s\n", input);
    writeString(&cb, input);

    char output[100];
    readAll(&cb, output);

    printf("Read: %s\n", output);

    if (isEmpty(&cb)) {
        printf("Buffer is EMPTY after reading \n");
    } else {
        printf("Buffer is NOT empty \n");
    }

    freeBuffer(&cb);
}

// ---------------- MAIN ----------------
int main() {
    char name[50];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    // Remove newline
    name[strcspn(name, "\n")] = 0;

    char finalString[100];
    strcpy(finalString, name);
    strcat(finalString, "CE-ESY");

    // Two tests:
    testBuffer(10, finalString); // smaller than data
    testBuffer(30, finalString); // larger than data

    return 0;
}

