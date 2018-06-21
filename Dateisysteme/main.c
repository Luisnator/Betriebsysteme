#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    //WRITE AND READ FILE
    const char *path = "allesasasss.txt";
    const char *newpath = "NEWFILEEEEEEEE.COM";
    int desc = open(path,O_RDWR | O_APPEND | O_CREAT,S_IRWXU);
    printf("%d\n",desc);
    perror(errno);
    char buf[3] = "LEL";
    char buf2[1];
    ssize_t size = write(desc,buf, sizeof(buf) / sizeof(char));
    int count = 0;
    off_t endoffile = lseek(desc,0,SEEK_END);
    lseek(desc,0,SEEK_SET);
    while(lseek(desc,0,SEEK_CUR) != endoffile)
    {
        count ++;
        ssize_t size2 = read(desc,buf2,1);
      //  printf("%c",buf2[0]);
     //   printf("%d\n",count);
    }




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
    printf("%s\n",lasttenchar);
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
    printf("%d\n",counter);
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
        compl[cc+i] = newpath[strlen(newpath)-counter+i];
        ccc++;
    }
    compl[ccc] = '\0';


    for(int i = 0;i<25;i++)
    {
        printf("%c",compl[i]);
    }
    printf("\n");
    printf("%s\n",compl);
    printf("%d\n",strlen(compl));


    //CHANGE Name
    //const char *temppath = "temp.temp";
    int desc2 = open(compl,O_RDWR | O_APPEND | O_CREAT,S_IRWXU);
    perror(errno);



    //CLOSE STREAMS
    int status2 = close(desc2);
    int status = close(desc);


    //const char * test = "Hall";
  //  write(STDOUT_FILENO,test,strlen(test));
  //  printf("%d\n",status);

    return 0;
}