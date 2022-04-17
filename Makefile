CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

main: s_shell_07.c findpath.c envfunc.c t_string.c
	$(CC) $(CFLAGS) findpath.c t_string.c envfunc.c s_shell_07.c  -o shell_07 && ./shell_07