#include "ft_printf.h"
#include "stdio.h"

int ft_printf(const char *restrict format, ...)
{
    va_list         Va_List;
    int             i;
    int             int_field;
    unsigned int    unsigned_int_field;
    unsigned char   char_field;
    char            *string_field;
    long long int   pointer_field;
    double          double_field;
    int             pound_sign;
    int             zero_flag;
    int             plus_sign_flag;
    int             minus_sign_flag;
    int             width;
    int             width_number;
    // char            width_char[100];

    va_start(Va_List, format);
    i = 0;
    if (!(string_field = malloc(1024 * sizeof(char))))
        return (-1);
    pound_sign = 0;
    zero_flag = 0;
    plus_sign_flag = 0;
    minus_sign_flag = 0;
    width = 0;

    while (format[i] != '\0')
    {
        // ft_bzero(string_field, ft_strlen(string_field));
        if (format[i] == '%')
        {
            i++;
            while (format[i])
            {   
                if (format[i] == '#')
                {
                    pound_sign = 1;
                    i++; 
                }
                else if (format[i] == '0')
                {
                    zero_flag = 1;
                    i++;
                }
                else if (format[i] == '+')
                {
                    plus_sign_flag = 1;
                    i++;
                }
                else if (format[i] == '-')
                {
                    minus_sign_flag = 1;
                    i++;
                }
                else if (ft_isdigit(format[i]))
                {
                    width_number = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i])) 
                        i++;
                    width = 1;
                }
                else if (format[i] == 'd' || format[i] == 'i')
                {
                    int_field = va_arg(Va_List, int);
                    string_field = ft_itoa(int_field);
                    if (plus_sign_flag)
                        ft_prepend(string_field, "+");
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }
                else if (format[i] == 'o')
                {
                    unsigned_int_field = va_arg(Va_List, unsigned int);
                    unsigned_int_field = ft_dec_to_oct(unsigned_int_field);
                    string_field = ft_itoa(unsigned_int_field);
                    if (pound_sign)
                        ft_prepend(string_field, "0");
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }                    
                    ft_putstr(string_field);
                    i++;
                    break;
                }                
                else if (format[i] == 'u')
                {
                    unsigned_int_field = va_arg(Va_List, unsigned int);
                    string_field = ft_itoa(unsigned_int_field);
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }
                else if (format[i] == 'x')
                {
                    unsigned_int_field = va_arg(Va_List, unsigned int);
                    string_field = ft_dec_to_hex(unsigned_int_field, 0);
                    if (pound_sign)
                        ft_prepend(string_field, "0x");
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }
                else if (format[i] == 'X')
                {
                    unsigned_int_field = va_arg(Va_List, unsigned int);
                    string_field = ft_dec_to_hex(unsigned_int_field, 1);
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }
                else if (format[i] == 'f' || format[i] == 'F')
                {
                    double_field = va_arg(Va_List, double);
                    string_field = ft_ftoa(double_field);
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }                
                else if (format[i] == 'g' || format[i] == 'G')
                {
                    double_field = va_arg(Va_List, double);
                    string_field = ft_ftoa(double_field);
                    int len = (ft_strlen(string_field) - 1);
                    while (string_field[len] == '0')
                        string_field[len--] = '\0';
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }                
                else if (format[i] == 'c')
                {
                    char_field = va_arg(Va_List, int);
                    ft_putchar(char_field);
                    i++;
                    break;
                }
                else if (format[i] == 's')
                {
                    string_field = va_arg(Va_List, char *);
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }
                    ft_putstr(string_field);
                    i++;
                    break;
                }
                else if (format[i] == 'p')
                {
                    pointer_field = va_arg(Va_List, long long int);
                    string_field = ft_dec_to_hex(pointer_field, 0);
                    ft_prepend(string_field, "0x");
                    if (width)
                    {
                        width_number = width_number - ft_strlen(string_field);
                        int cnt = 0;
                        while (cnt < width_number)  
                        {
                            ft_prepend(string_field, " ");
                            cnt++;
                        }
                    }                    
                    ft_putstr(string_field);
                    i++;
                    break;
                }
                else if (format[i] == '%')
                {
                    ft_putchar('%');
                    i++;
                    break;
                }
                else
                {
                    ft_putchar('%');
                    ft_putchar(format[i]);
                    i++;
                    break;
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