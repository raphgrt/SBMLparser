/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** dependencies.c
*/

#include "../../include/sbml.h"

dependencies_t set_dependencies(char *tag_title)
{
    if (strcmp(tag_title, "listOfCompartments") == 0)
        return (LISTOF_COMPARTEMENT);
    if (strcmp(tag_title, "listOfSpecies") == 0)
        return (LISTOF_SPECIES);
    if (strcmp(tag_title, "listOfReactions") == 0)
        return (LISTOF_REACTIONS);
    if (strcmp(tag_title, "listOfReactants") == 0)
        return (LISTOF_REACTANS);
    if (strcmp(tag_title, "listOfProducts") == 0)
        return (LISTOF_PRODUCT);
    if (strcmp(tag_title, "reaction") == 0)
        return (REACT_DEP);
    return (NONE);
}

static dependencies_list_t *create_dependencies(dependencies_t dep,
    tag_t *current)
{
    dependencies_list_t *new;

    new = malloc(sizeof(dependencies_list_t));
    if (!new)
        exit(84);
    new->next = NULL;
    new->dep = dep;
    new->quick_link = current;
    return (new);
}

void add_dependencies(dependencies_list_t **list, dependencies_t dep,
    tag_t *current)
{
    dependencies_list_t *new = create_dependencies(dep, current);
    dependencies_list_t *tmp = *list;

    if (list == NULL || *list == NULL) {
        *list = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

dependencies_list_t *dup_dependencies_list(dependencies_list_t *list)
{
    dependencies_list_t *new = NULL;
    dependencies_list_t *runner = list;

    if (list == NULL)
        return (NULL);
    while (runner != NULL) {
        add_dependencies(&new, runner->dep, runner->quick_link);
        runner = runner->next;
    }
    return (new);
}

void remove_last_dep(dependencies_list_t **list)
{
    dependencies_list_t *runner = *list;
    dependencies_list_t *tmp = NULL;

    if (runner == NULL || list == NULL)
        return;
    if (runner->next == NULL) {
        free(runner);
        *list = NULL;
        return;
    }
    while (runner->next != NULL) {
        tmp = runner;
        runner = runner->next;
    }
    free(runner);
    tmp->next = NULL;
}

void print_dependencies_list(dependencies_list_t *list)
{
    dependencies_list_t *runner = list;

    while (runner != NULL) {
        printf("Dependency: %d\n", runner->dep);
        runner = runner->next;
    }
}
