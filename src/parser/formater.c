/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** formater.c
*/

#include "../../include/sbml.h"


void remove_spaces_and_tabs(char *input)
{
    int i = 0;
    int j = 0;
    int len = strlen(input);

    while (input[i] == ' ' || input[i] == '\t')
        i++;
    while (i < len) {
        input[j] = input[i];
        j++;
        i++;
    }
    input[j] = '\0';
}

static char **allocate_output(int len)
{
    char **output = malloc((len + 1) * sizeof(char *));

    if (!output)
        return (NULL);
    for (int i = 0; i <= len; i++) {
        output[i] = malloc(len + 1);
        if (!output[i])
            return (NULL);
    }
    return (output);
}

static void fill_output(char **output, char *input, int len)
{
    int j = 0;
    int k = 0;
    int inside_quotes = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '\"')
            inside_quotes = !inside_quotes;
        if (inside_quotes || (input[i] != ' ' && input[i] != '\t')) {
            output[k][j] = input[i];
            j++;
        }
        if (!inside_quotes && (input[i] == ' ' || input[i] == '\t')) {
            output[k][j] = '\0';
            k++;
            j = 0;
        }
    }
    output[k][j] = '\0';
    output[k + 1] = NULL;
}

char **parse_line(char *input)
{
    int len = strlen(input);
    char **output = allocate_output(len);

    if (!output) {
        return NULL;
    }
    fill_output(output, input, len);
    return (output);
}
