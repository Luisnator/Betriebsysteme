#include <stdio.h>
#include "miniz.c"
#include "queue.h"
#include "miniz.h"
#include <pthread.h>
#include <dirent.h>
#include <string.h>

static Queue queue;
char test;
pthread_mutex_t mut;
typedef struct Job
{
    char *content;
    char *directory;
    char *filewithoutext;
};


const char *get_filename_ext(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot +1;
}
char *removeExt(char* file)
{
    char *retstr;
    char *lastdot;
    if (file == NULL)
    {
        return NULL;
    }
    if((retstr = malloc(strlen(file)+1)) == NULL)
    {
        return NULL;
    }
    strcpy(retstr,file);
    lastdot = strrchr(retstr,'.');
    if(lastdot != NULL)
    {
        *lastdot = '\0';
    }
    return retstr;
}
char *loadfile(char *path)
{
    char* buffer = 0;
    long length;
    FILE *f = fopen(path, "rb");
    if(f)
    {
        fseek(f,0,SEEK_END);
        length = ftell(f);
        fseek(f,0,SEEK_SET);
        buffer = (char*)malloc((length+1)* sizeof(char));
        if(buffer)
        {
            fread(buffer, sizeof(char),length,f);
        }
        fclose(f);
    }
    buffer[length] = '\0';
    return buffer;
}
void* fillqueue(void *arg)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            struct Job job;
            char buf[PATH_MAX +1];
            char *path = realpath(dir->d_name,buf);
            char *ext = get_filename_ext(&dir->d_name);
            unsigned char type = dir->d_type;
            char *fileWithoutExt = removeExt(dir->d_name);
            if(ext != "compr" && type == 8)
            {
                job.directory = path;
                job.filewithoutext = fileWithoutExt;
                job.content = loadfile(path);
                printf("%s\n",job.content);
            }
        }
    }
}
int main() {
    queue = queue_create();
    pthread_t handle1;
    char arg1 = 'a';
    int suc = pthread_create(&handle1,NULL,fillqueue,&arg1);
    pthread_join(handle1,NULL);

    return 0;
}