/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extract_species.c
*/

#include "../../include/sbml.h"

static tag_t *get_last_reaction(dependencies_list_t *dep)
{
    dependencies_list_t *runner;
    dependencies_list_t *tmp = NULL;

    if (dep == NULL || dep->dep == NONE)
        return (NULL);
    runner = dep;
    while (runner) {
        if (runner->dep == REACT_DEP)
            tmp = runner;
        runner = runner->next;
    }
    if (!tmp)
        return (NULL);
    return (tmp->quick_link);
}

dependencies_t get_last_dep(dependencies_list_t *dep)
{
    dependencies_list_t *runner;

    if (dep == NULL)
        return NONE;
    runner = dep;
    while (runner->next) {
        runner = runner->next;
    }
    return (runner->dep);
}

void give_reaction_value(dependencies_list_t *dep, attribute_t *attr,
    extract_t *res)
{
    tag_t *latest = get_last_reaction(dep);
    char *reaction_id = NULL;
    char *stoicho = NULL;
    dependencies_t last = get_last_dep(dep);

    if (dep == NULL || attr == NULL || latest == NULL)
        return;
    stoicho = get_value_attribute(attr, "stoichiometry");
    reaction_id = get_value_attribute(latest->attributes, "id");
    add_extract(&res, reaction_id, stoicho, (dep_print_t) {last, 4});
}

void extract_species(char *_id, tag_t *elem, extract_t *res)
{
    if (!_id || !elem)
        return;
    if (elem->tag_type == SPECIES_REFERENCE &&
        check_attribute_exist(elem->attributes, "species", _id) == 1) {
        give_reaction_value(elem->dependencies, elem->attributes, res);
    }
}
