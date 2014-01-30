#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <dirent.h>

//count how many arguments are in the command
int count_f(char* buffer)
{
    int count=0;
    int i = 0;
    while (buffer[i]!='\n')
    {
        if (buffer[i]==' ')
            count++;
        i++;
    }
    count++;
    return count;
}

//implement ls command
void ls()
{
    char pathname[80];
    int count,i;
    //dirent: file system independent directory entry
    struct dirent **files;
    int file_select();

    // get the current working directory
    if (getcwd(pathname,sizeof(pathname)) == NULL )
    { 
        printf("Error getting pathn");
        exit(0);
    }

    //printf("Current Working Directory = %sn",pathname);
    
    //scan a directory for matching entries
    count = scandir(pathname, &files, file_select, alphasort);

    //if there is no file
    if (count <= 0)
    {        
        printf("No files in this directoryn");
        exit(0);
    }

    //printf("Number of files = %dn",count);
    //if there is some files
    for (i=0;i<count;i++)
        printf("%s  ",files[i]->d_name);    
    printf("\n"); 
    exit(0);
}

//filter function, filt out the cureent directory and upper directory file
int file_select(struct direct *entry)
{
    if ((strcmp(entry->d_name, ".") == 0) ||(strcmp(entry->d_name, "..") == 0))
    return (0);
    else
    return (1);
}

//implement cd command
void cd(char **input)
{
	int ret = 0;
    if(input[1] == NULL)
    {
        ret = chdir( getenv("HOME") );
    }
    else
    {
      	char two = input[1][0];
        if(two == '~' || two == ' ')
        {
            char* home = getenv("HOME");
            ret = chdir(home);
        }
        else ret = chdir(input[1]);
    }
    exit(0);
}

//implement pwd command
void pwd()
{
    char pathname[80];
    //printf("pwd");
    if (getcwd(pathname,sizeof(pathname)) == NULL )
    { 
        printf("Error getting path\n");
        exit(0);
    }
    printf("Current Working Directory = %s\n",pathname);
    exit(0);
}

//main funcation starts
int main(int argc, char **argv)
{
        //buffer is to hold the commands that the user will type in
        char buffer[80];
        time_t mytime;
        mytime = time(NULL);
        char *s_close = "exit\n";

		char pathname[80];
    	getcwd(pathname,sizeof(pathname));
 
        while(1)
        {
                //print the prompt, including time and welcome
                printf("%s",ctime(&mytime));
                printf("Jeremy's Shell:~%s$",pathname);
                
                //get input
                fgets(buffer, 80, stdin);
                
                if (strcmp (buffer,s_close) == 0)
                {
                	exit(0);
                }

                //fork!
                int pid = fork();
                //Error checking to see if fork works
                //If pid !=0 then it's the parent
                if(pid!=0)
                {
                        wait(NULL);
                }
                else
                {
                    int no_of_args = count_f(buffer);
                    //printf("no_of_args = %d\n",no_of_args);
                    //Add one to the no_of_args so that the last one array is NULL
                    char** array_of_strings = malloc((sizeof(char*)*(no_of_args+1)));
 
                    //break the string up and create an array of pointers that point to each of the arguments.          
                    int count=0;
                    char* pch2;

                    if (no_of_args>1)
                    {
                        pch2 = strtok (buffer," ");
                        while (pch2 != NULL)
                        {
                            array_of_strings[count]=(char*)malloc((sizeof(char)*strlen(pch2)));
                            strcpy(array_of_strings[count], pch2);
                            pch2 = strtok (NULL, " ");
                            count++;
                        }
                        //printf("count = %d\n",count);
                    }
                    else
                    {
                        count=1;
                        array_of_strings[0] = buffer;
                        array_of_strings[1]=NULL;
                    }
                    //deal with the '\n' in the string
                    count--;
                    int i=0;
                    while(1)
                    {
                        if (array_of_strings[count][i] == '\n')
                        {
                            array_of_strings[count][i] = 0;
                            break;
                        }
                        i++;
                    }

                    //format for command is eg. ls -a -l
                    //the first element in the array will be the program name
          
                    char *prog = malloc(sizeof(char)*(strlen(array_of_strings[0])));
                    prog = array_of_strings[0];
                    
                      //  int k=0;
                      // for(k=0; k<=(no_of_args); k++)
                      //      printf(">>>>%s\n", array_of_strings[k]);
                    

                    char *s_cd = "cd";
                    char *s_pwd = "pwd";
                    char *s_ls = "ls";

                    if (strcmp (prog,s_cd) == 0)
                    {
                        cd(array_of_strings);
                    }
                    else if (strcmp (prog,s_pwd) == 0)
                    {
                        pwd();
                    }
                    else if (strcmp (prog,s_ls) == 0)
                    {
                        ls();
                    }
                    else
                    {
                        //pass the prepared arguments to execv and we're done!
                        int rv = 0;
                        rv = execvp(prog, array_of_strings);
                        printf("No command \"%s\" found!\n",prog);
                        exit(0);
                        //printf("%s\n",strerror(errno));
                    }
                }
        }
        return 0;
}


