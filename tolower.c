#include    <stdio.h>
#include    <stdlib.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <string.h>
#include    <ctype.h>

int main(int argc, char **argv){
    char inputFile[1024];
    int fd_head;
    int readSize;
    char *buf, *ptr, *qtr;
    unsigned int fileSize;
    int i=0;
    char c;

    if(argc == 2){
        strcpy(inputFile, argv[1]);
        fd_head = open(inputFile, O_RDWR);
        if(fd_head < 0){
            fprintf(stderr, "檔案:%s開啟失敗\n", inputFile);
            exit(1);
        }
        fileSize = lseek(fd_head, 0, SEEK_END);
        buf = (char *) malloc(sizeof(char) * fileSize + 1);
        ptr = buf;
	qtr = ptr;
        lseek(fd_head, 0, SEEK_SET);
        readSize = read(fd_head, buf, fileSize);
        buf[fileSize] = '\0';
        while(*ptr){
            c = *ptr;
            if(isupper(c)) c = c - 'A' + 'a';
	    *ptr = c;
            ptr++;
        }
	lseek(fd_head, 0, SEEK_SET);
        ptr[fileSize] = '\0';
        write(fd_head, qtr, fileSize);
    }
    else fprintf(stderr, "error format!\n");
    return 0;
}
