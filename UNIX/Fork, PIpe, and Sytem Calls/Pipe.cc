/* Vansh Rai
Z1877949
CSCI 330 
Assignment 05
Due Date: 10/23/2020
I certify that this is my own work and where appropriate an extension
of the starter code provided for the assignment.*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main() {
    char c1 [255], c2[255]; //Size is 256 because that is the max size.
    while (1) {
        cout << "c1? ";
        cin.getline(c1, 255);  
        if ((strcmp(c1, "quit") == 0)) { //Checking for quit.
            exit(0);
        }
        cout << "c2? ";
        cin.getline(c2, 255); 
        if ((strcmp(c2, "quit") == 0)) { //Checking for quit.
            exit(0);
        }
        int pipefd[2]; //Declaring variables.
        int rs = pipe(pipefd); 
        char *p1, *p2;    
        char *carr1[10], *carr2[10]; 
        int i = 1, j = 1; 

        p1 = strtok(c1, " ");
        carr1[0] = p1;
        while (p1 != NULL) {
            p1 = strtok(NULL, " ");
            carr1[i] = p1;
            i++;
        }
        p2 = strtok(c2, " ");
        carr2[0] = p2;
        while (p2 != NULL) {
            p2 = strtok(NULL, " ");
            carr2[j] = p2;
            j++;
        }
        if (rs < 0) {
            exit(0);
        }
        rs = fork();
        if (rs < 0) {
            exit(0);
        }
        if (rs == 0) { //Child process
            close(pipefd[1]); 
            close(0); 
            dup(pipefd[0]); 
            close(pipefd[0]);
            rs = execvp(carr2[0], carr2); 
            if (rs < 0) {
                exit(0);
            }
        }
        else { //Parent function
                int rs2 = fork();
                if (rs2 == -1) {
                    exit(0);
                }
                if (rs2 == 0) {
                    close(pipefd[0]);
                    close(1); 
                    dup(pipefd[1]);
                    close(pipefd[1]); 
                    rs = execvp(carr1[0], carr1);
                    if (rs == -1) {
                        exit(1);
                    }
                }
            else { //Closing and waiting.
                close(pipefd[0]);
                close(pipefd[1]);
                wait(&rs2);
                wait(&rs);
            }
        }
    }
    return 0;
}
