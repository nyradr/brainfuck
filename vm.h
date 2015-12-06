#ifndef VM_H_INCLUDED
#define VM_H_INCLUDED

#include "memory.h"

#include <stdio.h>

#define		BF_ERR_MACCES	0


/*  Brainfuck interpreter
*/
struct bfvm{
	Mem*	mem;		//memory
	Mem*	prg;		//program

	int		debug;		//debug flag (1 if in debug mode, 0 else)
	int		verbose;	//verbose flag (1 if in verbose mode, 0 else)
	int		mcar;
};
typedef struct bfvm Bfvm;

/*  Create new brainfuck interpreter
	memsize	: memory size
	debug	: debug flag
	verbose : verobse flag

	return	: pointer on brainfuck interpreter or NULL if fail
*/

Bfvm*	bfvm_create(int memsize, int debug, int verbose, int mcar);

/*  Free the brainfuck interpreter
	vm	: brainfuck interpreter
*/
void	bfvm_free(Bfvm*	vm);

/*	Load brainfuck program from a string
	vm	: brainfuck interpreter
	prg	: string containing the ASCII brainfuck program
*/
void	bfvm_loadStr(Bfvm* vm, char* prg);

/*  Load brainfuck program from a file
	vm		: brainfuck interpreter
	file	: input file with the brainfuck program
*/
void	bfvm_loadFile(Bfvm* vm, FILE* file);

/*	Execute the brainfuck program loaded
	vm	: brainfuck interpreter
*/
void    bfvm_execute(Bfvm* vm);

/*  Execute the current program instruction and jump to the next instruction
	vm	: brainfuck interpreter
	return	: 0 if the end of the program is reached
*/
int		bfvm_next(Bfvm* vm);


#endif // VM_H_INCLUDED
