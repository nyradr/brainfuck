#include "vm.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	bf_error(Bfvm *vm, int err){
    printf("Error\n");

    if(vm->debug)
        printf("\tInstruction %d\n\tMemory %d(%d)\n", mem_getpos(vm->prg), mem_getpos(vm->mem), mem_get(vm->mem));
}


void	bf_moveleft(Bfvm* vm){
    if(mem_decr(vm->mem) == 0)
    	bf_error(vm, BF_ERR_MACCES);
}

void	bf_moveright(Bfvm* vm){
	if(mem_incr(vm->mem) == 0)
		bf_error(vm, BF_ERR_MACCES);
}

void	bf_incr(Bfvm* vm){
	mem_set(vm->mem, mem_get(vm->mem) +1);
}

void	bf_decr(Bfvm* vm){
	mem_set(vm->mem, mem_get(vm->mem) -1);
}

void	bf_output(Bfvm* vm){
	char* str;

	if(vm->mcar)
		str = "%c";
	else
		str = "%d";

    printf(str, mem_get(vm->mem));
}

void	bf_input(Bfvm* vm){
    int inp = 0;

    char* str;
    if(vm->mcar)
    	str = "%c";
	else
		str = "%d";

    scanf(str, &inp);

    while(getchar() != '\n');

    mem_set(vm->mem, inp);
}

void	bf_jumppast(Bfvm* vm){
    if(mem_get(vm->mem) == 0){
        int ctn = 1;
		int open = 0;

        while(ctn){
            mem_incr(vm->prg);

			if(mem_get(vm->prg) == '[')
				open++;
			else if(mem_get(vm->prg) == ']'){
                ctn = open != 0;
                open--;
			}
        }
    }
}

void	bf_jumpback(Bfvm* vm){
    if(mem_get(vm->mem) != 0){
		int open = 0;
        int ctn = 1;

        while(ctn){
			mem_decr(vm->prg);

			if(mem_get(vm->prg) == ']')
                open++;
			else if(mem_get(vm->prg) == '['){
				ctn = open != 0;
				open--;
			}
        }
    }
}

Bfvm*	bfvm_create(int memsize, int debug, int verbose, int mcar){
	Bfvm* vm = malloc(sizeof(Bfvm));

	if(vm){
        vm->mem = mem_create(memsize);

        if(!vm->mem)
        	bfvm_free(vm);

		vm->debug = debug;
		vm->verbose = verbose;
		vm->mcar = mcar;
	}

	return vm;
}

void	bfvm_free(Bfvm*	vm){
    free(vm->mem);
    free(vm->prg);
    free(vm);
    vm = NULL;
}

void	bfvm_loadStr(Bfvm* vm, char* prg){
	if(vm->verbose)
		printf("load program : %s\n", prg);

	int prgsize = strlen(prg);

    vm->prg = mem_create(prgsize);

	if(vm->prg){
		for(int i = 0; i < prgsize; i++){
            mem_set(vm->prg, prg[i]);

            mem_incr(vm->prg);
		}
		mem_deb(vm->prg);
	}
}

void	bfvm_loadFile(Bfvm* vm, FILE* file){
	if(vm->verbose)
		printf("load program from file\n");

    if(file){
		int size = 0;

		fseek(file, 0, SEEK_END);
        size = ftell(file);
		fseek(file, 0, SEEK_SET);

		vm->prg = mem_create(size);

		if(vm->prg){
        	for(int i = 0; i < size; i++){
            	mem_set(vm->prg, fgetc(file));
            	mem_incr(vm->prg);
        	}

			mem_deb(vm->prg);
		}
		fclose(file);
    }
}

void    bfvm_execute(Bfvm* vm){
	mem_deb(vm->mem);
	mem_deb(vm->prg);

	while(bfvm_next(vm));
}

int		bfvm_next(Bfvm* vm){
	if(vm->debug)
		printf("%c\t: %x (%d)\n", mem_get(vm->prg), mem_getpos(vm->mem), mem_get(vm->mem));

	switch(mem_get(vm->prg)){

	case '>':
		bf_moveright(vm);
		break;

	case '<':
		bf_moveleft(vm);
		break;

	case '+':
		bf_incr(vm);
		break;

	case '-':
		bf_decr(vm);
		break;

	case '.':
		bf_output(vm);
		break;

	case ',':
		bf_input(vm);
		break;

	case '[':
		bf_jumppast(vm);
		break;

	case ']':
		bf_jumpback(vm);
		break;

	default:
		break;
	}

	return mem_incr(vm->prg);
}
