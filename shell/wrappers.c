//wrappers.c
//CSCI 315
//Dale Hartman

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/socket.h>

pid_t Fork(void) {
    pid_t pid = fork();
    if ( -1 == pid) { //We encountered an error
        perror("fork() was unable to create a child process");
        exit(-1);
    } else {
        return pid;
    }
}

int Pipe(int pipefd[2]) {
    int retval = pipe(pipefd);
    if ( -1 == retval ) {
        perror("pipe() was unable to create a pipe");
        exit(-1);
    } else {
        return retval;
    }
}

int Read(int fd, void *buf, size_t count) {
    int retval = read(fd, buf, count);
    if ( -1 == retval ) {
        perror("read() was unable to read from the file");
        exit(-1);
    } else {
        return retval;
    }
}

int Write(int fd, const void *buf, size_t count) {
    int retval = write(fd, buf, count);
    if ( -1 == retval ) {
        perror("write() was unable to write to the file");
        exit(-1);
    } else {
        return retval;
    }
}

pid_t Wait(int *status) {
    pid_t retval = wait(status);
    if ( -1 == retval ) {
        perror("wait() encountered and error");
        exit(-1);
    } else {
        return retval;
    }
}

pid_t Waitpid(pid_t pid, int *status, int options) {
    pid_t retval = waitpid(pid, status, options);
    if ( -1 == retval ) {
        perror("waitpid() encountered and error");
        exit(-1);
    } else {
        return retval;
    }
}

int Open(const char *pathname, int flags) {
    int retval = open(pathname, flags);
    if ( -1 == retval ) {
        perror("open() was unable to open the specified file");
        exit(-1);
    } else {
        return retval;
    }
}

int Close(int fd) {
    int retval = close(fd);
    if ( -1 == retval ) {
        perror("close() was unable to close the specified file");
        exit(-1);
    } else {
        return retval;
    }
}

int Listen(int sockfd, int backlog) {
    int retval = listen(sockfd, backlog);
    if ( -1 == retval ) {
        perror("listen() encountered an error");
        exit(-1);
    } else {
        return retval;
    }
}

int Socket(int domain, int type, int protocol) {
    int retval = socket(domain, type, protocol);
    if ( -1 == retval ) {
        perror("socket() was unable to setup a socket");
        exit(-1);
    } else {
        return retval;
    }
}

ssize_t Send(int sockfd, const void *msg, int len, int flags) {
    int retval = send(sockfd, msg, len, flags);
    if ( -1 == retval ) {
        perror("send() was unable to send your message");
        exit(-1);
    } else {
        return retval;
    }
}

ssize_t Recv(int sockfd, void *buf, int len, int flags) {
    int retval = recv(sockfd, buf, len, flags);
    if ( -1 == retval ) {
        perror("recv() was unable to receive a message");
        exit(-1);
    } else {
        return retval;
    }
}
