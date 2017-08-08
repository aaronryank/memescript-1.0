#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int getmeme(char*,FILE*);
int meme_interp(char*);
void meme(int*);

int main(int argc, char **argv)
{
    if (argc != 2)
        return fprintf(stderr,"Usage: %s <input file>\n",argv[0]);

    FILE *in = fopen(argv[1],"r");

    if (!in)
        return fprintf(stderr,"Error: Could not open file %s: %s\n",argv[1],strerror(errno));

    char buf[1000] = {0};
    int code[10000] = {0};
    int i = 0;
    for (; strcmp(buf,"what the"); getmeme(buf,in));
    while (getmeme(buf,in)) code[i++] = meme_interp(buf);

    meme(code);
}

int getmeme(char *buf, FILE *in)
{
    char word1[1000] = {0};
    char word2[1000] = {0};

    if (!~fscanf(in," %s",word1))
        return 0;
    if (strlen(word1) <= 7)
        if (!~fscanf(in," %s",word2))
            return 0;

    strcpy(buf,word1);
    if (word2[0])
        strcat(buf," "),
        strcat(buf,word2);

    return 1;
}

int meme_interp(char *command)
{
    //puts(command);
    if (!strcmp(command,"frick frack"))
        return 1;
    else if (!strcmp(command,"diddily dack"))
        return 2;
    else if (!strcmp(command,"patty wack"))
        return 3;
    else if (!strcmp(command,"snick snack"))
        return 4;
    else if (!strcmp(command,"crack pack"))
        return 5;
    else if (!strcmp(command,"slack mack"))
        return 6;
    else if (!strcmp(command,"quarterback"))
        return 7;
    else if (!strcmp(command,"crackerjack"))
        return 8;
    else if (!strcmp(command,"biofeedback"))
        return 9;
    else if (!strcmp(command,"backtrack"))
        return 10;
    else if (!strcmp(command,"thumbtack"))
        return 11;
    else if (!strcmp(command,"sidetrack"))
        return 12;
    else if (!strcmp(command,"tic tac"))
        return 13;
    //else if (!strcmp(command,"does she"))
      //  exit(EXIT_SUCCESS);
    else
        return 14;
}

/* memescript */

int op = 0;
enum { NO_OP, PUSH, ADD, SUBTRACT, MULTIPLY, DIVIDE, PRINT, READ };

int stack[30000] = {0};
int size = 0;

void meme(int *code)
{
    int i, current, loop;

    for (i = 0; code[i]; i++)
    {
        /* not currently in an operation */
        if (op == NO_OP) {
          switch (code[i]) {
            case 1: op = PUSH;         break;
            case 2: op = ADD;          break;
            case 3: op = SUBTRACT;     break;
            case 4: op = MULTIPLY;     break;
            case 5: op = DIVIDE;       break;
            case 6: stack[--size] = 0; break;
            case 7: op = PRINT;        break;
            case 8: op = READ;         break;
            case 9: continue;
            case 10:
              if (!stack[size-1]) break;
              loop = 1;
              while (loop > 0) {
                  current = code[--i];
                  if (current == 9) {
                      loop--;
                  } else if (current == 10) {
                      loop++;
                  }
              }
              break;
          }
        }

        else if (op == PUSH) {
            stack[size++] = code[i];
            op = NO_OP;
        }
        else if (op == ADD) {
            stack[size-1] += code[i];
            op = NO_OP;
        }

        else if (op == SUBTRACT) {
            stack[size-1] -= code[i];
            op = NO_OP;
        }

        else if (op == MULTIPLY) {
            stack[size-1] *= code[i];
            op = NO_OP;
        }

        else if (op == DIVIDE) {
            stack[size-1] /= code[i];
            op = NO_OP;
        }

        else if (op == PRINT) {
            switch (code[i]) {
              case 1: printf("%d",stack[size-1]); break;
              case 2: printf("%c",stack[size-1]); break;
            }
            op = NO_OP;
        }

        else if (op == READ) {
            switch(code[i]) {
              case 1: stack[size++] = getchar() - '0'; break;
              case 2: stack[size++] = getchar();       break;
            }
            op = NO_OP;
        }
    }
    putchar('\n');
}
