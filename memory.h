#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

/* Memory array
*/
struct mem{
    char* deb;	//array start
    char* ptr;	//current position
    char* end;	//array end
};
typedef struct mem Mem;

/*	Create new Mem structure and initialize all the bytes to 0
	size	: size of the memory
	return	: Pointer on mem or NULL if fail
*/
Mem*	mem_create(int size);

/*  Free the memory
*/
void	mem_free(Mem* mem);

/*  Get the byte value at ptr
*/
char	mem_get(Mem* mem);

/*	Get the ptr position
*/
int		mem_getpos(Mem* mem);

/*  Set the byte value of ptr
*/
void	mem_set(Mem* mem, char v);

/*  Go to the next memory case
	return 0 if the next case is out of the allowed memory
*/
int		mem_incr(Mem* mem);

/*  Go to the previous memory case
	return 0 if the previous case is out of the allowed memory
*/
int		mem_decr(Mem* mem);

/*  Go at the begining of the memory
*/
void	mem_deb(Mem* mem);



#endif // MEMORY_H_INCLUDED
