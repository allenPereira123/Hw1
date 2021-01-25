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





		}
		pc++;
	}
}
