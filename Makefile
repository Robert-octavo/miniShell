CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic

main: s_shell_05.c findpath.c t_string.c
	$(CC) $(CFLAGS) findpath.c t_string.c s_shell_05.c  -o shell_05 && ./shell_05