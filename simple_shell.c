#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/**
 * @brief Simpel Shell
 * 
 */
int main ()
{
    pid_t hijo;
    char *line;
    size_t len = 0;
    char separador[] = {" "};/*para identificar cuantas palabras hay*/
    int i, ex, status, contar = 1;
    char **words = NULL;
    char *tok;

    do{
        printf("#Cisfun$ ");
        if (getline(&line, &len, stdin) == -1)
            break;
        for (i = 0; line[i] != '\0'; i++)
        {
            if(line[i] == separador[0] && line[i + 1] != '\0')
                contar++;
        }

        /* printf("la cantidad palabras es: %d \n", contar); check if its adding right*/
        words = malloc(sizeof(char *) * (contar));
        /*primero linea donde se guarda lo que digito - 
        *segundo parametro delimitador
        */
        tok = strtok(line, " ");
        /*Guardamos la primer palabra esta es el comando*/
        /*el resto son argumentos*/ 
        words[0] = tok;
        printf("%s",words[0]);
        words[1] = NULL;
        /*check if we really save the frist word
        printf("este es el comando[0]: %s\n", words[0]);*/
        /*we save the rest words*/
        for (i = 1; tok != NULL; i++)
        {
            //printf("%s", tok);
            tok = strtok(NULL, " ");
            words[i] = tok;
            if (words[i] == NULL)
                break;
        }
   
        hijo = fork();
        if (hijo == 0)
        {
            /*On success, execve() does not return, on error -1 is returned,
              and errno is set to indicate the error.*/
            
            ex = execve(words[0], words, NULL);
            if (ex == -1)
            {
                printf("Error al ejecutar el comando. \n");
                exit (EXIT_FAILURE);
            }
                
        }
        if (hijo > 0)
            wait(&status);
    }while(1);
    free(line);
    return (0);
}