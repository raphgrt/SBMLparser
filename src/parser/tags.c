/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** tags.c
*/

#include "../../include/sbml.h"

static int is_alphanum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static char get_last_char(char *str)
{
    int last = 0;

    for (last = 0; str[last]; last++);
    return (str[last - 1]);
}

static int get_index_last(char *str)
{
    int res = 0;

    for (res = 0; str[res]; res++);
    return (res - 1);
}

type_t get_type(char *str)
{
    char last;

    if (str[0] != '<' || !str)
        return (REMOVE);
    last = get_last_char(str);
    if (str[1] == '/' && last == '>')
        return (END_TAG);
    if (is_alphanum(str[1]) == 0)
        return (REMOVE);
    if (str[get_index_last(str) - 1] != '/')
        return (OPEN_TAG);
    if (last == '>')
        return (OPEN_TAG);
    return (INLINE_TAG);
}
