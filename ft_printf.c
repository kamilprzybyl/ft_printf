#include "ft_printf.h"

int ft_printf(const char *restrict format, ...)
{
    va_list         Va_List;
    char            *string_field;
    unsigned char   char_field;
    int             int_field;
    double          double_field;
    long long int   pointer_field;
    int             i;

    va_start(Va_List, format);
    i = 0;
    if (!(string_field = malloc(1024 * sizeof(char))))
        return (-1);

    while (format[i] != '\0' && ft_bzero(string_field, ft_strlen(string_field)))
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i])
            {
                if (format[i] == 's')
                {
                    string_field = va_arg(Va_List, char *);
                    ft_putstr(string_field);
                    i++;
                }
                else if (format[i] == 'c')
                {
                    char_field = va_arg(Va_List, int);
                    ft_putchar(char_field);
                    i++;
                }
                else if (format[i] == 'd' )
                {
                    int_field = va_arg(Va_List, int);
                    string_field = ft_itoa(int_field);
                    ft_putstr(string_field);
                    i++;
                }
                else if (format[i] == 'l')
                {
                    i++;
                    if (format[i] == 'f')
                    {
                        double_field = va_arg(Va_List, double);
                        string_field = ft_itoa(double_field);
                        ft_putstr(string_field);
                        i++;
                    }
                }
                else if (format[i] == 'p')
                {
                    pointer_field = va_arg(Va_List, long long int);
                    string_field = ft_dec_to_hex(pointer_field);
                    ft_putstr(string_field);
                    i++;
                }
                else if (format[i] == '%')
                {
                    ft_putchar('%');
                    i++;
                }
                else
                {
                    ft_putchar('%');
                    ft_putchar(format[i]);
                    i++;
                }
            } 
        }
        else
        {
            ft_putchar(format[i]);
            i++;
        }
    }
    va_end(Va_List);

    return (0);
}

#include <stdio.h>

int main()
{
    char name[12] = "James";
    int age = 21;
    int i = 0;

    ft_printf("string test - %s\n", name);
    printf("string test - %s\n", name);
    ft_printf("integer test - %d\n", age);
    printf("integer test - %d\n", age);    
    ft_printf("address test - %p\n", &i);
    printf("address test - %p\n", &i);
    ft_printf("modulo character test - %%\n");
    printf("modulo character test - %%\n");
    ft_printf("char test - %c\n", 'a');
    printf("char test - %c\n", 'a');
    // ft_printf("single modulo test %\n");
    // printf("single modulo test - %");

    return (0);
}