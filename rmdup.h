#ifndef RMDUP_H
#define RMDUP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <sys/wait.h>

#define BUFFER_SIZE 255

typedef struct InfoLine{
char inode[7];
char permissions[11];
char name[256];
char data[17];
char path[PATH_MAX+1];
}InfoLine;


/**
 * @brief Function that sort all files in all directorys and sub-directorys of a path by calling lsdir
 *
 * @param dir_path path to sort files
 * @return 0 on success
 */
int sortFiles(char* dir_path);


/**
 * @brief Compare the content of the files
 *
 * @param pathfile1 path of the first file
 * @param pathfile2 path of the second file
 * @return 0 if they have the same content, and other otherwise
 */
int sameContent(char* pathfile1,char* pathfile2);


/**
 * @brief Analyses the files.txt and create hardinks of duplicated files to the most recent modefied
 * @return 0 on success
 */
int analyseFiles ();

#endif // RMDUP_H
