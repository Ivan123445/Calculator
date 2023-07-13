#include "s21_utils.h"

bool isddigit(char num) { return num >= '0' && num <= '9'; }

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
  if (**str != '.' && (end_scan != *str || !width)) {  // scan first digit
    status = OK;
    num = **str - ASCII_NUM_OFFSET;
    (*str)++;
  }

  for (; isddigit(**str) && (end_scan != *str || !width);
       (*str)++) {  // scan integer part
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