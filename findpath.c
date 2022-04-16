#include "shell.h"

char *_getenv(const char *name)
{
    int largo = str_lenght((char *)name);
    extern char **environ; 

    while (*environ != NULL)
    {
        if (str_compare(*environ, (char *)name, largo)== 0 && environ[0][largo] == '=')
            return (*environ + largo + 1);
        environ++;
    }
    return (NULL);
}

void print_env(void)
{
    extern char **environ;
    int i = 0;

    while (environ[i])
    {
        write(1, environ[i], str_lenght(environ[i]));
        write(1, "\n", 1);
        ++i;
    }
}

char *findpath(char *comando)
{
    /*Check if i get the ls*/
    //char s[2] = "/";
    //printf("Este es el comando: %s\n", comando);
    char *path, *ctoprint;
    struct stat stats;
    char *token;
    /*char *c_source;*/
    
    if (stat(comando, &stats) == 0)
        return (comando);
    path = _getenv("PATH");
    /*check if i get the path*/
    //printf("%s\n",path); 
    token = strtok(path, ":");
    //printf("Este es el Path: %s\n", token);
    comando = str_concat("/", comando);
    //printf("Este es el Comando con / concatenado: %s", comando);
    //ctoprint = str_concat(token, comando);
    /*check if i get the ctoprint*/
    //printf("\nPath con e comando concatenado: %s", ctoprint);
    //printf("\n");
    /*stat() return 0 on successful
    *returns -1 if its unable to get file
    *properties
    */
    while (token != NULL)
    {
        ctoprint = str_concat(token, comando);
        if (stat(ctoprint, &stats) == 0)
        {
            return(ctoprint);
        }
        free(ctoprint);
        token = strtok(NULL, ":");
    }
        //printf("\nComando a ejecutar: %s", ctoprint);
    return(NULL);

}
/*
int main(int argc, char *argv[], char *envp[])
{
    char *comando = "cat";
    //findpath(comando);
    printf("desde el main este es el path: [%s]",findpath(comando) );
    exit(0);
}*/