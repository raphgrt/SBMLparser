/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extract_reaction.c
*/

#include "../../include/sbml.h"

static dependencies_t get_last_dep(dependencies_list_t *dep)
{
    dependencies_list_t *runner;

    if (!dep)
        return (NONE);
    runner = dep;
    while (runner->next) {
        runner = runner->next;
    }
    return (runner->dep);
}

static dependencies_t avant_der(dependencies_list_t *dep, dependencies_t srch)
{
    dependencies_list_t *runner;

    if (!dep)
        return (NONE);
    runner = dep;
    while (runner && runner->next && runner->next->next) {
        runner = runner->next;
    }
    if (!runner)
        return (NONE);
    if (runner->dep == srch)
        return (runner->dep);
    return (0);
}

void give_react_prod(tag_t *tag, extract_t *res)
{
    dependencies_t latest;
    dependencies_t oui;
    tag_t *runner;
    char *species_id;

    if (!tag)
        return;
    latest = get_last_dep(tag->dependencies);
    oui = avant_der(tag->dependencies, latest);
    runner = tag;
    while (runner) {
        latest = get_last_dep(runner->dependencies);
        if (latest == oui && runner->tag_type == LISTOF &&
            runner->type != INLINE_TAG)
            break;
        species_id = get_value_attribute(runner->attributes, "species");
        add_extract(&res, species_id, NULL, (dep_print_t) {latest, 3});
        runner = runner->next;
    }
}

void extract_reaction(char *_id, tag_t *elem, extract_t *res)
{
    tag_t *runner;

    if (!_id || !elem)
        return;
    if (elem->tag_type == REACTION &&
        check_attribute_exist(elem->attributes, "id", _id) == 1) {
        give_react_prod(elem, res);
    }
}
