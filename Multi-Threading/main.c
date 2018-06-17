#include <stdio.h>
#include "miniz.c"
#include "queue.h"
#include "miniz.h"
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
static Queue queue;
char test;
bool fin = 0;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut2 = PTHREAD_MUTEX_INITIALIZER;
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
    d = opendir("./");

    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            Job *data = (Job *) malloc(sizeof(Job));
            char buf[PATH_MAX +1];
            char *path = realpath(dir->d_name,buf);
            char *ext = get_filename_ext(&dir->d_name);
            unsigned char type = dir->d_type;
            char *fileWithoutExt = removeExt(dir->d_name);
            if(strcmp(ext,"compr") != 0 && type == 8)
            {
                data->directory = path;
                data->filewithoutext = fileWithoutExt;
                data->path = "./";
                data->content = loadfile(path);
                pthread_mutex_lock(&mut2);
                queue_insert(queue,data);
                pthread_mutex_unlock(&mut2);
                sleep(1);
            }
        }
    }
    else
    {
        printf("Directory not valid") ;
    }
    fin = 1;
}
void* compressData(void *arg)
{
    printf("%s, ",arg);
    while(!queue_empty(queue) || fin == 0)
    {
        if(!queue_empty(queue))
        {
            pthread_mutex_lock(&mut);
            Job *data = queue_head(queue);
            queue_delete(queue);
            pthread_mutex_unlock(&mut);
            FILE *fp;
            char newFile[1000];
            strcpy(newFile,data->path);
            strcat(newFile,data->filewithoutext);
            strcat(newFile,".compr");
            fp = fopen(newFile,"w+");
            printf("%s\n",newFile);
            Result *result = compress_string(data->content);
            fprintf(fp,result->data);
            free(result);
            fclose(fp);
            sleep(3);
        }
    }

}
int main(int argc, char *argv[]) {
    time_t start_t,end_t;
    double diff_t;
    time(&start_t);
    //create queue
    queue = queue_create();
    chdir(argv[0]);
    char *bread = argv[2];
    int count = atoi(bread);
    //Thread fill Queue
    pthread_t handle1;
    //Tread Queue
    int suc = pthread_create(&handle1,NULL,fillqueue,argv[1]);
    //Thread compress
    pthread_t handles[count];
    int id[count];
    char str[count][1000];
    for(int i = 0; i < count ; i++)
    {
        sprintf(str[i],"%d",i);
        id[i] = pthread_create(&handles[i],NULL,compressData,&str[i]);
    }
    for(int i = 0;i < count;i++)
    {
        pthread_join(handles[i],NULL);
    }
    pthread_join(handle1,NULL);
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    printf("Execution time: %f\n",diff_t);
    return 0;
}