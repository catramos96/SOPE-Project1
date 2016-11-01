#ifndef LSDIR_H
#define LSDIR_H

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

/**
 * @brief Returns the permissions of a file
 *
 * @param st struct stat of the file
 * @param p char where the permissions will be saved
 * @return void
 */
void getPermissions(struct stat *st, char * p);

#endif // LSDIR_H
