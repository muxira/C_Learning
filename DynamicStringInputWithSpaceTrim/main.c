#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void trim(char* pBuffer, size_t* pLength);

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
            if (!tmpBuffer) {
                free(buffer);
                return 1;
            }
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

void trim(char* pBuffer, size_t* pLength) {
    // Обрезка пробелов слева
    size_t start = 0;
    while (start < *pLength && pBuffer[start] == ' ') start++;

    if (start == *pLength) {
        // Строка полностью из пробелов
        pBuffer[0] = '\0';
        *pLength = 0;
        return;
    }

    if (start > 0) {
        for (size_t i = start; i <= *pLength; i++) {
            pBuffer[i - start] = pBuffer[i];
        }
        *pLength -= start;
    }

    // Обрезка пробелов справа
    if (*pLength == 0) return;

    size_t end = *pLength - 1;
    while (end != (size_t)-1 && pBuffer[end] == ' ') end--;

    pBuffer[end + 1] = '\0';
    *pLength = end + 1;
}
