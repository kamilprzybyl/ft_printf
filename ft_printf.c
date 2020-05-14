#include "ft_printf.h"
#include "stdio.h"


void handle_width(t_info *info, char spec)
{
    int     j;

    j = 0;

    if (spec == 'p')
        info->width_number = info->width_number - (ft_strlen(info->res) + 2);
    else if (spec == 'c')
        info->width_number = info->width_number - 1;
    else
    {
        info->width_number = info->width_number - ft_strlen(info->res) - info->precision_number;
        if (info->precision_number > ft_strlen(info->res))
            info->width_number += ft_strlen(info->res);
    }

    if (info->is_plus_sign_flag)
        info->width_number = info->width_number - 1;
    if (info->is_pound_sign && spec == 'x')
        info->width_number = info->width_number - 2;

    while (j++ < info->width_number)
        ft_putchar(' ');
}

void handle_precision(t_info *info, char spec)
{
    int     j;
    char    *after_dot;
    
    j = 0;

    if (spec == 'f')
    {
        after_dot = ft_strchr(info->res, '.');
        info->precision_number = info->precision_number - (ft_strlen(after_dot) - 1);

        // if precision-number is higher than 0 it does the loop at the end so nothing changes but  if it's lower than zero it removes precision-number characters from the end of res
        while (info->precision_number < 0 && j > info->precision_number)
        {
            info->res[ft_strlen(info->res) - 1] = 0;
            j--;                          
        }
    }
    else
        info->precision_number = info->precision_number - ft_strlen(info->res);
    
    j = 0;
    while (j++ < info->precision_number)
        ft_putchar('0');
}

void handle_hex(t_info *info, va_list va_arg_list)
{
    info->unsigned_int_field = va_arg(va_arg_list, unsigned int);
    info->res = ft_dec_to_hex(info->unsigned_int_field, 0);
    if (info->is_width)
        handle_width(info, 'x');
    if (info->is_pound_sign)
        ft_putstr("0x");                        
    if (info->is_precision)
        handle_precision(info, 'x');
    ft_putstr(info->res);
    free(info->res);    
}

void handle_integer(t_info *info, va_list va_arg_list)
{
    info->int_field = va_arg(va_arg_list, int);
    info->res = ft_itoa(info->int_field);

    if (info->is_width)
        handle_width(info, 'd');
    if (info->is_plus_sign_flag)
        ft_putchar('+');
    if (info->is_precision)
        handle_precision(info, 'd');

    ft_putstr(info->res);   
    free(info->res); 
}

void handle_octal(t_info *info, va_list va_arg_list)
{
    info->unsigned_int_field = va_arg(va_arg_list, unsigned int);
    info->unsigned_int_field = ft_dec_to_oct(info->unsigned_int_field);
    info->res = ft_itoa(info->unsigned_int_field);
    if (info->is_width)
        handle_width(info, 'o');                
    if (info->is_pound_sign)
        ft_prepend(info->res, "0");
    if (info->is_precision)
        handle_precision(info, 'o');
    ft_putstr(info->res); 
    free(info->res);   
}

void handle_u_char(t_info *info, va_list va_arg_list)
{
    info->unsigned_int_field = va_arg(va_arg_list, unsigned int);
    info->res = ft_itoa(info->unsigned_int_field);

    if (info->is_width)
        handle_width(info, 'u');
    if (info->is_precision)
        handle_precision(info, 'u');
    
    ft_putstr(info->res);
    free(info->res);    
}

void handle_heX(t_info *info, va_list va_arg_list)
{
    info->unsigned_int_field = va_arg(va_arg_list, unsigned int);
    info->res = ft_dec_to_hex(info->unsigned_int_field, 1);

    if (info->is_width)
        handle_width(info, 'X');
    if (info->is_precision)
        handle_precision(info, 'X');

    ft_putstr(info->res);
    free(info->res);    
}

void handle_f_F(t_info *info, va_list va_arg_list)
{
    info->double_field = va_arg(va_arg_list, double);
    info->res = ft_ftoa(info->double_field);

    if (info->is_width)
        handle_width(info, 'f');
    if (info->is_precision)
        handle_precision(info, 'f');

    ft_putstr(info->res);
    free(info->res); 
}

void handle_g_G(t_info *info, va_list va_arg_list)
{
    info->double_field = va_arg(va_arg_list, double);
    info->res = ft_ftoa(info->double_field);

    while (info->res[ft_strlen(info->res) - 1] == '0')
        info->res[ft_strlen(info->res) - 1] = '\0';

    if (info->is_width)
        handle_width(info, 'g');

    ft_putstr(info->res);    
    free(info->res);
}

void handle_char(t_info *info, va_list va_arg_list)
{
    info->char_field = va_arg(va_arg_list, int);

    if (info->is_width)
        handle_width(info, 'c');

    ft_putchar(info->char_field);    
}

void handle_string(t_info *info, va_list va_arg_list)
{
    info->res = va_arg(va_arg_list, char *);

    if (info->is_width)
        handle_width(info, 's');

    ft_putstr(info->res);   
}

void handle_pointer(t_info *info, va_list va_arg_list)
{
    info->pointer_field = va_arg(va_arg_list, long long int);
    info->res = ft_dec_to_hex(info->pointer_field, 0);

    if (info->is_width)
        handle_width(info, 'p');  

    ft_putstr("0x");
    ft_putstr(info->res);
    free(info->res);
}

void reset_info(t_info *info)
{
    info->is_pound_sign = 0;
    info->is_zero_flag = 0;
    info->is_plus_sign_flag = 0;
    info->is_minus_sign_flag = 0;
    info->is_width = 0;
    info->is_precision = 0;
    info->width_number = 0;
    info->precision_number = 0;
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
                    info.is_pound_sign = 1;
                    i++; 
                }
                else if (format[i] == '0')
                {
                    info.is_zero_flag = 1;
                    i++;
                }
                else if (format[i] == '+')
                {
                    info.is_plus_sign_flag = 1;
                    i++;
                }
                else if (format[i] == '-')
                {
                    info.is_minus_sign_flag = 1;
                    i++;
                }
                else if (ft_isdigit(format[i]))
                {
                    info.width_number = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i])) 
                        i++;
                    info.is_width = 1;
                }
                else if (format[i] == '.')
                {
                    i++;
                    info.precision_number = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i]))
                        i++;
                    info.is_precision = 1;
                }
                else if (format[i] == 'd' || format[i] == 'i')
                {
                    handle_integer(&info, va_arg_list);
                    i++;
                    break;
                }
                else if (format[i] == 'o')
                {
                    handle_octal(&info, va_arg_list);
                    i++;
                    break;
                }                
                else if (format[i] == 'u')
                {
                    handle_u_char(&info, va_arg_list);
                    i++;
                    break;
                }
                else if (format[i] == 'x')
                {
                    handle_hex(&info, va_arg_list);
                    i++;
                    break;
                }
                else if (format[i] == 'X')
                {
                    handle_heX(&info, va_arg_list);
                    i++;
                    break;
                }
                else if (format[i] == 'f' || format[i] == 'F')
                {
                    handle_f_F(&info, va_arg_list);
                    i++;
                    break;
                }                
                else if (format[i] == 'g' || format[i] == 'G')
                {
                    handle_g_G(&info, va_arg_list);
                    i++;
                    break;
                }                
                else if (format[i] == 'c')
                {
                    handle_char(&info, va_arg_list);
                    i++;
                    break;
                }
                else if (format[i] == 's')
                {
                    handle_string(&info, va_arg_list);
                    i++;
                    break;
                }
                else if (format[i] == 'p')
                {
                    handle_pointer(&info, va_arg_list);
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