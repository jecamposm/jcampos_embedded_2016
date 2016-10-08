#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

void printHelp(void);
void printAuthorInfo(void);

// The LD_PRELOAD path is passed through a preprocessor variable from GCC cmd line (LD_OVERRIDE)
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
	int no_opt = 1;
	int execute_allowed = 0;
  	opterr = 0;
	
// Handle the arguments from cmd
  	while ((c = getopt (argc, argv, "ahp:")) != -1)
    {
		no_opt = 0;
		switch (c)
	    {
	    case 'a':
			a_used = 1;
	        break;
	      case 'h':
			h_used = 1;
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
	}

//if no option, die
	if(no_opt == 1)
	{
		fprintf(stderr, "Error: No option specified\n");
	}

// handle help as priority
	if(h_used == 1)
	{
		printHelp();
		return 0;
	}

// next author information
	if(a_used == 1)
	{
		printAuthorInfo();
		return 0;
	}

// check i -fp was used and if the file exitst
	if(p_used == 1 &&  access( program , X_OK ) == 0)
	{
		fprintf(stderr, "Program to execute: %s\n", program );
		execute_allowed = 1;

	}
	else if(p_used == 1)
	{
		fprintf (stderr, "Program %s does not exist\n" , program);
		return 1;	
	}else if(a_used == 1 || h_used == 1)
	{
		fprintf (stderr, "Must used -p to specify the program\n");
		return 1;	
	}

    pid_t pid = fork();
	int status;
	// create fork to execute the binary with LD_PRELOADED
    if (pid == 0)
    {
		if(execute_allowed == 1)
		{
			putenv(LD_PRELOAD); // set ethe env to the libmemcheck
			execl(program, program, NULL); // execute the program
		}
	}
	else if (pid > 0)
    {
		if (waitpid (pid, &status, 0) == pid){
			exit(0);		
		}
	}
	else
	{
		fprintf (stderr, "Fork failed\n");
		return 1;	
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
	char *help =\
"\nUsage: ./memcheck [OPTIONS]\n\
	Where OPTIONS are:\n\
\n\
	-a displays the information of the author of the program\n\
	-h displays the usage message to let the user know how to execute the application.\n\
	-p PROGRAM specifies the path to the program binary that will be analyzed, for example:\n\
		./memcheck -p /home/myuser/buggy\n";

	printf("%s\n" , help);
}
