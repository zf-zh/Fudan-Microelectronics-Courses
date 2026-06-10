#include "read_labels.h"
// 读取文件到二维字符数组中
void read_labels(char labels[][MAX_LABEL_LENGTH], char* filename) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Failed to open file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LABEL_LENGTH + 10];
    char *start, *end, *quote;

    for (int i = 0; i < 1000; i++) {
        fgets(line, sizeof(line), fp);

        quote = strchr(line, '\"');
        if (quote != NULL) {
            start = quote + 1;
            end = strchr(start, '\"');
        } else {
            start = strchr(line, '\'');
            if (start != NULL) {
                start++;
                end = strchr(start, '\'');
            } else {
                end = NULL;
            }
        }

        if (end != NULL) {
            *end = '\0';
            strncpy(labels[i], start, MAX_LABEL_LENGTH - 1);
            labels[i][MAX_LABEL_LENGTH - 1] = '\0'; // 确保字符串以 '\0' 结尾
        } else {
            strcpy(labels[i], ""); // 如果提取失败，给标签赋空字符串
        }
    }

    fclose(fp);
}

// 打印标签
// void print_labels(char labels[][MAX_LABEL_LENGTH]) {
//     for (int i = 0; i < 1000; i++) {
//         printf("%s\n", labels[i]);
//     }
// }

// int main() {
//     char labels[1000][MAX_LABEL_LENGTH];
//     read_labels(labels, "imagenet1000_labels.txt");
//     print_labels(labels);

//     return 0;
// }
