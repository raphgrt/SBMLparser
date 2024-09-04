/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** classical.c
*/

#include "../../include/sbml.h"


void split_alpha(extract_t *source, extract_t **front, extract_t **back)
{
    extract_t *fast;
    extract_t *slow;

    slow = source;
    fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

extract_t *alpha_merge(extract_t *a, extract_t *b)
{
    extract_t *result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (strcmp(a->result, b->result) < 0) {
        result = a;
        result->next = alpha_merge(a->next, b);
    } else {
        result = b;
        result->next = alpha_merge(a, b->next);
    }
    return (result);
}

void alpha_merge_sort(extract_t **ext)
{
    extract_t *head = *ext;
    extract_t *a;
    extract_t *b;

    if ((head == NULL) || (head->next == NULL))
        return;
    split_alpha(head, &a, &b);
    alpha_merge_sort(&a);
    alpha_merge_sort(&b);
    *ext = alpha_merge(a, b);
}
