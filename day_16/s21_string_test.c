#include "s21_string_test.h"

#include <stdio.h>

#include "s21_string.h"

int main() {
#ifdef STRLEN
    char *string = "\n";
    string = "\n";
    s21_strlen_test(string, 1);
    string = "";
    s21_strlen_test(string, 0);
    string = "\0";
    s21_strlen_test(string, 0);
    string = "HELLO, WORLD!\n";
    s21_strlen_test(string, 14);
    string = "111111111111111111111111111 111111111111111111111111 1111111";
    s21_strlen_test(string, 60);
#endif

#ifdef STRCMP
    char *str1 = "";
    char *str2 = "HELLO";
    ;
    s21_strcmp_test(str1, str2, -1);
    str1 = NULL;
    str2 = NULL;
    s21_strcmp_test(str1, str2, -2);
    str1 = "MY MAC";
    str2 = "MY CODE";
    s21_strcmp_test(str1, str2, 1);
    str1 = "\n";
    str2 = "MY CODE";
    s21_strcmp_test(str1, str2, -1);
    str1 = "0";
    str2 = "\0";
    s21_strcmp_test(str1, str2, 1);
    str1 = "123";
    str2 = "123";
    s21_strcmp_test(str1, str2, 0);
#endif

#ifdef STRCPY
    char *str1 = "School21";
    char str2[50] = "";
    s21_strcpy_test(str2, str1, "School21");
    str1 = "";
    s21_strcpy_test(str2, str1, "");
    str1 = NULL;
    s21_strcpy_test(str2, str1, "");
    str1 = "Hello, world!!!";
    s21_strcpy_test(str2, str1, "Hello, world!!!");
#endif

#ifdef STRCAT
    char *str1 = "world!!!";
    char str2[50] = "Hello, ";
    s21_strcat_test(str2, str1, "Hello, world!!!");
    str1 = "";
    s21_strcat_test(str2, str1, "Hello, world!!!");
    str1 = "\n";
    s21_strcat_test(str2, str1, "Hello, world!!!\n");
    str1 = "\0";
    s21_strcat_test(str2, str1, "Hello, world!!!\n");
#endif

#ifdef STRCHR
    char *str1 = "123456789";
    int ch = '6';
    s21_strchr_test(str1, ch, "6789");
    str1 = NULL;
    ch = ' ';
    s21_strchr_test(str1, ch, NULL);
    str1 = "HELLO";
    ch = '1';
    s21_strchr_test(str1, ch, NULL);
    str1 = "HELlO";
    ch = 'l';
    s21_strchr_test(str1, ch, "lO");
#endif

#ifdef STRSTR
    char *str1 = "123456789";
    char *str2 = "67";
    s21_strstr_test(str1, str2, "6789");
    str1 = NULL;
    str2 = " ";
    s21_strstr_test(str1, str2, NULL);
    str1 = "Hello";
    str2 = "1";
    s21_strstr_test(str1, str2, NULL);
    str1 = "Hello, world!!!";
    str2 = "l";
    s21_strstr_test(str1, str2, "llo, world!!!");
#endif

    return 0;
}

void s21_strlen_test(const char *str, int expected_len) {
    int len = s21_strlen(str);
    int result = len == expected_len ? 1 : 0;
    if (result)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}

void s21_strcmp_test(const char *str1, const char *str2, int expected_result) {
    int result = s21_strcmp(str1, str2);
    if (result == expected_result)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}

void s21_strcpy_test(char *destination, const char *source, char *expected_result) {
    char *str = s21_strcpy(destination, source);
    if (!s21_strcmp(expected_result, str))
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}

void s21_strcat_test(char *destination, const char *append, char *expected_result) {
    char *result_cat = s21_strcat(destination, append);
    if (!s21_strcmp(result_cat, expected_result))
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}

void s21_strchr_test(char *str, int ch, char *expected_result) {
    char *result_chr = s21_strchr(str, ch);
    if (!s21_strcmp(result_chr, expected_result) || result_chr == expected_result)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}

void s21_strstr_test(char *str1, char *str2, char *expected_result) {
    char *result = s21_strstr(str1, str2);
    if (!s21_strcmp(result, expected_result) || result == expected_result)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
}
