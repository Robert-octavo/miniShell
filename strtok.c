#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief Write a function that splits a string and 
 * returns an array of each word of the string
 * @return int 
 */
int main()
{
    char *line;
    size_t len = 0;
    char separador[] = {" "};/*para identificar cuantas palabras hay*/
    int i, contar = 1;
    char **words = NULL;
    char *tok; /*use to save what strkot returns*/

    getline(&line, &len, stdin);
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
    /*check if we really save the frist word*/
    printf("este es el comando[0]: %s\n", words[0]);
    /*we save the rest words*/
    for (i = 1; tok != NULL; i++)
    {
        printf(" %s", tok);
        tok = strtok(NULL, " ");
        words[i] = tok;
        if (words[i] == NULL)
            break;
        printf("\n");
    }
    /*Check if it saves correctly*/
    for (i = 0; words[i] != NULL; i++)
        printf("En el array estan guardadas las palabras: [%s][%d]\n", words[i],i);
    return (0);

}