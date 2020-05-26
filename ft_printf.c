#include "ft_printf.h"
#include "stdio.h"

void handle_integer(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'd');

    if (info->flags & ZERO_FLAG)
        handle_zero_flag(info, 'd');
    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'd');
    if (info->flags & PLUS_SIGN)
        ft_putchar('+');
    if (info->precision)
        handle_precision(info, 'd');
    ft_putstr(info->res);
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'd');
    
    free(info->res); 
}

void handle_octal(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'o');

    if (info->flags & ZERO_FLAG)
        handle_zero_flag(info, 'o');
    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'o');                
    if (info->flags & POUND_SIGN)
        ft_putchar('0');
    if (info->precision)
        handle_precision(info, 'o');
    ft_putstr(info->res); 
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'o');   

    free(info->res);   
}

void handle_u_char(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'u');

    if ((info->flags & ZERO_FLAG))
        handle_zero_flag(info, 'u');
    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'u');
    if (info->precision)
        handle_precision(info, 'u');
    ft_putstr(info->res);
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'u');

    free(info->res);    
}

void handle_hex(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'x');

    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'x');
    if ((info->flags & POUND_SIGN) && ft_strcmp(info->res, "0"))       // to fix
        ft_putstr("0x");                        
    if (info->flags & ZERO_FLAG)
        handle_zero_flag(info, 'x');
    if (info->precision)
        handle_precision(info, 'x');
    ft_putstr(info->res);
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'x');

    free(info->res);    
}

void handle_heX(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'X');

    if (info->flags & ZERO_FLAG)
        handle_zero_flag(info, 'X');
    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'X');
    if (info->flags & POUND_SIGN)
        ft_putstr("0X");   
    if (info->precision)
        handle_precision(info, 'X');
    ft_putstr(info->res); 
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'X');   

    free(info->res);    
}

void handle_char(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'c'); 

    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'c');
    ft_putchar(info->ll_int_field); 
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'c');   
}

void handle_string(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 's');

    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 's');
    if (info->precision)
        handle_precision(info, 's');
    ft_putstr(info->res);
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 's');
}

void handle_pointer(t_info *info, va_list va_arg_list)
{
    info->ll_int_field = va_arg(va_arg_list, long long int);
    info->res = ft_dec_to_hex(info->ll_int_field, 0);

    if (!(info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'p');  
    ft_putstr("0x");
    ft_putstr(info->res);
    if ((info->flags & MINUS_SIGN) && info->width)
        handle_width(info, 'p');  

    free(info->res);
}

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