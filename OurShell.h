/*
 * OurShell.h
 * Tyler Nickel and Nathanial Harris
 * Feb. 13, 2013
 *
 * CS441/541: Project 1 Part 1
 *
 */
#ifndef OURSHELL_H
#define OURSHELL_H

#include "Support.h"
/* For fork, exec, sleep */
#include <sys/types.h>
#include <unistd.h>
/* For waitpid */
#include <sys/wait.h>

/******************************
 * Defines
 ******************************/



/******************************
 * Structures
 ******************************/


/******************************
 * Global Variables
 ******************************/
 //Track Non-built-in jobs, Built-in jobs, newest job, and background jobs
 int ext_Jobs = 0, current_Job = 1, back_Jobs = 0,num_jobs = 0;;

/******************************
 * Function declarations
 ******************************/
/*
 * Call split_into_jobs, then split_into_args for each job, then prints job stats
 *   input_str : String read from the input stream (may contain multiple jobs)
 *   num_jobs : Number of jobs in the input stream
 *   loc_jobs : Array of job_t's each representing a single job
 * Return 0 on success, ow error
 */
int assess_command_input(char *input_str, int *num_jobs, job_t **loc_jobs);

/*
 * Displays ext_jobs, job history, and background jobs on exit
 *   Return void pointer
 */
void display_end_characteristics();

#endif /* OURSHELL_H */
