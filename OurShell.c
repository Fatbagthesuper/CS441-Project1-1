/* OurShell.c
 * Tyler Nickel and Nathaniel Harris
 * Feb. 13, 2013
 *
 * CS441/541: Project 1 Part 1
 *
 */
#include "OurShell.h"
#include "Support.c"
int main(int argc, char * argv[]) {
    int i,j,num_jobs = 0;
    job_t *loc_jobs = NULL;
    
    /*
     * Allocate some space for the job_t array
     * Necessary so split_input_into_jobs() function has a memory
     * handle to work with.
     */
    loc_jobs = (job_t*)malloc(sizeof(job_t) * 1);
    if( NULL == loc_jobs ) {
        fprintf(stderr, "Error: Failed to allocate memory! Critical failure on %d!", __LINE__);
        exit(-1);
    }
    //./OurShell ITest to run Hursey example
    if(argc > 1 ){
    	/*
    	 * Below is just an example of how to use the support functionality.
     	* You will want to remove this code when you get started, but
     	* it may serve as a helpful reference while you are getting started.
     	*/
    	char command[1024] = "echo Hello CS441 ; echo Welcome to my shell ; ls & sleep 10 &";
    	
    	/*
    	 * Split out the individual jobs from the larger command
     	*/
    	printf("Splitting the command: \"%s\"\n", command);
    	split_input_into_jobs(command, &num_jobs, &loc_jobs);

    	/*
     	* For each of those jobs split out the argument set
     	*/
    	for( i = 0; i < num_jobs; ++i ) {
        	printf("Processing the job: \"%s\"\n", loc_jobs[i].full_command);

        	split_job_into_args( &(loc_jobs[i]) );

        	/*
        	 * Display the arguments
         	*/
        	printf("Arguments: ");
        	fflush(NULL);
       	 	for( j = 0; j < loc_jobs[i].argc; ++j ) {
           		printf(" [%s]", loc_jobs[i].argv[j]);
            		fflush(NULL);
         	}
       	 	printf("\n");
         	fflush(NULL);
    	}
    }else{
    	//Interactive mode 
    	char command[1024];
   	char *fgets_rtn = NULL;
	//Track Non-built-in jobs
	int ext_Jobs = 0, current_Job = 0, back_Jobs = 0;
	//FALSE == TRUE ON MY MACHINE
    	while(FALSE){
		printf("OurShell$");
      		//Put up to command.Length chars in command
      		fgets_rtn = fgets(command, sizeof(command)/sizeof(char), stdin);
      		//Strip Newline?
      		if( '\n' == command[ strlen(command) - 1] ) {
			command[ strlen(command) - 1] = '\0';
      		}
      		if(fgets_rtn == NULL){
			printf("Exit\n");
			fflush(NULL);
			break;
      		}
		/*
     		 * Split out the individual jobs from the larger command
     		 */
    		printf("Splitting the command: \"%s\"\n", command);
    		split_input_into_jobs(command, &num_jobs, &loc_jobs);
		/*
     		 * For each of those jobs split out the argument set
     		 */
    		for( i = current_Job; i < num_jobs; ++i ) {
			char jobFlag = ' ';
        		printf("Processing the job: \"%s\"\n", loc_jobs[i].full_command);

        		split_job_into_args( &(loc_jobs[i]) );

			//Assess Flag (this should work)
			if(strcmp(loc_jobs[i].Name, "jobs\0") == 0||
				strcmp(loc_jobs[i].Name, "history\0") == 0||
				strcmp(loc_jobs[i].Name, "exit\0") == 0) {
					jobFlag = '^';
			}
			else if(loc_jobs[i].BProcess) jobFlag = '*';

        		/*
        	 	* Display the Job characteristics
         		*/
        		printf("Job %d%c: %s ", i, jobFlag, loc_jobs[i].Name);
        		fflush(NULL);
       	 		for( j = 0; j < loc_jobs[i].argc; ++j ) {
           		printf("[%s]", loc_jobs[i].argv[j]);
            		fflush(NULL);
         		}
       	 	printf("\n");
         	fflush(NULL);
		current_Job++;
    		}
    	}
    }
    /*
     * Cleanup
     */
    if( NULL != loc_jobs ) {
        /* Cleanup struct fields */
        for( i = 0; i < num_jobs; ++i ) {
            /* .full_command */
            if( NULL != loc_jobs[i].full_command ) {
                free( loc_jobs[i].full_command );
                loc_jobs[i].full_command = NULL;
            }

            /* .argv */
            if( NULL != loc_jobs[i].argv ) {
                for( j = 0; j < loc_jobs[i].argc; ++j ) {
                    if( NULL != loc_jobs[i].argv[j] ) {
                        free( loc_jobs[i].argv[j] );
                        loc_jobs[i].argv[j] = NULL;
                    }
                }
                free( loc_jobs[i].argv );
                loc_jobs[i].argv = NULL;
            }

            /* .argc */
            loc_jobs[i].argc = 0;
        }

        /* Free the array */
        free(loc_jobs);
        loc_jobs = NULL;
    }
    return 0;

}
