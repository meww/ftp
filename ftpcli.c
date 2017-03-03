#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fctl.h>

#define MAXLEN 256
#define ARGS 80
#define DATASIZE (100*1024*1024)

struct myftph {
    uint8_t type;
    uint8_t code;
    uint16_t length;
};

struct command_table {
    char *cmd;
    void (*func)(int, char *[]);
} cmd_tbl[] = {
    {"quit", quit},
    {"pwd", pwd},
    {"cd", cd},
    {"dir", dir},
    {"lpwd", lpwd},
    {"lcd", lcd},
    {"ldir", ldir},
    {"get", get},
    {"put", put},
    {"help", help},
    {NULL, NULL}
};

void quit(int, int, char*[]);
void pwd();
void cd();
void dir();
void lpwd();
void lcd();
void ldir();
void get();
void put();
void help();

int main(int argc, char *argv[])
{
    int s, ac;
    struct sockaddr_in servskt;
    struct command_table *p;
    in_port_t myport;
    socklen_t servlen;
    char buf[MAXLEN];
    char *av[ARGS];
    uint8_t *data;

    if (argc != 3) {
        fprintf(stderr, "Usage: ./udpcli localhost port\n");
        exit(1);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    myport = strtol(argv[2], NULL, 10);
    memset(&servskt, 0, sizeof servskt);
    servskt.sin_family = AF_INET;
    servskt.sin_port = htons(myport);
    inet_aton(argv[1], &servskt.sin_addr);

    if (connect(s, (struct sockaddr *)&servskt, sizeof servskt) < 0) {
        perror("connect");
        exit(1);
    } 

    
    for (;;) {
        printf("myFTP% ");
        if (fgets(buf, sizeof buf, stdin) == NULL) {
            continue;
        }
        servlen = sizeof servskt;
        if ((n = send(s, &echo, sizeof echo, 0)) < 0) {
            perror("send");
            exit(1);
        }
        if ((n = recv(s, &echo, sizeof echo, 0)) < 0) {
            perror("recv");
            exit(1);
        }
        printf("seq: %d msg: %s\n", echo.seq, echo.msg);
        if ((strcmp(echo.msg, "FIN")) == 0) {
            printf("Finished\n");
            break;
        }
        if (echo.seq == 10) {
            printf("Finished\n");
            break;
        }
    }
    close(s);

    return 0;
}


void quit(int, char*[])
{
}
void pwd(){
}
void cd(){
}
void dir(){
}
void lpwd(){
}
void lcd(){
}
void ldir(){
}
void get(int s, int ac, char *av[]){
    char filename[80];
    struct myftph *msg_header;
    struct myftph recv_header;

    if (ac < 2 || ac > 3) {
        fpirntf(stderr, "Usage: get filename [filename]\n");
        return;
    } else if (ac == 2) {
        strcpy(filename, av[1]);
    } else {
        strcpy(filename, av[2]);
    }
    msg_header->type = 0x05;
    msg_header->code = 0x00;
    msg_header->length = strlen(av[1]);

    if (send(s, msg_header, sizeof msg_header, 0) < 0) {
        perror("send");
        exit(1);
    }
    if (recv(s, &recv_header, sizeof(struct myftph), 0) < 0) {
        perror("recv");
        exit(1);
    }
    if
}
void put(){
}
void help(){
}
