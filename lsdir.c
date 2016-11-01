#include "lsdir.h"

void getPermissions(struct stat *st, char * p){
int perm = st->st_mode;
//type
(S_ISDIR(perm)) ? (p[0]='d') : (p[0]='-');
//USER
(perm & S_IRUSR) ? (p[1]='r') : (p[1]='-');
(perm & S_IWUSR) ? (p[2]='w') : (p[2]='-');
(perm & S_IXUSR) ? (p[3]='x') : (p[3]='-');
//GROUP
(perm & S_IRGRP) ? (p[4]='r') : (p[4]='-');
(perm & S_IWGRP) ? (p[5]='w') : (p[5]='-');
(perm & S_IXGRP) ? (p[6]='x') : (p[6]='-');
//OTHER
(perm & S_IROTH) ? (p[7]='r') : (p[7]='-');
(perm & S_IWOTH) ? (p[8]='w') : (p[8]='-');
(perm & S_IXOTH) ? (p[9]='x') : (p[9]='-');
}

int main (int argc, char* argv[]){
char filepath[PATH_MAX+1];
DIR *diretorio;
struct dirent *d;
struct stat fs;
int file,tmp_files;
	if (argc != 2){
		printf("WRONG NUMBER OF ARGUMENTS\n");
		exit(1);
	}

	if ((diretorio = opendir (argv[1])) == NULL)
		exit(1);
	 if((file= open("files.txt",O_WRONLY | O_CREAT | O_SYNC | O_TRUNC | O_APPEND,0644)) == -1)	//sorted files
		exit(1);
	if((tmp_files= open("tmp_files.txt",O_WRONLY | O_CREAT | O_SYNC |O_APPEND,0644)) == -1)		//not sorted
		exit(1);

	//reach for every file in the path folder
	
	while ((d = readdir (diretorio)) != NULL)
	{
		if(sprintf(filepath,"%s/%s",argv[1],d->d_name) == -1)
			exit(1);
		if(lstat(filepath,&fs) == -1)
			exit(1);

		//if the file is regular
		if(S_ISREG(fs.st_mode) && !S_ISDIR(fs.st_mode)){
			char *name = d->d_name;
			char time[18];
			char p[11];
			char tmp[strlen(name)+37 + strlen(filepath)];

			getPermissions(&fs,p);
			if(strftime(time,18,"%y_%m_%d_%T",localtime(&fs.st_mtime)) == -1)
				exit(1);
			if(sprintf(tmp,"%s#%s#%s#%d#%s\n",name,time, p,(int)fs.st_ino, filepath) == -1) //if they are separated by "#" we can detect files names with spaces
				exit(1);
			lseek(file,0,SEEK_END);
			if(write(tmp_files,tmp,strlen(tmp)) == -1)
				exit(1);
   	 	}
	}

	dup2(file,STDOUT_FILENO);
	closedir (diretorio);
 	close(file);
	close(tmp_files);
	execlp("sort","sort","-r","tmp_files.txt",NULL);
	return 0;
}
