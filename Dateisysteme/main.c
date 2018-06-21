#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc,char* argv[]) {
    //WRITE AND READ FILE
    const char *path = argv[1];
    const char *newpath = argv[2];
    int desc = open(path,O_RDWR | O_APPEND | O_CREAT,S_IRWXU);
    printf("%d\n",desc);
    //perror(errno);
    int count = 0;
    off_t endoffile = lseek(desc,0,SEEK_END);
    int half = endoffile/2;
    char first[half];
    char second[half+1];
    char complete[endoffile+1];
    lseek(desc,half,SEEK_SET);
    ssize_t size2 = read(desc,first, sizeof(first));
    write(STDOUT_FILENO,first, strlen(first));
    printf("\n");
    lseek(desc,0,SEEK_SET);
    if(half / 2 == 0)
    {
        ssize_t size3 = read(desc,second, sizeof(second)-1);
        write(STDOUT_FILENO,second, strlen(second));
    }
    else
    {
        ssize_t size3 = read(desc,second, sizeof(second)-1);
        write(STDOUT_FILENO,second, strlen(second));
    }
    lseek(desc,0,SEEK_SET);
    read(desc,complete, sizeof(complete)-1);
    printf("%s",complete);



    //Parse Filename
    int lengthpath = strlen(path);
    char lasttenchar[10];
    if(lengthpath < 10)
    {
        for(int i = 0; i < lengthpath; i++)
        {
            lasttenchar[i] = path[i];
        }
    }
    else
    {
        for(int i = 0; i< 10;i++)
        {
            lasttenchar[i] = path[lengthpath-10+i];
        }
    }
    int endoffset = 0;
    int lengthpath2 = strlen(newpath);
    int fin = 0;
    int counter = 0;
    while(fin != 1)
    {
        if(newpath[lengthpath2 - 1 -counter] == '.' || lengthpath - 1 -counter == 0)
        {
            fin = 1;
            counter++;
            if(lengthpath - 1 -counter == 0)
            {
                counter = 0;
            }
        }
        else
        {
            counter++;
        }
    }
    char compl[21+counter];
    int c;
    for(int i = 0; i<=lengthpath2-counter && i<11;i++)
    {
        compl[i] = newpath[i];
        c = i;
    }
    int cc = c;
    for(int i = 0; i< 10 ; i++)
    {
        compl[c+i] = lasttenchar[i];
        cc++;
    }
    int ccc = cc;
    for(int i = 0;i<counter;i++)
    {
        compl[cc+i-1] = newpath[strlen(newpath)-counter+i];
        ccc++;
    }
    compl[ccc] = '\0';


    //CHANGE Name
    //const char *temppath = "temp.temp";
    int desc2 = open(compl,O_RDWR | O_CREAT,S_IRWXU);
    write(desc2,complete, sizeof(complete)-1);
    perror(errno);
    char complete2[lseek(desc2,0,SEEK_END)+1];
    read(desc2,complete2,strlen(complete2)-1);
    write(STDOUT_FILENO,complete2, strlen(complete2)-1);



    //CLOSE STREAMS
    int status2 = close(desc2);
    int status = close(desc);


    //const char * test = "Hall";
  //  write(STDOUT_FILENO,test,strlen(test));
  //  printf("%d\n",status);

    return 0;
}