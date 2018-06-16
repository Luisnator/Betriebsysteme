#include <stdio.h>
#include "miniz.c"
#include "queue.h"
#include "miniz.h"
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
static Queue queue;
char test;
bool fin = 0;
pthread_mutex_t mut;
typedef struct job
{
    char *path;
    char *content;
    char *directory;
    char *filewithoutext;
}Job;


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
    const char *test = (char *)arg;
    char buf[1000];
    chdir(test);
    d = opendir(getcwd(buf, sizeof(buf)));

    if(d)
    {
        printf("Got here");
        while((dir = readdir(d)) != NULL)
        {
            Job *data = (Job *) malloc(sizeof(Job));
            char buf[PATH_MAX +1];
            char *path = realpath(dir->d_name,buf);
            char *ext = get_filename_ext(&dir->d_name);
            unsigned char type = dir->d_type;
            char *fileWithoutExt = removeExt(dir->d_name);
            if(ext != "compr" && type == 8)
            {
                data->directory = path;
                printf("%s\n",path);
                data->filewithoutext = fileWithoutExt;
                data->path = "./";
                data->content = loadfile(path);
                queue_insert(queue,data);
                printf("Juhu\n");
            }
        }
    }
    else
    {
        printf("Directory not valid") ;
    }
}
void* compressData(void *arg)
{
    while(!queue_empty(queue) && fin == 0)
    {
        if(!queue_empty(queue))
        {
            Job *data = queue_head(queue);
            queue_delete(queue);
            FILE *fp;
            char newFile[1000];
            strcpy(newFile,data->path);
            strcat(newFile,data->filewithoutext);
            strcat(newFile,".compr");
            fp = fopen(newFile,"w+");
            printf("%s\n",data->path);
            printf("%s\n",newFile);
            Result *result = compress_string(data->content);
            fprintf(fp,result->data);
            free(result);
            fclose(fp);
        }
    }
}
int main(int argc, char **argv) {
    queue = queue_create();
    chdir(argv[0]);
    char buf[100000];
    printf("%s\n",getcwd(buf, sizeof(buf)));
    pthread_t handle1;
    pthread_t handle2;
    int suc = pthread_create(&handle1,NULL,fillqueue,argv[1]);
    pthread_join(handle1,NULL);
    int suc2 = pthread_create(&handle2,NULL,compressData,argv[1]);
    pthread_join(handle2,NULL);
    return 0;
}