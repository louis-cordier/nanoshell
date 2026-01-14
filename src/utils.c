#include "../include/nanoshell.h"

char *ns_strchr(const char *s, int c)
{
    const unsigned char uc = (unsigned char)c;
    while (*s)
    {
        if ((unsigned char)*s == uc)
            return (char *)s;
        s++;
    }
    if (uc == '\0')
        return (char *)s;
    return NULL;
}
