/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extract_chemicals.c
*/

#include "../../include/sbml.h"

void extract_chemicals(tag_t *head, extract_t *res)
{
    tag_t *runner;
    char *name;

    if (!head)
        return;
    runner = head;
    while (runner) {
        if (runner->tag_type == SPECIES && runner->attributes) {
            name = get_value_attribute(runner->attributes, "name");
            add_extract(&res, name, NULL, (dep_print_t) {LISTOF_SPECIES, 1});
        }
        runner = runner->next;
    }
}
