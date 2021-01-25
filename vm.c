#include <stdlib.h>
#include <stdio.h>

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100


typedef struct instruction
{
	int opcode;
	int l;
	int m;

} instruction;



int main(int argc, char **argv)
{
  FILE * file_ptr = fopen(argv[1], "r");
  instruction text[MAX_CODE_LENGTH];
	int stack[MAX_STACK_HEIGHT];
  int count = 0;
	int sp = -1;
	int bp = 0;
	int pc = 0;
	instruction *ir = NULL;
	int last_index = -1;
	int halt = 1;


  while (feof(file_ptr) == 0)
  {
    fscanf(file_ptr, "%d %d %d", &text[count].opcode, &text[count].l, &text[count].m);
    count++;
  }

	last_index = count - 1;

	printf("\t\t PC\tBP\tSP\tstack\n");
	printf("Initial values:  %2d\t%2d\t%2d\n",pc,bp,sp);

	while (halt)
	{
		switch (text[pc].opcode)
		{
			case 1 :
				sp++;
				stack[sp] = text[pc].m;
				break;

			case 2 :
				switch (text[pc].m)
				{
					case 0 :
						stack[bp-1] = stack[sp];
						sp = bp-1;
						bp = stack[sp+2];
						pc = stack[sp+3];
						break;

					case 1 :
						stack[sp] = -1 * stack[sp];
						break;

					case 2 :
						sp = sp-1;
						stack[sp] = stack[sp] + stack[sp+1];
						break;

					case 3:
						sp = sp - 1;
						stack[sp] = stack[sp] - stack[sp + 1];
						break;

					case 4 :
						sp = sp - 1;
						stack[sp] = stack[sp] * stack[sp+1];
						break;

					case 5 :
						sp = sp - 1;
						stack[sp] = stack[sp] / stack[sp+1];
						break;

					case 6 :
						stack[sp] = stack[sp] % 2;
						break;

					case 7 :
						sp = sp - 1;
						stack[sp] = stack[sp] % stack[sp+1];
						break;

					case 8 :
						sp = sp - 1;
						stack[sp] = (stack[sp] == stack[sp+1]);
						break;

					case 9 :
						sp = sp - 1;
						stack[sp] = stack[sp] != stack[sp + 1];
						break;

					case 10 :
						sp = sp - 1;
						stack[sp] = stack[sp] < stack[sp + 1];
						break;

					case 11 :
						sp = sp - 1;
						stack[sp] = stack[sp] <= stack[sp + 1];
						break;

					case 12 :
						sp = sp - 1;
						stack[sp] = stack[sp] > stack[sp + 1];
						break;

					case 13 :
						sp = sp - 1;
						stack[sp] = stack[sp] >= stack[sp + 1];
						break;
				}
				break;
		}
		pc++;
	}
}
