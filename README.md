<article class="">
<h1 class="d-flex flex-column gap-2">Everything you need to know to start coding your own shell</h1>
<div>&nbsp;</div>
<div class="gap formatted-content">
<h2>PID &amp; PPID</h2>
<p>A process is an instance of an executing program, that has a unique process ID. This process ID is used by many functions and system calls to interact with and manipulate processes. In order to retrieve the current process&rsquo; ID, you can use the system call <code>getpid</code> (man 2 <code>getpid</code>):</p>
<pre><code>julien@ubuntu:~/c/shell$ cat pid.c
#include &lt;stdio.h&gt;
#include &lt;unistd.h&gt;

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;

    my_pid = getpid();
    printf("%u\n", my_pid);
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Werror -pedantic pid.c -o mypid &amp;&amp; ./mypid
3237
julien@ubuntu:~/c/shell$ ./mypid 
3238
julien@ubuntu:~/c/shell$ ./mypid 
3239
julien@ubuntu:~/c/shell$ 
</code></pre>
<p>Note in the example above, that every time you run the program, a new process is created, and its ID is different.</p>
<p>Each process has a parent: the process that created it. It is possible to get the PID of a parent process by using the <code>getppid</code> system call (man 2 <code>getppid</code>), from within the child process.</p>
<h3>Exercises</h3>
<h4>0. getppid</h4>
<p>Write a program that prints the PID of the parent process. Run your program several times within the same shell. It should be the same. Does <code>echo $$</code> print the same value? Why?</p>
<h4>1. /proc/sys/kernel/pid_max</h4>
<p>Write a shell script that prints the maximum value a process ID can be.</p>
<h2>Arguments</h2>
<p>The command line arguments are passed through the <code>main</code> function: <code>int main(int ac, char **av);</code></p>
<ul>
<li><code>av</code> is a <code>NULL</code> terminated array of strings</li>
<li><code>ac</code> is the number of items in <code>av</code></li>
</ul>
<p><code>av[0]</code> usually contains the name used to invoke the current program. <code>av[1]</code> is the first argument of the program, <code>av[2]</code> the second, and so on.</p>
<h3>Exercises</h3>
<h4>0. av</h4>
<p>Write a program that prints all the arguments, without using <code>ac</code>.</p>
<h4>1. Read line</h4>
<p>Write a program that prints <code>"$ "</code>, wait for the user to enter a command, prints it on the next line.</p>
<p>man 3 <code>getline</code></p>
<p><strong>important</strong> make sure you read the man, and the RETURN VALUE section, in order to know when to stop reading Keyword: &ldquo;end-of-file&rdquo;, or <code>EOF</code> (or <code>Ctrl+D</code>).</p>
<p><em>#advanced</em>: Write your own version of <code>getline</code>.</p>
<pre><code>julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic prompt.c -o prompt
julien@ubuntu:~/c/shell$ ./prompt 
$ cat prompt.c
cat prompt.c
julien@ubuntu:~/c/shell$ 
</code></pre>
<h4>2. command line to av</h4>
<p>Write a function that splits a string and returns an array of each word of the string.</p>
<p>man <code>strtok</code></p>
<p><em>#advanced</em>: Write the function without <code>strtok</code></p>
<h2>Executing a program</h2>
<p>The system call <code>execve</code> allows a process to execute another program (man 2 <code>execve</code>). Note that this system call does load the new program into the current process&rsquo; memory in place of the &ldquo;previous&rdquo; program: on success <code>execve</code> does not return to continue the rest of the &ldquo;previous&rdquo; program.</p>
<pre><code>julien@ubuntu:~/c/shell$ cat exec.c
#include &lt;stdio.h&gt;
#include &lt;unistd.h&gt;

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    printf("Before execve\n");
    if (execve(argv[0], argv, NULL) == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic exec.c -o exec
julien@ubuntu:~/c/shell$ ./exec 
Before execve
total 120
drwxr-xr-x   2 root root 61440 Dec  4 00:08 bin
drwxr-xr-x   2 root root  4096 Jul 19 13:47 games
drwxr-xr-x  58 root root  4096 Oct 27 13:10 include
drwxr-xr-x 138 root root  4096 Dec  4 00:08 lib
drwxr-xr-x   3 root root  4096 Nov 10 09:54 lib32
drwxr-xr-x   3 root root  4096 Nov 10 09:54 libx32
drwxr-xr-x  10 root root  4096 Jul 19 13:42 local
drwxr-xr-x   3 root root  4096 Jul 19 13:48 locale
drwxr-xr-x   2 root root 12288 Dec  2 11:03 sbin
drwxr-xr-x 295 root root 12288 Jul 27 08:58 share
drwxr-xr-x   6 root root  4096 Dec  1 11:39 src
julien@ubuntu:~/c/shell$ 
</code></pre>
<h2>Creating processes</h2>
<p>The system call <code>fork</code> (man 2 <code>fork</code>) creates a new child process, almost identical to the parent (the process that calls <code>fork</code>). Once <code>fork</code> successfully returns, two processes continue to run the same program, but with different stacks, datas and heaps.</p>
<pre><code>julien@ubuntu:~/c/shell$ cat fork.c
#include &lt;stdio.h&gt;
#include &lt;unistd.h&gt;

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t pid;

    printf("Before fork\n");
    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }
    printf("After fork\n");
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    return (0);
}
julien@ubuntu:~/c/shell$ ./fork 
Before fork
After fork
My pid is 4819
julien@ubuntu:~/c/shell$ After fork
My pid is 4820
</code></pre>
<p><em>Note: there is no typo in the above example</em></p>
<p>Using the return value of <code>fork</code>, it is possible to know if the current process is the father or the child: <code>fork</code> will return <code>0</code> to the child, and the PID of the child to the father.</p>
<pre><code>julien@ubuntu:~/c/shell$ cat fork.c
#include &lt;stdio.h&gt;
#include &lt;unistd.h&gt;

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return (1);
    }
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    if (child_pid == 0)
    {
        printf("(%u) Nooooooooo!\n", my_pid);
    }
    else
    {
        printf("(%u) %u, I am your father\n", my_pid, child_pid);
    }
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic fork.c -o fork
julien@ubuntu:~/c/shell$ ./fork 
My pid is 4869
(4869) 4870, I am your father
julien@ubuntu:~/c/shell$ My pid is 4870
(4870) Nooooooooo!
</code></pre>
<h2>Wait</h2>
<p>The <code>wait</code> system call (man 2 <code>wait</code>) suspends execution of the calling process until one of its children terminates.</p>
<pre><code>julien@ubuntu:~/c/shell$ cat wait.c
#include &lt;stdio.h&gt;
#include &lt;unistd.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/wait.h&gt;

/**
 * main - fork &amp; wait example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return (1);
    }
    if (child_pid == 0)
    {
        printf("Wait for me, wait for me\n");
        sleep(3);
    }
    else
    {
        wait(&amp;status);
        printf("Oh, it's all better now\n");
    }
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic wait.c -o wait
julien@ubuntu:~/c/shell$ ./wait 
Wait for me, wait for me
Oh, it's all better now
julien@ubuntu:~/c/shell$ 
</code></pre>
<h2>Exercise: fork + wait + execve</h2>
<p>Write a program that executes the command <code>ls -l /tmp</code> in 5 different child processes. Each child should be created by the same process (the father). Wait for a child to exit before creating a new child.</p>
<h2>Exercise: super simple shell</h2>
<p>Using everything we saw, write a first version of a super simple shell that can run commands with their full path, without any argument.</p>
<pre><code>julien@ubuntu:~/c/shell$ l
total 140
drwxrwxr-x  2 julien julien 4096 Dec  4 20:55 .
drwxrwxr-x 17 julien julien 4096 Dec  4 13:04 ..
-rw-rw-r--  1 julien julien  249 Dec  4 13:15 env-environ.c
-rw-rw-r--  1 julien julien  231 Dec  4 13:09 env-main.c
-rwxrwxr-x  1 julien julien 8768 Dec  4 19:52 exec
-rw-rw-r--  1 julien julien  302 Dec  4 19:38 exec.c
-rwxrwxr-x  1 julien julien 8760 Dec  4 20:11 fork
-rw-rw-r--  1 julien julien  438 Dec  4 19:57 fork.c
-rwxrwxr-x  1 julien julien 8656 Dec  4 13:45 mypid
-rw-rw-r--  1 julien julien  179 Dec  4 19:49 pid.c
-rwxrwxr-x  1 julien julien 8656 Dec  4 13:48 ppid
-rw-rw-r--  1 julien julien  180 Dec  4 13:48 ppid.c
-rwxrwxr-x  1 julien julien 8680 Dec  4 13:44 printenv
-rwxrwxr-x  1 julien julien 8760 Dec  4 14:38 prompt
-rwxrwxr-x  1 julien julien 8760 Dec  4 14:38 promptc
-rw-rw-r--  1 julien julien  191 Dec  4 14:17 prompt.c
-rw-rw-r--  1 julien julien  753 Dec  4 20:49 shell.c
-rwxrwxr-x  1 julien julien 8864 Dec  4 20:38 wait
-rw-rw-r--  1 julien julien  441 Dec  4 20:15 wait.c
julien@ubuntu:~/c/shell$ gcc -Wall -Werror -pedantic shell.c -o shell
julien@ubuntu:~/c/shell$ ./shell 
#cisfun$ /bin/ls
env-environ.c  exec    fork    mypid  ppid    printenv  promptc   shell    wait
env-main.c     exec.c  fork.c  pid.c  ppid.c  prompt    prompt.c  shell.c  wait.c
#cisfun$ ./ppid
5451
#cisfun$ ./ppid
5451
#cisfun$ ^C
julien@ubuntu:~/c/shell$ 
</code></pre>
<h2>File information</h2>
<p>The <code>stat</code> (man 2 stat) system call gets the status of a file. On success, zero is returned. On error, -1 is returned.</p>
<pre><code>julien@ubuntu:~/c/shell$ cat stat.c
#include &lt;stdio.h&gt;
#include &lt;sys/types.h&gt;
#include &lt;sys/stat.h&gt;
#include &lt;unistd.h&gt;

/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    unsigned int i;
    struct stat st;

    if (ac &lt; 2)
    {
        printf("Usage: %s path_to_file ...\n", av[0]);
        return (1);
    }
    i = 1;
    while (av[i])
    {
        printf("%s:", av[i]);
        if (stat(av[i], &amp;st) == 0)
        {
            printf(" FOUND\n");
        }
        else
        {
            printf(" NOT FOUND\n");
        }
        i++;
    }
    return (0);
}
julien@ubuntu:~/c/shell$ ./stat ls /bin/ls /usr/bin/ls
ls: NOT FOUND
/bin/ls: FOUND
/usr/bin/ls: NOT FOUND
julien@ubuntu:~/c/shell$ 
</code></pre>
<h3>Exercise: find a file in the PATH</h3>
<p>Write a program that looks for files in the current <code>PATH</code>.</p>
<ul>
<li>Usage: <code>_which filename ...</code></li>
</ul>
<h2>Environment</h2>
<p>We have seen earlier that the shell uses an environment list, where environment variables are &ldquo;stored&rdquo;. The list is an array of strings, with the following format: <code>var=value</code>, where <code>var</code> is the name of the variable and <code>value</code> its value. As a reminder, you can list the environment with the command <code>printenv</code>:</p>
<pre><code>julien@ubuntu:~/c/shell$ printenv
XDG_VTNR=7
XDG_SESSION_ID=c2
CLUTTER_IM_MODULE=xim
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/julien
SESSION=ubuntu
GPG_AGENT_INFO=/home/julien/.gnupg/S.gpg-agent:0:1
TERM=xterm-256color
SHELL=/bin/bash
XDG_MENU_PREFIX=gnome-
VTE_VERSION=4205
QT_LINUX_ACCESSIBILITY_ALWAYS_ON=1
WINDOWID=23068682
UPSTART_SESSION=unix:abstract=/com/ubuntu/upstart-session/1000/1558
GNOME_KEYRING_CONTROL=
GTK_MODULES=gail:atk-bridge:unity-gtk-module
USER=julien
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
QT_ACCESSIBILITY=1
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
SESSION_MANAGER=local/ubuntu:@/tmp/.ICE-unix/1792,unix/ubuntu:/tmp/.ICE-unix/1792
DEFAULTS_PATH=/usr/share/gconf/ubuntu.default.path
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/usr/share/upstart/xdg:/etc/xdg
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DESKTOP_SESSION=ubuntu
QT_IM_MODULE=ibus
QT_QPA_PLATFORMTHEME=appmenu-qt5
XDG_SESSION_TYPE=x11
JOB=dbus
PWD=/home/julien/c/shell_course
XMODIFIERS=@im=ibus
GNOME_KEYRING_PID=
LANG=en_US.UTF-8
GDM_LANG=en_US
MANDATORY_PATH=/usr/share/gconf/ubuntu.mandatory.path
IM_CONFIG_PHASE=1
COMPIZ_CONFIG_PROFILE=ubuntu
GDMSESSION=ubuntu
SESSIONTYPE=gnome-session
GTK2_MODULES=overlay-scrollbar
XDG_SEAT=seat0
HOME=/home/julien
SHLVL=1
LANGUAGE=en_US
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
XDG_SESSION_DESKTOP=ubuntu
LOGNAME=julien
QT4_IM_MODULE=xim
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-jH9kfagEpM
LESSOPEN=| /usr/bin/lesspipe %s
INSTANCE=
XDG_RUNTIME_DIR=/run/user/1000
DISPLAY=:0
XDG_CURRENT_DESKTOP=Unity
GTK_IM_MODULE=ibus
LESSCLOSE=/usr/bin/lesspipe %s %s
XAUTHORITY=/home/julien/.Xauthority
OLDPWD=/home/julien/c
_=/usr/bin/printenv
julien@ubuntu:~/c/shell$ 
</code></pre>
<p>Actually, every process comes with an environment. When a new process is created, it inherits a copy of its parent&rsquo;s environment. To access the entire environment within a process, you have several options:</p>
<ul>
<li>via the <code>main</code> function</li>
<li>via the global variable <code>environ</code> (man environ)</li>
</ul>
<h3>main</h3>
<p>So far we have seen that <code>main</code> could have different prototypes:</p>
<ul>
<li><code>int main(void);</code></li>
<li><code>int main(int ac, char **av);</code></li>
</ul>
<p>There is actually another prototype:</p>
<ul>
<li><code>int main(int ac, char **av, char **env);</code></li>
</ul>
<p>where <code>env</code> is a <code>NULL</code> terminated array of strings.</p>
<pre><code>julien@ubuntu:~/c/shell$ cat env-main.c
#include &lt;stdio.h&gt;

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    unsigned int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Werror -pedantic env-main.c -o printenv &amp;&amp; ./printenv 
XDG_VTNR=7
XDG_SESSION_ID=c2
CLUTTER_IM_MODULE=xim
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/julien
SESSION=ubuntu
GPG_AGENT_INFO=/home/julien/.gnupg/S.gpg-agent:0:1
TERM=xterm-256color
SHELL=/bin/bash
XDG_MENU_PREFIX=gnome-
VTE_VERSION=4205
QT_LINUX_ACCESSIBILITY_ALWAYS_ON=1
WINDOWID=23068682
UPSTART_SESSION=unix:abstract=/com/ubuntu/upstart-session/1000/1558
GNOME_KEYRING_CONTROL=
GTK_MODULES=gail:atk-bridge:unity-gtk-module
USER=julien
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
QT_ACCESSIBILITY=1
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
SESSION_MANAGER=local/ubuntu:@/tmp/.ICE-unix/1792,unix/ubuntu:/tmp/.ICE-unix/1792
DEFAULTS_PATH=/usr/share/gconf/ubuntu.default.path
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/usr/share/upstart/xdg:/etc/xdg
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DESKTOP_SESSION=ubuntu
QT_IM_MODULE=ibus
QT_QPA_PLATFORMTHEME=appmenu-qt5
XDG_SESSION_TYPE=x11
JOB=dbus
PWD=/home/julien/c/shell
XMODIFIERS=@im=ibus
GNOME_KEYRING_PID=
LANG=en_US.UTF-8
GDM_LANG=en_US
MANDATORY_PATH=/usr/share/gconf/ubuntu.mandatory.path
IM_CONFIG_PHASE=1
COMPIZ_CONFIG_PROFILE=ubuntu
GDMSESSION=ubuntu
SESSIONTYPE=gnome-session
GTK2_MODULES=overlay-scrollbar
XDG_SEAT=seat0
HOME=/home/julien
SHLVL=1
LANGUAGE=en_US
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
XDG_SESSION_DESKTOP=ubuntu
LOGNAME=julien
QT4_IM_MODULE=xim
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-jH9kfagEpM
LESSOPEN=| /usr/bin/lesspipe %s
INSTANCE=
XDG_RUNTIME_DIR=/run/user/1000
DISPLAY=:0
XDG_CURRENT_DESKTOP=Unity
GTK_IM_MODULE=ibus
LESSCLOSE=/usr/bin/lesspipe %s %s
XAUTHORITY=/home/julien/.Xauthority
OLDPWD=/home/julien/c
_=./printenv
julien@ubuntu:~/c/shell$ 
</code></pre>
<h3>Exercises</h3>
<h4>0. printenv with environ</h4>
<p>Write a program that prints the environment using the global variable <code>environ</code>.</p>
<h4>1. env vs environ</h4>
<p>Write a program that prints the address of <code>env</code> (the third parameter of the <code>main</code> function) and <code>environ</code> (the global variable). Are they they same? Does this make sense?</p>
<h4>2. getenv()</h4>
<p>Write a function that gets an environment variable. (without using <code>getenv</code>)</p>
<ul>
<li>Prototype: <code>char *_getenv(const char *name);</code></li>
</ul>
<p>man 3 <code>getenv</code></p>
<h4>3. PATH</h4>
<p>Write a function that prints each directory contained in the the environment variable <code>PATH</code>, one directory per line.</p>
<h4>4. PATH</h4>
<p>Write a function that builds a linked list of the <code>PATH</code> directories.</p>
<h4>5. setenv</h4>
<p>Write a function that changes or adds an environment variable (without using <code>setenv</code>).</p>
<ul>
<li>Prototype: <code>int _setenv(const char *name, const char *value, int overwrite);</code></li>
</ul>
<p>man 3 <code>setenv</code></p>
<h4>6. unsetenv</h4>
<p>Write a function that deletes the variable name from the environment (without using <code>unsetenv</code>).</p>
<ul>
<li>Prototype: <code>int _unsetenv(const char *name);</code></li>
</ul>
<p>man 3 <code>unsetenv</code></p>
</div>
</article>
