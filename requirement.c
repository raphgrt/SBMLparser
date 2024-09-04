/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** requirement.c
*/

#include <stdlib.h>

static int my_char_issep(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int str_count_words(char const *str)
{
    int res = 0;

    for (int x = 0; str[x]; x++)
        if ((my_char_issep(str[x]) == 0 && my_char_issep(str[x - 1]) == 1)
            || (str[x + 1] == '\0' && my_char_issep(str[x]) == 1))
            res++;
    return (res);
}

char *my_strndup(const char *str, int n)
{
    char *new_str = malloc(sizeof(char) * (n + 1));
    int i = 0;

    if (new_str == NULL)
        return (NULL);
    while (i < n) {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return (new_str);
}

int get_len(int index, const char *str, char **tmp, int i)
{
    int start = index;
    int len;

    while (my_char_issep(str[index]) == 1)
        index++;
    len = index - start;
    tmp[i] = my_strndup(&str[start], len);
    return (index);
}

char **my_str_to_word_array_synthesis(char const *str)
{
    int nb_words;
    char **tmp;
    int i = 0;

    if (str == NULL)
        return (NULL);
    nb_words = str_count_words(str);
    tmp = malloc(sizeof(char *) * nb_words + 1);
    for (int x = 0; str[x] != '\0'; x++) {
        if (my_char_issep(str[x]) == 1) {
            x = get_len(x, str, tmp, i);
            i++;
        }
        if (i == nb_words)
            break;
    }
    tmp[nb_words] = NULL;
    return (tmp);
}
