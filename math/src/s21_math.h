#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_
#define S21_M_PI 3.14159265358979323846264338327950288
#define S21_M_EULER 2.71828182845904523536028747135266250
#define S21_EPS 1e-17
#define S21_NAN __builtin_nanf("0x7fc00000")
#define S21_INFINITY 1.0 / 0.0
#define s21_isnan(x) __builtin_isnan(x)  // проверяет, является ли аргумент не числом (nan)
#define s21_isfinite(x) __builtin_isfinite(x)  // макрос проверяет, является ли аргумент конечным числом

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

int s21_abs(int x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_log(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_sqrt(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_factorial(int x);

#endif  // SRC_S21_MATH_H_
