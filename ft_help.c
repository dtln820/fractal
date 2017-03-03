#include "b_fractal.h"

void    ft_putstr(char const *s)
{
        int i;

        i = 0;
        if (s)
        {
                while (s[i])
                {
                        write(1, &s[i], 1);
                        i++;
                }
        }
}

int     ft_strcmp(const char *str1, const char *str2)
{
        while (*str1 == *str2)
        {
                if (*str1 == '\0')
                        return (0);
                str1++;
                str2++;
        }
        return (*(unsigned char*)str1 - *(unsigned char*)str2);
}
