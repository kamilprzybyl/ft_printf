#include "ft_printf.h"
#include "stdio.h"


void handle_width(t_info *info, char spec)
{
    int     j;

    j = 0;

    if (spec == 'c')
        info->width_val -= 1;
    else if (spec == 's')
    {
        if (info->is_precision && info->precision_val < ft_strlen(info->res))
            info->width_val -= info->precision_val;
        else
            info->width_val -= ft_strlen(info->res);
    }
    else
    {
        if (info->is_precision && info->precision_val > ft_strlen(info->res))
            info->width_val -= info->precision_val;
        else
            info->width_val -= ft_strlen(info->res);
    }

    if (info->is_plus_sign_flag || (info->is_pound_sign && spec == 'o'))
        info->width_val -= 1;
    if ((info->is_pound_sign && (spec == 'x' || spec == 'X')) || spec == 'p')
        info->width_val -= 2;
    if (info->is_zero_flag)
        info->width_val -= info->zero_flag_val;
    
    while (j++ < info->width_val)
        ft_putchar(' ');
}

void handle_precision(t_info *info, char spec)
{
    int     j;
    int     zeros_to_be_padded;
    
    j = 0;

    if (spec == 's')
        info->res[info->precision_val] = '\0'; 
    else
    {
        zeros_to_be_padded = info->precision_val - ft_strlen(info->res);
        
        while (j++ < zeros_to_be_padded)
            ft_putchar('0');
    }
}
  
void handle_zero_flag(t_info *info, int spec)
{
    int     j;

    j = 0;

    info->zero_flag_val = info->width_val - ft_strlen(info->res);

    if (info->is_pound_sign && (spec == 'x' || spec == 'X')) 
        info->zero_flag_val -= 2;
    if (info->is_pound_sign && spec == 'o')
        info->zero_flag_val -= 1;
    
    if (info->zero_flag_val > info->precision_val)
        while (j++ < info->zero_flag_val)
            ft_putchar('0');
}

void handle_h(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.ll_int_field = va_arg(va_arg_list, int);
        info->res = ft_itoa(info->fields.ll_int_field);
    }
    else if (spec == 'o')
    {
        info->fields.ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.ll_int_field));
    }
    else if (spec == 'u')
    {
        info->fields.ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.ll_int_field);    
    }
    else if (spec == 'x')
    {
        info->fields.ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.ll_int_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.ll_int_field, 1);
    }
}

void handle_hh(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.char_field = va_arg(va_arg_list, int);
        info->res = ft_itoa(info->fields.char_field);
    }
    else if (spec == 'o')
    {
        info->fields.u_char_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.u_char_field));
    }
    else if (spec == 'u')
    {
        info->fields.u_char_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.u_char_field);    
    }
    else if (spec == 'x')
    {
        info->fields.u_char_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_char_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.u_char_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_char_field, 1);
    }
}

void handle_l(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.long_int_field = va_arg(va_arg_list, long int);
        info->res = ft_itoa(info->fields.long_int_field);
    }
    else if (spec == 'o')
    {
        info->fields.u_l_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.u_l_int_field));
    }
    else if (spec == 'u')
    {
        info->fields.u_l_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.u_l_int_field);    
    }
    else if (spec == 'x')
    {
        info->fields.u_l_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_l_int_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.u_l_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_l_int_field, 1);
    }
    // else if (spec == 'c')
    //     info->fields.wint_t_field = va_arg(va_arg_list, wint_t);
    // else if (spec == 's')
        // info->wchar_t_field = va_arg(va_arg_list, wchar_t *);
}

void handle_ll(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.ll_int_field = va_arg(va_arg_list, long long int);
        info->res = ft_itoa(info->fields.ll_int_field);
    }
    else if (spec == 'o')
    {
        info->fields.u_ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.u_ll_int_field));
    }
    else if (spec == 'u')
    {
        info->fields.u_ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.u_ll_int_field);    
    }
    else if (spec == 'x')
    {
        info->fields.u_ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_ll_int_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.u_ll_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_ll_int_field, 1);
    }
}

void handle_j(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.intmax_t_field = va_arg(va_arg_list, intmax_t);
        info->res = ft_itoa(info->fields.intmax_t_field);
    }
    else if (spec == 'o')
    {
        info->fields.uintmax_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.uintmax_t_field));
    }
    else if (spec == 'u')
    {
        info->fields.uintmax_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.uintmax_t_field);    
    }
    else if (spec == 'x')
    {
        info->fields.uintmax_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.uintmax_t_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.uintmax_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.uintmax_t_field, 1);
    }
}

void handle_z(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.size_t_field = va_arg(va_arg_list, size_t);
        info->res = ft_itoa(info->fields.size_t_field);
    }
    else if (spec == 'o')
    {
        info->fields.size_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.size_t_field));
    }
    else if (spec == 'u')
    {
        info->fields.size_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.size_t_field);    
    }
    else if (spec == 'x')
    {
        info->fields.size_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.size_t_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.size_t_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.size_t_field, 1);
    }
}

void handle_no_len_mod(t_info *info, va_list va_arg_list, int spec)
{
    if (spec == 'd')
    {
        info->fields.int_field = va_arg(va_arg_list, int);
        info->res = ft_itoa(info->fields.int_field);
    }
    else if (spec == 'o')
    {
        info->fields.u_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(ft_dec_to_oct(info->fields.u_int_field));
    }
    else if (spec == 'u')
    {
        info->fields.u_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_itoa(info->fields.u_int_field);    
    }
    else if (spec == 'x')
    {
        info->fields.u_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_int_field, 0);
    }
    else if (spec == 'X')
    {
        info->fields.u_int_field = va_arg(va_arg_list, unsigned int);
        info->res = ft_dec_to_hex(info->fields.u_int_field, 1);
    }        
    else if (spec == 'c')
        info->fields.u_char_field = va_arg(va_arg_list, int);
    else if (spec == 's')
        info->res = ft_strcpy(info->res, va_arg(va_arg_list, char *));
}    

void handle_lenght_modifier(t_info *info, va_list va_arg_list, int spec)
{
    if (info->is_h)
        handle_h(info, va_arg_list, spec);
    else if (info->is_hh)
        handle_hh(info, va_arg_list, spec);
    else if (info->is_l)
        handle_l(info, va_arg_list, spec);
    else if (info->is_ll)
        handle_ll(info, va_arg_list, spec);
    else if (info->is_j)
        handle_j(info, va_arg_list, spec);
    else if (info->is_z)
        handle_z(info, va_arg_list, spec);
    else
        handle_no_len_mod(info, va_arg_list, spec);
}

void handle_integer(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'd');

    if (info->is_minus_sign_flag)
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'd');
        if (info->is_plus_sign_flag)
            ft_putchar('+');
        if (info->is_precision)
            handle_precision(info, 'd');
        ft_putstr(info->res);
        if (info->is_width)
            handle_width(info, 'd');
    }
    else
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'd');
        if (info->is_width)
            handle_width(info, 'd');
        if (info->is_plus_sign_flag)
            ft_putchar('+');
        if (info->is_precision)
            handle_precision(info, 'd');
        ft_putstr(info->res);
    }
       
    free(info->res); 
}

void handle_octal(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'o');

    if (info->is_minus_sign_flag)
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'o');
        if (info->is_pound_sign)
            ft_putchar('0');
        if (info->is_precision)
            handle_precision(info, 'o');
        ft_putstr(info->res); 
        if (info->is_width)
            handle_width(info, 'o');                
    }
    else
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'o');
        if (info->is_width)
            handle_width(info, 'o');                
        if (info->is_pound_sign)
            ft_putchar('0');
        if (info->is_precision)
            handle_precision(info, 'o');
        ft_putstr(info->res); 
    }

    free(info->res);   
}

void handle_u_char(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'u');
    
    if (info->is_minus_sign_flag)
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'u');
        if (info->is_precision)
            handle_precision(info, 'u');
        ft_putstr(info->res);
        if (info->is_width)
            handle_width(info, 'u');
    }
    else
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'u');
        if (info->is_width)
            handle_width(info, 'u');
        if (info->is_precision)
            handle_precision(info, 'u');
        ft_putstr(info->res);
    }

    free(info->res);    
}

void handle_hex(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'x');

    if (info->is_minus_sign_flag)
    {
        if (info->is_pound_sign && ft_strcmp(info->res, "0")) // to fix
            ft_putstr("0x");                        
        if (info->is_zero_flag)
            handle_zero_flag(info, 'x');
        if (info->is_precision)
            handle_precision(info, 'x');
        ft_putstr(info->res);
        if (info->is_width)
            handle_width(info, 'x');
    }    
    else
    {
        if (info->is_width)
            handle_width(info, 'x');
        if (info->is_pound_sign && ft_strcmp(info->res, "0")) // to fix
            ft_putstr("0x");                        
        if (info->is_zero_flag)
            handle_zero_flag(info, 'x');
        if (info->is_precision)
            handle_precision(info, 'x');
        ft_putstr(info->res);
    }

    free(info->res);    
}

void handle_heX(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'X');

    if (info->is_minus_sign_flag)
    {
        if (info->is_pound_sign)
            ft_putstr("0X");   
        if (info->is_zero_flag)
            handle_zero_flag(info, 'X');
        if (info->is_precision)
            handle_precision(info, 'X');
        ft_putstr(info->res);
        if (info->is_width)
            handle_width(info, 'X');
    }
    else
    {
        if (info->is_zero_flag)
            handle_zero_flag(info, 'X');
        if (info->is_width)
            handle_width(info, 'X');
        if (info->is_pound_sign)
            ft_putstr("0X");   
        if (info->is_precision)
            handle_precision(info, 'X');
        ft_putstr(info->res);
    }

    free(info->res);    
}

void handle_char(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 'c');
    
    if (info->is_minus_sign_flag)
    {
        ft_putchar(info->fields.u_char_field);
        if (info->is_width)
            handle_width(info, 'c');
    }
    else
    {
        if (info->is_width)
            handle_width(info, 'c');
        ft_putchar(info->fields.u_char_field);
    }    
}

void handle_string(t_info *info, va_list va_arg_list)
{
    handle_lenght_modifier(info, va_arg_list, 's');

    if (info->is_minus_sign_flag)
    {
        if (info->is_precision)
            handle_precision(info, 's');
        ft_putstr(info->res);         
        if (info->is_width)
            handle_width(info, 's');
    }
    else
    {
        if (info->is_width)
            handle_width(info, 's');
        if (info->is_precision)
            handle_precision(info, 's');
        ft_putstr(info->res);   
    }
}

void handle_pointer(t_info *info, va_list va_arg_list)
{
    info->fields.pointer_field = va_arg(va_arg_list, long long int);
    info->res = ft_dec_to_hex(info->fields.pointer_field, 0);

    if (info->is_minus_sign_flag)
    {
        ft_putstr("0x");
        ft_putstr(info->res);        
        if (info->is_width)
            handle_width(info, 'p');  
    }
    else
    {
        if (info->is_width)
            handle_width(info, 'p');  
        ft_putstr("0x");
        ft_putstr(info->res);
    }
    free(info->res);
}

void reset_info(t_info *info)
{
    info->is_pound_sign = 0;
    info->is_plus_sign_flag = 0;
    info->is_minus_sign_flag = 0;
    info->is_width = 0;
    info->width_val = 0;
    info->is_precision = 0;
    info->precision_val = 0;
    info->is_zero_flag = 0;
    info->zero_flag_val = 0;
    info->is_h = 0;
    info->is_hh = 0;
    info->is_l = 0;
    info->is_ll = 0;
    info->is_z = 0;
    info->is_j = 0;
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
                    info.width_val = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i])) 
                        i++;
                    info.is_width = 1;
                }
                else if (format[i] == '.')
                {
                    i++;
                    info.precision_val = ft_atoi(&(format[i]));
                    while (ft_isdigit(format[i]))
                        i++;
                    info.is_precision = 1;
                }
                else if (format[i] == 'h')
                {
                    info.is_h = 1;
                    i++;
                    if (format[i] == 'h')
                    {
                        info.is_hh = 1;
                        info.is_h = 0;
                        i++;
                    }
                }
                else if (format[i] == 'l')
                {
                    info.is_l = 1;
                    i++;
                    if (format[i] == 'l')
                    {
                        info.is_ll = 1;
                        info.is_l = 0;
                        i++;
                    }
                }
                else if (format[i] == 'z')
                {
                    info.is_z = 1;
                    i++;
                }
                else if (format[i] == 'j')
                {
                    info.is_j = 1;
                    i++;
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