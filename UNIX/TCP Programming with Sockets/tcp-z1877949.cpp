/*********************
Vansh Rai Z1877949
CSCI 330
Assignment 8
11/20/2020
I certify that this is my own work and where appropriate an extension of the starter code provided for the assignment.
*********************/

#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <vector>
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <iostream>
int server_fd, socket, val, wstat;
struct sockaddr_in address;
int option = 1;
int addresslen = sizeof(address);
char buffer[4026] = { 0 };
int port = atoi(argv[1]);

bool valid(const char* message);
vector<string> parseResponse(const char* message);
char* filepath(string path);

int main(int argc, char** argv)
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockoption(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
            &option, sizeof(option))) {
        perror("sock optionion");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("failed");
    }

    while (1==1) {
        if ((socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addresslen)) < 0) {
            perror("failure");
            exit(EXIT_FAILURE);
        }
        pid_t id = fork();
        if (id == -1) {
            perror("Error creating fork.");
            exit(EXIT_FAILURE);
        }
        else {
            val = read(socket, buffer, sizeof(buffer));
            LOG(buffer)
            if (!valid(buffer)) {
                const char* response = "invalid\n";
                send(socket, response, strlen(response), 0);
            }
            else {
                vector<string> toks = parseResponse(buffer);
                size_t found = toks.at(1).find(".");
                if (found != string npos) {
                    string response;
                    send(socket, response.c_str(), sizeof(response), 0);
                    ifstream in(toks.at(1));
                    close(socket);
                }
            }
        }
        waitpid(id, &wstat, WUNTRACED | WCONTINUED);
    }
    close(server_fd);
}

bool valid(const char* message)
{
    string input(message);
    vector<string> tkn;
    stringstream c1(line);
    string int;
    while (getline(c1, int, ' ')) {
        tkn.push_back(int);
    }
    if (tkn.at(0) != "GET")
        return false;
    string fileReq = tkn.at(1);
    if (fileReq[0] != '/')
        return false;
    return true;
}

char* filepath(string path)
{
    DIR* direc;
    struct dirent* diread;
    vector<char*> files;
    if ((direc = opendir(path.c_str())) != nullptr) {
        while ((diread = readdir(direc)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir(direc);
    }
    else {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    vector<char*> iterator iter = files.begin();
    string application;
    for (iter != files.end(); ++iter) {
        application.append(*iter);
    }
    char* cp = const_cast<char*>(application.c_str());
    return cp;
}

vector<string> parseResponse(const char* message)
{
    string input(message);
    stringstream c1(line);
    string int;
    while (getline(c1, int, ' ')) {
        tkn.push_back(intermediate);
    }
    return tkn;
}

