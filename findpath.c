#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
char *findpath(char *comando);
char *str_concat(char *str1, char *str2);
char str_lenght(char *string);
char str_compare(char *str1, char *str2, int n);
char *_getenv(const char *name);
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
char str_compare(char *str1, char *str2, int n)
{
    int i = 0;
    while (i < n)
    {
        if (str1[i] == str2[i])
            i++;
        else if (str1[i] != str2[i])
            return (-1);
    }
    return (0);
}
char str_lenght(char *string)
{
    int i = 0;
    while (*string != '\0')
    {
        i++;
        string++;
    }
    return (i);
}
char *str_concat(char *str1, char *str2)
{
    char *cstring; /*String concatenada*/
    int lenght1 = 0;/*Largo string 1*/
    int lenght2 = 0;/*Largo string 2*/
    int i = 0;

    if (str1 == NULL)
        str1 = "";
    if (str2 == NULL)
        str2 = "";
    /*largos de las cadenas que entraron*/
    while (str1[lenght1] != '\0')
        lenght1++;
    while (str2[lenght2] != '\0')
        lenght2++;
    /*Reservamos memoria para concatenar ambas cadenas*/
    cstring = malloc(sizeof(char) * (lenght1 + lenght2 + 1));
    if (cstring == NULL)
        return (NULL);
    while (*str1)
    {
        cstring[i] = *str1;
        i++;
        str1++;
    }
    while (*str2)
    {
        cstring[i] = *str2;
        i++;
        str2++;
    }
    cstring[i] = '\0';
    return(cstring);
}

char *findpath(char *comando)
{
    /*Check if i get the ls*/
    //char s[2] = "/";
    printf("Este es el comando: %s\n", comando);
    char *path, *ctoprint;
    struct stat stats;
    char *c_source, *token;
    
    if (stat(comando, &stats) == 0)
        return (comando);
    path = _getenv("PATH");
    /*check if i get the path*/
    //printf("%s\n",path); 
    token = strtok(path, ":");
    printf("Este es el Path: %s\n", token);
    comando = str_concat("/", comando);
    printf("Este es el Comando con / concatenado: %s", comando);
    ctoprint = str_concat(token, comando);
    /*check if i get the ctoprint*/
    printf("\nPath con e comando concatenado: %s", ctoprint);
    printf("\n");
    return(ctoprint);

}

int main(/*int argc, char *argv[], char *envp[]*/)
{
    char *comando = "cat";
    //findpath(comando);
    printf("desde el main este es el path: [%s]",findpath(comando) );
    exit(0);
}