#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void main() {
  char input[10], add[6], length[10];
  int start, len, i, address, opcode, addr, actualadd;
  FILE *fp1, *fp2;

  fp1 = fopen("relinput.txt", "r");
  fp2 = fopen("absoutput.txt", "w");

  fscanf(fp1, "%s", input);

  while (strcmp(input, "E") != 0) {    
    if (strcmp(input, "H") == 0) {
      fscanf(fp1, "%s", add);
      fscanf(fp1, "%s", length);
      fscanf(fp1, "%s", input);
    }

    if (strcmp(input, "T") == 0) {
      fscanf(fp1, "%x", &address);
      while (fscanf(fp1, "%d %d", &opcode, &addr) == 2) {
        actualadd = addr;
        fprintf(fp2, "%d\t%d %d\n", address, opcode, actualadd);
        address += 3;
      }
      fscanf(fp1, "%s", input);
    }
  }

  fclose(fp1);
  fclose(fp2);

  printf("FINISHED\nCheck for file absoutput.txt\n");
}
