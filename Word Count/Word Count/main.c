#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countCharacters(FILE* file) {
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

int countWords(FILE* file) {
    int count = 0;
    char c;
    int inWord = 0; // ��ǵ�ǰ�Ƿ��ڵ�����
    while ((c = fgetc(file)) != EOF) {
        if (c == ' ' || c == ',' || isspace(c)) { // �ո񣬶��ź������հ��ַ���Ϊ���ʷָ�
            if (inWord) {
                count++;
                inWord = 0;
            }
        }
        else {
            inWord = 1;
        }
    }
    // ����ļ�ĩβ�ǵ��ʣ�ҲҪ����
    if (inWord) {
        count++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c | -w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char* option = argv[1];
    char* filename = argv[2];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int result;
    if (strcmp(option, "-c") == 0) {
        result = countCharacters(file);
        printf("�ַ�����%d\n", result);
    }
    else if (strcmp(option, "-w") == 0) {
        result = countWords(file);
        printf("��������%d\n", result);
    }
    else {
        fprintf(stderr, "Invalid option: %s\n", option);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}