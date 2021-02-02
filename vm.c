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
	int old_pc  = 0;
	int pc = 0;
	int halt = 1;
	instruction *IR = NULL;


	// read in instructions into an array of structs
  while (feof(file_ptr) == 0)
  {
    fscanf(file_ptr, "%d %d %d", &text[count].opcode, &text[count].l, &text[count].m);
    count++;

  }
	// initialize stack array and static links array to keep track of the position of the static links
	for (int i =0; i < MAX_STACK_HEIGHT; i++)
	{
		static_links[i] = 0;
		stack[i] = 0;
	}



	printf("\t\t  PC\tBP\tSP\tstack\n");
	printf("Initial values:  %2d\t%2d\t%2d\n",pc,bp,sp);

	while (halt)
	{
		// fetch cycle
		old_pc = pc;
		pc++;
		IR = &text[old_pc];
		// Execution Cycle
		switch (IR->opcode)
		{
			// push constant value on top of stack
			case 1:
				sp++;
				stack[sp] = text[old_pc].m;
				printf("%2d LIT %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i] == 1)
						printf("|");
					printf("%d", stack[i]);
				}
				printf("\n");
				break;
			// Operation to be performed on data at the top of the stack
			case 2:
				switch (text[old_pc].m)
				{
					// Return to caller
					case 0:
						stack[bp-1] = stack[sp];
						sp = bp-1;
						static_links[bp] = 0;
						bp = stack[sp+2];
						printf("%2d RTN %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
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

					// switch the sign of the number at the top of the stack
					case 1:
						stack[sp] = -1 * stack[sp];
						printf("%2d NEG %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// add two numbers that are on top of stack
					case 2:
						sp = sp - 1;
						stack[sp] = stack[sp] + stack[sp + 1];
						printf("%2d ADD %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// subtract
					case 3:
					sp = sp - 1;
					stack[sp] = stack[sp] - stack[sp + 1];
					printf("%2d SUB %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
					printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

					for (int i = 0; i <= sp; i++)
					{
						if (static_links[i])
							printf("|");
						printf("%d", stack[i]);
					}
					printf("\n");
					break;

					// multiply
					case 4:
						sp = sp - 1;
						stack[sp] = stack[sp] * stack[sp+1];
						printf("%2d MUL %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);


						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// divide
					case 5:
						sp = sp - 1;
						stack[sp] = stack[sp] / stack[sp+1];
						printf("%2d DIV %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
								printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// odd
					case 6:
						stack[sp] = stack[sp] % 2;

						printf("%2d ODD %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// MOD
					case 7:
						sp = sp - 1;
						stack[sp] = stack[sp] % stack[sp+1];
						printf("%2d MOD %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// EQL
					case 8:
						sp = sp - 1;
						stack[sp] = stack[sp] == stack[sp+1];
						printf("%2d EQL %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// NEQ
					case 9:
						sp = sp - 1;
						stack[sp] = stack[sp] != stack[sp+1];
						printf("%2d NEQ %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// LSS
					case 10:
						sp = sp - 1;
						stack[sp] = stack[sp] < stack[sp+1];
						printf("%2d LSS %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// LEQ
					case 11:
						sp = sp - 1;
						stack[sp] = stack[sp] <= stack[sp+1];
						printf("%2d LEQ %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// GTR
					case 12:
						sp = sp - 1;
						stack[sp] = stack[sp] > stack[sp+1];
						printf("%2d GTR %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;

					// GEQ
					case 13:
						sp = sp - 1;
						stack[sp] = stack[sp] >= stack[sp+1];
						printf("%2d GEQ %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i >= sp; i++)
						{
							if (static_links[i])
								printf("|");
							printf("%d", stack[i]);
						}
						printf("\n");
						break;


					}
				break;

			// Load number to the top of the stack
			case 3:
				sp = sp + 1;
				stack[sp] = stack[base(stack, text[old_pc].l,bp) + text[old_pc].m];
				printf("%2d LOD %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);

				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i])
						printf("|");
					printf("%d", stack[i]);
				}
				printf("\n");
				break;

			// Store number that is on top of the stack at the specified location
			case 4:
				stack[base(stack, text[old_pc].l,bp) + text[old_pc].m] = stack[sp];
				sp = sp - 1;
				printf("%2d STO %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);

				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i])
						printf("|");
						printf("%d", stack[i]);
				}
				printf("\n");
				break;

			// function call
			case 5:
				stack[sp+1] = base(stack, text[old_pc].l,bp);
				static_links[sp+1] = 1;
				stack[sp+2] = bp;
				stack[sp+3] =  old_pc+1;
				stack[sp+4] = stack[sp];
				bp = sp + 1;
				printf("%2d CAL %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
				pc = text[old_pc].m;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);


				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i])
						printf("|");
					printf("%d", stack[i]);
				}
				printf("\n");
				break;

			// increment stack pointer by specified amount
			case 6:
				sp += text[old_pc].m;
				printf("%2d INC %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);

				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i] == 1)
						printf("|");
					printf("%d", stack[i]);
				}

				printf("\n");
				break;

			// jump to specified instruction
			case 7:
				printf("%2d JMP %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
				pc = text[old_pc].m;
				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i] == 1)
						printf("|");
					printf("%d", stack[i]);
				}

				printf("\n");
				break;

			// if top of stack is zero, jump to specified instruction
			case 8:
				printf("%2d JPC %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);
				if (stack[sp] == 0)
					pc = text[old_pc].m;

					sp = sp - 1;


				printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);
				for (int i = 0; i <= sp; i++)
				{
					if (static_links[i] == 1)
						printf("|");

						printf("%d", stack[i]);
				}

				printf("\n");
				break;

			// SYS
			case 9:
				switch (text[old_pc].m)
				{
					// print value that is at the top of stack
					case 1:
						printf("Top of Stack Value: %d\n", stack[sp]);
						sp--;
						printf("%2d SYS %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);

						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i] == 1)
								printf("|");
							printf("%d", stack[i]);
						}

						printf("\n");
						break;

					// read in value from user and add it to the top of the stack
					case 2:
						sp++;
						printf("Please Enter an Integer: ");
						scanf("%d", &stack[sp]);
						printf("\n");
						printf("%2d SYS %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);

						printf("\t %2d\t%2d\t%2d\t", pc, bp, sp);

						for (int i = 0; i <= sp; i++)
						{
							if (static_links[i] == 1)
								printf("|");
							printf("%d", stack[i]);
						}

						printf("\n");
						break;

					// ends program
					case 3:
						printf("%2d SYS %2d %2d", old_pc, text[old_pc].l, text[old_pc].m);

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
