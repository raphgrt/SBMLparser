/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** parser.c
*/

#include "../../include/sbml.h"

static tag_t **save_in_struct(char **line_array, tag_t **list,
    dependencies_list_t **dep)
{
    attribute_t *tmp = NULL;
    tag_t *new = NULL;

    for (int x = 1; line_array[x]; x++) {
        add_attribute(&tmp, line_array[x]);
    }
    add_tag(list, line_array[0], &tmp);
    free(line_array);
    return (list);
}

void parser(sbml_t *sbml)
{
    char **line_array;
    dependencies_list_t *dep = NULL;

    for (int x = 0; sbml->buffer_array[x]; x++) {
        remove_spaces_and_tabs(sbml->buffer_array[x]);
        line_array = parse_line(sbml->buffer_array[x]);
        sbml->tags = *save_in_struct(line_array, &sbml->tags, &dep);
    }
}
