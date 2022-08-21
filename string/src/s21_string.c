#include "s21_string.h"

// Поиск первого вхождения указанного символа в массиве
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

// Сравнение массивов
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

// Копирование непересекающихся массивов
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    s21_size_t i = 0;
    while (i < n) {
        *((unsigned char *) dest + i) = *((unsigned char *) src + i);
        i++;
    }
    return (dest);
}

// Копирование массивов (в том числе пересекающихся)
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

// Заполнения массива указанными символами.
void *s21_memset(void *str, int c, s21_size_t len) {
    while (len >= 1) {
        *((unsigned char *) str + len - 1) = (unsigned char) c;
        len--;
    }
    return (str);
}

// Слияние строк
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

// Поиск первого вхождения символа в строку
char *s21_strchr(const char *str, int c) {
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

// Сравнение строк
int s21_strcmp(const char *str1, const char *str2) {  // Сравнение строк
    const char *s1 = str1;
    const char *s2 = str2;
    int f = 0;
    while (*s1 == *s2) {
        if (*s1 == '\0') {  // Две строчки одинаковые
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

// Определение длины участка строки не содержащего указанные симв
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

// Поиск первого вхожд. в строку символа из указанного множества
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

// Поиск последнего вхождения символа в строку
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

// Опред максим длины участка строки, содерж только указанные симв
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

// поиск первого вхождения строки needle в строку haystack
char* s21_strstr(const char *haystack, const char *needle) {
    const char *res = s21_NULL;
    if (s21_strlen(needle) == 0) {
        res = haystack;
    } else {
        int flag = 0;  //  если найдена 1 буква needle, flag = 1
        const char *copy = needle;
        for (; *haystack && *needle; haystack++) {
            if (*haystack == *needle) {
                if (!flag) {
                    res = haystack;
                    flag = 1;
                }
                needle++;
            } else {
                needle = copy;
                flag = 0;
            }
        }
        if (*needle) res = s21_NULL;
    }
    return (char*)res;
}

// Разбиение строки на части по указанному разделителю
char *s21_strtok(char *str, const char *delim) {
    static char* buffer;
    char* token = s21_NULL;
    if (str) {
        buffer = str;
        while (*buffer && s21_strchr(delim, *buffer))
            *buffer++ = '\0';
    }
    if (buffer && *buffer) {
        str = buffer;
        while (*buffer && !s21_strchr(delim, *buffer)) {
            ++buffer;
        }
        while (*buffer && s21_strchr(delim, *buffer)) {
            *buffer++ = '\0';
        }
        token = str;
    }
    return token;
}

// Преобразует целое число в строку
void s21_itoa(long long int m, char *str) {
    if (m < 0) {
        if (m != LONG_MIN) {
            m = m * (-1);
            long long int power = 0, j = 0;
            j = m;
            for (power = 1; j >= 10; j /= 10)
                power = power * 10;
            *str = '-';
            str++;
            for (; power > 0; power /= 10) {
                *str++ = '0' + m / power;
                m %= power;
            }
            *str = '\0';
        }
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

// Выполняет преобраз прописных букв в строч
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

// Выполняет преобразование строчных букв в прописные
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

// Вставляет строку в строку в заданное место
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

// Удаляет начальные и конечные символы
void *s21_trim(const char *src, const char *trim_chars) {
    char* new_str = s21_NULL;
    if (src && trim_chars) {
        char* ptr_str = (char*)src;
        char* end_str = (char*)src + s21_strlen(src);
        for (; *ptr_str && s21_strchr(trim_chars, *ptr_str); ptr_str++) {
        }
        for (; end_str != ptr_str && s21_strchr(trim_chars, *(end_str - 1));
            end_str--) {
        }
        new_str = (char*)malloc((end_str - ptr_str + 1) * sizeof(char));
        if (new_str) {
            s21_strncpy(new_str, ptr_str, end_str - ptr_str);
            *(new_str + (end_str - ptr_str)) = '\0';
        }
    }
    return (void*)new_str;
}
