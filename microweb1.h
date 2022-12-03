#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>

void concatenarCharACadena(char c, char *cadena)
{
    char cadenaTemporal[2];
    cadenaTemporal[0] = c;
    cadenaTemporal[1] = '\0';
    strcat(cadena, cadenaTemporal);
}


char *read_file(char *filename, char *outstr)
{
    char str[1024*1024] = {0};
    if (!filename || !outstr)
    {
        printf("input error\n");
        return NULL;
    }
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    if(!fp)
    {
        return NULL;
    }
    while( fgets(str, 1024*1024, fp) )
    {
        strcat(outstr,str);
        memset(str, 0, 1024*1024);
    }

    fclose(fp);

    return outstr;
}
