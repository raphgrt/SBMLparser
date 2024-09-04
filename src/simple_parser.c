/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** simple_parser.c
*/

#include "../include/sbml.h"

void simple_parser(tag_t *list)
{
    tag_t *runner;

    merge_sort(&list);
    runner = list;
    while (runner != NULL) {
        merge_sort_attributes(&runner->attributes);
        runner = runner->next;
    }
}

void print_attributes(attribute_t *attrs)
{
    while (attrs != NULL) {
        printf("--->%s\n", attrs->name);
        attrs = attrs->next;
    }
}

void print_tag_and_attributes(tag_t *runner)
{
    printf("%s\n", runner->name);
    print_attributes(runner->attributes);
}

static int is_printable_tags(tag_t *tags)
{
    if (tags->type != INLINE_TAG)
        return (0);
    if (tags->tag_type == LISTOF || tags->tag_type == OTHER)
        return (0);
    return (1);
}

void print_simple_parser(tag_t *list)
{
    tag_t *runner = list;

    while (runner != NULL) {
        if (is_printable_tags(runner) == 1) {
            print_tag_and_attributes(runner);
        }
        runner = runner->next;
    }
}
