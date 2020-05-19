
#include "libft/src/libft.h"
#include <stdarg.h>

int ft_printf(const char *restrict format, ...);

typedef union   s_spec_fields
{
    int                     int_field;
    unsigned int            u_int_field;
    double                  double_field;
    long long int           pointer_field;
    unsigned char           u_char_field;
    char                    char_field;
    short int               short_int_field;
    long int                long_int_field;
    long long               ll_int_field;
    size_t                  size_t_field;
    intmax_t                intmax_t_field;
    unsigned short int      u_short_int_field;
    unsigned long int       u_l_int_field;
    unsigned long long int  u_ll_int_field;
    uintmax_t               uintmax_t_field;
    wchar_t                 *wchar_t_field;
    // wint_t                  wint_t_field;
}               t_spec_fields;

typedef struct  s_info
{
    t_spec_fields   fields;
    char            *res;

    int is_width;
    int is_precision;
    int width_val;
    int precision_val;
    int is_pound_sign;
    int is_zero_flag;
    int is_plus_sign_flag;
    int is_minus_sign_flag;
    int is_h;
    int is_hh;
    int is_l;
    int is_ll;
    int is_z;
    int is_j;
    int zero_flag_val;

}               t_info;