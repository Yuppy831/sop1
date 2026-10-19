#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
int scanDir(){
    DIR *MyDir=opendir(".");
    if (MyDir==NULL){
        printf("Error opening directory");
        return -1;
    }
    struct dirent *Myfile;
    int countOfPrograms=0;
    int countOfLinks=0;
    int countOfFolders=0;
    int countOfAnother=0;
    struct stat fileStat;
    while ((Myfile = readdir(MyDir)) != NULL) {
        if(lstat(Myfile->d_name, &fileStat)==-1)
        {
            printf("Error getting file information");
            closedir(MyDir);
            return -1;
        }
        else if(S_ISREG(fileStat.st_mode)!=0){
            countOfPrograms++;
        }
        else if(S_ISDIR(fileStat.st_mode)!=0){
            countOfFolders++;
        }
        else if(S_ISLNK(fileStat.st_mode)!=0){
            countOfLinks++;
        }
        else{
            countOfAnother++;
        }
    }
    closedir(MyDir);
    printf("Programs: %d\n", countOfPrograms);
    printf("Folders: %d\n", countOfFolders);
    printf("Links: %d\n", countOfLinks);
    printf("Another: %d\n", countOfAnother);
    return 0;
}
int main(int argc, char *argv[]){
    return scanDir()==0?0:-1;
}