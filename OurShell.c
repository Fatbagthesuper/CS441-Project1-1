/* 
 * OurShell.c
 * Tyler Nickel and Nathanial Harris
 * Feb. 13, 2013
 *
 * CS441/541: Project 1 Part 1
 *
 */
#include "OurShell.h"
#include "Support.c"
int main(int argc, char * argv[]) {
    int i,j;
    job_t *loc_jobs = NULL;
	char* fgets_rtn = NULL;
	char command[1024];
	//int ext_Jobs = 0, current_Job = 0, back_Jobs = 0;
    
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
	
    //If CMDLINE args, Batch File Processing Mode
    if(argc > 1){
		
		//Test last arg in argv to make sure == NULL, tests suggest as much
		//printf("Last argv: %s", argv[argc]);
		
		//Process each file
		for(i = 1; i < argc; i++){
			FILE *fd = NULL;
			// TODO: Open the file here
			fd = fopen(argv[i], "r");
			if(fd == NULL){
				fprintf(stderr, "Error: Cannot open the file %s for reading.\n", argv[i]);
				return -1;
			}
		
			// Read each line of file
			while( feof(fd) == 0 ) {
				fgets_rtn = fgets(command, sizeof(command)/sizeof(char), fd);
				if( NULL == fgets_rtn) {
					/* Ctrl-D */
					
					printf("End of File. %d\n", (int)strlen(command));
					break;
				}
			
				/* Strip off the new line */
				if( '\n' == command[ strlen(command) - 1] ) {
					command[ strlen(command) - 1] = '\0';
				}
				if(assess_command_input(command, &num_jobs, &loc_jobs) != 0){
					printf("Failure to assess command input.\n");
					return -1;
				}
				//"empty" command string, so that it is overwritten
				//command[0] = '\0';

			}
			
			//Close the file
			fclose(fd);
		}
		
    	//print final stats
		display_end_characteristics();
    }else{
		//Interactive mode 
		//Test last arg in argv to make sure == NULL, tests suggest as much
		//printf("Last Argv Test: %s\n", argv[1]);
    	
		//FALSE == TRUE ON MY MACHINE
    	while(FALSE){
			printf("OurShell$");
      		//Put up to command.Length chars in command
      		fgets_rtn = fgets(command, sizeof(command)/sizeof(char), stdin);
      		//Strip Newline
      		if( '\n' == command[ strlen(command) - 1] ) {
				command[ strlen(command) - 1] = '\0';
      		}
      		if(fgets_rtn == NULL){
				//printf("Exit\n");
				
				//Print Final stats
				display_end_characteristics();
				fflush(NULL);
				break;
      		}
			if(assess_command_input(command, &num_jobs, &loc_jobs) != 0){
				printf("Failed to assess command input.\n");
				return -1;
			}
			//"empty" command string, so that it is overwritten
			//command[0] = '\0';
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
				//THIS CAUSES ISSUES FOR SOME REASON (full_command never allocated?)
                free( loc_jobs[i].full_command );
                loc_jobs[i].full_command = NULL;
				loc_jobs[i].BProcess = 0;
            }

            /* .argv */
            if( NULL != loc_jobs[i].argv ) {
                for( j = 0; j < loc_jobs[i].argc; ++j ) {
                    if( NULL != loc_jobs[i].argv[j] ) {
                        free( loc_jobs[i].argv[j] );
                        loc_jobs[i].argv[j] = NULL;
                    }
                }
				//redundant call that fucks up the program
                //free( loc_jobs[i].argv );
                loc_jobs[i].argv = NULL;
            }

            /* .argc */
            loc_jobs[i].argc = 0;
			
        }

        /* Free the array */
        free(loc_jobs);
        loc_jobs = NULL;
		
    }
	//Free other stuff
	num_jobs = 0;
	current_Job = 0;
	ext_Jobs = 0;
	back_Jobs = 0;
	fgets_rtn = NULL;
	i = 0;
	j = 0;
    return 0;

}
//MUST BE **loc_jobs to pass reference down through methods
int assess_command_input(char *input_str, int *num_jobs, job_t **loc_jobs){
	int i,j;
	/*
	 * Split out the individual jobs from the larger command
	 */
	if(split_input_into_jobs(input_str, num_jobs, loc_jobs) != 0){
		printf("Error splitting input into jobs.\n");
		return -1;
	}
	/*
	 * For each of those jobs split out the argument set
	 */
	for( i = current_Job-1; i < *num_jobs; ++i ) {
		char jobFlag = ' ';
		
		if(split_job_into_args( &((*loc_jobs)[i]) ) != 0){
			printf("Error splitting input into args.\n");
			return -1;
		}
		
		//Assess Flag by checking job name
		//Built-in job
		if(strcmp((*loc_jobs)[i].argv[0], "jobs\0") == 0||
		   strcmp((*loc_jobs)[i].argv[0], "history\0") == 0||
		   strcmp((*loc_jobs)[i].argv[0], "exit\0") == 0) {
			jobFlag = '^';
		}
		//Background job
		else if((*loc_jobs)[i].BProcess){
			back_Jobs++;
			ext_Jobs++;
			jobFlag = '*';
			
		}//External job
		else{ext_Jobs++;}
		
		/*
		 * Display the Job characteristics
		 */
		printf("Job %2d%c: \"%s\" ", current_Job, jobFlag, (*loc_jobs)[i].argv[0]);
		fflush(NULL);
		for( j = 1; j < (*loc_jobs)[i].argc; ++j ) {
			printf("[%s]", (*loc_jobs)[i].argv[j]);
			fflush(NULL);
		}
		printf("\n");
		fflush(NULL);
		current_Job++;
	}
	return 0;
}
void display_end_characteristics(){
	printf("Total number of jobs: %d\n", ext_Jobs);
	printf("Total number of jobs in history: %d\n", num_jobs);
	printf("Total number of jobs in background: %d\n", back_Jobs);
	return;
}
