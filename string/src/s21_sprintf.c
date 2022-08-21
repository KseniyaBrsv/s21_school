#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {  // функция с переменным количеством аргументов
    setlocale(LC_ALL, "");
    setlocale(LC_ALL, "en_US.UTF-8");
    va_list ap;  // указатель на переменные, которые будут приниматься
    va_start(ap, format);  // определение списка параметров, которые идут после format
    str[0] = '\0';
    char *str_0 = str;
    int counter = 0;
    while (*format != '\0') {
        struct forms new;
        s21_init(&new);
        int len = 0, shift = 0;
        if (*format != '%') {  // считываем до '%'
            *str = *format;
            str++;
            counter++;
            format++;
        } else if (*++format == '%') {
            format += 1;  // считываем символ
            *str++ = '%';  // записываем % в буфер
            counter++;
        } else {
            len = parse(&new, format);  // парсер показывает были ли включены флаги
        }
        if (new.type != '\0') {
            shift = check_type(&new, str, ap, &shift);  // тип данных
            str += shift;
            counter +=shift;
        }
        format += len;
    }
    *str = '\0';
    va_end(ap);
    return (int) (str - str_0);
}

void s21_init(struct forms *p) {
    p->minus = 0;
    p->plus = 0;
    p->space = 0;
    p->width = 0;
    p->precision = 0;
    p->flag_precision = 0;
    p->length = 0;
    p->type = '\0';
    p->zero = 0;
}

// %[flags][width][.precision][length]specifier
int parse(struct forms *p, const char *format) {
    int len = 0, temp = 0;
    while (*format != '%' && *format != '\0' && p->type == '\0') {
        if (!p->width && !p->precision && !p->length && !p->type) {
            temp = 0;
            temp += parse_flags(p, format);
            len += temp;
            format += temp;
        }
        if (!p->width && !p->precision) {
            temp = 0;
            temp += parse_width(p, format);
            len += temp;
            format += temp;
        }
        if (!p->precision) {
            temp = 0;
            temp += parse_precision(p, format);
            len += temp;
            format += temp;
        }
        if (!p->length) {
            temp = 0;
            temp += parse_length(p, format);
            len += temp;
            format += temp;
        }
        if (!p->type) {
            temp = 0;
            temp += parse_type(p, format);
            len += temp;
            format += temp;
        }
    }
    return len;
}

int parse_flags(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    switch (*str) {
        case '-':
            p->minus = 1;
            len += 1;
            break;
        case '+':
            p->plus = 1;
            len += 1;
            break;
        case ' ':
            p->space = 1;
            len += 1;
            break;
        case '0':
            p->zero = 1;
            len += 1;
            break;
    }
    return len;
}

int parse_width(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    int tempNum = 0;
    while (*str >= '0' && *str <= '9') {
            tempNum = (*str - 48) + (tempNum * 10);
            str++;
            len += 1;
    }
    p->width = tempNum;
    return len;
}

int parse_precision(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    int tempNum = 0;
    if (*str == '.') {
        p->flag_precision = 1;
        len += 1;
        while (*(str + 1) >= '0' && *(str + 1) <= '9') {
            tempNum = (*(str+1) - 48) + (tempNum * 10);
            len += 1;
            str += 1;
        }
    }
    p->precision = tempNum;
    return len;
}

int parse_length(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    switch (*str) {
        case 'h':
            p->length = 1;
            len += 1;
            break;
        case 'l':
            p->length = -1;
            len += 1;
            break;
    }
    return len;
}

int parse_type(struct forms *p, const char *format) {
    const char *str = format;
    int len = 0;
    if (*str == 'd' || *str == 'i' || *str == 'u' || *str == 'o' ||
        *str == 'x' || *str == 'X' || *str == 'e' || *str == 'E' ||
        *str == 'g' || *str == 'G' || *str == 'c' || *str == 's' ||
        *str == 'p' || *str == 'n' || *str == 'f') {
        p->type = *str;
        len += 1;
    }
    return len;
}

int check_type(struct forms *p, char *str, va_list arg, int *shift) {
    if (p->type == 's') {  // Строка символов
        *shift = parse_s(p, str, arg);
    } else if (p->type == 'c') {  // Символ
        *shift = parse_c(p, str, arg);
    } else if (p->type == 'd' || p->type == 'i') {  // Знаковое десятичное целое число
        *shift = d_to_string(p, str, arg);
    } else if (p->type == 'f') {  // Десятичное число с плавающей точкой
        *shift = f_to_string(p, str, arg);
    } else if (p->type == 'u') {  // Беззнаковое десятичное целое число
        *shift = u_to_string(p, str, arg);
    }
    return *shift;
}

void add_spaces_right(struct forms *p, char *str, int flag) {  // выравнивание по правому краю
    char *temp_array = (char*)calloc(1024, sizeof(char));
    if (temp_array == s21_NULL) {
        exit(0);
    }
    int counter = (int)p->width - (int)s21_strlen(str);
    for (int i = 0; i < counter; i++) {
        if (flag == 1) {
            temp_array[i] = ' ';  // добавляем пробелы ширины, если нужно
        }
    }
    temp_array[counter] = '\0';
    s21_strcat(str, temp_array);  // соединяем буфер с данными
    free(temp_array);
}

void add_spaces_or_zeros_left(char *buffer, int dif, int flag) {
    char *temp_array = (char*)calloc(1024, sizeof(char));
    if (temp_array == s21_NULL) {
        exit(0);
    }
    for (int i = 0; i < dif; i++) {
        if (flag == 1) {  // добавляем пробелы ширины, если нужно
            temp_array[i] = ' ';
        } else if (flag == 0) {
            temp_array[i] = '0';
        }
    }
    temp_array[dif] = '\0';
    s21_strcat(temp_array, buffer);
    int counter = s21_strlen(temp_array);
    for (int j = 0; j < counter; j++) {
        buffer[j] = temp_array[j];
    }
    buffer[counter] = '\0';
    free(temp_array);
}

void reduce_after_precision(char *buffer, struct forms *p) {
    buffer[p->precision] = '\0';
}

int parse_c(struct forms *p, char *str, va_list arg) {
    int i = 0;
    if (p->length == -1) {
        wchar_t wc = va_arg(arg, wchar_t);
        i = wc_to_string(p, str, wc);
    } else {
        i = c_to_string(p, str, arg);
    }
    return i;
}

int wc_to_string(struct forms *p, char *str, wchar_t wc) {
    char temp[10] = {'\0'};
    char buffer[BUFFER_SIZE] = {'\0'};
    int count = 0, dif = 0;
    wcstombs(temp, &wc, 10);
    s21_strcpy(buffer, temp);
    if (!p->minus && p->width) {
        dif = p->width - s21_strlen(buffer);  // разница между входящей шириной и тем, что имеем
        add_spaces_or_zeros_left(buffer, dif, 1);
    } else if (p->width) {
        add_spaces_right(p, buffer, 1);
    }
    for (int j = 0; j < (int)s21_strlen(buffer); j++) str[j] = buffer[j];
    str[(int)s21_strlen(buffer)] = '\0';
    count = s21_strlen(str);
    return count;
}

int c_to_string(struct forms *p, char *str, va_list arg) {
int dif = 0, i = 0;
    char buffer[BUFFER_SIZE] = {'\0'};
    if ((p->width == 0 && p->minus == 0) || (p->width == 0 && p->minus != 0)) {
        *(str) = (char)va_arg(arg, int);  // получаем значение текущ параметра тип int, записываем в буфер
        i++;
    }
    if (p->minus == 0 && p->width != 0) {
        buffer[0] = (char)va_arg(arg, int);
        dif = p->width - s21_strlen(buffer);  // разница между входящей шириной и тем, что имеем
        add_spaces_or_zeros_left(buffer, dif, 1);  // справа
        s21_strcpy(str, buffer);
        i = s21_strlen(str);
    }
    if (p->minus != 0 && p->width != 0) {
        *(str) = (char) va_arg(arg, int);  // получаем знач текущ параметра тип int, записываем его в буфер
        add_spaces_right(p, str, 1);  // слева
        i = s21_strlen(str);
    }
    return i;
}

int parse_s(struct forms *p, char *str, va_list arg) {
int i = 0;
    if (p->length == -1) {
        wchar_t *ws = va_arg(arg, wchar_t *);
        if (ws == s21_NULL) {
            ws = L"(null)";
        }
        i = ws_to_string(p, str, ws);
    } else {
        char *argument = va_arg(arg, char *);  // получаем знач текущ параметра тип char, запис в арг
        i = s_to_string(p, str, argument);
    }
    return i;
}

int ws_to_string(struct forms *p, char *str, wchar_t *ws) {
    char temp[BUFFER_SIZE] = {'\0'};
    char buf[BUFFER_SIZE] = {'\0'};
    int len = 0;
    wcstombs(temp, ws, BUFFER_SIZE);
    s21_strcpy(buf, temp);
    if (p->precision) {
        reduce_after_precision(buf, p);
    }
    int shift = p->width - s21_strlen(buf);
    if (p->minus != 0 && shift > 0) {
        add_spaces_right(p, buf, 1);
    } else if (shift > 0) {
        add_spaces_or_zeros_left(buf, shift, 1);
    }
    for (int j = 0; j < (int)s21_strlen(buf) + 1; j++) str[j] = buf[j];
    len = s21_strlen(str);
    return len;
}

int s_to_string(struct forms *p, char *str, char *argument) {
    int i = 0;
    char buffer[BUFFER_SIZE] = {'\0'};
    int length_val = 0, length_add = 0;
    if (argument == s21_NULL) {
        argument = "(null)";
    }
    int size_of_arg = s21_strlen(argument);  // узнаем, какое кол-во символов в аргументе
    if (p->flag_precision && (p->precision == 0 || (p->precision == 0 && p->width))) {
        int dif = p->width - s21_strlen(buffer);
        add_spaces_or_zeros_left(buffer, dif, 1);
    } else {
    s21_strcat(buffer, argument);  // конкатенация буффера с аргументом
    if (p->precision < size_of_arg && p->precision) {
        reduce_after_precision(buffer, p);
        length_val = p->precision;
    } else {
        length_val = size_of_arg;
    }
    length_add = (length_val < p->width) ? p->width - length_val : s21_NULL;
    if (p->width && !p->minus) {
        add_spaces_or_zeros_left(buffer, length_add, 1);
    }
    if (p->width && p->minus && (p->width > (int)s21_strlen(buffer))) {
        add_spaces_right(p, buffer, 1);
    }
    }
    s21_strcpy(str, buffer);
    i = s21_strlen(str);
    return i;
}

void s21_ftoa(struct forms *p, char *str, long double num) {
    long double left = 0;
    long double right = modfl(num, &left);
    char str1[100] = {'\0'}, str2[100] = {'\0'};
    int diff = 0;

    if (num >= 0 || num <= -1) {
        s21_itoa(left, str1);
    } else {
        str1[0] = '-';
        str1[1] = '0';
    }

    if (p->flag_precision == 0) {
        p->precision = 6;
    }

    if (p->precision != 0) {
        if (right < 0) {
            right = right * -1;
        }
        if (right != 0) {
            right = right * pow(10, p->precision);
            right = roundl(right);
            if (right == (1 * pow(10, p->precision))) {
                (num >= 0) ? (left += 1) : (left -= 1);
                s21_itoa(left, str1);
            } else {
            s21_itoa(right, str2);
            }
            if ((int) s21_strlen(str2) < p->precision) {
                diff = p->precision - s21_strlen(str2);
                add_spaces_or_zeros_left(str2, diff, 0);
            }
        } else {
            for (int i = 0; i < p->precision; i++) {
                str2[i] = '0';
            }
        }
        s21_strcat(str, str1);
        s21_strcat(str, ".");
        s21_strcat(str, str2);
    } else {
        if (num < -1.0 || num > 0.0) {
            num = roundl(num);
            s21_itoa(num, str);
        }
    }
    free_array_2(str1, str2);
}

int f_to_string(struct forms *p, char *str, va_list arg) {
    long double num = va_arg(arg, double);
    char ftoaBuff[100] = {'\0'}, temp_buf[100] = {'\0'};
    int diff = 0;
    s21_ftoa(p, ftoaBuff, num);
    if ((p->plus == 1) && (num > 0)) {  // При флаге + указать знак явно
        temp_buf[0] = '+';
        s21_strcat(temp_buf, ftoaBuff);
         s21_memcpy(ftoaBuff, temp_buf, s21_strlen(temp_buf));
        free_array_1(temp_buf);
    }
    if (p->space && (!p->plus) && (num > 0)) {  // Если знак " ", то ставим в начало пробел
        temp_buf[0] = ' ';
        s21_strcat(temp_buf, ftoaBuff);
        s21_memcpy(ftoaBuff, temp_buf, s21_strlen(temp_buf));
        free_array_1(temp_buf);
    }
    if ((p->width > (int) s21_strlen(ftoaBuff)) && (!p->minus)) {  // Если ширина больше, чем длина строки
        diff = p->width - s21_strlen(ftoaBuff);  // и нет знака "-", то добавляем пробелы слева
        add_spaces_or_zeros_left(ftoaBuff, diff, 1);
    }
    if ((p->width > (int) s21_strlen(ftoaBuff)) && (p->minus)) {  // Если ширина больше, чем длина строки,
        s21_memcpy(temp_buf, ftoaBuff, s21_strlen(ftoaBuff));  // и есть знак "-", то передвигаем влево
        diff = p->width - s21_strlen(ftoaBuff);
        add_spaces_right(p, temp_buf, 1);
        s21_memcpy(ftoaBuff, temp_buf, s21_strlen(temp_buf));
        free_array_1(temp_buf);
    }
    s21_strcpy(str, ftoaBuff);
    return s21_strlen(str);
}

int d_to_string(struct forms *p, char *str, va_list arg) {
    long long int num = va_arg(arg, long long int);
    char dtoaBuff[200] = {'\0'}, temp_buf[200] = {'\0'};
    int diff1 = 0, diff2 = 0;

    if (p->length == -1) {  // Разбираемся с длиной
        num = (long long int) num;
    } else if (p->length == 1) {
        num = (short int) num;
    } else {
        num = (int) num;
    }
    if (num >= 0) {
        if (num != 0) s21_itoa(num, dtoaBuff);  // Переводим num в массив символов dtoaBuff
        if (num == LONG_MAX) {
            s21_strcpy(dtoaBuff, "9223372036854775807\0");
        }
        if (p->precision > (int)s21_strlen(dtoaBuff)) {
            diff1 = p->precision - s21_strlen(dtoaBuff);
            add_spaces_or_zeros_left(dtoaBuff, diff1, 0);
        }
        if (p->flag_precision == 0 && (p->zero) && (p->width)) {  // Обрабатываем флаг 0
            diff1 = p->width - s21_strlen(dtoaBuff);
            add_spaces_or_zeros_left(dtoaBuff, diff1, 0);
        }
        if (p->plus == 1) {  // При флаге + указать знак явно
            temp_buf[0] = '+';
            s21_strcat(temp_buf, dtoaBuff);
            s21_memcpy(dtoaBuff, temp_buf, s21_strlen(temp_buf));
            free_array_1(temp_buf);
        }
        if (p->space && (!p->plus)) {  // Если знак " ", то ставим в начало пробел
            temp_buf[0] = ' ';
            s21_strcat(temp_buf, dtoaBuff);
            s21_memcpy(dtoaBuff, temp_buf, s21_strlen(temp_buf));
            free_array_1(temp_buf);
        }
        if ((p->width > (int) s21_strlen(dtoaBuff)) && (!p->minus)) {  // Если ширина больше, чем длина строки
            diff2 = p->width - s21_strlen(dtoaBuff);   // и нет знака "-", то добавляем пробелы слева
            add_spaces_or_zeros_left(dtoaBuff, diff2, 1);
        }
        if ((p->width > (int) s21_strlen(dtoaBuff)) && (p->minus)) {  // Если ширина больше длины строки,
            s21_memcpy(temp_buf, dtoaBuff, s21_strlen(dtoaBuff));  // и есть знак "-", то передвигаем влево
            diff2 = p->width - s21_strlen(dtoaBuff);
            add_spaces_right(p, temp_buf, 1);
            s21_memcpy(dtoaBuff, temp_buf, s21_strlen(temp_buf));
            free_array_1(temp_buf);
        }
    }
    // Случай, когда число меньше 0, аналогично
    if (num < 0) {
        s21_itoa(num, dtoaBuff);  // Переводим num в массив символов dtoaBuff
        if (num == LONG_MIN) {
            s21_strcpy(dtoaBuff, "-9223372036854775808\0");
        }
        if (p->precision >= (int)s21_strlen(dtoaBuff)) {
            char temp_buf_1[100] = {'\0'};
            for (int i = 0; i < (int) s21_strlen(dtoaBuff) - 1; i++) {
                temp_buf_1[i] = dtoaBuff[i + 1];
            }
            temp_buf_1[s21_strlen(dtoaBuff) - 1] = '\0';
            diff1 = p->precision - s21_strlen(temp_buf_1);
            add_spaces_or_zeros_left(temp_buf_1, diff1, 0);
            temp_buf[0] = '-';
            s21_strcat(temp_buf, temp_buf_1);
            temp_buf[s21_strlen(temp_buf_1) + 1] = '\0';
            free_array_1(temp_buf_1);
            s21_memcpy(dtoaBuff, temp_buf, s21_strlen(temp_buf));
            dtoaBuff[s21_strlen(temp_buf)] = '\0';
            free_array_1(temp_buf);
        }
        if ((p->width > (int) s21_strlen(dtoaBuff)) && (!p->minus)) {
            diff2 = p->width - s21_strlen(dtoaBuff);
            add_spaces_or_zeros_left(dtoaBuff, diff2, 1);
        }
        if ((p->width > (int) s21_strlen(dtoaBuff)) && (p->minus)) {
            s21_memcpy(temp_buf, dtoaBuff, s21_strlen(dtoaBuff));
            diff2 = p->width - s21_strlen(dtoaBuff);
            add_spaces_right(p, temp_buf, 1);
            s21_memcpy(dtoaBuff, temp_buf, s21_strlen(temp_buf));
            free_array_1(temp_buf);
        }
    }
    s21_strcpy(str, dtoaBuff);
    return s21_strlen(str);
}

void s21_itoa_unsigned(unsigned long long num, char *str, unsigned int base) {
    unsigned long long power = 0, j = 0;
    j = num;
    for (power = 1; j >= base; j /= base)
        power *= base;

    for (; power > 0; power /= base) {
        if (num / power < 10) {
            *str++ = '0' + num / power;
        } else {
            *str++ = 'a' + num / power - 10;
        }
        num %= power;
    }
    *str = '\0';
}

int u_to_string(struct forms *p, char *str, va_list arg) {
    unsigned long long num = va_arg(arg, unsigned long long);
    char dtoaBuff[100] = {'\0'}, temp_buf[100] = {'\0'};
    int diff = 0;

    if (p->length == -1) {
        num = (unsigned long long) num;
    } else if (p->length == 1) {
        num = (unsigned short) num;
    } else {
        num = (unsigned int) num;
    }
    if (num > 0) {
        s21_itoa_unsigned(num, dtoaBuff, 10);  // Переводим num в массив символов dtoaBuff
    }
    if (p->flag_precision == 0 && (p->zero) && (p->width)) {  // Обрабатываем флаг 0
        diff = p->width - s21_strlen(dtoaBuff);
        add_spaces_or_zeros_left(dtoaBuff, diff, 0);
    }
    if (p->precision > (int)s21_strlen(dtoaBuff)) {
        diff = p->precision - s21_strlen(dtoaBuff);
        add_spaces_or_zeros_left(dtoaBuff, diff, 0);
    }
    if ((p->width > (int) s21_strlen(dtoaBuff)) && (!p->minus)) {  // Если ширина больше, чем длина строки
        diff = p->width - s21_strlen(dtoaBuff);     //  и нет знака "-", то добавляем пробелы слева
        add_spaces_or_zeros_left(dtoaBuff, diff, 1);
    }
    if ((p->width > (int) s21_strlen(dtoaBuff)) && (p->minus)) {  // Если ширина больше, чем длина строки,
        s21_memcpy(temp_buf, dtoaBuff, s21_strlen(dtoaBuff));  // и есть знак "-", то передвигаем влево
        diff = p->width - s21_strlen(dtoaBuff);
        add_spaces_right(p, temp_buf, 1);
        s21_memcpy(dtoaBuff, temp_buf, s21_strlen(temp_buf));
        free_array_1(temp_buf);
    }
    s21_strcpy(str, dtoaBuff);
    return s21_strlen(str);
}

void free_array_2(char *arr1, char *arr2) {
    for (int i = 0; i < 100; i++) {
        arr1[i] = '\0';
        arr2[i] = '\0';
    }
}

void free_array_1(char *arr1) {
    for (int i = 0; i < 100; i++) {
        arr1[i] = '\0';
    }
}
