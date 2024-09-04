/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** sbml.h
*/

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifndef SBML_PARSER_H
    #define SBML_PARSER_H
    #define HELPER_PATH "./helper.txt"
    #define HELPER_LEN 400
    #define TAG_NB 9

char **my_str_to_word_array_synthesis(char const *str);
char **my_str_to_word_array(char const *str);
char **my_str_to_word_array_sep(const char *str, const char sep);

typedef enum type_e {
    INLINE_TAG,
    OPEN_TAG,
    END_TAG,
    REMOVE
} type_t;

typedef enum tag_type_e {
    OTHER,
    COMPARTMENT,
    SPECIES,
    REACTION,
    SPECIES_REFERENCE,
    LISTOF
} tag_type_t;

typedef enum dependencies_e {
    NONE,
    LISTOF_COMPARTEMENT,
    LISTOF_SPECIES,
    LISTOF_REACTIONS,
    LISTOF_REACTANS,
    LISTOF_PRODUCT,
    REACT_DEP
} dependencies_t;

typedef enum print_type_e {
    NO_PRINT,
    CHEMICALS_PRINT,
    COMPARTMENT_PRINT,
    REACTION_PRINT,
    SPECIES_PRINT
} print_type_t;

typedef struct attribute_s {
    char *name;
    char *value;
    struct attribute_s *next;
} attribute_t;

typedef struct dependencies_list_s dependencies_list_t;

typedef struct tag_s {
    char *name;
    type_t type;
    tag_type_t tag_type;
    attribute_t *attributes;
    dependencies_list_t *dependencies;
    struct tag_s *next;
} tag_t;

struct dependencies_list_s {
    dependencies_t dep;
    tag_t *quick_link;
    struct dependencies_list_s *next;
};

typedef struct sbml_s {
    char *buffer;
    char **buffer_array;
    char flags[4];
    tag_t *tags;
} sbml_t;

typedef struct extract_s {
    char *result;
    char *quantity;
    dependencies_t extract_type;
    print_type_t print_type;
    struct extract_s *next;
} extract_t;

typedef struct dep_print_s {
    dependencies_t extract_type;
    print_type_t pt;
} dep_print_t;

void parser(sbml_t *sbml);
void remove_spaces_and_tabs(char *input);
char **parse_line(char *input);
void add_tag(tag_t **list, char *name,
    attribute_t **attribute);
void add_attribute(attribute_t **list, char *str);
type_t get_type(char *str);
void merge_sort(tag_t **source);
void merge_sort_attributes(attribute_t **source);
void print_simple_parser(tag_t *list);
void simple_parser(tag_t *list);
void print_dependencies_list(dependencies_list_t *list);
void add_dependencies(dependencies_list_t **list, dependencies_t dep,
    tag_t *current);
dependencies_t set_dependencies(char *tag_title);
dependencies_list_t *dup_dependencies_list(dependencies_list_t *list);
extract_t *extract_data(char *search, tag_t *list, extract_t *res);
void remove_last_dep(dependencies_list_t **list);
char *get_value_attribute(attribute_t *list, char *name);
int check_attribute_exist(attribute_t *list, char *name, char *value);

void extract_compartment(char *search_id, tag_t *elem, extract_t *res);
void extract_species(char *_id, tag_t *elem, extract_t *res);
void extract_reaction(char *_id, tag_t *elem, extract_t *res);
void extract_chemicals(tag_t *head, extract_t *res);
void add_extract(extract_t **list, char *res, char *qty, dep_print_t dprint);
void print_struct(tag_t **tags);
void compartment_print(extract_t *list, char *id);
void species_print(extract_t *list, char *id);
void chemical_print(extract_t *list);
void reaction_print(extract_t *list, char *id);
void alpha_merge_sort(extract_t **ext);
void json_print(extract_t *list);
#endif //SBML_PARSER_H
