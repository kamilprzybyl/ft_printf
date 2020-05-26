#include "ft_printf.h"
#include "stdio.h"


void reset_info(t_info *info)
{
    info->width = 0;
    info->width_val = 0;
    info->precision = 0;
    info->precision_val = 0;
    info->zero_flag_val = 0;
    info->len_mod = NO_MOD;
    info->flags = NO_FLAG;
}

typedef struct  s_call_function
{
    void    (*fct)(t_info *info, va_list va_arg_list);
    char     spec;
}               t_call_fucntion;

t_call_fucntion spec_table[] = 
{
    {handle_integer, 'd'},      //struct s_call_function number 0
    {handle_integer, 'i'},      //struct s_call_function number 1
    {handle_octal, 'o'},
    {handle_u_char, 'u'},
    {handle_hex, 'x'},
    {handle_heX, 'X'},
    {handle_char, 'c'},
    {handle_string, 's'},
    {handle_pointer, 'p'},
    {NULL, '\0'}
};

int check_spec(t_info *info, va_list va_arg_list, char spec)
{
    int i;

    i = 0;

    while (spec_table[i].fct)
    {
        if (spec_table[i].spec == spec)
        {
            spec_table[i].fct(info, va_arg_list);
            return (true);
        }
        i++;
    }
    return (false);
}

int ft_printf(const char *restrict format, ...)
{
    va_list         va_arg_list;
    t_info          info;
    int             i;
    
    va_start(va_arg_list, format);
    i = 0;

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            reset_info(&info);
            i++;
            while (format[i])
            {   
                if (format[i] == '#')
                {
                    info.flags |= POUND_SIGN;
                    i++; 
                }
                else if (format[i] == '0')
                {
                    info.flags |= ZERO_FLAG;
                    i++;
                }
                else if (format[i] == '+')
                {
                    info.flags |= PLUS_SIGN;
                    i++;
                }
                else if (format[i] == '-')
                {
                    info.flags |= MINUS_SIGN;
                    i++;
                }
                else if (ft_isdigit(format[i]))
                {
                    info.width_val = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i])) 
                        i++;
                    info.width = true;
                }
                else if (format[i] == '.')
                {
                    i++;
                    info.precision_val = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i]))
                        i++;
                    info.precision = true;
                }
                else if (format[i] == 'h')
                {
                    info.len_mod = MOD_H;
                    i++;
                    if (format[i] == 'h')
                    {
                        info.len_mod = MOD_HH;
                        i++;
                    }
                }
                else if (format[i] == 'l')
                {
                    info.len_mod = MOD_L;
                    i++;
                    if (format[i] == 'l')
                    {
                        info.len_mod = MOD_LL;
                        i++;
                    }
                }
                else if (format[i] == 'z')
                {
                    info.len_mod = MOD_Z;
                    i++;
                }
                else if (format[i] == 'j')
                {
                    info.len_mod = MOD_J;
                    i++;
                }
                else if (check_spec(&info, va_arg_list, format[i]) == true)
                {
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
    va_end(va_arg_list);

    return (0);
}