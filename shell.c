#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
 
//count how many arguments are in the command
int count(char* buffer)
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
 
int main(int argc, char **argv)
{
        //buffer is to hold the commands that the user will type in
        char buffer[80];
        time_t mytime;
        mytime = time(NULL);
 
        while(1)
        {
                //print the prompt, including time and welcome
                printf("%s",ctime(&mytime));
                printf("Jeremy's Shell>");
                
                //get input
                fgets(buffer, 80, stdin);
                
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
                    int no_of_args = count(buffer);
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
          
                    char* prog = malloc(sizeof(char)*(strlen(array_of_strings[0])));
                    prog = array_of_strings[0];
            
                      //  int k=0;
                      // for(k=0; k<=(no_of_args); k++)
                      //      printf(">>>>%s\n", array_of_strings[k]);
            
                    //pass the prepared arguments to execv and we're done!
                    int rv = execvp(prog, array_of_strings);
                    printf("%s\n",strerror(errno));
                }
        }
        return 0;
}