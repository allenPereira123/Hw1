// Allen Pereira
// Allec Pereira.
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

int base(int stack[], int level, int BP)
{
	int base = BP;
	int counter = level;
	while (counter > 0)
	{
		base = stack[base];
		counter--;
	}
	return base;
}



int main(int argc, char **argv)
{
  FILE * file_ptr = fopen(argv[1], "r");
  instruction text[MAX_CODE_LENGTH];
	int static_links[MAX_STACK_HEIGHT];
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
	//	printf("%d %d %d \n", text[count].opcode, text[count].l, text[count].m);
    count++;

  }

	for (int i =0; i < MAX_STACK_HEIGHT; i++)
	{
		static_links[i] = 0;
		stack[i] = 0;
	}

	last_index = count - 1;

	printf("\t\t  PC\tBP\tSP\tstack\n");
	printf("Initial values:  %2d\t%2d\t%2d\n",pc,bp,sp);

	while (halt)
	{
		switch (text[pc].opcode)
		{
			case 1:
				sp++;
				stack[sp] = text[pc].m;
				printf("%2d LIT %2d %2d", pc, text[pc].l, text[pc].m);
				pc++;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i] == 1)
						printf("|");
					printf("%d", stack[i]);
				}
				printf("\n");
				break;

			case 2:
				switch (text[pc].m)
				{
					case 0:
						stack[bp-1] = stack[sp];
						sp = bp-1;
						static_links[bp] = 0;
						bp = stack[sp+2];
						printf("%2d RTN %2d %2d", pc, text[pc].l, text[pc].m);
						pc = stack[sp+3];
						
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;
				}
				break;

			case 3:
				sp = sp + 1;
				stack[sp] = stack[base(stack, text[pc].l,bp) + text[pc].m];
				printf("%2d LOD %2d %2d", pc, text[pc].l, text[pc].m);
				pc++;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i])
						printf("|");
					printf("%d", stack[i]);
				}
				printf("\n");
				break;

			case 4:
				stack[base(stack, text[pc].l,bp) + text[pc].m] = stack[sp];
				sp = sp - 1;
				printf("%2d RTN %2d %2d", pc, text[pc].l, text[pc].m);
				pc++;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i])
						printf("|");
						printf("%d", stack[i]);
				}
				printf("\n");
				break;


			case 5:
				stack[sp+1] = base(stack, text[pc].l,bp);
				static_links[sp+1] = 1;
				stack[sp+2] = bp;
				stack[sp+3] =  pc+1;
				stack[sp+4] = stack[sp];
				bp = sp + 1;
				printf("%2d CAL %2d %2d", pc, text[pc].l, text[pc].m);
				pc = text[pc].m;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);


				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i])
						printf("|");
					printf("%d", stack[i]);
				}
				printf("\n");
				break;


			case 6:
				sp += text[pc].m;
				printf("%2d INC %2d %2d", pc, text[pc].l, text[pc].m);
				pc++;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i] == 1)
						printf("|");
					printf("%d", stack[i]);
				}

				printf("\n");

				break;

			case 7:
				printf("%2d JMP %2d %2d", pc, text[pc].l, text[pc].m);
				pc = text[pc].m;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					printf("%d", stack[i]);
					if (static_links[i] == 1)
						printf("|");
				}

				printf("\n");
				break;

			case 8:
				printf("%2d JMP %2d %2d", pc, text[pc].l, text[pc].m);
				if (stack[sp] == 0)
					pc = text[pc].m;

				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);
				for (int i = 0; i <= sp; i++)
				{
					printf("%d", stack[i]);
					if (static_links[i] == 1)
						printf("|");
				}

				printf("\n");
				break;

			case 9:
				switch (text[pc].m)
				{
					case 1:
						printf("Top of Stack Value: %d\n", stack[sp]);
						sp--;
						printf("%2d SYS %2d %2d", pc, text[pc].l, text[pc].m);
						pc++;
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i] == 1)
								printf("|");
							printf("%d", stack[i]);
						}

						printf("\n");
						break;

					case 2:
						sp++;
						printf("Please Enter an Integer: ");
						scanf("%d", &stack[sp]);

						printf("%2d SYS %2d %2d", pc, text[pc].l, text[pc].m);
						pc++;
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i] == 1)
								printf("|");
							printf("%d", stack[i]);
						}

						printf("\n");
						break;

					case 3:
						printf("%2d SYS %2d %2d", pc, text[pc].l, text[pc].m);
						pc++;
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i] == 1)
								printf("|");
							printf("%d", stack[i]);
						}

						printf("\n");
						halt = 0;
						break;
				}
				break;
		}

	}





















}
