#ifndef STRING_H_
#define STRING_H_

int s21_strlen(const char *string);
int s21_strcmp(const char *str1, const char *str2);
char *s21_strcpy(char *destination, const char *source);
char *s21_strcat(char *destination, const char *append);
char *s21_strchr(char *str, int ch);
char *s21_strstr(char *str, char *substr);

#endif
