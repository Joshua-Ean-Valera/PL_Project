#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int choice, mode, output_mode;
    char temp_input_file[] = "temp_input.txt";
    char temp_output_file[] = "temp_output.txt";
    char results_file[64];
    FILE *fp, *fin, *fout, *fres;
    char c;

    while (1) {
        printf("Select language for lexical analysis:\n");
        printf("1. C\n2. Python\n3. Java\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while ((c = getchar()) != '\n' && c != EOF); // clear input buffer
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        if (choice < 1 || choice > 3) {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
            continue;
        }
        // Set results file name based on language
        if (choice == 1)
            strcpy(results_file, "C_Results.txt");
        else if (choice == 2)
            strcpy(results_file, "Python_Results.txt");
        else
            strcpy(results_file, "Java_Results.txt");
        break;
    }

    while (1) {
        printf("Select input mode:\n");
        printf("1. File mode (process input file)\n");
        printf("2. Terminal mode (enter input directly)\n");
        printf("Enter mode: ");
        if (scanf("%d", &mode) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        if (mode != 1 && mode != 2) {
            printf("Invalid mode. Please select 1 or 2.\n");
            continue;
        }
        break;
    }
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

    while (1) {
        printf("Select output mode:\n");
        printf("1. Print results to terminal\n");
        printf("2. Save results to results.txt\n");
        printf("Enter output mode: ");
        if (scanf("%d", &output_mode) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        if (output_mode != 1 && output_mode != 2) {
            printf("Invalid output mode. Please select 1 or 2.\n");
            continue;
        }
        break;
    }
    getchar(); // consume newline

    char cmd[512];
    const char *input_file = (mode == 1) ? 
        (choice == 1 ? "input.c" : (choice == 2 ? "input.py" : "input.java")) : temp_input_file;

    if (output_mode == 1) {
        switch(choice) {
            case 1:
                sprintf(cmd, "flex c_lexer.l && gcc lex.yy.c -o c_lexer && .\\c_lexer < %s", input_file);
                system(cmd);
                break;
            case 2:
                sprintf(cmd, "flex python_lexer.l && gcc lex.yy.c -o python_lexer && .\\python_lexer < %s", input_file);
                system(cmd);
                break;
            case 3:
                sprintf(cmd, "flex java_lexer.l && gcc lex.yy.c -o java_lexer && .\\java_lexer < %s", input_file);
                system(cmd);
                break;
            default:
                printf("Invalid choice.\n");
        }
    } else if (output_mode == 2) {
        // Run lexer and redirect output to temp_output.txt
        switch(choice) {
            case 1:
                sprintf(cmd, "flex c_lexer.l && gcc lex.yy.c -o c_lexer && .\\c_lexer < %s > %s", input_file, temp_output_file);
                system(cmd);
                break;
            case 2:
                sprintf(cmd, "flex python_lexer.l && gcc lex.yy.c -o python_lexer && .\\python_lexer < %s > %s", input_file, temp_output_file);
                system(cmd);
                break;
            case 3:
                sprintf(cmd, "flex java_lexer.l && gcc lex.yy.c -o java_lexer && .\\java_lexer < %s > %s", input_file, temp_output_file);
                system(cmd);
                break;
            default:
                printf("Invalid choice.\n");
        }
        // Write original input and results to results file
        fin = fopen(input_file, "r");
        fout = fopen(temp_output_file, "r");
        fres = fopen(results_file, "w");
        if (fin && fout && fres) {
            fprintf(fres, "===== ORIGINAL INPUT =====\n");
            while ((c = fgetc(fin)) != EOF) fputc(c, fres);
            fprintf(fres, "\n===== LEXICAL ANALYSIS RESULTS =====\n");
            while ((c = fgetc(fout)) != EOF) fputc(c, fres);
            fclose(fin);
            fclose(fout);
            fclose(fres);
            printf("Results saved to %s\n", results_file);
        } else {
            printf("Error writing results file.\n");
        }
        remove(temp_output_file);
    }

    if (mode == 2) {
        remove(temp_input_file);
    }
    return 0;
}
