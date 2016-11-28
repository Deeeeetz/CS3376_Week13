/*
 *  * sh1.c: sample version 1 of a UNIX command shell/interpreter.
 *   *
 *    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char line[256];
    char prompt[] = "SimpleShell: Enter command or exit % ";

    /* spit out the prompt */
    printf("%s", prompt );

    /* Try getting input. If error or EOF, exit */
    while( fgets(line, sizeof line, stdin) != NULL )
    {
    	/* fgets leaves '\n' in input buffer. ditch it */
	line[strlen(line)-1] = '\0';

	if(strcmp(line,"exit") == 0){
            break;
        }
	/*If the user inputs a "list" or "print" command to do "ls -l" or "cat respectively*/
	else if(strcmp(line,"list") == 0){
		system( "ls -l");
	}
	else if(strcmp(line,"print") == 0){
		system( "cat");
	}
	else {
	      system( line );
        }

  	printf("%s", prompt );
    }

return 0;
										}
