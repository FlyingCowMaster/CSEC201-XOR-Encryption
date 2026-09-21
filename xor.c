#include <stdio.h>
#include <stdlib.h>

void encryptDecrypt(char *message, char *key) {
    int keyLen = 0;
    while (key[keyLen] != '\0') {
        keyLen++;
    }

    for (int i = 0; message[i] != '\0'; i++) {
        message[i] ^= key[i % keyLen];
    }
}

void encrypt(char *message, char *filename, char *key) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    encryptDecrypt(message, key);
    fprintf(file, "%s", message);
    fclose(file);
}

void decrypt(char *filename, char *key) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *message = (char *)malloc((fileSize + 1) * sizeof(char));
    if (!message) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return;
    }

    fread(message, sizeof(char), fileSize, file);
    message[fileSize] = '\0';
    fclose(file);

    encryptDecrypt(message, key);
    printf("%s\n", message);
    free(message);
}

int main() {
    char choice[10];
    printf("Enter 'encrypt' or 'decrypt': ");
    scanf("%s", choice);

    if (strcmp(choice, "encrypt") == 0) {
        char message[256];
        char filename[256];
        char key[256];

        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);

        printf("Enter the encryption key: ");
        scanf("%s", key);

        encrypt(message, filename, key);
    } else if (strcmp(choice, "decrypt") == 0) {
        char filename[256];
        char key[256];

        printf("Enter the filename to read encrypted data: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        scanf("%s", key);

        decrypt(filename, key);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}