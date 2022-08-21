#include "s21_math.h"

// вычисляет абсолютное значение целого числа
int s21_abs(int x) {
    if (x < 0) x = -x;
    return x;
}

// вычисляет абсолютное значение числа с плавающей точкой
long double s21_fabs(double x) {
    if (x < 0) x = -x;
    return x;
}

// возвращает значение e, возведенное в заданную степень
long double s21_exp(double x) {
    bool attention = false;
    long double res = 1;
    if (x == S21_INFINITY) {
        res = x;
        attention = true;
    }
    if (x == -S21_INFINITY) {
        res = 0;
        attention = true;
    }
    if (attention == false) {
        bool minus = false;
        if (x < 0) {
            x = -x;
            minus = true;
        }
        long double value = 1;
        long double i = 1;
        while (s21_fabs(value) > S21_EPS) {
            if (res > __DBL_MAX__) {
                res = S21_INFINITY;
                break;
            }
            value = value * (x / i);
            i++;
            res = res + value;
        }
        if (minus == true) {
            res = 1.0 / res;
        }
    }
    return res;
}

// вычисляет натуральный логарифм
long double s21_log(double x) {
    int whole_counter = 0;
    double fractional_res = 0;
    bool inf_test = false;
    if (x == 0.0) inf_test = true;
    if (x > 0) {
        if (x == S21_INFINITY) {
            fractional_res = S21_INFINITY;
        } else {
            for (; x >= S21_M_EULER; whole_counter++) {
                x = x / S21_M_EULER;
            }
            for (int i = 0; i < 100; i++) {
                fractional_res =
                    fractional_res + 2 * ((x - s21_exp(fractional_res)) /
                                          (x + s21_exp(fractional_res)));
            }
        }
    } else {
        fractional_res = S21_NAN;
    }
    return inf_test == true ? -S21_INFINITY : (whole_counter + fractional_res);
}

// остаток операции деления с плавающей точкой
long double s21_fmod(double x, double y) {
    long double res = 0;
    long long int denum = x / y;
    if (y == 0.0 || x == S21_INFINITY || x == -S21_INFINITY) {
        res = S21_NAN;
    } else if (y == S21_INFINITY || y == -S21_INFINITY) {
        res = x;
    } else {
        res = x - (denum * y);
    }
    return res;
}

// возводит число в заданную степень
long double s21_pow(double base, double exp) {
    long double res = 1;
    bool attention = false;
    bool minus_exp = false;
    if ((base == 0 && exp == -1) ||
        ((s21_fabs(base) > 1 || base == -S21_INFINITY) &&
         exp == S21_INFINITY) ||
        ((base > 0 && base < 1) && exp == -S21_INFINITY)) {
        res = S21_INFINITY;
        attention = true;
    }
    if ((base == 0 && (exp == 1 || exp == S21_INFINITY)) ||
        (base == S21_INFINITY && (exp == -1 || exp == -S21_INFINITY)) ||
        (base == -S21_INFINITY && exp == -S21_INFINITY) ||
        ((base > 0 && base < 1) && (exp == S21_INFINITY)) ||
        (s21_fabs(base) > 1 && exp == -S21_INFINITY)) {
        res = 0;
        attention = true;
    }
    if ((base == S21_INFINITY && exp == 1) || (base == 0 && exp == 0) ||
        (s21_fabs(base) == 1 && (exp == -S21_INFINITY || s21_isnan(exp)))) {
        res = 1;
        attention = true;
    }
    if (s21_isnan(base) || (base == -1 && s21_isnan(exp))) {
        res = S21_NAN;
        attention = true;
    }
    if (attention == false) {
        if (base < 0) {
            base = s21_fabs(base);
            long double overflow = __DBL_MAX__ / base;
            if (exp == (int)exp) {
                if (exp < 0) {
                    exp = -exp;
                    minus_exp = true;
                }
                int i = (int)exp;
                while (i--) {
                    res = res * base;
                    if (res > overflow) {
                        res = S21_INFINITY;
                        break;
                    }
                }
                if ((int)exp % 2 != 0) {
                    res = res * -1;
                }
            } else {
                if (base == S21_INFINITY && !s21_isnan(exp)) {
                    res = S21_INFINITY;
                } else {
                    res = S21_NAN;
                }
            }
        } else {
            res = s21_exp(exp * s21_log(base));
        }
    }
    if (minus_exp == true) res = 1.0 / res;
    if (exp == 0.0) res = 1;
    return res;
}

// возвращает ближайшее целое число, не меньшее заданного значения
long double s21_ceil(double x) {
    long double ceil_res = 0;
    bool attention = false;
    if (x == S21_INFINITY || x == -S21_INFINITY || s21_isnan(x)) {
        if (s21_isnan(x)) {
            ceil_res = S21_NAN;
        } else {
            ceil_res = x;
        }
        attention = true;
    }
    if (attention == false) {
        ceil_res = (long long int)x;
        if (ceil_res != x && x > 0.0) {
            ceil_res++;
        }
    }
    return ceil_res;
}

// возвращает ближайшее целое число, не превышающее заданное значение
long double s21_floor(double x) {
    long double floor_res = 0;
    bool attention = false;
    if (x == S21_INFINITY || x == -S21_INFINITY || s21_isnan(x)) {
        if (s21_isnan(x)) {
            floor_res = S21_NAN;
        } else {
            floor_res = x;
        }
        attention = true;
    }
    if (attention == false) {
        floor_res = (long long int)x;
        if (floor_res != x && x < 0.0) {
            floor_res--;
        }
    }
    return floor_res;
}

// вычисляет квадратный корень
long double s21_sqrt(double x) {
    long double res = 0;
    if (s21_isnan(x) || x == -S21_INFINITY || x < 0) {
        res = S21_NAN;
    } else {
        if (x > 0) {
            res = s21_pow(x, 0.5);
        }
    }
    return res;
}

// вычисляет синус
long double s21_sin(double x) {
    int sign = 1;
    int flag = 0;
    if (s21_isnan(x) || !s21_isfinite(x)) flag = 1;
    x = s21_fmod(x, 2 * S21_M_PI);  // делим число от -2пи до 2пи
    // приводим х в 1 четверть с опр. знаком
    if (x > (S21_M_PI / 2.0) && x <= S21_M_PI) {
        x = S21_M_PI - x;
    } else if (x > S21_M_PI && x <= S21_M_PI * 3.0 / 2.0) {
        x -= S21_M_PI;
        sign = -1;
    } else if (x > (S21_M_PI * 3.0) / 2.0 && x <= 2.0 * S21_M_PI) {
        x = 2 * S21_M_PI - x;
        sign = -1;
    }

    long double add_to_sum = (long double)x;
    long double sum = (long double)x;

    for (int i = 1; i < 500; i++) {
        add_to_sum = (-add_to_sum * x * x) / ((2.0 * i + 1) * (2.0 * i));
        sum += add_to_sum;
    }
    return flag == 1 ? S21_NAN : sum * sign;
}

// вычисляет косинус
long double s21_cos(double x) {
    int sign = 1;
    int flag = 0;
    long double sum = 1.0;
    long double add_to_sum = 1.0;
    if (s21_isnan(x) || !s21_isfinite(x)) flag = 1;
    x = s21_fmod(x, 2 * S21_M_PI);
    if (x > (S21_M_PI / 2.0) && x <= S21_M_PI) {
        x = S21_M_PI - x;
        sign *= -1;
    } else if (x > S21_M_PI && x <= S21_M_PI * 3.0 / 2.0) {
        x -= S21_M_PI;
        sign *= -1;
    } else if (x > (S21_M_PI * 3.0) / 2.0 && x <= 2.0 * S21_M_PI) {
        x = 2 * S21_M_PI - x;
    }
    for (int i = 1; i < 500; i++) {
        add_to_sum = (-add_to_sum * x * x) / ((2.0 * i - 1) * (2.0 * i));
        sum += add_to_sum;
    }
    return flag == 1 ? S21_NAN : sum * sign;
}

// вычисляет тангенс
long double s21_tan(double x) {
    int flag = 0;
    if (s21_isnan(x) || !s21_isfinite(x)) flag = 1;
    return flag == 1 ? S21_NAN : s21_sin(x) / s21_cos(x);
}

// вычисляет арккосинус
long double s21_acos(double x) {
    long double res = 0.0;
    if (s21_isnan(x) || !s21_isfinite(x) || s21_fabs(x) > 1) {
        res = S21_NAN;
    } else {
        if (x > 0 && x < 1) {
            res = s21_atan((s21_sqrt(1 - (x * x))) / x);
        } else if (x > -1 && x < 0) {
            res = s21_atan((s21_sqrt(1 - (x * x))) / x) + S21_M_PI;
        } else if (x == 0.) {
            res = S21_M_PI / 2;
        } else if (x == -1.) {
            res = (S21_M_PI);
        }
    }
    return res;
}

// вычисляет арксинус
long double s21_asin(double x) {
    long double res = 0.0;
    if (s21_isnan(x) || !s21_isfinite(x) || s21_fabs(x) > 1) {
        res = S21_NAN;
    } else {
        if (s21_fabs(x) < 1) {
            res = s21_atan(x / (s21_sqrt(1 - (x * x))));
        } else if (x == 1.) {
            res = S21_M_PI / 2;
        } else if (x == -1.) {
            res = (-S21_M_PI / 2);
        }
    }
    return res;
}

// вычисляет арктангенс
long double s21_atan(double x) {
    long double res = 0.0;
    if (x == S21_NAN) res = S21_NAN;
    if (x == -S21_NAN) res = -S21_NAN;
    if (x == S21_INFINITY) res = S21_M_PI / 2;
    if (x == -S21_INFINITY) res = -S21_M_PI / 2;
    if (x == -1.) res = -S21_M_PI / 4;
    if (x == 1.) res = S21_M_PI / 4;
    if (res == 0.0) {
        if (s21_fabs(x) < 1) {
            for (int i = 0; i < 250; i++) {
                res += s21_pow(-1, i) * s21_pow(x, 1 + (2 * i)) / (1 + (2 * i));
            }
        } else {
            for (int i = 0; i < 250; i++) {
                res +=
                    s21_pow(-1, i) * s21_pow(x, -1 - (2 * i)) / (1 + (2 * i));
            }
            res = S21_M_PI * s21_sqrt(x * x) / (2 * x) - res;
        }
    }
    return res;
}

long double s21_factorial(int x) {
    long double res = 0;
    if (x < 0) {
        res = 0;
    } else {
        if (x == 0) {
            res = 1;
        } else {
            res = x * s21_factorial(x - 1);
        }
    }
    return res;
}
