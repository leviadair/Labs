/*
 * CSCI 315 Operating Systems Design
 * Date: 2014-09-02
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual or
 * institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright and
 * permission notice is maintained, intact, in all copies and supporting
 * documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h> 
#include <math.h>
#include <stdlib.h> 
#include <errno.h>
#include "wrappers.h" 

#define READ_END 0
#define WRITE_END 1

/*
 * The added feature is a very basic implementation of Bash's alias feature.
 * During a run of the shell, simply type:
 * > alias [name of alias] [command to reference]
 * The command to reference must conform to the limitations of the shell's 
 * parsing (must not contain spaces).
 * example run:
 * > alias list ls
 * > list .
 */

void view_help() {
	printf("gshell version 1.0\n");
	printf("available features:\n");
	printf("\n");
	printf("semicolon recognition: Use a semicolon to separate two distinct commands on the same line:\n");
	printf("ishell> ls; cp Makefile Hello\n");
	printf("\n");
	printf("ls shortcut: enter two blank lines in a row to run the ls command on the current directory.\n");

}

struct alias {
	char *name;
	char *reference;
	struct alias *next;
}; 

void pipe_com(char* left, char* right){ // consulted http://stackoverflow.com/questions/3642732/using-dup2-for-piping
 
	char *right_side[256] = {0}; 
   	char *left_side[256] = {0};
    int i = 0;
    char *t = strtok(left, " ");
    int n;

    while (t != NULL) { 

        //printf("1 putting %s in array index %d\n", t, i);
        n = strlen(t) + 1;
        left_side[i] = malloc(n*sizeof(char));
        strcpy(left_side[i], t);
        i++;
        t = strtok(NULL, " ");
    } 
    char *q = strtok(right, " ");
    i =0;  
   

    while (q != NULL) { 

        //printf("2 putting %s in array index %d\n", q, i);
        n = strlen(q) + 1;
        right_side[i] = malloc(n*sizeof(char));
        strcpy(right_side[i], q);
        i++;
        q = strtok(NULL, " ");
    } 




  pid_t pid; 
  int fd[2]; 
  pipe(fd); 
  pid = Fork(); 
  if(0 == pid){
  	dup2(fd[WRITE_END], STDOUT_FILENO); 
  	close(fd[WRITE_END]);  
  	execvp(left_side[0], left_side);



  } 
  else{ 
  	pid = Fork(); 
  	if(0 == pid){
 		dup2(fd[READ_END], STDIN_FILENO); 
  		close(fd[READ_END]);  
  		execvp(right_side[0], right_side);

  	}

  }
}
int calculate(int var1, char operator, int var2){   
  int ret_val; 
  double answer =0; 
  switch(operator){
        case '+':  
          answer = var1 + var2;   
	  ret_val = 1;
          printf("gshell>answer is %f \n", answer);
          break;
        case '-':  
          answer = var1 - var2; 
	  ret_val = 1;
	  printf("gshell>answer is %f \n", answer);
          break;
        case '*':  
          answer = var1 * var2; 
	  ret_val = 1;
	  printf("gshell>answer is %f \n", answer);
          break;
        case '/':  
          answer = (double)var1 / (double)var2; 
	  ret_val = 1;
	  printf("gshell>answer is %f \n", answer);
          break; 
        case '%':  
          answer = var1 / var2; 
	  ret_val = 1;
	  printf("gshell>answer is %f \n", answer);
          break; 
        case '^':  
          answer = pow((double)var1 , (double)var2);
	  ret_val = 1;
	  printf("gshell>answer is %f  \n", answer);
          break; 
        default: 
	  ret_val = 0;
          printf("gshell>Arithmetic not presented \n");
  } 
  return ret_val;
}
//Declare our global alias list
struct alias *alias_list = NULL;

void create_alias(char* name, char* ref) {
	//Set up to traverse the alias list
	struct alias *curr_alias = alias_list;
	//While we have not reached the end of the list
	while (curr_alias != NULL) {
		//If we find an alias with a matching name, we update it
		if (0 == strcmp(curr_alias->name, name)) {
			curr_alias->reference = ref;
			//Then, exit the function
			return;
		//Else, step forward on the list and loop		
        } else {
			curr_alias = curr_alias->next;
		}
	} //If we exit the while loop, we reached the end of the list without finding a matching alias, meaning we make a new element in the list
	curr_alias = (struct alias *) malloc(sizeof(struct alias));
	curr_alias->name = name;
	curr_alias->reference = ref;
	//Put it at the head of the list
	curr_alias->next = alias_list;
	alias_list = curr_alias;
	return;
}

char *check_alias(char* name) {
	//Set up to traverse the alias list
	struct alias *curr_alias = alias_list;
	//While we have not reached the end of the list
	while (curr_alias != NULL) {
		//If we find an alias with a matching name, return its reference
		if (0 == strcmp(curr_alias->name, name)) {
			return curr_alias->reference;
		//Else, step forward on the list and loop		
        } else {
			curr_alias = curr_alias->next;
		}
	}//If we exit the loop, the name we are checking does not exist in our alias list, so we return NULL
	return NULL;
}



void run_com(char *command) {

  char *p[256] = {0};
    int i = 0;
    char *t = strtok(command, " ");
    int n;

    while (t != NULL) { 

        //printf("putting %s in array index %d\n", t, i);
        n = strlen(t) + 1;
        p[i] = malloc(n*sizeof(char));
        strcpy(p[i], t);
        i++;
        t = strtok(NULL, " ");
    } 
    
    if(p[2] != NULL){ 
      int calc_val =calculate(atoi(p[0]),p[1][0],atoi(p[2])); 
      if(calc_val){

	return; 
      }
    }
    // printf("putting Null terminator at array index %d\n", i);
    p[i] = NULL;

	if (0 == strcmp(p[0],"help")) {
		view_help();
		return;
	}

	// Check to see if this command is creating an alias
	if (0 == strcmp(p[0],"alias")) {
		create_alias(p[1], p[2]);
		return;
	}

	// Check to see if this command is exiting
	if (0 == strcmp(p[0],"exit")) {
			exit(0);
	}

	// Check to see if this command is changing directory
	if (0 == strcmp(p[0],"cd")) {
			if (p[1] != NULL) {
				chdir(p[1]);
				printf("[gshell: program terminated successfully]\n");
			}
			return;
	}

    // Check to see if this command is using an alias
    char *reference = check_alias(p[0]);
    // If it actually was in the alias list, replace the alias name with the referenced command
    if (reference != NULL) {
        p[0] = reference;
    }
	
  
    pid_t pid;
    int status; // exit status to be filled by wait

    if ((pid = Fork()) == 0) {
      // child process

      int trm = 0;

      trm = execvp(p[0], p);

      exit(trm);

    } else {

      // parent process

      Wait(&status);

      if (status == 0) { //no error was encountered
          printf("[gshell: program terminated successfully]\n");
      } else { //the child didn't run properly
         printf("[gshell: program terminated abnormally][%d]\n", status);
      }
    }
}

int main(int argc, char* argv[]) { 


  bool one_blank = false;
  char last_command_ran[256] = "ls"; 
  bool run_pipe = false;

  while(1) {

    char *input = readline("gshell> ");

	if (0 == strlen(input)) {
		if (one_blank) {
			one_blank = false;
			char *command = (char*) malloc(3*sizeof(char));
			strcpy(command, "ls");
			run_com(command);
		} else {
			one_blank = true;
		}
	} else {
		
		one_blank = false;

		char *command1 = strtok(input, ";");
		char *command2 = strtok(NULL, ";"); 

		char *pipe1 = strtok(input, "|"); 
		char *pipe2 = strtok(NULL, "|"); 
		if(NULL != pipe2){ 
		  run_pipe = true; 
		  //printf("pipe 1 is %s\n", pipe1 ); 
		  //printf("pipe 2 is %s\n",pipe2 );
		  pipe_com(pipe1, pipe2);
		}
        
        if(0 == strcmp(command1, "!!")){
            command1 = last_command_ran;
        }

        
        strcpy(last_command_ran, command1); 
        if(!run_pipe){
        	run_com(command1);
        }
		

		if (command2 != NULL && !run_pipe) {
            if(0 == strcmp(command2, "!!")){
                command2 = last_command_ran;
            }
            strcpy(last_command_ran, command2);
			run_com(command2);
		}
	}
  }
}
