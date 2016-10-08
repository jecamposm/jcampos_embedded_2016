#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

void printHelp(void);
void printAuthorInfo(void);
int fileExists(char *file);

//static char *var = "LD_PRELOAD=/home/jo/Dropbox/TEC/III_2016/sistemas_empotrados/tarea1/malloc/libmy_malloc.so";
static char *var = "LD_PRELOAD=TOSTRING(LD_OVERRIDE)";
#define LD_PRELOAD "LD_PRELOAD=" TOSTRING(LD_OVERRIDE) 
int
main (int argc, char **argv)
{
  char *program = NULL;
	int c;
	int p_used = 0;
	int a_used = 0;
	int h_used = 0;
	int execute_allowed = 0;
  	opterr = 0;
	
  	while ((c = getopt (argc, argv, "ahp:")) != -1)
    switch (c)
    {
    case 'a':
		printAuthorInfo();
		a_used = 1;
		return;
        break;
      case 'h':
		printHelp();
		return;
        break;
      case 'p':
		p_used = 1;
        program = optarg;
        break;
      case '?':
        if (optopt == 'p')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }

	if(p_used == 1 &&  access( program , X_OK ) == 0)
	{
		fprintf(stderr, "Program to execute: %s\n", program );
		execute_allowed = 1;

	}
	else if(p_used == 1)
	{
		fprintf (stderr, "Program %s specified does not exist\n" , program);
		return 0;	
	}else if(a_used == 1 || h_used == 1)
	{
		fprintf (stderr, "Must used -p to specify the program\n");
		return 0;	
	}


	if(execute_allowed == 1)
	{
		putenv(LD_PRELOAD);
		execl(program , "");
	}

}

void printAuthorInfo(void){
	char *info = \
"########### memcheck tool ##########\n\n\
Author: Jose Esteban Campos Murillo\n\
Carne: 2016254354 \n\n \
######################################\n";

	printf("%s" , info);
}

void printHelp(void){
	printf("Usage model\n");
}
