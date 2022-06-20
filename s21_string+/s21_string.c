#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    s21_size_t i = 0;
    int f = 0;
    while (i < n) {
        if (*((unsigned char *) str + i) == (unsigned char) c) {
            f = 1;
            break;
        }
        i++;
    }
    return f == 1 ? ((void *)((unsigned char *)str + i)) : 0;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
    s21_size_t i = 0;
    int f = 0;
    while (i < n) {
        if (*((unsigned char *) str1 + i) != *((unsigned char *) str2 + i)) {
            f = 1;
            break;
        }
        i++;
    }
    return f == 1 ? ((int)(*((unsigned char *) str1 + i) - *((unsigned char *) str2 + i))) : (s21_NULL);
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    s21_size_t i = 0;
    while (i < n) {
        *((unsigned char *) dest + i) = *((unsigned char *) src + i);
        i++;
    }
    return (dest);
}

void *s21_memmove(void *dest, const void *src, s21_size_t len) {
    int f = 0;
    if (!dest && !src) f = 1;
    if (src > dest) {
        dest = s21_memcpy(dest, src, len);
    } else {
        while (len > 0) {
            *((unsigned char *) dest + len - 1) = *((unsigned char *) src + len - 1);
            len--;
        }
    }
    return f == 1 ? s21_NULL: dest;
}

void *s21_memset(void *str, int c, s21_size_t len) {
    while (len >= 1) {
        *((unsigned char *) str + len - 1) = (unsigned char) c;
        len--;
    }
    return (str);
}

char *s21_strcat(char *dest, const char *src) {
    int j = 0;
    s21_size_t dest_len = s21_strlen(dest);
    for (; src[j]; j++)
        dest[dest_len+j] = src[j];
    dest[dest_len+j] = '\0';
    return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {  // Добавление строки на n сиволов.
    s21_size_t j = 0;
    s21_size_t dest_len = s21_strlen(dest);
    for (; j < n && src[j]; j++)
        dest[dest_len+j] = src[j];
    dest[dest_len+j] = '\0';
    return dest;
}

char *s21_strchr(const char *str, int c) {  // Поиск первого вхождения символа в строке.
    s21_size_t i = 0;
    int f = 0;
    char *a = (char*) str;
    while (str[i] != '\0') {
        if (str[i] == c) {
            f = 1;
            break;
        }
        i++;
    }
    if (c == 0) f = 1;
    return (f == 1) ? (a + i) : s21_NULL;
}

int s21_strcmp(const char *str1, const char *str2) {  // Сравнение строк.
    const char *s1 = str1;
    const char *s2 = str2;
    int f = 0;
    while (*s1 == *s2) {
        if (*s1 == '\0') {  // Две строчки одинаковые.
            f = 1;
            break;
        }
        s1++;
        s2++;
    }
    return f == 1 ? s21_NULL : *(unsigned char*)s1 - *(unsigned char*)s2;
}  // Позиц законч стр или встрет различ между строк

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    unsigned char *s1 = (unsigned char*)str1;
    unsigned char *s2 = (unsigned char*)str2;
    s21_size_t i = 0;
    int f = 0;
    while ((s1[i] != '\0' || s2[i] != '\0') && i < n) {
        if (s1[i] != s2[i]) {
            f = 1;
            break;
        }
        i++;
    }
    return f == 1 ? s1[i] - s2[i] : s21_NULL;
}

char *s21_strcpy(char *dest, const char *src) {  // копирование строки
    s21_size_t i;
    if (*src == '\0') {
        *dest = '\0';
    }
    for (i = 0; *(src + i) != '\0'; i++) {
        *(dest + i) = (char) *(src + i);
    }
    *(dest + i) = '\0';
    return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    s21_size_t i;
    i = 0;
    while (src[i] != '\0' && i < n) {
        dest[i] = (char) src[i];
        i++;
    }
    while (i < n) {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t i, j, flag = 0;
    for (i = 0; i < s21_strlen(str1); i++) {
        for (j = 0; j < s21_strlen(str2); j++) {
            if (str1[i] == str2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }
    return i;
}

char *s21_strerror(int errnum) {
    static char *str_errors[] = s21_ERRORS;
    int max;
    char error[1000] = {'\0'};
    char space[100];
    static char final[1000] = {'\0'};
    for (int i = 0; i < 1000; i++) final[i] = '\0';
#if defined(__APPLE__) && defined(__MACH__)
    max = 106;
#else
    max = 133;
#endif
    if (errnum > max || errnum < 0) {
        #if defined(__APPLE__) && defined(__MACH__)
            char err[16] = "Unknown error: ";
        #else
            char err[16] = "Unknown error ";
        #endif
        s21_itoa(errnum, space);
        s21_strcpy(error, err);
        s21_strncat(error, space, s21_strlen(error));
    } else {
        s21_strcat(error, str_errors[errnum]);
    }
    s21_strcat(final, error);
    return final;
}

s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;
    for (; str[len]; len++) {
    }
    return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
    char *ptr = s21_NULL;
    if (str1 && str2) {
        if (str1 == str2) {
            ptr = (char*)str1;
        } else {
            for (s21_size_t i = 0; str1[i]; i++)
                if (s21_strchr(str2, str1[i])) {
                    ptr = (char*)(str1 + i);
                    break;
                }
        }
    }
    return ptr;
}

char *s21_strrchr(const char *str, int c) {
    char *result = s21_NULL;
    s21_size_t len = s21_strlen(str);

    for (int i = len; i >= 0; i--) {
        if (str[i] == c) {
            result = ((char *)str) + i;
            break;
        }
    }
    return result;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t  i = (s21_size_t) s21_NULL;
    if (str1 && str2) {
        i = s21_strlen(str1);
        if (str1 != str2) {
            for (i = 0; str1[i] && s21_strchr(str2, str1[i]); i++) ;
        }
    }
    return i;
}

char *s21_strstr(const char *haystack, const char *needle) {
    char *result = s21_NULL;
    if (!needle || !haystack) {
        result = s21_NULL;
    } else if (s21_strlen(needle) == 0 || needle == haystack) {
        result = (char *)haystack;
    } else {
        for (s21_size_t i = 0; haystack[i]; i++) {  // Пока не равно нулевому символу
            for (s21_size_t j = 0; needle[j] == haystack[i + j]; j++)
                if (!needle[j + 1]) {        // Когда заканч. строка needle ...
                    result = (char*)(haystack + i);
                    break;
                }
        }
    }
    return result;
}

char *s21_strtok(char *str, const char *delim) {
    int next_null = 0, flag;
    s21_size_t new_number = 0;
    char *end_of_line = s21_NULL;
    char *ptr = s21_NULL;
    char *res = s21_NULL;
    if (str) {
        flag = 1;
        new_number = 0;
        ptr = str + s21_strspn(str, delim);  // Пропускаем конечные разделители
        end_of_line = str + s21_strlen(str);  // Указатель на последний эл-т
    }
    if (!(ptr >= end_of_line || next_null)) {
        int non_delim = 1;
        for (int i = 0; ptr[i]; i++) {
            s21_size_t step = s21_strspn(ptr + i, delim);  // если разделителей больше 1
            if (step) {
                non_delim = 0;
                for (s21_size_t j = i; j < i + step; j++) ptr[j] = '\0';  // отрезаем кусок

                new_number = step + i;  // новый номера элемента
                break;
            }
        }
        if (flag == 1 && non_delim) next_null = 1;  // если не найдено разделителей

        res = ptr;   // Прежнее начало строки
        ptr += new_number;  // Новое начало строки
    }
    ++flag;
    return res;
}

void s21_itoa(long long int m, char *str) {
    if (m < 0) {
        m = m * (-1);
        long long int power = 0, j = 0;
        j = m;
        for (power = 1; j >= 10; j /= 10)
            power = power * 10;
        *str++ = '-';
        for (; power > 0; power /= 10) {
            *str++ = '0' + m / power;
            m %= power;
        }
        *str = '\0';
    } else {
        long long int power = 0, j = 0;
        j = m;
        for (power = 1; j >= 10; j /= 10) {
            power *= 10;
        }
        for (; power > 0; power /= 10) {
            *str++ = '0' + m / power;
            m %= power;
        }
        *str = '\0';
    }
}

void *s21_to_lower(const char *string) {
    char *str_copy = s21_NULL;
    if (string != s21_NULL) {
        s21_size_t len = s21_strlen(string);
        str_copy = (char *)calloc(len + 1, 1);
        if (str_copy) {
            for (s21_size_t i = 0; i <= len; i++) {
                if (string[i] >= 'A' && string[i] <= 'Z') {
                    str_copy[i] = (string[i] - 'A') + 'a';
                } else {
                    str_copy[i] = string[i];
                }
            }
            str_copy[len] = '\0';
        }
    }
    return str_copy;
}

void *s21_to_upper(const char *string) {
    char *str_copy = s21_NULL;
    if (string != s21_NULL) {
        s21_size_t len = s21_strlen(string);
        str_copy = (char *)calloc(len + 1, 1);
        if (str_copy) {
            for (s21_size_t i = 0; i <= len; i++) {
                if (string[i] >= 'a' && string[i] <= 'z') {
                    str_copy[i] = (string[i] - 'a') + 'A';
                } else {
                    str_copy[i] = string[i];
                }
            }
            str_copy[len] = '\0';
        }
    }
    return str_copy;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *string1 = s21_NULL;
    if (src != s21_NULL && str != s21_NULL) {
        s21_size_t new_len = 0;
        new_len = s21_strlen(src) + s21_strlen(str);
        if (s21_strlen(src) >= start_index) {
            string1 = (char *)calloc(100 + 1, 1);
        }
        if (string1) {
            s21_size_t i = 0, k = 0;
            while (src[i] != '\0' && (i < start_index)) {
                string1[i] = src[i];
                i++;
            }
            k = i;
            i = 0;
            while (str[i] != '\0') {
                string1[i + start_index] = str[i];
                i++;
            }
            for (i = i + start_index; i < new_len; i++) {
                string1[i] = src[k];
                k++;
            }
            string1[new_len]= '\0';
        }
    }
    return string1;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *result = s21_NULL;
    if (src) {
        if (trim_chars && *trim_chars) {
            s21_size_t len = s21_strlen(src);
            s21_size_t chars_len = s21_strlen(trim_chars);
            s21_trim_left(&src, trim_chars, &len, chars_len);
            if (len)
                s21_trim_right(&src, trim_chars, &len, chars_len);
            result = (char *)calloc(len + 1, 1);
            if (result) {
                for (s21_size_t i = 0; i < len + 1; i++) {
                    if (i < len) {
                        result[i] = src[i];
                    } else {
                        result[i] = '\0';
                    }
                }
            }
        }
    }
    return result;
}

void s21_trim_left(const char **src, const char *trim_chars,
                   s21_size_t *src_len, const s21_size_t trim_chars_len) {
    s21_size_t m = 0;
    while (src && m != trim_chars_len) {
        if ((**src) == trim_chars[m]) {
            (*src)++;
            (*src_len) -= 1;
            m = 0;
            continue;
        }
        m++;
    }
}

void s21_trim_right(const char **src, const char *trim_chars,
                    s21_size_t *src_len, const s21_size_t trim_chars_len) {
    s21_size_t m = 0;
    s21_size_t i = (*src_len) - 1;
    while (src && m != trim_chars_len) {
        if ((*src)[i] == trim_chars[m]) {
            i--;
            (*src_len)--;
            m = 0;
            continue;
        }
    m++;
    }
}
