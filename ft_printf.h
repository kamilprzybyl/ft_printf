
#include "libft/src/libft.h"
#include <stdarg.h>

int ft_printf(const char *restrict format, ...);

typedef struct  s_info
{
    int             int_field;
    unsigned int    unsigned_int_field;
    double          double_field;
    long long int   pointer_field;
    unsigned char   char_field;
    char            *res;

    int is_width;
    int is_precision;
    int width_number;
    int precision_number;
    int is_pound_sign;
    int is_zero_flag;
    int is_plus_sign_flag;
    int is_minus_sign_flag;

}               t_info;