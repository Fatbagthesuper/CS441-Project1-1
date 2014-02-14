/*
 * Support.c
 * Tyler Nickel and Nathaniel Harris
 * Feb. 13, 2013
 *
 * CS441/541: Project 1 Part 1
 *
 */
#include "Support.h"

int split_input_into_jobs(char *input_str, int *num_jobs, job_t **loc_jobs)
{
    char * str_ptr  = NULL;
	//input copy, necessary to get delimiter, not sure why
    char * copy = strdup(input_str);
    /* Start counting at 0 */
    //(*num_jobs) = 0;

    /* Split by ';' and '&' */
    for( str_ptr = strtok(input_str, "&;");
         NULL   != str_ptr;
         str_ptr = strtok(NULL, "&;") ) {
		if(strlen(str_ptr) == 1 && str_ptr[0] == ' '){
			fprintf(stderr, "Job cannot be a blank space. Continuing...\n");
			continue;
		}
        /*
         * Make a place for the new job in the local jobs array
         */
        (*loc_jobs) = (job_t *)realloc((*loc_jobs), (sizeof(job_t) * ((*num_jobs)+1)));
        if( NULL == (*loc_jobs) ) {
            fprintf(stderr, "Error: Failed to allocate memory! Critical failure on %d!", __LINE__);
            exit(-1);
        }

        /* Initialize the job_t structure */
        (*loc_jobs)[(*num_jobs)].full_command = strdup(str_ptr);
        (*loc_jobs)[(*num_jobs)].argc = 0;
		(*loc_jobs)[(*num_jobs)].BProcess = 0;
        (*loc_jobs)[(*num_jobs)].argv = NULL;

		//Gets delimeter (&/*), set BProcess for job if == &	
		if(copy[str_ptr-input_str+strlen(str_ptr)] == '&')
			(*loc_jobs)[(*num_jobs)].BProcess = 1;
		/* Increment the number of jobs */
		(*num_jobs)++;
    }
    
    /* Note: May need to add code here to check for forground/background */

    return 0;
}

int split_job_into_args(job_t *loc_job)
{
    char * str_ptr  = NULL;

    /* Start counting at 0 */
    loc_job->argc = 0;

    /* Split by ' ' */
    for( str_ptr = strtok(loc_job->full_command, " ");
         NULL   != str_ptr;
         str_ptr = strtok(NULL, " ") ) {

        /*
         * Make a place for the new argument in the argv array
         * +1 for NULL termination in the sizeof calculation below (for execvp)
         */
        loc_job->argc++;
        loc_job->argv = (char **)realloc(loc_job->argv, (sizeof(char*) * ((loc_job->argc)+1)));
        if( NULL == loc_job->argv ) {
            fprintf(stderr, "Error: Failed to allocate memory! Critical failure on %d!", __LINE__);
            exit(-1);
        }

        /* Copy over the argument */
        loc_job->argv[(loc_job->argc)-1] = strdup(str_ptr);
        loc_job->argv[loc_job->argc] = NULL;
		
    }

    return 0;
}
