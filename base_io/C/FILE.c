#include <stdio.h>
#include <string.h>

int main()
{
    const char *msg0 = "printf\n";
    const char *msg1 = "fwrite\n";
    const char *msg2 = "write\n";

    printf("%s", msg0);
    fwrite(msg1, strlen(msg1), 1, stdout);
    write(1, msg2, strlen(msg2));

    fork();

    return 0;
}
