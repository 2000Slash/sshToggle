#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

void replaceAllString(char *, const char *, const char *);

void setConfig(int enable)
{
    openlog("MEEM", LOG_CONS, LOG_USER);
    FILE *f = fopen("/etc/ssh/sshd_config", "r+");
    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    rewind(f);
    char *text = calloc(size + 1, sizeof(char));
    fread(text, sizeof(char), size, f);
    rewind(f);
    if (enable)
    {
        replaceAllString(text, "PermitRootLogin no", "PermitRootLogin yes");
    }
    else
    {
        replaceAllString(text, "PermitRootLogin yes", "PermitRootLogin no");
    }
    fwrite(text, sizeof(char), strlen(text), f);
    fclose(f);
    free(text);
}

void replaceAllString(char *buf, const char *orig, const char *replace)
{
    int olen, rlen;
    char *s, *d;
    char *tmpbuf;

    if (!buf || !*buf || !orig || !*orig || !replace)
        return;

    tmpbuf = malloc(strlen(buf) + 1);
    if (tmpbuf == NULL)
        return;

    olen = strlen(orig);
    rlen = strlen(replace);

    s = buf;
    d = tmpbuf;

    while (*s)
    {
        if (strncmp(s, orig, olen) == 0)
        {
            strcpy(d, replace);
            s += olen;
            d += rlen;
        }
        else
            *d++ = *s++;
    }

    *d = '\0';

    strcpy(buf, tmpbuf);
    free(tmpbuf);
}