#include    <stdio.h>
#include    <stdlib.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <string.h>

int main(int argc, char **argv){
    char inputFile[1024];
    int fd_in, fd_out;
    int readSize;
    char *buf;
    unsigned int fileSize;
    char outputFile[1024];

    if(argc == 3){
        strcpy(inputFile, argv[1]);
        strcpy(outputFile, argv[2]);
        fd_in = open(inputFile, O_RDWR);
        if(fd_in < 0){
            fprintf(stderr, "檔案:%s開啟失敗\n", inputFile);
            exit(1);
        }
        fileSize = lseek(fd_in, 0, SEEK_END);
        buf = (char *) malloc(sizeof(char) * fileSize + 1);
        lseek(fd_in, 0, SEEK_SET);
        readSize = read(fd_in, buf, fileSize);
        buf[fileSize] = '\0';
        fd_out = open(outputFile, O_RDWR | O_CREAT, 0600);
        write(fd_out, buf, fileSize);
    }
    else fprintf(stderr, "error format!\n");
    return 0;
}
