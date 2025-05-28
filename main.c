#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int choice, mode;
    char temp_input_file[] = "temp_input.txt";
    FILE *fp;
    char c;

    printf("Select language for lexical analysis:\n");
    printf("1. C\n2. Python\n3. Java\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    printf("Select input mode:\n");
    printf("1. File mode (process input file)\n");
    printf("2. Terminal mode (enter input directly)\n");
    printf("Enter mode: ");
    scanf("%d", &mode);
    getchar(); // consume newline

    if (mode == 2) {
        printf("Enter your code below (end with a single line containing only 'END'):\n");
        fp = fopen(temp_input_file, "w");
        if (!fp) {
            printf("Error creating temporary input file.\n");
            return 1;
        }
        char line[1024];
        while (1) {
            if (!fgets(line, sizeof(line), stdin)) break;
            if (strcmp(line, "END\n") == 0 || strcmp(line, "END\r\n") == 0) break;
            fputs(line, fp);
        }
        fclose(fp);
    }

    switch(choice) {
        case 1:
            if (mode == 1)
                system("flex c_lexer.l && gcc lex.yy.c -o c_lexer && .\\c_lexer < input.c");
            else
                system("flex c_lexer.l && gcc lex.yy.c -o c_lexer && .\\c_lexer < temp_input.txt");
            break;
        case 2:
            if (mode == 1)
                system("flex python_lexer.l && gcc lex.yy.c -o python_lexer && .\\python_lexer < input.py");
            else
                system("flex python_lexer.l && gcc lex.yy.c -o python_lexer && .\\python_lexer < temp_input.txt");
            break;
        case 3:
            if (mode == 1)
                system("flex java_lexer.l && gcc lex.yy.c -o java_lexer && .\\java_lexer < input.java");
            else
                system("flex java_lexer.l && gcc lex.yy.c -o java_lexer && .\\java_lexer < temp_input.txt");
            break;
        default:
            printf("Invalid choice.\n");
    }

    if (mode == 2) {
        remove(temp_input_file);
    }
    return 0;
}
