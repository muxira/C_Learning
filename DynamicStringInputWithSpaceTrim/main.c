#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void trim(char* pBuffer, size_t* pLenght);

int main() {
    // Создаём буфер на 16 символов
    size_t size = 16;
    size_t length = 0;
    char *buffer = malloc(size);
    if (!buffer) return 1;

    printf("Enter a string: ");
    int tmpChar; // note: int, not char, required to handle EOF
    while ((tmpChar = fgetc(stdin)) != EOF && tmpChar != '\n') {
        if (length >= size - 1) {
            size *= 2;
            char* tmpBuffer = realloc(buffer, size);
            if (!tmpBuffer) return 1;
            buffer = tmpBuffer;
        }
        buffer[length] = (char)tmpChar;
        length++;
    }
    buffer[length] = '\0';
    printf("You entered: %s\n", buffer);
    trim(buffer, &length);
    printf("Trimmed input: %s\n", buffer);
    free(buffer);
    return 0;
}

void trim(char* pBuffer, size_t* pLenght) {
    size_t start = 0;
    while (pBuffer[start] == ' ') start++;

    if (start == *pLenght) {
        pBuffer[0] = '\0';
        *pLenght = 0;
        return;
    }

    if (start > 0) {
        for (size_t i = start; i <= *pLenght; i++) {
            pBuffer[i - start] = pBuffer[i];
        }
        *pLenght -= start;
    }

    size_t end = *pLenght - 1;
    while (pBuffer[end] == ' ') end--;

    if (end > 0) {
        pBuffer[end + 1] = '\0';
    }
}
