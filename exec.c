#include <stdio.h>
#include <unistd.h>

int main()
{
    char *const argv[] = {"ps", "-ef", NULL};
    char *const envp[] = {"PATH=/bin:/usr/bin", "MYENV=hello world", NULL};
    execl("/bin/ps", "ps", "-ef", NULL);
    
    execlp("ps", "ps", "-ef", NULL);
    
    execle("ps", "ps", "-ef", NULL, envp);
    
    execv("/bin/ps", argv);
    
    execvp("ps", argv);
    
    execve("/bin/ps", argv, envp);
    
    return 0;
}
