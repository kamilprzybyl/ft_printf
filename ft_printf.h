#include "libft/src/libft.h"
#include <stdarg.h>
#include <stdbool.h>

typedef struct  s_info
{
    char            *res;
    long long       ll_int_field;

    int width;
    int precision;
    int width_val;
    int precision_val;
    int flags;
    int len_mod;
    int zero_flag_val;

}               t_info;

#define NO_MOD  0 
#define MOD_H   1 
#define MOD_HH  2 
#define MOD_L   3 
#define MOD_LL  4 
#define MOD_J   5 
#define MOD_Z   6 

#define NO_FLAG     0 
#define POUND_SIGN  1 
#define MINUS_SIGN  2 
#define PLUS_SIGN   4 
#define ZERO_FLAG   8 

int ft_printf(const char *restrict format, ...);

void handle_width(t_info *info, char spec);
void handle_precision(t_info *info, char spec);
void handle_zero_flag(t_info *info, int spec);

void handle_h(t_info *info, va_list va_arg_list, int spec);
void handle_hh(t_info *info, va_list va_arg_list, int spec);
void handle_l(t_info *info, va_list va_arg_list, int spec);
void handle_ll(t_info *info, va_list va_arg_list, int spec);
void handle_j(t_info *info, va_list va_arg_list, int spec);
void handle_z(t_info *info, va_list va_arg_list, int spec);
void handle_no_len_mod(t_info *info, va_list va_arg_list, int spec);
void handle_lenght_modifier(t_info *info, va_list va_arg_list, int spec);

void handle_hex(t_info *info, va_list va_arg_list);
void handle_heX(t_info *info, va_list va_arg_list);
void handle_string(t_info *info, va_list va_arg_list);
void handle_pointer(t_info *info, va_list va_arg_list);
void handle_integer(t_info *info, va_list va_arg_list);
void handle_octal(t_info *info, va_list va_arg_list);
void handle_char(t_info *info, va_list va_arg_list);
void handle_u_char(t_info *info, va_list va_arg_list);