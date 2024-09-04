/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** struct.c
*/

#include "../../include/sbml.h"

static void split_name_attribute(char *str, attribute_t *element)
{
    int index = 0;

    for (index = 0; str[index] != '=' && str[index]; index ++);
    element->name = malloc(sizeof(char) * index + 1);
    strncpy(element->name, str, index);
    element->name = strtok(element->name, "\"=");
    element->name[index] = '\0';
    element->value = strtok(&str[index + 1], ">\"");
}

static attribute_t *create_attribute(char *str)
{
    attribute_t *new;

    if (!str)
        return (NULL);
    new = malloc(sizeof(attribute_t));
    if (!new)
        exit(84);
    split_name_attribute(str, new);
    new->next = NULL;
    return (new);
}

void add_attribute(attribute_t **list, char *str)
{
    attribute_t *new = create_attribute(str);
    attribute_t *tmp = *list;

    if (list == NULL || *list == NULL) {
        *list = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

static tag_type_t get_tag_type(char *word)
{
    if (strcmp(word, "compartment") == 0)
        return (COMPARTMENT);
    if (strcmp(word, "species") == 0)
        return (SPECIES);
    if (strcmp(word, "reaction") == 0)
        return (REACTION);
    if (strcmp(word, "speciesReference") == 0)
        return (SPECIES_REFERENCE);
    if (strncmp(word, "listOf", 6) == 0)
        return (LISTOF);
    return (OTHER);
}

static tag_t *create_tag(char *name, attribute_t **attribute)
{
    tag_t *new = malloc(sizeof(tag_t));

    if (!new)
        exit(84);
    new->type = get_type(name);
    new->name = strtok(name, "<>/");
    new->attributes = *attribute;
    new->tag_type = get_tag_type(new->name);
    new->dependencies = NULL;
    new->next = NULL;
    if (new->attributes && new->type == OPEN_TAG)
        new->type = INLINE_TAG;
    return (new);
}

void add_tag(tag_t **list, char *name,
    attribute_t **attribute)
{
    tag_t *new = create_tag(name, attribute);
    tag_t *tmp = *list;

    if (!tmp) {
        *list = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

static void free_attributes(attribute_t *list)
{
    attribute_t *tmp = list;
    attribute_t *next;

    while (tmp) {
        next = tmp->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
}

static void free_tag(attribute_t *list)
{
    attribute_t *tmp = list;
    attribute_t *next;

    while (tmp) {
        next = tmp->next;
        free(tmp->name);
        free(tmp->value);
        free(tmp);
        tmp = next;
    }
}
