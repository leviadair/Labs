//wrappers.h
//CSCI 315
//Dale Hartman

#ifndef WRAPPERS_H
#define WRAPPERS_H

pid_t Fork(void);

int Pipe(int pipefd[2]);

int Read(int fd, void *buf, size_t count);

int Write(int fd, const void *buf, size_t count);

pid_t Wait(int *status);

pid_t Waitpid(pid_t pid, int *status, int options);

int Open(const char *pathname, int flags);

int Close(int fd);

int Listen(int sockfd, int backlog);

int Socket(int domain, int type, int protocol);

ssize_t Send(int sockfd, const void *msg, int len, int flags);

ssize_t Recv(int sockfd, void *buf, int len, int flags);
#endif
