#include<stdio.h>
#include<stdlib.h>
/**
 * @brief prints "$" then wais for the user to enter a command
 * 
 * @return 0
 */
int main()
{
    char *line;/*Command that the user enters*/
    size_t len = 0;/*Buffer SIze*/
    int r;/*USe to return and check if error*/

    printf("$ ");
    r = getline(&line, &len, stdin);
    /*
    *$line: is the addres of the first character position
    * where the input string will be stored
    * &len: is the address of the variable that hold the
    * size of the input buffer
    * stdin: is the input file handle. You can use getline
    * to read a line of text from a file, but when stdin
    * is specified, standar input is read
    * https://c-for-dummies.com/blog/?p=1112
    */
    if (r == -1)/*return -1 if error*/ 
        return (-1);
    printf("%s", line);
    return (r);
}