#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcode[10], operand[10], label[10], t1[20], t2[20], t3[20];
int locctr, start, len, symtab_index = -1, optab_index = -1;
FILE *fp1, *fp2, *fp3, *fp4, *fp5;

struct SYMTAB {
    char label[10];
    int addr;
} symtab[20];

struct OPTAB {
    char opcode[10], hexcode[10];
} optab[30];

void read_OPTAB() {
    while (1) {
        optab_index++;
        fscanf(fp2, "%s%s", optab[optab_index].opcode, optab[optab_index].hexcode);
        if (getc(fp2) == EOF)
            break;
    }
}

void read_line() {
    strcpy(t1, ""); strcpy(t2, ""); strcpy(t3, "");
    fscanf(fp1, "%s", t1);
    if (getc(fp1) != '\n') { 
        fscanf(fp1, "%s", t2);
        if (getc(fp1) != '\n')
            fscanf(fp1, "%s", t3);
    }
    if (strcmp(t1, "") != 0 && strcmp(t2, "") != 0 && strcmp(t3, "") != 0) {
        strcpy(label, t1);
        strcpy(opcode, t2);
        strcpy(operand, t3);
    } else if (strcmp(t1, "") != 0 && strcmp(t2, "") != 0) {
        strcpy(label, "");
        strcpy(opcode, t1);
        strcpy(operand, t2);
    } else if (strcmp(t1, "") != 0) {
        strcpy(label, "");
        strcpy(opcode, t1);
        strcpy(operand, "");
    }
}

int main() {
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermed.txt", "w");
    fp5 = fopen("length.txt", "w");

    read_OPTAB();

    int operand_value;
    fscanf(fp1, "%s%s%x", label, opcode, &operand_value);

    if (strcmp(opcode, "START") == 0) {
        start = operand_value;
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%x\n", label, opcode, operand_value);
        read_line();
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(fp4, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "") != 0) {
            for (int i = 0; i <= symtab_index; i++) {
                if (strcmp(symtab[i].label, label) == 0) {
                    printf("Error: Duplicate label found in SYMTAB.\n");
                    exit(1);
                }
            }
            symtab_index++;
            strcpy(symtab[symtab_index].label, label);
            symtab[symtab_index].addr = locctr;
        }

        int flag = 0;
        for (int i = 0; i <= optab_index; i++) {
            if (strcmp(opcode, optab[i].opcode) == 0) {
                locctr += 0x3;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 0x3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += 0x3 * atoi(operand);
            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else if (strcmp(opcode, "BYTE") == 0) {
                len = strlen(operand);
                if (operand[0] == 'C' || operand[0] == 'c')
                    len -= 3;
                else
                    len = (len - 3) / 2;
                locctr += len;
            }
        }

        read_line();
    }

    fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);

    for (int i = 0; i <= symtab_index; i++) {
        fprintf(fp3, "%s\t%x\n", symtab[i].label, symtab[i].addr);
    }

    fprintf(fp5, "%x", locctr - start);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    return 0;
}
