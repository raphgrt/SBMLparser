/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extract_struct.c
*/

#include "../../include/sbml.h"

static extract_t *create_extract(char *res, char *qty, dep_print_t dprint)
{
    extract_t *new = malloc(sizeof(extract_t));

    if (!new)
        exit(84);
    new->result = res;
    new->quantity = qty;
    new->extract_type = dprint.extract_type;
    new->print_type = dprint.pt;
    new->next = NULL;
    return (new);
}

void add_extract(extract_t **list, char *res, char *qty, dep_print_t dprint)
{
    extract_t *new = create_extract(res, qty, dprint);
    extract_t *tmp = *list;

    if (list == NULL || *list == NULL) {
        *list = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
