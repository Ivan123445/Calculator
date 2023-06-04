#include "s21_utils.h"

bool isddigit(char num) { return num >= '0' && num <= '9'; }

int get_num_len(long long num) {
    int len = 0;
    for (; num; num /= 10, len++)
        ;
    return len;
}

double scan_decimal(const char **str, int width) {
    int status = ERROR;
    if (!isddigit(**str) && !strchr("+-.,", **str)) {
        return status;
    }
    double num = 0;
    const char *end_scan = *str + width;
    int sign = 1;
    if (strchr("+-", **str)) {
        sign = **str == '-' ? -1 : 1;
        (*str)++;
    }
    if (**str != '.' && (end_scan != *str || !width)) { // scan first digit
        status = OK;
        num = **str - ASCII_NUM_OFFSET;
        (*str)++;
    }

    for (; isddigit(**str) && (end_scan != *str || !width); (*str)++) {  // scan integer part
        num = num * 10 + **str - ASCII_NUM_OFFSET;
    }

    if (**str == '.' && (end_scan != *str || !width)) {  // scan float part
        status = OK;

        (*str)++;
        for (long double i = 0.1; isddigit(**str) && (end_scan != *str || !width);
             (*str)++, i /= 10) {
            num = num + (**str - ASCII_NUM_OFFSET) * i;
        }
    }
    // scan scientific node
    if (strchr("eE", **str) &&
        (isddigit(*(*str + 1)) ||
         (strchr("+-", *(*str + 1)) && isddigit(*(*str + 2)))) &&
        (end_scan != *str || !width)) {
        (*str)++;
        int sign_exp = 1;
        if (strchr("+-", **str) && end_scan != *str) {
            **str == '-' ? sign_exp = -1 : 0;
            (*str)++;
        }
        int exp = 0;
        for (; isddigit(**str) && end_scan != *str; (*str)++) {
            exp = exp * 10 + **str - ASCII_NUM_OFFSET;
        }
        exp *= sign_exp;
        num *= pow(10, exp);
    }

    num *= sign;
    return num;
}

void print_decimal(double num, char *str) {
    int width;
    if (num < 0) {
        width = '-';
        width++;
        num *= -1;
    }

    num = round(num * 1000000) / 1000000.0;
    num += 1 / 10000000.0;


    long int_num = num;
    if (get_num_len(int_num)) {
        for (int len = get_num_len(int_num); len > 0; len--, width++) {
            str[width] =
                    (char)((int_num / (long long)pow(10, len - 1)) % 10 +
                           ASCII_NUM_OFFSET);
        }
    } else {
        str[width] = '0';
        width++;
    }

    str[width] = '.';
    width++;

    for (int i = 0; i < 6; i++, width++) {
        long int fract_num = num * pow(10, i + 1);
        fract_num %= 10;
        str[width] = fract_num + ASCII_NUM_OFFSET;
    }
//
//    if (specifier.flags & FLAG_ZERO) {
//        var_t tmp = DEFAULT_VAR;
//        if (var.str[0] == '-' || var.str[0] == '+') {
//            tmp.str[0] = var.str[0];
//            tmp.width++;
//            for (; tmp.width - 1 + var.width < specifier.width &&
//                   !(specifier.flags & FLAG_MINUS);
//                   tmp.width++) {
//                tmp.str[tmp.width] = '0';
//            }
//            s21_strcat(tmp.str, var.str + 1);
//            s21_strcpy(var.str, tmp.str);
//            var.width += tmp.width - 1;
//        } else {
//            for (; tmp.width + var.width < specifier.width &&
//                   !(specifier.flags & FLAG_MINUS);
//                   tmp.width++) {
//                tmp.str[tmp.width] = '0';
//            }
//            s21_strcat(tmp.str, var.str);
//            s21_strcpy(var.str, tmp.str);
//            var.width += tmp.width;
//        }
//    }
}