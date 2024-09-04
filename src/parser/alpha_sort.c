/*
** EPITECH PROJECT, 2024
** sbml_parser
** File description:
** alpha_sort.c
*/

#include "../../include/sbml.h"

static tag_t *merge(tag_t *first, tag_t *second)
{
    if (!first)
        return (second);
    if (!second)
        return (first);
    if (strcmp(first->name, second->name) < 0) {
        first->next = merge(first->next, second);
        return (first);
    } else {
        second->next = merge(first, second->next);
        return (second);
    }
}

static void split(tag_t *source, tag_t **front, tag_t **back)
{
    tag_t *fast;
    tag_t *slow;

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

void merge_sort(tag_t **source)
{
    tag_t *head = *source;
    tag_t *a;
    tag_t *b;

    if ((head == NULL) || (head->next == NULL))
        return;
    split(head, &a, &b);
    merge_sort(&a);
    merge_sort(&b);
    *source = merge(a, b);
}

static attribute_t *merge_attributes(attribute_t *first, attribute_t *second)
{
    if (!first)
        return (second);
    if (!second)
        return first;
    if (strcmp(first->name, second->name) < 0) {
        first->next = merge_attributes(first->next, second);
        return (first);
    } else {
        second->next = merge_attributes(first, second->next);
        return (second);
    }
}

void split_attributes(attribute_t *src, attribute_t **front, attribute_t **bck)
{
    attribute_t *fast;
    attribute_t *slow;

    slow = src;
    fast = src->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = src;
    *bck = slow->next;
    slow->next = NULL;
}

void merge_sort_attributes(attribute_t **source)
{
    attribute_t *head = *source;
    attribute_t *a;
    attribute_t *b;

    if ((head == NULL) || (head->next == NULL))
        return;
    split_attributes(head, &a, &b);
    merge_sort_attributes(&a);
    merge_sort_attributes(&b);
    *source = merge_attributes(a, b);
}
