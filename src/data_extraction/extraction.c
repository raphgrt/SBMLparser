/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extraction.c
*/

#include "../../include/sbml.h"

int check_attribute_exist(attribute_t *list, char *name, char *value)
{
    attribute_t *runner = NULL;

    if (list == NULL)
        return (0);
    runner = list;
    while (runner != NULL) {
        if (strcmp(runner->name, name) == 0 &&
            strcmp(runner->value, value) == 0) {
            return (1);
        }
        runner = runner->next;
    }
    return (0);
}

char *get_value_attribute(attribute_t *list, char *name)
{
    attribute_t *runner = NULL;

    if (list == NULL)
        return (NULL);
    runner = list;
    while (runner != NULL) {
        if (!runner->name)
            return (NULL);
        if (strcmp(runner->name, name) == 0)
            return (runner->value);
        runner = runner->next;
    }
    return (NULL);
}

static void apply_dependancies(tag_t *tags)
{
    tag_t *runner = tags;
    dependencies_list_t *dependencies = NULL;
    int operation;

    if (tags == NULL)
        return;
    while (runner) {
        operation = runner->tag_type == LISTOF || runner->tag_type == REACTION;
        if (runner->type == OPEN_TAG && operation)
            add_dependencies(&dependencies, set_dependencies(runner->name),
            runner);
        if (runner->type == END_TAG && operation)
            remove_last_dep(&dependencies);
        if (dependencies != NULL)
            runner->dependencies = dup_dependencies_list(dependencies);
        else
            runner->dependencies = NULL;
        runner = runner->next;
    }
}

extract_t *extract_data(char *search, tag_t *list, extract_t *res)
{
    tag_t *runner = list;

    if (!search || !list)
        return (NULL);
    apply_dependancies(list);
    while (runner) {
        if (runner->tag_type == COMPARTMENT)
            extract_compartment(search, runner, res);
        if (runner->tag_type == SPECIES_REFERENCE)
            extract_species(search, runner, res);
        if (runner->tag_type == REACTION)
            extract_reaction(search, runner, res);
        runner = runner->next;
    }
    if (!res->next)
        extract_chemicals(list, res);
    res = res->next;
    return (res);
}
