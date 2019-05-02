#include <stdio.h>
#include <string.h>

int main()
{
    const char *msg = "fwrite\n";
    fwrite(msg, strlen(msg), 1, stdout);

    printf("printf\n");
    fprintf(stdout, "fprintf\n");
    return 0;
}
