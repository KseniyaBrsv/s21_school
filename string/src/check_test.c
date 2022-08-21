#include <check.h>
#include <limits.h>

#include "s21_string.h"


char mass1[BUFFER_SIZE] = {'\0'};
char mass2[BUFFER_SIZE] = {'\0'};

void free_array(char *arr1, char *arr2) {
for (int i = 0; i < BUFFER_SIZE; i++) {
arr1[i] = '\0';
arr2[i] = '\0';
}
}

START_TEST(s21_memchr_ts) {
char dest1[100] = "Hello,";
char dest3[100] = "\0";
char src3[20] = "World!\n\0";
char src5[20] = "Wo\n\0rld!";
int ch1 = 'l';
char emp1[10] = " ";
ck_assert_ptr_eq(s21_memchr(dest1, ch1, 6), memchr(dest1, ch1, 6));
ck_assert_ptr_eq(s21_memchr(src3, '\n', 3), memchr(src3, '\n', 3));
ck_assert_ptr_eq(s21_memchr(src5, 'y', 8), memchr(src5, 'y', 8));
ck_assert_ptr_eq(s21_memchr(dest3, 'y', 4), memchr(dest3, 'y', 4));
ck_assert_ptr_eq(s21_memchr(dest3, 'y', 4), memchr(dest3, 'y', 4));
ck_assert_ptr_eq(s21_memchr(dest1, 'y', 0), memchr(dest1, 'y', 0));
ck_assert_ptr_eq(s21_memchr(dest1, 500, 2), memchr(dest1, 500, 2));
ck_assert_ptr_eq(s21_memchr(emp1, 500, 1), memchr(emp1, 500, 1));
ck_assert_ptr_eq(s21_memchr(emp1, 'k', 9), memchr(emp1, 'k', 9));
ck_assert_ptr_eq(s21_memchr(emp1, 0, 9), memchr(emp1, 0, 9));
ck_assert_ptr_eq(s21_memchr(dest1, 0, 1), memchr(dest1, 0, 1));
}
END_TEST

START_TEST(s21_memcmp_ts_1) {
free_array(mass1, mass2);
ck_assert_int_eq(s21_memcmp(mass1, mass2, 2), memcmp(mass1, mass2, 2));
ck_assert_uint_le(s21_memcmp(mass1, mass2, 10) * memcmp(mass1, mass2, 10), 1);
ck_assert_int_eq(s21_memcmp(mass1, mass2, 0), memcmp(mass1, mass2, 0));
free_array(mass1, mass2);
memset(mass1, 'y', 4);
ck_assert_uint_gt(s21_memcmp(mass1, mass2, 2) * memcmp(mass1, mass2, 2), 1);
ck_assert_uint_gt(s21_memcmp(mass1, mass2, 10) * memcmp(mass1, mass2, 10), 1);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_memcmp_ts_2) {
char dest3[100] = "\0";
char src2[20] = "World!";
char src3[20] = "World!\n\0";
char src4[20] = "World!\n\0";
char src5[20] = "Wo\n\0rld!";
char src6[20] = "Wo\n\0rld!";
char src7[20] = " \n\0";
char src8[20] = "\0";
ck_assert_int_eq(s21_memcmp(src3, src4, 4), memcmp(src3, src4, 4));
ck_assert_int_eq(s21_memcmp(src5, src6, 10), memcmp(src5, src6, 10));
ck_assert_uint_gt(s21_memcmp(dest3, src3, 10) * memcmp(dest3, src3, 10), 1);
ck_assert_uint_gt(s21_memcmp(src7, src8, 10)* memcmp(src7, src8, 10), 1);
ck_assert_uint_gt(s21_memcmp(src2, src3, 10)* memcmp(src2, src3, 10), 1);
}
END_TEST

START_TEST(s21_memcpy_ts_1) {
char dest1[100] = "Hello,";
char dest3[100] = "\0";
char src1[20] = "World!";
char src5[20] = "Wo\n\0rld!";
char src7[20] = " \n\0";
char src9[20] = "123456";
ck_assert_ptr_eq(s21_memcpy(dest1, src1, 3), memcpy(dest1, src1, 3));
ck_assert_ptr_eq(s21_memcpy(dest1, dest3, 1), memcpy(dest1, dest3, 1));
ck_assert_ptr_eq(s21_memcpy(src9, src7, 1), memcpy(src9, src7, 1));
ck_assert_ptr_eq(s21_memcpy(src5, src9, 2), memcpy(src5, src9, 2));
}
END_TEST

START_TEST(s21_memcpy_ts_2) {
ck_assert_str_eq(s21_memcpy(mass1, mass2, 11), memcpy(mass1, mass2, 11));
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_memcpy_ts_3) {
ck_assert_mem_eq(s21_memcpy(mass1, mass2, 10), mass2, 5);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_memcpy_ts_4) {
ck_assert_str_eq(s21_memcpy(mass1, mass2, 10), memcpy(mass1, mass2, 10));
ck_assert_str_eq(s21_memcpy(mass1, mass2, 8), memcpy(mass1, mass2, 8));
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_memmove_ts_1) {
char str1[100] = "123";
const  char str2[20] = " \0";
char src1[20] = "World!";
char src8[20] = "\0";
char src9[20] = "123456";
ck_assert_ptr_eq(s21_memmove(src9, src1, 5), memmove(src9, src1, 5));
ck_assert_ptr_eq(s21_memmove(src9, str2, 1), memmove(src9, str2, 1));
ck_assert_ptr_eq(s21_memmove(str1, str2, 1), memmove(str1, str2, 1));
ck_assert_ptr_eq(s21_memmove(src8, "1" , 1), memmove(src8, "1", 1));
ck_assert_ptr_eq(s21_memmove(src9, str1 , 6), memmove(src9, str1, 6));
}
END_TEST

START_TEST(s21_memmove_ts_2) {
ck_assert_str_eq(s21_memmove(mass1, mass2, 10), memmove(mass1, mass2, 10));
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_memset_ts_1) {
char dest1[100] = "Hello,";
char dest3[100] = "\0";
char src9[20] = "123456";
int ch1 = 'l';
ck_assert_ptr_eq(s21_memset(src9, ch1, 3), memset(src9, ch1, 3));
ck_assert_ptr_eq(s21_memset(dest3, '\n', 1), memset(dest3, '\n', 1));
ck_assert_ptr_eq(s21_memset(dest1, 'e', 2), memset(dest1, 'e', 2));
ck_assert_ptr_eq(s21_memset(src9, '\0', 3), memset(src9, '\0', 3));
ck_assert_ptr_eq(s21_memset(src9, '\n', 3), memset(src9, '\n', 3));
}
END_TEST

START_TEST(s21_memset_ts_2) {
s21_memset(mass1, 'k', 10);
memset(mass2, 'k', 10);
ck_assert_str_eq(s21_memset(mass1, 'k', 10), memset(mass1, 'k', 10));
free_array(mass1, mass2);

s21_memset(mass1, '4', 3);
memset(mass2, '4', 3);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);

s21_memset(mass1, '\0', 10);
memset(mass2, '\0', 10);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_strcat_ts) {
char dest1[100] = "Hello,";
char dest2[100] = "Hello,";
char dest3[100] = "\0";
char dest4[100] = "\0";
char src1[20] = "World!";
char src2[20] = "World!";
char src3[20] = "World!\n\0";
char src4[20] = "World!\n\0";
char src5[20] = "Wo\n\0rld!";
char src6[20] = "Wo\n\0rld!";
char src9[20] = "123456";
ck_assert_str_eq(s21_strcat(dest1, src1), strcat(dest2, src2));
ck_assert_str_eq(s21_strcat(dest1, src3), strcat(dest2, src4));
ck_assert_str_eq(s21_strcat(dest1, src5), strcat(dest2, src6));
ck_assert_str_eq(s21_strcat(dest3, src5), strcat(dest4, src6));
ck_assert_str_eq(s21_strcat(dest3, ""), strcat(dest4, ""));
ck_assert_str_eq(s21_strcat(dest3, src9), strcat(dest4, src9));
ck_assert_str_eq(s21_strcat(dest3, "1z"), strcat(dest4, "1z"));
}
END_TEST

START_TEST(s21_strncat_ts) {
char dest1[100] = "Hello,";
char dest2[100] = "Hello,";
char dest3[100] = "\0";
char dest4[100] = "\0";
char src5[20] = "Wo\n\0rld!";
char src6[20] = "Wo\n\0rld!";
char src9[20] = "123456";
s21_size_t n1 = 3;
size_t n2 = 3;
s21_size_t n3 = '\n';
size_t n4 = '\n';
ck_assert_str_eq(s21_strncat(dest1, " World!", n1),
                    strncat(dest2, " World!", n2));
ck_assert_str_eq(s21_strncat(dest1, " World!", n3),
                    strncat(dest2, " World!", n4));
ck_assert_str_eq(s21_strncat(dest1, src5, n3), strncat(dest2, src6, n4));
ck_assert_str_eq(s21_strncat(dest1, "1z", 3), strncat(dest2, "1z", 3));
ck_assert_str_eq(s21_strncat(dest1, "", 1), strncat(dest2, "", 1));
ck_assert_str_eq(s21_strncat(dest1, "1z", 3), strncat(dest2, "1z", 3));
ck_assert_str_eq(s21_strncat(dest1, "", 0), strncat(dest2, "", 0));
ck_assert_str_eq(s21_strncat(dest3, src9, 2), strncat(dest4, src9, 2));
ck_assert_str_eq(s21_strncat(dest3, "\0", 6), strncat(dest4, "\0", 6));
}
END_TEST

START_TEST(s21_strchr_ts) {
char dest1[100] = "Hello,";
char src1[20] = "World!";
int ch1 = 'l';
char str[] = "a\n\0";
int c = '\0';
char *s1 = "QWERTY";
char s2 = 'E';
ck_assert_str_eq(s21_strchr(src1, ch1), strchr(src1, ch1));
ck_assert_ptr_eq(s21_strchr(" ", ' '), strchr(" ", ' '));
ck_assert_str_eq(s21_strchr("0123456789", '6'), strchr("0123456789", '6'));
ck_assert_str_eq(s21_strchr(dest1, 0), strchr(dest1, 0));
ck_assert_str_eq(s21_strchr(dest1, '\0'), strchr(dest1, '\0'));
ck_assert_ptr_eq(s21_strchr(dest1, 'b'), NULL);
ck_assert_ptr_eq(strrchr(str, c), s21_strrchr(str, c));
ck_assert_pstr_eq(strrchr(s1, s2), s21_strrchr(s1, s2));
}
END_TEST

START_TEST(s21_strcmp_ts) {
char emp1[10] = " ";
char emp2[10] = " ";
char dest1[100] = "Hello,";
char dest2[100] = "Hello,";
char src1[20] = "World!";
char src2[20] = "World!";
char src3[20] = "World!\n\0";
char src4[20] = "World!\n\0";
char src5[20] = "Wo\n\0rld!";
char src6[20] = "Wo\n\0rld!";
ck_assert_int_eq(s21_strcmp("Hello", "Hello"), strcmp("Hello", "Hello"));
ck_assert_int_gt(s21_strcmp(dest1, src1) * strcmp(dest2, src2), 0);
ck_assert_int_eq(s21_strcmp("", ""), strcmp("", ""));
ck_assert_int_gt(s21_strcmp(dest1, src3) * strcmp(dest2, src4), 0);
ck_assert_int_eq(s21_strcmp(src3, src4), strcmp(src5, src6));
ck_assert_int_gt(s21_strcmp(emp1, src4) * strcmp(emp2, src6), 0);
ck_assert_int_gt(s21_strcmp(emp1, "Hello.") * strcmp(emp2, "Hello."), 0);
}
END_TEST

START_TEST(s21_strncmp_ts) {
char dest1[100] = "Hello,";
char dest2[100] = "Hello,";
char src1[20] = "World!";
char src2[20] = "World!";
char emp1[10] = " ";
char emp2[10] = " ";
ck_assert_int_eq(s21_strncmp(dest1, "Hello,", 2), strncmp(dest2, "Hello,", 2));
ck_assert_int_gt(s21_strncmp(emp1, "Hello", 5) * strncmp(emp2, "Hello", 5), 0);
ck_assert_int_eq(s21_strncmp("", "", 5), strncmp("", "", 5));
ck_assert_int_eq(s21_strncmp(dest1, "Hello.", 5), strncmp(dest2, "Hello.", 5));
ck_assert_int_gt(s21_strncmp(src1, "Hello.", 5)
                    * strncmp(src2, "Hello.", 5), 0);
}
END_TEST

START_TEST(s21_strcpy_ts_1) {
char dest1[100] = "Hello,";
char dest2[100] = "Hello,";
ck_assert_str_eq(s21_strcpy(mass1, "1234567890"), strcpy(mass2, "1234567890"));
ck_assert_str_eq(s21_strcpy(mass1, ""), strcpy(mass2, ""));
ck_assert_str_eq(s21_strcpy(dest1, "\0"), strcpy(dest2, "\0"));
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_strcpy_ts_2) {
char dest_strcpy_ts_1[100] = {'\0'};
char dest_strcpy_ts_2[100] = {'\0'};
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "1234567890"),
                                strcpy(dest_strcpy_ts_2, "1234567890"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, ""),
                                strcpy(dest_strcpy_ts_2, ""));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "\0"),
                                strcpy(dest_strcpy_ts_2, "\0"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "Wo\n\0rld!"),
                                strcpy(dest_strcpy_ts_2, "Wo\n\0rld!"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "  \n\0"),
                                strcpy(dest_strcpy_ts_2, "  \n\0"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "\n\0sdf"),
                                strcpy(dest_strcpy_ts_2, "\n\0sdf"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "~fg"), strcpy(dest_strcpy_ts_2, "~fg"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, " - =<ks\0\t"), strcpy(dest_strcpy_ts_2, " - =<ks\0\t"));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "#!-\0  "), strcpy(dest_strcpy_ts_2, "#!-\0  "));
ck_assert_str_eq(s21_strcpy(dest_strcpy_ts_1, "\n%$asd \0 \n"), strcpy(dest_strcpy_ts_2, "\n%$asd \0 \n"));
}
END_TEST

START_TEST(s21_strncpy_ts) {
ck_assert_str_eq(s21_strncpy(mass1, "012345678", 10), strncpy(mass2, "012345678", 10));
ck_assert_str_eq(s21_strncpy(mass1, "", 10), strncpy(mass2, "", 10));
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_strcspn_ts) {
ck_assert_int_eq(s21_strcspn("1234567890", "567"), strcspn("1234567890", "567"));
ck_assert_int_eq(s21_strcspn("Wo\n\0rld!", "rld"), strcspn("Wo\n\0rld!", "rld"));
ck_assert_int_eq(s21_strcspn(" - =<ks\0\t", "\t"), strcspn(" - =<ks\0\t", "\t"));
ck_assert_int_eq(s21_strcspn("#!-\0  ", " "), strcspn("#!-\0  ", " "));
ck_assert_int_eq(s21_strcspn(" 1", "as"), strcspn(" 1", "as"));
ck_assert_int_eq(s21_strcspn("\n\0 ", " "), strcspn("\n\0 ", " "));
ck_assert_int_eq(s21_strcspn(" - =<ks\0\t", "\t"), strcspn(" - =<ks\0\t", "\t"));
ck_assert_int_eq(s21_strcspn("#!-\0  ", "32# "), strcspn("#!-\0  ", "32# "));
ck_assert_int_eq(s21_strcspn("\0", "\0"), strcspn("\0", "\0"));
ck_assert_int_eq(s21_strcspn("\0", "as"), strcspn("\0", "as"));
}
END_TEST

START_TEST(s21_strerror_ts) {
for(int i = -1000; i < 150; i++) {
ck_assert_str_eq(s21_strerror(i), strerror(i));}
ck_assert_str_eq(s21_strerror(-44), strerror(-44));
ck_assert_str_eq(s21_strerror(12345), strerror(12345));
}
END_TEST

START_TEST(s21_strlen_ts) {
char dest3[100] = "\0";
char dest4[100] = "\0";
char src5[20] = "Wo\n\0rld!";
char src6[20] = "Wo\n\0rld!";
ck_assert_int_eq(s21_strlen("World\0"), strlen("World\0"));
ck_assert_uint_eq(s21_strlen("World\n"), strlen("World\n"));
ck_assert_int_eq(s21_strlen("World \0 Hello"), strlen("World "));
ck_assert_int_eq(s21_strlen(""), strlen(""));
ck_assert_int_eq(s21_strlen(dest3), strlen(dest4));
ck_assert_int_eq(s21_strlen(src5), strlen(src6));
ck_assert_int_eq(s21_strlen("\n\0sdf"), strlen("\n\0sdf"));
ck_assert_int_eq(s21_strlen("#!-\0  "), strlen("#!-\0  "));
ck_assert_int_eq(s21_strlen("\0"), strlen("\0"));
ck_assert_int_eq(s21_strlen(" \n\0"), strlen(" \n\0"));
ck_assert_int_eq(s21_strlen("\0World\0"), strlen("\0World\0"));
ck_assert_int_eq(s21_strlen("--1/0afawe\0wfw~4"), strlen("--1/0afawe\0wfw~4"));
}
END_TEST

START_TEST(s21_strpbrk_ts) {
const  char *str1 = "is";
const  char *str2 = "this is a test";
const  char *str3 = "";
const  char *str4 = "\0";
const  char *str5 = "\0World\0";
const  char *str6 = "\b\n\0";
const  char *str7 = "World\n";

ck_assert_ptr_eq(s21_strpbrk(str2, str1), strpbrk(str2, str1));
ck_assert_ptr_eq(s21_strpbrk(str1, s21_NULL), s21_NULL);
ck_assert_ptr_eq(s21_strpbrk(str1, str1), strpbrk(str1, str1));
ck_assert_ptr_eq(s21_strpbrk(str5, str4), strpbrk(str5, str4));
ck_assert_ptr_eq(s21_strpbrk(str3, str4), strpbrk(str3, str4));
ck_assert_ptr_eq(s21_strpbrk(str2, str4), strpbrk(str2, str4));
ck_assert_ptr_eq(s21_strpbrk(str2, str3), strpbrk(str2, str3));
ck_assert_ptr_eq(s21_strpbrk(str2, str4), strpbrk(str2, str4));
ck_assert_ptr_eq(s21_strpbrk(str2, str6), strpbrk(str2, str6));
ck_assert_ptr_eq(s21_strpbrk(str7, str5), strpbrk(str7, str5));
}
END_TEST

START_TEST(s21_strrchr_ts) {
const  char *str1 = "Hello world\0";
int c1 = ' ';
const  char *str2 = "--1/0afawe\0wfw~4";
int c2 = 'w';
const  char *str3 = "";
int c3 = '\0';
const  char *str4 = "  \0";
int c4 = ' ';
const  char *str5 = "\0World\n\0";
int c5 = '\n';
ck_assert_ptr_eq(s21_strrchr(str1, c1), strrchr(str1, c1));
ck_assert_ptr_eq(s21_strrchr(str2, c2), strrchr(str2, c2));
ck_assert_ptr_eq(s21_strrchr(str3, c3), strrchr(str3, c3));
ck_assert_ptr_eq(s21_strrchr(str5, c5), strrchr(str5, c5));
ck_assert_ptr_eq(s21_strrchr(str5, c5), strrchr(str5, c5));
ck_assert_str_eq(s21_strrchr(str4, c4), strrchr(str4, c4));
}
END_TEST

START_TEST(s21_strspn_ts) {
const  char *str1 = "1234567890";
const  char *str2 = "567";
ck_assert_int_eq(s21_strspn(str1, str2), strspn(str1, str2));
ck_assert_int_eq(s21_strspn("Wo\n\0rld!", "rld"), strspn("Wo\n\0rld!", "rld"));
ck_assert_int_eq(s21_strspn(" - =<ks\0\t", "\t"), strspn(" - =<ks\0\t", "\t"));
ck_assert_int_eq(s21_strspn("#!-\0  ", " "), strspn("#!-\0  ", " "));
ck_assert_int_eq(s21_strspn(" 1", "as"), strspn(" 1", "as"));
ck_assert_int_eq(s21_strspn("\n\0 ", " "), strspn("\n\0 ", " "));
ck_assert_int_eq(s21_strspn(" - =<ks\0\t", "\t"), strspn(" - =<ks\0\t", "\t"));
ck_assert_int_eq(s21_strspn("#!-\0  ", "32# "), strspn("#!-\0  ", "32# "));
ck_assert_int_eq(s21_strspn("\0", "\0"), strspn("\0", "\0"));
ck_assert_int_eq(s21_strspn("\0", "as"), strspn("\0", "as"));
}
END_TEST

START_TEST(s21_strstr_ts) {
ck_assert_ptr_eq(s21_strstr("Wo\n\0rld!", "rld"), strstr("Wo\n\0rld!", "rld"));
ck_assert_ptr_eq(s21_strstr("1234567890", "567"), strstr("1234567890", "567"));
ck_assert_ptr_eq(s21_strstr("Wo\n\0rldrldrld!", "rld"), strstr("Wo\n\0rldrldrld!", "rld"));
ck_assert_ptr_eq(s21_strstr(" - =<ks\0\t", "\t"), strstr(" - =<ks\0\t", "\t"));
ck_assert_ptr_eq(s21_strstr("#!-\0  ", " "), strstr("#!-\0  ", " "));
ck_assert_ptr_eq(s21_strstr(" 1as123as", "as"), strstr(" 1as123as", "as"));
ck_assert_ptr_eq(s21_strstr("\n\0 ", " "), strstr("\n\0 ", " "));
ck_assert_ptr_eq(s21_strstr(" - =<ks\0\t", "\t"), strstr(" - =<ks\0\t", "\t"));
ck_assert_ptr_eq(s21_strstr("#!-\0  ", "32# "), strstr("#!-\0  ", "32# "));
ck_assert_ptr_eq(s21_strstr("\0", "\0"), strstr("\0", "\0"));
ck_assert_ptr_eq(s21_strstr("\0", "as"), strstr("\0", "as"));
}
END_TEST

START_TEST(s21_strtok_ts) {
char mass11[100] = "1/2/3/4", mass12[100] = "77683-2768-178",
mass13[100] = "7 768 3-27 \0s68-17 8", mass14[100] = "7 *768 3*-27 6*8-17 8", mass15[100] = "\0";
char mass21[100] = "/", mass22[100] = "-", mass23[100] = "- ", mass24[100] = "- *";
ck_assert_str_eq(s21_strtok(mass11, mass21), strtok(mass11, mass21));
ck_assert_str_eq(s21_strtok(mass12, mass22), strtok(mass12, mass22));
ck_assert_str_eq(s21_strtok(mass11, mass22), strtok(mass11, mass22));
ck_assert_str_eq(s21_strtok(mass13, mass23), strtok(mass13, mass23));
ck_assert_str_eq(s21_strtok(mass14, mass24), strtok(mass14, mass24));
ck_assert_str_eq(s21_strtok(mass11, mass24), strtok(mass11, mass24));
ck_assert_str_eq(s21_strtok(mass11, mass23), strtok(mass11, mass23));
ck_assert_str_eq(s21_strtok(mass11, mass21), strtok(mass11, mass21));
ck_assert_str_eq(s21_strtok(mass14, mass22), strtok(mass14, mass22));
ck_assert_ptr_eq(s21_strtok(mass15, mass22), strtok(mass15, mass22));
ck_assert_ptr_eq(s21_strtok(mass13, mass15), strtok(mass13, mass15));
}
END_TEST

START_TEST(s21_sprintf_ts_1) {
char mass1[100] = {'\0'};
char mass2[100] = {'\0'};
sprintf(mass1, "aaa%.2sbbb _% dldkl %-1d%f", "Hello", 5, 232, 1.23223);
s21_sprintf(mass2, "aaa%.2sbbb _% dldkl %-1d%f", "Hello", 5, 232, 1.23223);
ck_assert_str_eq(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_ts_2) {
sprintf(mass1, "%s %d %c", "one", 2, '3');
s21_sprintf(mass2, "%s %d %c", "one", 2, '3');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_ts_3) {
s21_sprintf(mass1, "% d %s %.3s %s", -2, "Hello", " world", "!");
sprintf(mass2, "% d %s %.3s %s", -2, "Hello", " world", "!");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_4) {
s21_sprintf(mass1, "%c %c %c", ' ', '#', '@');
sprintf(mass2, "%c %c %c", ' ', '#', '@');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_5) {
sprintf(mass1, "%-1c %-c", 'H', 'z');
s21_sprintf(mass2, "%-1c %-c", 'H', 'z');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_6) {
sprintf(mass1, "%c", 'Z');
s21_sprintf(mass2, "%c", 'Z');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_7) {
sprintf(mass1, "%c", '0' + 5);
s21_sprintf(mass2, "%c", '0' + 5);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_8) {
sprintf(mass1, " Char: %c", '0' + 5);
s21_sprintf(mass2, " Char: %c", '0' + 5);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_9) {
sprintf(mass1, "%10c", 'Z');
s21_sprintf(mass2, "%10c", 'Z');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_10) {
sprintf(mass1, "%-10c", 'Z');
s21_sprintf(mass2, "%-10c", 'Z');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_11) {
sprintf(mass1, "%c %-c %c %c", 'Z', '5', 'Z', '5');
s21_sprintf(mass2, "%c %-c %c %c", 'Z', '5', 'Z', '5');
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_c_ts_12) {
    sprintf(mass1, "%c %-c %c %c", 'Z', '5', 'Z', '5');
    s21_sprintf(mass2, "%c %-c %c %c", 'Z', '5', 'Z', '5');
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_wc_ts_12_1) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    char *format = "This is a simple wide char %5c";
    char w = 'c';
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_wc_ts_12_2) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    char *format = "This is a simple wide char %-5lc";
    unsigned long w = L'森';
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_s_ts_13) {
    sprintf(mass1, "%.1s", "Hello");
    s21_sprintf(mass2, "%.1s", "Hello");
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_14) {
    sprintf(mass1, "%7s", "Hello");
    s21_sprintf(mass2, "%7s", "Hello");
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_15) {
sprintf(mass1, "%-10s", "Hello");
s21_sprintf(mass2, "%-10s", "Hello");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_16) {
sprintf(mass1, "%s", "Hello");
s21_sprintf(mass2, "%s", "Hello");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_18) {
sprintf(mass1, "%.1s", "123.45678");
s21_sprintf(mass2, "%.1s", "123.45678");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_19) {
sprintf(mass1, "%15.14s", "123.45678");
s21_sprintf(mass2, "%15.14s", "123.45678");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_20) {
sprintf(mass1, "%-15.2s", "123.45678");
s21_sprintf(mass2, "%-15.2s", "123.45678");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_s_ts_21) {
sprintf(mass1, "%-15.2s", "123.45678");
s21_sprintf(mass2, "%-15.2s", "123.45678");
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_ws_ts_21_1) {
    char data[3000];
    char data1[3000];
    wchar_t buf[100] = L"hello";
    s21_sprintf(data, "%ls", buf);
    sprintf(data1, "%ls", buf);
    ck_assert_str_eq(data, data1);
}
END_TEST

START_TEST(s21_sprintf_ws_ts_21_2) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    char *format = "This is a simple wide char %ls";
    wchar_t w[] = L"森我爱菠萝";
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_ws_ts_21_3) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    char *format = "This is a simple wide char %5.12ls";
    wchar_t w[] = L"森我爱菠萝";
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_ws_ts_21_4) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    char *format = "This is a simple wide char %120ls ABOBA";
    wchar_t w[] = L"森我爱菠萝";
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}
END_TEST

START_TEST(s21_sprintf_ws_ts_21_5) {
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    char *format = "This is a simple wide char %-43ls";
    wchar_t w[] = L"森我爱菠萝";
    int a = s21_sprintf(str1, format, w);
    int b = sprintf(str2, format, w);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(a, b);
}

START_TEST(s21_sprintf_i_ts_22) {
sprintf(mass1, "%i", 123);
s21_sprintf(mass2, "%i", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_i_ts_23) {
short v = 5;
sprintf(mass1, "%hi", v);
s21_sprintf(mass2, "%hi", v);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_i_ts_24) {
sprintf(mass1, "% i", 123);
s21_sprintf(mass2, "% i", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_25) {
sprintf(mass1, "%+d", 123);
s21_sprintf(mass2, "%+d", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_26) {
sprintf(mass1, "%-5.8d", -123);
s21_sprintf(mass2, "%-5.8d", -123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_27) {
char mass1[BUFFER_SIZE] = {'\0'};
char mass2[BUFFER_SIZE] = {'\0'};
sprintf(mass1, "%2.0d", 0);
s21_sprintf(mass2, "%2.0d", 0);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_28) {
char mass1[BUFFER_SIZE] = {'\0'};
char mass2[BUFFER_SIZE] = {'\0'};
sprintf(mass1, "%4d", 123);
s21_sprintf(mass2, "%4d", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_29) {
sprintf(mass1, "qwer%-4d fr", 123);
s21_sprintf(mass2, "qwer%-4d fr", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_30) {
sprintf(mass1, "%-+d", 123);
s21_sprintf(mass2, "%-+d", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_31) {
sprintf(mass1, "dede %-6d", 123);
s21_sprintf(mass2, "dede %-6d", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_32) {
sprintf(mass1, "%4d", -123);
s21_sprintf(mass2, "%4d", -123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_33) {
long int key_d = 123456789012;
sprintf(mass1, "%ld", key_d);
s21_sprintf(mass2, "%ld", key_d);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_34) {
sprintf(mass1, "%-4d", -123);
s21_sprintf(mass2, "%-4d", -123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_35) {
sprintf(mass1, "%6d", -123);
s21_sprintf(mass2, "%6d", -123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_36) {
sprintf(mass1, "%2.0d", 0);
s21_sprintf(mass2, "%2.0d", 0);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_37) {
sprintf(mass1, "qw%-6d", -123);
s21_sprintf(mass2, "qw%-6d", -123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_38) {
sprintf(mass1, "%4.2d", 123);
s21_sprintf(mass2, "%4.2d", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_39) {
sprintf(mass1, "%4.0d", 123);
s21_sprintf(mass2, "%4.0d", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_40) {
sprintf(mass1, "Hello, %d!", 123);
s21_sprintf(mass2, "Hello, %d!", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_41) {
sprintf(mass1, "%d%%\n", 4);
s21_sprintf(mass2, "%d%%\n", 4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_42) {
sprintf(mass1, "%.10d%%\n", 4);
s21_sprintf(mass2, "%.10d%%\n", 4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_43) {
sprintf(mass1, "%0d%%\n", -4);
s21_sprintf(mass2, "%0d%%\n", -4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_44) {
sprintf(mass1, "%-+10d%%\n", 4);
s21_sprintf(mass2, "%-+10d%%\n", 4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_45) {
sprintf(mass1, "asas%-10d%%\n", -4);
s21_sprintf(mass2, "asas%-10d%%\n", -4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_46) {
sprintf(mass1, "%+10d%%\n", 4);
s21_sprintf(mass2, "%+10d%%\n", 4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_47) {
sprintf(mass1, "%+10d%%\n", -4);
s21_sprintf(mass2, "%+10d%%\n", -4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_48) {
long int var_long = 100;
sprintf(mass1, "%ld%%\n", var_long);
s21_sprintf(mass2, "%ld%%\n", var_long);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_49) {
int key_d = -2;
sprintf(mass1, "qw%5.7d", key_d);
s21_sprintf(mass2, "qw%5.7d", key_d);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_50) {
short var_short = 123;
sprintf(mass1, "%hd%%\n", var_short);
s21_sprintf(mass2, "%hd%%\n", var_short);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_51) {
sprintf(mass1, "Hello, %-5d!", 123);
s21_sprintf(mass2, "Hello, %-5d!", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_52) {
sprintf(mass1, "%2.4d", -2);
s21_sprintf(mass2, "%2.4d", -2);
ck_assert_str_eq(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_53) {
sprintf(mass1, "%-5.8d", 123);
s21_sprintf(mass2, "%-5.8d", 123);
ck_assert_str_eq(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_d_ts_54) {
sprintf(mass1, "%d", -1234);
s21_sprintf(mass2, "%d", -1234);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_55) {
unsigned short n = 2;
unsigned long m = 33;
s21_sprintf(mass1, "%hu %lu %u", n, m, (unsigned)58432322);
sprintf(mass2, "%hu %lu %u", n, m, (unsigned)58432322);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_56) {
unsigned key_u = 0;
sprintf(mass1, "%2.0u", key_u);
s21_sprintf(mass2, "%2.0u", key_u);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_57) {
sprintf(mass1, "%u", 123);
s21_sprintf(mass2, "%u", 123);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_58) {
sprintf(mass1, "%2.5u%%\n", 4);
s21_sprintf(mass2, "%2.5u%%\n", 4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_59) {
sprintf(mass1, "%2.5u%%\n", -4);
s21_sprintf(mass2, "%2.5u%%\n", -4);
ck_assert_str_eq(mass1, mass2);
free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_60) {
    sprintf(mass1, "%10.5u%%\n", 4);
    s21_sprintf(mass2, "%10.5u%%\n", 4);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_61) {
    sprintf(mass1, "%10u%%\n", 421);
    s21_sprintf(mass2, "%10u%%\n", 421);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_62) {
    short unsigned key_h = 421;
    sprintf(mass1, "%-10hu%%\n", key_h);
    s21_sprintf(mass2, "%-10hu%%\n", key_h);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST


START_TEST(s21_sprintf_u_ts_63) {
    unsigned key_u = 0;
    sprintf(mass1, "%.0u", key_u);
    s21_sprintf(mass2, "%.0u", key_u);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_64) {
    unsigned key_u = 0;
    sprintf(mass1, "%2.0u", key_u);
    s21_sprintf(mass2, "%2.0u", key_u);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_65) {
    long unsigned key_l = 421;
    sprintf(mass1, "%-10lu%%\n", key_l);
    s21_sprintf(mass2, "%-10lu%%\n", key_l);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_u_ts_66) {
    sprintf(mass1, "%-10.0u", 3);
    s21_sprintf(mass2, "%-10.0u", 3);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_67) {
    double n = 7.0004522;
    s21_sprintf(mass1, "%f", n);
    sprintf(mass2, "%f", n);
    ck_assert_str_eq(mass1, mass2);
    free_array(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_68) {
    double n = -7.0004522;
    s21_sprintf(mass1, "%f", n);
    sprintf(mass2, "%f", n);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_69) {
    sprintf(mass1, "%lf", 123.456789);
    s21_sprintf(mass2, "%lf", 123.456789);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_70) {
    sprintf(mass1, "%lf", 123.456789);
    s21_sprintf(mass2, "%lf", 123.456789);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_71) {
    sprintf(mass1, "%lf", (double)123.456789);
    s21_sprintf(mass2, "%lf", (double)123.456789);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_72) {
    sprintf(mass1, "%f", 123.456789);
    s21_sprintf(mass2, "%f", 123.456789);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_73) {
    sprintf(mass1, "%.1f", 777.56);
    s21_sprintf(mass2, "%.1f", 777.56);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_74) {
    sprintf(mass1, "%-10.1f", 777.555);
    s21_sprintf(mass2, "%-10.1f", 777.555);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_75) {
    sprintf(mass1, "%f", -100000.4);
    s21_sprintf(mass2, "%f", -100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_76) {
    sprintf(mass1, "%+f %+f", -100000.4, 1000.231);
    s21_sprintf(mass2, "%+f %+f", -100000.4, 1000.231);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_77) {
    sprintf(mass1, "%-20f", 100000.4);
    s21_sprintf(mass2, "%-20f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_78) {
    sprintf(mass1, "%-+20f", 100000.4);
    s21_sprintf(mass2, "%-+20f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_79) {
    sprintf(mass1, "%-20f", -100000.4);
    s21_sprintf(mass2, "%-20f", -100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_80) {
    sprintf(mass1, "%+20f", 100000.4);
    s21_sprintf(mass2, "%+20f", 100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_81) {
    sprintf(mass1, "%+20f", -100000.4);
    s21_sprintf(mass2, "%+20f", -100000.4);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_82) {
    float key = 10000;
    sprintf(mass1, "%+20f", key);
    s21_sprintf(mass2, "%+20f", key);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_83) {
    float key_f = 9999.99999;
    sprintf(mass1, "%.1f", key_f);
    s21_sprintf(mass2, "%.1f", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_84) {
    sprintf(mass1, "% 10.1f", 777.555);
    s21_sprintf(mass2, "% 10.1f", 777.555);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_85) {
    sprintf(mass1, "% 10.0f", 777.555);
    s21_sprintf(mass2, "% 10.0f", 777.555);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_86) {
    float key_f = 777.555;
    sprintf(mass1, "%.0f", key_f);
    s21_sprintf(mass2, "%.0f", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_87) {
    float key_f = 777.555;
    sprintf(mass1, "%10.0f", key_f);
    s21_sprintf(mass2, "%10.0f", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_88) {
    float key_f = -1e10;
    sprintf(mass1, "%f", key_f);
    s21_sprintf(mass2, "%f", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_89) {
    double key_f = 123456789012;
    sprintf(mass1, "%.0lf", key_f);
    s21_sprintf(mass2, "%.0lf", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_90) {
    float key_f = 100000.4;
    sprintf(mass1, "%-12f", key_f);
    s21_sprintf(mass2, "%-12f", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_sprintf_f_ts_91) {
    float key_f = 777.555;
    sprintf(mass1, "%9.0f", key_f);
    s21_sprintf(mass2, "%9.0f", key_f);
    ck_assert_str_eq(mass1, mass2);
    free_array_2(mass1, mass2);
}
END_TEST

START_TEST(s21_to_upper_1) {
    char str1[] = "abc";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_2) {
    char str1[] = "aBc";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_3) {
    char str1[] = "abC";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_4) {
    char str1[] = "ABC";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_4_1) {
    char str1[] = "123";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "123");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_5) {
    char str1[] = "123abc";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "123ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_6) {
    char str1[] = "aBaBc";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_7) {
    char str1[] = ".,/.,/.,";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, ".,/.,/.,");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_8) {
    char str1[] = "09876abc";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "09876ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_9) {
    char str1[] = "abc123";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABC123");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_10) {
    char str1[] = " ";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, " ");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_11) {
    char str1[] = "";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_12) {
    char str1[] = "a1a1a1";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "A1A1A1");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_13) {
    char str1[] = " a1a1a1";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, " A1A1A1");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_14) {
    char str1[] = "a1a1a1 ";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "A1A1A1 ");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_15) {
    char str1[] = "Aa1a1a1";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "AA1A1A1");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_16) {
    char str1[] = "a1a1a1A";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "A1A1A1A");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_17) {
    char str1[] = "a1a1\0a1";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "A1A1\0A1");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_18) {
    char str1[] = "a1a\n1a1";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "A1A\n1A1");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_19) {
    char str1[] = "abcdefghijklmnopqrstuvwxyz";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_20) {
    char str1[] = ")(*&^YTRYUIKJHWR<LR3.,tmwnrg.";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, ")(*&^YTRYUIKJHWR<LR3.,TMWNRG.");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_21) {
    char str1[] = " ";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, " ");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_22) {
    char str1[] = "ABC";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "ABC");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_23) {
    char str1[] = "_a {";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "_A {");
    free(str2);
}
END_TEST

START_TEST(s21_to_upper_24) {
    char str1[] = "SDFGHKLPOIUYTREWQWERTYUIOP[OIUYTRFGHJKLJHBHJKLPOWQWERTYUIO";
    char *str2 = s21_to_upper(str1);
    ck_assert_str_eq(str2, "SDFGHKLPOIUYTREWQWERTYUIOP[OIUYTRFGHJKLJHBHJKLPOWQWERTYUIO");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_1) {
    char str1[] = "ABC";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "abc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_2) {
    char str1[] = "aBc";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "abc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_3) {
    char str1[] = "abC";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "abc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_4) {
    char str1[] = "ABC";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "abc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_5) {
    char str1[] = "123";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "123");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_6) {
    char str1[] = "123ABC";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "123abc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_7) {
    char str1[] = "aBaBc";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "ababc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_8) {
    char str1[] = ".,/.,/.,";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, ".,/.,/.,");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_9) {
    char str1[] = "09876ABC";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "09876abc");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_10) {
    char str1[] = "ABC123";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "abc123");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_11) {
    char str1[] = " ";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, " ");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_12) {
    char str1[] = "";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_13) {
    char str1[] = "A1A1A1";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "a1a1a1");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_14) {
    char str1[] = " A1A1A1";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, " a1a1a1");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_15) {
    char str1[] = "A1A1A1 ";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "a1a1a1 ");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_16) {
    char str1[] = "AA1A1A1";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "aa1a1a1");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_17) {
    char str1[] = "A1a1A1A";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "a1a1a1a");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_18) {
    char str1[] = "A1A1\0a1";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "a1a1\0a1");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_19) {
    char str1[] = "A1a\n1A1";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "a1a\n1a1");
    free(str2);
}
END_TEST

START_TEST(s21_to_lower_20) {
    char str1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *str2 = s21_to_lower(str1);
    ck_assert_str_eq(str2, "abcdefghijklmnopqrstuvwxyz");
    free(str2);
}
END_TEST

START_TEST(s21_trim_1) {
    char str1[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char str2[] = "ABC";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "DEFGHIJKLMNOPQRSTUVWXYZ");
    free(str3);
}
END_TEST

START_TEST(s21_trim_2) {
    char str1[] = "ABCDEFGHIabcABCPQRSTUVWXYZ";
    char str2[] = "ABC";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "DEFGHIabcABCPQRSTUVWXYZ");
    free(str3);
}
END_TEST

START_TEST(s21_trim_3) {
    char str1[] = "ABCDEFGHIabcABCPQRSTUVWXYZABC";
    char str2[] = "ABC";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "DEFGHIabcABCPQRSTUVWXYZ");
    free(str3);
}
END_TEST

START_TEST(s21_trim_4) {
    char str1[] = "ABCDEFGHIabcABCPQRSTUVWXYZabc";
    char str2[] = "ABC";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "DEFGHIabcABCPQRSTUVWXYZabc");
    free(str3);
}
END_TEST

START_TEST(s21_trim_5) {
    char str1[] = "ABCDEFGHIabcABCPQRSTUVWXYZabc";
    char str2[] = "abc";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "ABCDEFGHIabcABCPQRSTUVWXYZ");
    free(str3);
}
END_TEST

START_TEST(s21_trim_6) {
    char str1[] = "abc123abc";
    char str2[] = "abc";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "123");
    free(str3);
}
END_TEST

START_TEST(s21_trim_7) {
    char str1[] = "abc123abc456abc";
    char str2[] = "abc";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "123abc456");
    free(str3);
}
END_TEST

START_TEST(s21_trim_8) {
    char str1[] = "a1bc123abc456a1bc";
    char str2[] = "abc";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "1bc123abc456a1");
    free(str3);
}
END_TEST

START_TEST(s21_trim_9) {
    char str1[] = "a1bc123abc456a1bc";
    char str2[] = "a1bc";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "23abc456");
    free(str3);
}
END_TEST

START_TEST(s21_trim_10) {
    char str1[] = "abc123abc456a1bc";
    char str2[] = "ab2c";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "123abc456a1");
    free(str3);
}
END_TEST

START_TEST(s21_trim_11) {
    char str1[] = "abc123abc456a1bc";
    char str2[] = "ab12c";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "3abc456");
    free(str3);
}
END_TEST

START_TEST(s21_trim_12) {
    char str1[] = "abAc123abc456aB1bc";
    char str2[] = "ab12c";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "Ac123abc456aB");
    free(str3);
}
END_TEST

START_TEST(s21_trim_13) {
    char str1[] = "abAc123abc456aB1bc";
    char str2[] = "aBb12c";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "Ac123abc456");
    free(str3);
}
END_TEST

START_TEST(s21_trim_14) {
    char str1[] = "11222333444aaaBaabaA53332244445677Babab7878998";
    char str2[] = "aBbA12c";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "333444aaaBaabaA53332244445677Babab7878998");
    free(str3);
}
END_TEST

START_TEST(s21_trim_18) {
    char str1[] = "11222333444aaaBaabaA53332244445677Babab7878998";
    char str2[] = "4223aB6437bA1589117c";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "");
    free(str3);
}
END_TEST

START_TEST(s21_trim_19) {
    char str1[] = "11222333444aaaBaabaA53332244445677Babab7878998";
    char str2[] = "jK";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "11222333444aaaBaabaA53332244445677Babab7878998");
    free(str3);
}
END_TEST

START_TEST(s21_trim_20) {
    char str1[] = "";
    char str2[] = "jK";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "");
    free(str3);
}
END_TEST

START_TEST(s21_trim_21) {
    char str1[] = "sdfghjk";
    char str2[] = " ";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "sdfghjk");
    free(str3);
}
END_TEST

START_TEST(s21_trim_22) {
    char str1[] = "sdfg hjk";
    char str2[] = " ";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "sdfg hjk");
    free(str3);
}
END_TEST

START_TEST(s21_trim_23) {
    char str1[] = " ";
    char str2[] = " ";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "");
    free(str3);
}
END_TEST

START_TEST(s21_trim_24) {
    char str1[] = "a231546yutiljkhgtyre565786oiu;jlkhb12";
    char str2[] = "12333333333333333333333333333333333ab";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "546yutiljkhgtyre565786oiu;jlkh");
    free(str3);
}
END_TEST

START_TEST(s21_trim_25) {
    char str1[] = "a231546yutiljkhgtyre565786oiu;jlkhb12";
    char str2[] = "12333333333333333333333333333333333abmmmmmm";
    char *str3 = s21_trim(str1, str2);
    ck_assert_str_eq(str3, "546yutiljkhgtyre565786oiu;jlkh");
    free(str3);
}
END_TEST

START_TEST(s21_insert_1) {
    char str1[] = "abc";
    char str2[] = "def";
    int n = 3;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abcdef");
    free(str3);
}
END_TEST

START_TEST(s21_insert_2) {
    char str1[] = "abc";
    char str2[] = "def";
    int n = 2;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abdefc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_3) {
    char str1[] = "abc";
    char str2[] = "def";
    int n = 1;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "adefbc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_4) {
    char str1[] = "abc";
    char str2[] = "def";
    int n = 0;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "defabc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_5) {
    char str1[] = "abcdefghijkl123456789";
    char str2[] = "xyz";
    int n = 5;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abcdexyzfghijkl123456789");
    free(str3);
}
END_TEST

START_TEST(s21_insert_6) {
    char str1[] = "abc";
    char str2[] = "";
    int n = 0;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_7) {
    char str1[] = "abc";
    char str2[] = "";
    int n = 1;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_8) {
    char str1[] = "abc";
    char str2[] = "";
    int n = 3;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_9) {
    char str1[] = "";
    char str2[] = "abc";
    int n = 1;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_ptr_eq(str3, s21_NULL);
    free(str3);
}
END_TEST

START_TEST(s21_insert_10) {
    char str1[] = "";
    char str2[] = "abc";
    int n = 0;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "abc");
    free(str3);
}
END_TEST

START_TEST(s21_insert_11) {
    char str1[] = "";
    char str2[] = "abc";
    int n = 3;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_ptr_eq(str3, s21_NULL);
    free(str3);
}
END_TEST

START_TEST(s21_insert_12) {
    char str1[] = "";
    char str2[] = "";
    int n = 3;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_ptr_eq(str3, s21_NULL);
    free(str3);
}
END_TEST

START_TEST(s21_insert_13) {
    char str1[] = "";
    char str2[] = "";
    int n = 0;
    char *str3 = s21_insert(str1, str2, n);
    ck_assert_str_eq(str3, "");
    free(str3);
}
END_TEST

START_TEST(sprintf_6) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    sprintf(test_original, "Hello %s %.3f", "abc", -23.999999);
    s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.999999);
    ck_assert_str_eq(test_original, test_your);
} END_TEST

START_TEST(int_sprintf_pr_1) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %%"), s21_sprintf(test_your, "Hello %%"));
} END_TEST

START_TEST(int_sprintf_pr_2) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello 2022 World"), \
        s21_sprintf(test_your, "Hello 2022 World"));
} END_TEST

START_TEST(int_sprintf_c_1) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %c", 'W'), s21_sprintf(test_your, "Hello %c", 'W'));
} END_TEST

START_TEST(int_sprintf_c_2) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %-5c", 'W'), s21_sprintf(test_your, "Hello %-5c", 'W'));
} END_TEST

START_TEST(int_sprintf_c_3) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %5c", 'W'), s21_sprintf(test_your, "Hello %5c", 'W'));
} END_TEST

START_TEST(int_sprintf_c_4) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %-c", 'W'), s21_sprintf(test_your, "Hello %-c", 'W'));
} END_TEST

START_TEST(int_sprintf_c_5) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %c", 'W'), s21_sprintf(test_your, "Hello %c", 'W'));
} END_TEST

START_TEST(int_sprintf_c_6) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "%cHello %c", \
        's', 'W'), s21_sprintf(test_your, "%cHello %c", 's', 'W'));
} END_TEST

START_TEST(int_sprintf_c_7) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "He%cllo %-5c", \
        's', 'W'), s21_sprintf(test_your, "He%cllo %-5c", 's', 'W'));
} END_TEST

START_TEST(int_sprintf_c_8) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "%5cHello %5c", \
        's', 'W'), s21_sprintf(test_your, "%5cHello %5c", 's', 'W'));
} END_TEST

START_TEST(int_sprintf_c_9) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "%-10cHello %-c", \
        's', 'W'), s21_sprintf(test_your, "%-10cHello %-c", 's', 'W'));
} END_TEST

START_TEST(int_sprintf_c_10) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "He%%llo %c", 'W'), s21_sprintf(test_your, "He%%llo %c", 'W'));
} END_TEST

START_TEST(int_sprintf_d_1) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %d", 23), s21_sprintf(test_your, "Hello %d", 23));
} END_TEST

START_TEST(int_sprintf_d_2) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %05d", 23), s21_sprintf(test_your, "Hello %05d", 23));
} END_TEST

START_TEST(int_sprintf_d_3) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %-6d", 23), s21_sprintf(test_your, "Hello %-6d", 23));
} END_TEST

START_TEST(int_sprintf_d_4) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %+d", 23), s21_sprintf(test_your, "Hello %+d", 23));
} END_TEST

START_TEST(int_sprintf_d_5) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello % d", 23), \
        s21_sprintf(test_your, "Hello % d", 23));
} END_TEST

START_TEST(int_sprintf_d_6) {
    char test_original[1024];
    char test_your[1024];
    short des = 23;
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %hd", des), \
        s21_sprintf(test_your, "Hello %hd", des));
} END_TEST

START_TEST(int_sprintf_d_7) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %ld", 238230000006325000), \
        s21_sprintf(test_your, "Hello %ld", 238230000006325000));
} END_TEST

START_TEST(int_sprintf_d_8) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello % 10d", 23), \
        s21_sprintf(test_your, "Hello % 10d", 23));
} END_TEST

START_TEST(int_sprintf_d_9) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %+10d", 23), \
        s21_sprintf(test_your, "Hello %+10d", 23));
} END_TEST

START_TEST(int_sprintf_d_10) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %+10d", -23), \
        s21_sprintf(test_your, "Hello %+10d", -23));
} END_TEST

START_TEST(int_sprintf_d_11) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello % 10d", \
        - 23), s21_sprintf(test_your, "Hello % 10d", -23));
} END_TEST

START_TEST(int_sprintf_d_and_c_1) {
    char test_original[1024];
    char test_your[1024];
     free_array_2(test_original, test_your);
     ck_assert_int_eq(sprintf(test_original, "Hello %d %018d", 5, -23), \
                            s21_sprintf(test_your, "Hello %d %018d", 5, -23));
} END_TEST

START_TEST(int_sprintf_1) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %d %f", 5, -23.0), \
        s21_sprintf(test_your, "Hello %d %f", 5, -23.0));
} END_TEST

START_TEST(int_sprintf_2) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %s %f", "abc", -23.0), \
        s21_sprintf(test_your, "Hello %s %f", "abc", -23.0));
} END_TEST

START_TEST(int_sprintf_3) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hel%ulo %s %f", 100, \
        "abc", -23.0), s21_sprintf(test_your, "Hel%ulo %s %f", 100, "abc", -23.0));
} END_TEST

START_TEST(int_sprintf_4) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %s %.3f", "abc", -23.0000001), \
        s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.0000001));
} END_TEST

START_TEST(int_sprintf_5) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %s %.7f", "abc", \
        - 23.999999), s21_sprintf(test_your, "Hello %s %.7f", "abc", -23.999999));
} END_TEST

START_TEST(int_sprintf_6) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "Hello %s %.3f", \
        "abc", -23.999999), s21_sprintf(test_your, "Hello %s %.3f", "abc", -23.999999));
} END_TEST

START_TEST(int_sprintf_7) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, "H%ldello %s", \
        1234567890123456789, "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"), \
        s21_sprintf(test_your, "H%ldello %s", 1234567890123456789, \
            "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"));
} END_TEST

START_TEST(int_sprintf_8) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "H%uello %s", 123456789, "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"), \
        s21_sprintf(test_your, "H%uello %s", 123456789, \
            "abcdefghtabcdefghtabcdefghtabcdefghtabcdefghtabcdefght"));
} END_TEST

START_TEST(int_sprintf_9) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%lfdslkj", 1234.0), \
        s21_sprintf(test_your, "saeflkahj%lfdslkj", 1234.0));
} END_TEST

START_TEST(int_sprintf_10) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original,
        "saeflkahj%10.12f dslkj", -4353.235300),
        s21_sprintf(test_your, "saeflkahj%10.12f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_11) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%+010.12f dslkj", 4353.235300), \
        s21_sprintf(test_your, "saeflkahj%+010.12f dslkj", 4353.235300));
} END_TEST

START_TEST(int_sprintf_12) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj% 10.12f dslkj", 0.235300), \
        s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", 0.235300));
} END_TEST

START_TEST(int_sprintf_13) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj% 10.12f dslkj", -4353.235300), \
        s21_sprintf(test_your, "saeflkahj% 10.12f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_14) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%-.12f dslkj", 4353.235300), \
        s21_sprintf(test_your, "saeflkahj%-.12f dslkj", 4353.235300));
} END_TEST

START_TEST(int_sprintf_15) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%-.12f dslkj", -4353.235300), \
        s21_sprintf(test_your, "saeflkahj%-.12f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_16) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%-f dslkj", -4353.235300), \
        s21_sprintf(test_your, "saeflkahj%-f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_17) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%-.12f dslkj", -4353.235300), \
        s21_sprintf(test_your, "saeflkahj%-.12f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_18) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%-f dslkj", 0.235300), \
        s21_sprintf(test_your, "saeflkahj%-f dslkj", 0.235300));
} END_TEST

START_TEST(int_sprintf_19) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj%+f dslkj", 0.235300), \
        s21_sprintf(test_your, "saeflkahj%+f dslkj", 0.235300));
} END_TEST

START_TEST(int_sprintf_20) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj% f dslkj", -4353.235300), \
        s21_sprintf(test_your, "saeflkahj% f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_21) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "saeflkahj% 8f dslkj", -4353.235300), \
        s21_sprintf(test_your, "saeflkahj% 8f dslkj", -4353.235300));
} END_TEST

START_TEST(int_sprintf_22) {
    char test_original[1024];
    char test_your[1024];
    free_array_2(test_original, test_your);
    ck_assert_int_eq(sprintf(test_original, \
        "%s%s%s%s%s%ssaeflkahj% 8f dslkj", "ds", " ", " ", \
        "0", "+", "9999999", -4353.235300), \
        s21_sprintf(test_your, "%s%s%s%s%s%ssaeflkahj% 8f dslkj", \
            "ds", " ", " ", "0", "+", "9999999", -4353.235300));
} END_TEST

START_TEST(sprintf_2405) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%10.5lu", ULONG_MAX);
    sprintf(str1, "%10.5lu", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3374) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = s21_NULL;
    s21_sprintf(str2, "- %d - [%%s] - l.%d\n, [%s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%s] - l.%d\n, [%s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3376) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%3s] - l.%d\n, [%3s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3s] - l.%d\n, [%3s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3377) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3378) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.0s] - l.%d\n, [%3.0s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3379) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3380) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = s21_NULL;
    s21_sprintf(str2, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.2s] - l.%d\n, [%3.2s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3382) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%3.5s] - l.%d\n, [%3.5s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.5s] - l.%d\n, [%3.5s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3383) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3384) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%3.25s] - l.%d\n, [%3.25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3385) {
    char str1[BUFFER_SIZE];
    free_array_1(str1);
    char str2[BUFFER_SIZE];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%25s] - l.%d\n, [%25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25s] - l.%d\n, [%25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3386) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%25s] - l.%d\n, [%25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25s] - l.%d\n, [%25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3387) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3388) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25.0s] - l.%d\n, [%25.0s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3389) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3390) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%25.5s] - l.%d\n, [%25.5s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3391) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-s] - l.%d\n, [%-s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-s] - l.%d\n, [%-s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3392) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%-s] - l.%d\n, [%-s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-s] - l.%d\n, [%-s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3393) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3394) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3s] - l.%d\n, [%-3s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3395) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3396) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3.0s] - l.%d\n, [%-3.0s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3397) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = "Hello World";
    s21_sprintf(str2, "- %d - [%%-3.2s] - l.%d\n, [%-3.2s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3.2s] - l.%d\n, [%-3.2s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3398) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%-3.2s] - l.%d\n, [%-3.2s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3.2s] - l.%d\n, [%-3.2s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3400) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%-3.5s] - l.%d\n, [%-3.5s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3.5s] - l.%d\n, [%-3.5s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_3402) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    char* str = NULL;
    s21_sprintf(str2, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, __LINE__, str);
    sprintf(str1, "- %d - [%%-3.25s] - l.%d\n, [%-3.25s]", -2, __LINE__ - 1, str);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_12) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "%.0d";
    int val = 0;
    ck_assert_int_eq(s21_sprintf(str1, format, val),
                        sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_17) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "%.51u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_18) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "% 5.51u";
    unsigned int val = 14140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_20) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "%lu";
    unsigned long int val = 949149114140;
    ck_assert_int_eq(s21_sprintf(str1, format, val), sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_21) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "%lu, %u, %hu, %.5u, %5.u";
    unsigned long int val = 949149114140;
    ck_assert_int_eq(s21_sprintf(str1, \
        format, val, 14, 1441, 14414, 9681), \
        sprintf(str2, format, val, (unsigned)14, \
            (unsigned short)1441, (unsigned)14414,
            (unsigned)9681));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_33) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "%-15.9s";
    char* val = "69 IS MY FAVORITE NUMBER";
    ck_assert_int_eq(s21_sprintf(str1, format, val),
                        sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_35) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);

    char* format = "%s%s%s%s";
    char* val =
        "69 IS MY FAVORITE NUMBER THIS IS SUPPOSED TO BE A VERY LONG STRING";
    char* s1 = "";
    char* s2 = "87418347813748913749871389480913";
    char* s3 = "HAHAABOBASUCKER";
    ck_assert_int_eq(s21_sprintf(str1, format, val, s1, s2, s3),
                                    sprintf(str2, format, val, s1, s2, s3));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_36) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);
    char* val = "kjafdiuhfjahfjdahf";
    char* format = "%120s";
    ck_assert_int_eq(s21_sprintf(str1, format, val),
                        sprintf(str2, format, val));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_61) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);
    char format[] = "%7.4s";
    ck_assert_int_eq(s21_sprintf(str1, format, "aboba floppa"),
                        sprintf(str2, format, "aboba floppa"));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_68) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);
    char format[] = "%210s";
    ck_assert_int_eq(s21_sprintf(str1, format,
        "AHHAHAHA\0AHHAHAHAH"), sprintf(str2, format, "AHHAHAHA\0AHHAHAHAH"));
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_copy_69) {
    char str1[512];
    char str2[512];
    free_array_2(str1, str2);
    char format[] = "%-115s";
    ck_assert_int_eq(s21_sprintf(str1, format, "Nick her"),
                        sprintf(str2, format, "Nick her"));

    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2348) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "MIN %ld", LONG_MIN);
    sprintf(str1, "MIN %ld", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2349) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "Hola %li", 3534535547l);
    sprintf(str1, "Hola %li", 3534535547l);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2350) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%5ld'", 72342l);
    sprintf(str1, "padding '%5ld'", 72342l);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2351) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%5ld'", LONG_MAX);
    sprintf(str1, "padding '%5ld'", LONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2352) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%5ld'", LONG_MIN);
    sprintf(str1, "padding '%5ld'", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2353) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%05ld'", 72342l);
    sprintf(str1, "padding '%05ld'", 72342l);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2354) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%5ld'", LONG_MAX);
    sprintf(str1, "padding '%5ld'", LONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST


START_TEST(sprintf_2355) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%05ld'", LONG_MIN);
    sprintf(str1, "padding '%05ld'", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2358) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%-5ld'", LONG_MIN);
    sprintf(str1, "padding '%-5ld'", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2361) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "precision '%.5ld'", LONG_MIN);
    sprintf(str1, "precision '%.5ld'", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2364) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "precision '%3.5ld'", LONG_MIN);
    sprintf(str1, "precision '%3.5ld'", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2367) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "precision '%-3.5ld'", LONG_MIN);
    sprintf(str1, "precision '%-3.5ld'", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2370) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "MAX %lu", ULONG_MAX);
    sprintf(str1, "MAX %lu", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2373) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%5lu'", ULONG_MAX);
    sprintf(str1, "padding '%5lu'", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2376) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "padding '%-5lu'", ULONG_MAX);
    sprintf(str1, "padding '%-5lu'", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2379) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "precision '%.5lu'", ULONG_MAX);
    sprintf(str1, "precision '%.5lu'", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2382) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "precision '%3.5lu'", ULONG_MAX);
    sprintf(str1, "precision '%3.5lu'", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2385) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "precision '%-3.5lu'", ULONG_MAX);
    sprintf(str1, "precision '%-3.5lu'", ULONG_MAX);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2403) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%10.5ld", LONG_MIN);
    sprintf(str1, "%10.5ld", LONG_MIN);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2404) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%10.5f", -0.35);
    sprintf(str1, "%10.5f", -0.35);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2405_1) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%0f", 35.8989);
    sprintf(str1, "%0f", 35.8989);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2405_2) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%-12f", -35.8989);
    sprintf(str1, "%-12f", -35.8989);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2405_3) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%07f", 35.89);
    sprintf(str1, "%07f", 35.89);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2406) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%5d", -35);
    sprintf(str1, "%5d", -35);
    ck_assert_str_eq(str1, str2);
} END_TEST

START_TEST(sprintf_2407) {
    char str1[1024];
    free_array_1(str1);
    char str2[1024];
    free_array_1(str2);
    s21_sprintf(str2, "%05u", 35);
    sprintf(str1, "%05u", 35);
    ck_assert_str_eq(str1, str2);
} END_TEST

Suite *s21_sprintf_suite(void) {
Suite *s1 = suite_create("Core");
TCase *tc1_1 = tcase_create("Core");
tcase_add_test(tc1_1, s21_memchr_ts);
tcase_add_test(tc1_1, s21_memcmp_ts_1);
tcase_add_test(tc1_1, s21_memcmp_ts_2);
tcase_add_test(tc1_1, s21_memcpy_ts_1);
tcase_add_test(tc1_1, s21_memcpy_ts_2);
tcase_add_test(tc1_1, s21_memcpy_ts_3);
tcase_add_test(tc1_1, s21_memcpy_ts_4);
tcase_add_test(tc1_1, s21_memmove_ts_1);
tcase_add_test(tc1_1, s21_memmove_ts_2);
tcase_add_test(tc1_1, s21_memset_ts_1);
tcase_add_test(tc1_1, s21_memset_ts_2);
tcase_add_test(tc1_1, s21_strcat_ts);
tcase_add_test(tc1_1, s21_strncat_ts);
tcase_add_test(tc1_1, s21_strchr_ts);
tcase_add_test(tc1_1, s21_strcmp_ts);
tcase_add_test(tc1_1, s21_strncmp_ts);
tcase_add_test(tc1_1, s21_strcpy_ts_1);
tcase_add_test(tc1_1, s21_strcpy_ts_2);
tcase_add_test(tc1_1, s21_strncpy_ts);
tcase_add_test(tc1_1, s21_strcspn_ts);
tcase_add_test(tc1_1, s21_strerror_ts);
tcase_add_test(tc1_1, s21_strlen_ts);
tcase_add_test(tc1_1, s21_strpbrk_ts);
tcase_add_test(tc1_1, s21_strrchr_ts);
tcase_add_test(tc1_1, s21_strspn_ts);
tcase_add_test(tc1_1, s21_strstr_ts);
tcase_add_test(tc1_1, s21_strtok_ts);
tcase_add_test(tc1_1, s21_sprintf_ts_1);
tcase_add_test(tc1_1, s21_sprintf_ts_2);
tcase_add_test(tc1_1, s21_sprintf_ts_3);
tcase_add_test(tc1_1, s21_sprintf_c_ts_4);
tcase_add_test(tc1_1, s21_sprintf_c_ts_5);
tcase_add_test(tc1_1, s21_sprintf_c_ts_6);
tcase_add_test(tc1_1, s21_sprintf_c_ts_7);
tcase_add_test(tc1_1, s21_sprintf_c_ts_8);
tcase_add_test(tc1_1, s21_sprintf_c_ts_9);
tcase_add_test(tc1_1, s21_sprintf_c_ts_10);
tcase_add_test(tc1_1, s21_sprintf_c_ts_11);
tcase_add_test(tc1_1, s21_sprintf_c_ts_12);
tcase_add_test(tc1_1, s21_sprintf_wc_ts_12_1);
tcase_add_test(tc1_1, s21_sprintf_wc_ts_12_2);
tcase_add_test(tc1_1, s21_sprintf_s_ts_13);
tcase_add_test(tc1_1, s21_sprintf_s_ts_14);
tcase_add_test(tc1_1, s21_sprintf_s_ts_15);
tcase_add_test(tc1_1, s21_sprintf_s_ts_16);
tcase_add_test(tc1_1, s21_sprintf_s_ts_18);
tcase_add_test(tc1_1, s21_sprintf_s_ts_19);
tcase_add_test(tc1_1, s21_sprintf_s_ts_20);
tcase_add_test(tc1_1, s21_sprintf_s_ts_21);
tcase_add_test(tc1_1, s21_sprintf_ws_ts_21_1);
tcase_add_test(tc1_1, s21_sprintf_ws_ts_21_2);
tcase_add_test(tc1_1, s21_sprintf_ws_ts_21_3);
tcase_add_test(tc1_1, s21_sprintf_ws_ts_21_4);
tcase_add_test(tc1_1, s21_sprintf_ws_ts_21_5);
tcase_add_test(tc1_1, s21_sprintf_i_ts_22);
tcase_add_test(tc1_1, s21_sprintf_i_ts_23);
tcase_add_test(tc1_1, s21_sprintf_i_ts_24);
tcase_add_test(tc1_1, s21_sprintf_d_ts_25);
tcase_add_test(tc1_1, s21_sprintf_d_ts_26);
tcase_add_test(tc1_1, s21_sprintf_d_ts_27);
tcase_add_test(tc1_1, s21_sprintf_d_ts_28);
tcase_add_test(tc1_1, s21_sprintf_d_ts_29);
tcase_add_test(tc1_1, s21_sprintf_d_ts_30);
tcase_add_test(tc1_1, s21_sprintf_d_ts_31);
tcase_add_test(tc1_1, s21_sprintf_d_ts_32);
tcase_add_test(tc1_1, s21_sprintf_d_ts_33);
tcase_add_test(tc1_1, s21_sprintf_d_ts_34);
tcase_add_test(tc1_1, s21_sprintf_d_ts_35);
tcase_add_test(tc1_1, s21_sprintf_d_ts_36);
tcase_add_test(tc1_1, s21_sprintf_d_ts_37);
tcase_add_test(tc1_1, s21_sprintf_d_ts_38);
tcase_add_test(tc1_1, s21_sprintf_d_ts_39);
tcase_add_test(tc1_1, s21_sprintf_d_ts_40);
tcase_add_test(tc1_1, s21_sprintf_d_ts_41);
tcase_add_test(tc1_1, s21_sprintf_d_ts_42);
tcase_add_test(tc1_1, s21_sprintf_d_ts_43);
tcase_add_test(tc1_1, s21_sprintf_d_ts_44);
tcase_add_test(tc1_1, s21_sprintf_d_ts_45);
tcase_add_test(tc1_1, s21_sprintf_d_ts_46);
tcase_add_test(tc1_1, s21_sprintf_d_ts_47);
tcase_add_test(tc1_1, s21_sprintf_d_ts_48);
tcase_add_test(tc1_1, s21_sprintf_d_ts_49);
tcase_add_test(tc1_1, s21_sprintf_d_ts_50);
tcase_add_test(tc1_1, s21_sprintf_d_ts_51);
tcase_add_test(tc1_1, s21_sprintf_d_ts_52);
tcase_add_test(tc1_1, s21_sprintf_d_ts_53);
tcase_add_test(tc1_1, s21_sprintf_d_ts_54);
tcase_add_test(tc1_1, s21_sprintf_u_ts_55);
tcase_add_test(tc1_1, s21_sprintf_u_ts_56);
tcase_add_test(tc1_1, s21_sprintf_u_ts_57);
tcase_add_test(tc1_1, s21_sprintf_u_ts_58);
tcase_add_test(tc1_1, s21_sprintf_u_ts_59);
tcase_add_test(tc1_1, s21_sprintf_u_ts_60);
tcase_add_test(tc1_1, s21_sprintf_u_ts_61);
tcase_add_test(tc1_1, s21_sprintf_u_ts_62);
tcase_add_test(tc1_1, s21_sprintf_u_ts_63);
tcase_add_test(tc1_1, s21_sprintf_u_ts_64);
tcase_add_test(tc1_1, s21_sprintf_u_ts_65);
tcase_add_test(tc1_1, s21_sprintf_u_ts_66);
tcase_add_test(tc1_1, s21_sprintf_f_ts_67);
tcase_add_test(tc1_1, s21_sprintf_f_ts_68);
tcase_add_test(tc1_1, s21_sprintf_f_ts_69);
tcase_add_test(tc1_1, s21_sprintf_f_ts_70);
tcase_add_test(tc1_1, s21_sprintf_f_ts_71);
tcase_add_test(tc1_1, s21_sprintf_f_ts_72);
tcase_add_test(tc1_1, s21_sprintf_f_ts_73);
tcase_add_test(tc1_1, s21_sprintf_f_ts_74);
tcase_add_test(tc1_1, s21_sprintf_f_ts_75);
tcase_add_test(tc1_1, s21_sprintf_f_ts_76);
tcase_add_test(tc1_1, s21_sprintf_f_ts_77);
tcase_add_test(tc1_1, s21_sprintf_f_ts_78);
tcase_add_test(tc1_1, s21_sprintf_f_ts_79);
tcase_add_test(tc1_1, s21_sprintf_f_ts_80);
tcase_add_test(tc1_1, s21_sprintf_f_ts_81);
tcase_add_test(tc1_1, s21_sprintf_f_ts_82);
tcase_add_test(tc1_1, s21_sprintf_f_ts_83);
tcase_add_test(tc1_1, s21_sprintf_f_ts_84);
tcase_add_test(tc1_1, s21_sprintf_f_ts_85);
tcase_add_test(tc1_1, s21_sprintf_f_ts_86);
tcase_add_test(tc1_1, s21_sprintf_f_ts_87);
tcase_add_test(tc1_1, s21_sprintf_f_ts_88);
tcase_add_test(tc1_1, s21_sprintf_f_ts_89);
tcase_add_test(tc1_1, s21_sprintf_f_ts_90);
tcase_add_test(tc1_1, s21_sprintf_f_ts_91);
tcase_add_test(tc1_1, s21_to_upper_1);
tcase_add_test(tc1_1, s21_to_upper_2);
tcase_add_test(tc1_1, s21_to_upper_3);
tcase_add_test(tc1_1, s21_to_upper_4);
tcase_add_test(tc1_1, s21_to_upper_4_1);
tcase_add_test(tc1_1, s21_to_upper_5);
tcase_add_test(tc1_1, s21_to_upper_6);
tcase_add_test(tc1_1, s21_to_upper_7);
tcase_add_test(tc1_1, s21_to_upper_8);
tcase_add_test(tc1_1, s21_to_upper_9);
tcase_add_test(tc1_1, s21_to_upper_10);
tcase_add_test(tc1_1, s21_to_upper_11);
tcase_add_test(tc1_1, s21_to_upper_12);
tcase_add_test(tc1_1, s21_to_upper_13);
tcase_add_test(tc1_1, s21_to_upper_14);
tcase_add_test(tc1_1, s21_to_upper_15);
tcase_add_test(tc1_1, s21_to_upper_16);
tcase_add_test(tc1_1, s21_to_upper_17);
tcase_add_test(tc1_1, s21_to_upper_18);
tcase_add_test(tc1_1, s21_to_upper_19);
tcase_add_test(tc1_1, s21_to_upper_20);
tcase_add_test(tc1_1, s21_to_upper_21);
tcase_add_test(tc1_1, s21_to_upper_22);
tcase_add_test(tc1_1, s21_to_upper_23);
tcase_add_test(tc1_1, s21_to_upper_24);
tcase_add_test(tc1_1, s21_to_lower_1);
tcase_add_test(tc1_1, s21_to_lower_2);
tcase_add_test(tc1_1, s21_to_lower_3);
tcase_add_test(tc1_1, s21_to_lower_4);
tcase_add_test(tc1_1, s21_to_lower_5);
tcase_add_test(tc1_1, s21_to_lower_6);
tcase_add_test(tc1_1, s21_to_lower_7);
tcase_add_test(tc1_1, s21_to_lower_8);
tcase_add_test(tc1_1, s21_to_lower_9);
tcase_add_test(tc1_1, s21_to_lower_10);
tcase_add_test(tc1_1, s21_to_lower_11);
tcase_add_test(tc1_1, s21_to_lower_12);
tcase_add_test(tc1_1, s21_to_lower_13);
tcase_add_test(tc1_1, s21_to_lower_14);
tcase_add_test(tc1_1, s21_to_lower_15);
tcase_add_test(tc1_1, s21_to_lower_16);
tcase_add_test(tc1_1, s21_to_lower_17);
tcase_add_test(tc1_1, s21_to_lower_18);
tcase_add_test(tc1_1, s21_to_lower_19);
tcase_add_test(tc1_1, s21_to_lower_20);
tcase_add_test(tc1_1, s21_trim_1);
tcase_add_test(tc1_1, s21_trim_2);
tcase_add_test(tc1_1, s21_trim_3);
tcase_add_test(tc1_1, s21_trim_4);
tcase_add_test(tc1_1, s21_trim_5);
tcase_add_test(tc1_1, s21_trim_6);
tcase_add_test(tc1_1, s21_trim_7);
tcase_add_test(tc1_1, s21_trim_8);
tcase_add_test(tc1_1, s21_trim_9);
tcase_add_test(tc1_1, s21_trim_10);
tcase_add_test(tc1_1, s21_trim_11);
tcase_add_test(tc1_1, s21_trim_12);
tcase_add_test(tc1_1, s21_trim_13);
tcase_add_test(tc1_1, s21_trim_14);
tcase_add_test(tc1_1, s21_trim_18);
tcase_add_test(tc1_1, s21_trim_19);
tcase_add_test(tc1_1, s21_trim_20);
tcase_add_test(tc1_1, s21_trim_21);
tcase_add_test(tc1_1, s21_trim_22);
tcase_add_test(tc1_1, s21_trim_23);
tcase_add_test(tc1_1, s21_trim_24);
tcase_add_test(tc1_1, s21_trim_25);
tcase_add_test(tc1_1, s21_insert_1);
tcase_add_test(tc1_1, s21_insert_2);
tcase_add_test(tc1_1, s21_insert_3);
tcase_add_test(tc1_1, s21_insert_4);
tcase_add_test(tc1_1, s21_insert_5);
tcase_add_test(tc1_1, s21_insert_6);
tcase_add_test(tc1_1, s21_insert_7);
tcase_add_test(tc1_1, s21_insert_8);
tcase_add_test(tc1_1, s21_insert_9);
tcase_add_test(tc1_1, s21_insert_10);
tcase_add_test(tc1_1, s21_insert_11);
tcase_add_test(tc1_1, s21_insert_12);
tcase_add_test(tc1_1, s21_insert_13);
tcase_add_test(tc1_1, sprintf_6);
tcase_add_test(tc1_1, int_sprintf_pr_1);
tcase_add_test(tc1_1, int_sprintf_pr_2);
tcase_add_test(tc1_1, int_sprintf_c_1);
tcase_add_test(tc1_1, int_sprintf_c_2);
tcase_add_test(tc1_1, int_sprintf_c_3);
tcase_add_test(tc1_1, int_sprintf_c_4);
tcase_add_test(tc1_1, int_sprintf_c_5);
tcase_add_test(tc1_1, int_sprintf_c_6);
tcase_add_test(tc1_1, int_sprintf_c_7);
tcase_add_test(tc1_1, int_sprintf_c_8);
tcase_add_test(tc1_1, int_sprintf_c_9);
tcase_add_test(tc1_1, int_sprintf_c_10);
tcase_add_test(tc1_1, int_sprintf_d_1);
tcase_add_test(tc1_1, int_sprintf_d_2);
tcase_add_test(tc1_1, int_sprintf_d_3);
tcase_add_test(tc1_1, int_sprintf_d_4);
tcase_add_test(tc1_1, int_sprintf_d_5);
tcase_add_test(tc1_1, int_sprintf_d_6);
tcase_add_test(tc1_1, int_sprintf_d_7);
tcase_add_test(tc1_1, int_sprintf_d_8);
tcase_add_test(tc1_1, int_sprintf_d_9);
tcase_add_test(tc1_1, int_sprintf_d_10);
tcase_add_test(tc1_1, int_sprintf_d_11);
tcase_add_test(tc1_1, int_sprintf_d_and_c_1);
tcase_add_test(tc1_1, int_sprintf_1);
tcase_add_test(tc1_1, int_sprintf_2);
tcase_add_test(tc1_1, int_sprintf_3);
tcase_add_test(tc1_1, int_sprintf_4);
tcase_add_test(tc1_1, int_sprintf_5);
tcase_add_test(tc1_1, int_sprintf_6);
tcase_add_test(tc1_1, int_sprintf_7);
tcase_add_test(tc1_1, int_sprintf_8);
tcase_add_test(tc1_1, int_sprintf_9);
tcase_add_test(tc1_1, int_sprintf_10);
tcase_add_test(tc1_1, int_sprintf_11);
tcase_add_test(tc1_1, int_sprintf_12);
tcase_add_test(tc1_1, int_sprintf_13);
tcase_add_test(tc1_1, int_sprintf_14);
tcase_add_test(tc1_1, int_sprintf_15);
tcase_add_test(tc1_1, int_sprintf_16);
tcase_add_test(tc1_1, int_sprintf_17);
tcase_add_test(tc1_1, int_sprintf_18);
tcase_add_test(tc1_1, int_sprintf_19);
tcase_add_test(tc1_1, int_sprintf_20);
tcase_add_test(tc1_1, int_sprintf_21);
tcase_add_test(tc1_1, int_sprintf_22);
tcase_add_test(tc1_1, sprintf_2348);
tcase_add_test(tc1_1, sprintf_2349);
tcase_add_test(tc1_1, sprintf_2350);
tcase_add_test(tc1_1, sprintf_2351);
tcase_add_test(tc1_1, sprintf_2352);
tcase_add_test(tc1_1, sprintf_2353);
tcase_add_test(tc1_1, sprintf_2354);
tcase_add_test(tc1_1, sprintf_2355);
tcase_add_test(tc1_1, sprintf_2358);
tcase_add_test(tc1_1, sprintf_2361);
tcase_add_test(tc1_1, sprintf_2364);
tcase_add_test(tc1_1, sprintf_2367);
tcase_add_test(tc1_1, sprintf_2370);
tcase_add_test(tc1_1, sprintf_2373);
tcase_add_test(tc1_1, sprintf_2376);
tcase_add_test(tc1_1, sprintf_2379);
tcase_add_test(tc1_1, sprintf_2382);
tcase_add_test(tc1_1, sprintf_2385);
tcase_add_test(tc1_1, sprintf_2373);
tcase_add_test(tc1_1, sprintf_2403);
tcase_add_test(tc1_1, sprintf_2405);
tcase_add_test(tc1_1, sprintf_2405_3);
tcase_add_test(tc1_1, sprintf_3374);
tcase_add_test(tc1_1, sprintf_3376);
tcase_add_test(tc1_1, sprintf_3377);
tcase_add_test(tc1_1, sprintf_3378);
tcase_add_test(tc1_1, sprintf_3379);
tcase_add_test(tc1_1, sprintf_3380);
tcase_add_test(tc1_1, sprintf_3382);
tcase_add_test(tc1_1, sprintf_3383);
tcase_add_test(tc1_1, sprintf_3384);
tcase_add_test(tc1_1, sprintf_3385);
tcase_add_test(tc1_1, sprintf_3386);
tcase_add_test(tc1_1, sprintf_3387);
tcase_add_test(tc1_1, sprintf_3388);
tcase_add_test(tc1_1, sprintf_3389);
tcase_add_test(tc1_1, sprintf_3390);
tcase_add_test(tc1_1, sprintf_3391);
tcase_add_test(tc1_1, sprintf_3392);
tcase_add_test(tc1_1, sprintf_3393);
tcase_add_test(tc1_1, sprintf_3394);
tcase_add_test(tc1_1, sprintf_3395);
tcase_add_test(tc1_1, sprintf_3396);
tcase_add_test(tc1_1, sprintf_3397);
tcase_add_test(tc1_1, sprintf_3398);
tcase_add_test(tc1_1, sprintf_3400);
tcase_add_test(tc1_1, sprintf_3402);
tcase_add_test(tc1_1, sprintf_copy_12);
tcase_add_test(tc1_1, sprintf_copy_17);
tcase_add_test(tc1_1, sprintf_copy_18);
tcase_add_test(tc1_1, sprintf_copy_20);
tcase_add_test(tc1_1, sprintf_copy_21);
tcase_add_test(tc1_1, sprintf_copy_33);
tcase_add_test(tc1_1, sprintf_copy_35);
tcase_add_test(tc1_1, sprintf_copy_36);
tcase_add_test(tc1_1, sprintf_copy_61);
tcase_add_test(tc1_1, sprintf_copy_68);
tcase_add_test(tc1_1, sprintf_copy_69);
tcase_add_test(tc1_1, sprintf_2404);
tcase_add_test(tc1_1, sprintf_2405_1);
tcase_add_test(tc1_1, sprintf_2405_2);
tcase_add_test(tc1_1, sprintf_2406);
tcase_add_test(tc1_1, sprintf_2407);
suite_add_tcase(s1, tc1_1);
return s1;
}

int main(void) {
Suite *s1 = s21_sprintf_suite();
SRunner *sr = srunner_create(s1);
srunner_run_all(sr, CK_ENV);
int nf = srunner_ntests_failed(sr);
srunner_free(sr);
return nf == 0 ? 0 : 1;
}
