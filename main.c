#include <stdio.h>
#include <stdlib.h>
#include <argp.h>
#include <error.h>

#include "vm.h"

/* Program informations
*/
const char *argp_program_version = "brainfuck-0.9.3.0";
const char *argp_program_bug_address = "nyradr@protonmail.com";
static char doc[] = "Brainfuck interpreter";
static char args_doc[] = "";

/*  Entry type
*/
#define TYPE_NONE	0
#define	TYPE_TEXT	1
#define TYPE_FILE	2

/*	Possibles arguments
*/
static struct argp_option options[] = {
    {"verbose"	, 'v'	, 0		, 0		, "verbose output"},
    {"debug"	, 'd'	, 0		, 0		, "output in debug mode"},
    {"file"		, 'f'	, ""	, 0		, "file containing a brainfuck program"},
    {"memory"	, 'm'	, ""	, 0		, "memory allowed to the program interpreted"},
    {"char"		, 'c'	, 0		, 0		, "caracter mode"},
    {0}
};

/*  Options
*/
struct arguments{
	int		verbose;
	int 	debug;
	int		mcar;

	int		memory;
	int		type;
	char*	arg;
};

/*  argp option parser
*/
static error_t parse_opt(int key, char* arg, struct argp_state* state){
    struct arguments *args = state->input;

    switch(key){
	case 'v':
		args->verbose = 1;
		break;

	case 'd':
		args->debug = 1;
		break;

	case 'c':
		args->mcar = 1;
		break;

	case 'f':
		if(args->type == TYPE_NONE){
			args->type = TYPE_FILE;
			args->arg = arg;
		}else{
            argp_error(state, "Multiple arguments");
            return EINVAL;
		}
		break;

	case 'm':
		args->memory = atoi(arg);
		if(args->memory == 0){
            argp_error(state, "Invalid memory size");
			return EINVAL;
		}
		break;

	case ARGP_KEY_ARG:
		if(args->type == TYPE_NONE){
			args->type = TYPE_TEXT;
			args->arg = arg;
		}else{
			argp_error(state, "Multiple arguments lol");
			return EINVAL;
		}

		break;

	default:
		return ARGP_ERR_UNKNOWN;
		break;
    }

    return 0;
}

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char** argv)
{
    struct arguments args = {	//default options
		.verbose = 0,
		.debug = 0,
		.mcar = 0,
		.memory = 0xF,
        .type = TYPE_NONE,
        .arg = NULL
    };

    argp_parse(&argp, argc, argv, 0, 0, &args);	//argp parsing

    if(args.type != TYPE_NONE){
   		Bfvm* vm = bfvm_create(args.memory, args.debug, args.verbose, args.mcar);

   		if(vm){
            if(args.type == TYPE_FILE){
				FILE* file = fopen(args.arg, "r");

				if(!file){
					printf("Error : file loading error\n");
					exit(-1);
				}else
					bfvm_loadFile(vm, file);
			}else
                bfvm_loadStr(vm, args.arg);

			bfvm_execute(vm);
			bfvm_free(vm);

			printf("\n");
			exit(0);
   		}else
			printf("Error : interpretor creation error\n");
    }else
        printf("Error : no programs to interpret\n");

    exit(-1);
}
