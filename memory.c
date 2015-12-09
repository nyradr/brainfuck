#include "memory.h"

#include <stdlib.h>
#include <stdio.h>

Mem*	mem_create(int size){
	Mem* mem = malloc(sizeof(Mem));

	if(mem){
		mem->deb = malloc(size);

		if(mem->deb){
        	mem->end = mem->deb + size;
        	mem->ptr = mem->deb;

			do{
				mem_set(mem, 0);
			}while(mem_incr(mem));
			mem->ptr = mem->deb;
		}else
			mem_free(mem);
	}

	return mem;
}

void	mem_free(Mem* mem){
	free(mem->deb);
	free(mem);
	mem = NULL;
}

char	mem_get(Mem* mem){
	return *mem->ptr;
}

int		mem_getpos(Mem* mem){
    return mem->ptr - mem->deb;
}

void	mem_set(Mem* mem, char v){
	*mem->ptr = v;
}

int		mem_incr(Mem* mem){
	int incp = 0;
    if((incp = mem->ptr < mem->end))
    	mem->ptr++;

	return incp;
}

int		mem_decr(Mem* mem){
	int decp = 0;
	if((decp = mem->ptr > mem->deb))
		mem->ptr--;

	return decp;
}

void	mem_deb(Mem* mem){
	mem->ptr = mem->deb;
}
