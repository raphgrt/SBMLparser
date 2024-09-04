/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extract_component.c
*/

#include "../../include/sbml.h"

extract_t *extract_info_from_species(tag_t **head, extract_t *res, char *_id)
{
    tag_t *run = *head;
    char *str;

    if (!head)
        return (res);
    while (run != NULL) {
        if (run->tag_type == SPECIES &&
            check_attribute_exist(run->attributes, "compartment", _id) == 1) {
            str = get_value_attribute(run->attributes, "name");
            add_extract(&res, str, NULL, (dep_print_t) {2, 2});
        }
        run = run->next;
    }
    return (res);
}

void extract_compartment(char *search_id, tag_t *elem, extract_t *res)
{
    if (!search_id || !elem)
        return;
    if (elem->tag_type == COMPARTMENT &&
        check_attribute_exist(elem->attributes, "id", search_id) == 1)
        res = extract_info_from_species(&elem, res, search_id);
}
