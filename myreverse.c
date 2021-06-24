#include    <stdio.h>
#include    <stdlib.h>
#include    <fcntl.h>
#include    <unistd.h>
#include    <string.h>

int main(int argc, char **argv){
    char inputFile[1024];
    int fd_head;
    int readSize;
    char *buf, *ptr;
    unsigned int fileSize;
    int i=0;

    if(argc == 2){
        strcpy(inputFile, argv[1]);
        fd_head = open(inputFile, O_RDWR);
        if(fd_head < 0){
            fprintf(stderr, "檔案:%s開啟失敗\n", inputFile);
            exit(1);
        }
        fileSize = lseek(fd_head, 0, SEEK_END);
        buf = (char *) malloc(sizeof(char) * fileSize + 1);
        ptr = (char *) malloc(sizeof(char) * fileSize + 1);
        lseek(fd_head, 0, SEEK_SET);
        readSize = read(fd_head, buf, fileSize);
        buf[fileSize] = '\0';
        while(i < fileSize){
            ptr[i] = buf[fileSize - i - 1];
            i++;
        }
	if(ptr[strlen(ptr) - 1] == '\n') ptr[strlen(ptr) - 1] = '\0'; 
        ptr[fileSize] = '\0';
	lseek(fd_head, 0, SEEK_SET);
        write(fd_head, ptr, fileSize);
    }
    else fprintf(stderr, "error format!\n");
    return 0;
}
