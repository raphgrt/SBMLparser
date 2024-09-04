/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** json_print.c
*/

#include "../../include/sbml.h"


static void print_tag(tag_t *elem)
{
    attribute_t *attr;

    if (!elem || !attr)
        return;
    printf("\"%s\": [\n", elem->name);
    printf("\t{\n");
    attr = elem->attributes;
    while (attr) {
        printf("\t\t\"%s\": \"%s\"\n", attr->name, attr->value);
        attr = attr->next;
    }
    printf("\t}\n");
}

void json_print(extract_t *list)
{
    printf("{\n");
    printf("\t\"species\": [\n");
}
