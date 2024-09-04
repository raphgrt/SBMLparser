/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** extract_print.c
*/

#include "../../include/sbml.h"

void compartment_print(extract_t *list, char *id)
{
    extract_t *runner;

    if (list == NULL)
        return;
    alpha_merge_sort(&list);
    runner = list;
    printf("List of species in compartment %s\n", id);
    while (runner) {
        printf("--->%s\n", runner->result);
        runner = runner->next;
    }
}

static void norm_print(char *type, char *id)
{
    printf("List of %s consuming species %s (quantities)\n", type, id);
}

void species_print(extract_t *list, char *id)
{
    extract_t *runner;
    int first_a = 0;
    int first_b = 0;

    alpha_merge_sort(&list);
    runner = list;
    while (runner && runner->print_type == SPECIES_PRINT) {
        if (runner->extract_type == LISTOF_REACTANS && first_a == 0) {
            norm_print("reactions", id);
            first_a++;
        }
        if ((runner->extract_type == LISTOF_REACTANS ||
            runner->extract_type == LISTOF_PRODUCT) && first_a == 1)
            printf("--->%s (%s)\n", runner->result, runner->quantity);
        if (runner->extract_type == LISTOF_PRODUCT && first_b == 0) {
            norm_print("products", id);
            first_b++;
        }
        runner = runner->next;
    }
}

void chemical_print(extract_t *list)
{
    extract_t *runner;

    if (list == NULL)
        return;
    alpha_merge_sort(&list);
    runner = list;
    printf("List of species\n");
    while (runner) {
        printf("--->%s\n", runner->result);
        runner = runner->next;
    }
}

void reaction_print(extract_t *list, char *id)
{
    extract_t *runner;
    int first_a = 0;
    int first_b = 0;

    runner = list;
    while (runner && runner->print_type == REACTION_PRINT) {
        if (runner->extract_type == LISTOF_REACTANS && first_a == 0) {
            printf("List of reactants of reaction %s\n", id);
            first_a++;
        }
        if ((runner->extract_type == LISTOF_REACTANS ||
            runner->extract_type == LISTOF_PRODUCT) && first_a == 1)
            printf("--->%s\n", runner->result);
        if (runner->extract_type == LISTOF_PRODUCT && first_b == 0) {
            printf("List of products of reaction %s\n", id);
            first_b++;
        }
        runner = runner->next;
    }
}
