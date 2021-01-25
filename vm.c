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
  instruction instruction_array[MAX_CODE_LENGTH];
  int count = 0;
	int sp = -1;
	int bp = 0;
	int pc = 0;
	instruction *ir = NULL;
	int last_index = -1;


  while (feof(file_ptr) == 0)
  {
    fscanf(file_ptr, "%d %d %d", &instruction_array[count].opcode, &instruction_array[count].l, &instruction_array[count].m);
    count++;
  }

	last_index = count - 1;

	printf("\t\t PC\tBP\tSP\tstack\n");
	printf("Initial values:  %2d\t%2d\t%2d\n",pc,bp,sp);

	
}
