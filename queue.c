#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *list = malloc(sizeof(struct list_head));
    INIT_LIST_HEAD(list);
    return list;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    element_t *node = NULL, *safe = NULL;
    list_for_each_entry_safe(node, safe, head, list) {
        free(node->value);
        free(node);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if ((!head) || (!s))
        return false;
    element_t *node = malloc(sizeof(element_t));
    if (!node)
        return false;
    node->value = strdup(s);
    if (!node->value)
        return false;
    list_add(&node->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if ((!head) || (!s))
        return false;
    element_t *node = malloc(sizeof(element_t));
    if (!node)
        return false;
    node->value = strdup(s);
    if (!node->value)
        return false;
    list_add_tail(&node->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if ((!head) || (!sp) || (bufsize == 0))
        return NULL;
    element_t *node = list_entry(head->next, element_t, list);
    if (!node->value)
        return NULL;
    strncpy(sp, node->value, bufsize);
    list_del(head->next);
    return node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if ((!head) || (!sp) || (bufsize == 0))
        return NULL;
    element_t *node = list_entry(head->prev, element_t, list);
    if (!node->value)
        return NULL;
    strncpy(sp, node->value, bufsize);
    list_del(head->prev);
    return node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each(li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head)
        return false;
    if (list_empty(head))
        return false;

    size_t middle_index = q_size(head) / 2;
    size_t len = 0;

    element_t *node = NULL, *safe = NULL;
    list_for_each_entry_safe(node, safe, head, list) {
        if (len == middle_index) {
            list_del(&node->list);
            free(node->value);
            free(node);
            return true;
        }
        len++;
    }

    return false;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
// refer to Week1 Homework q3
static void rebuild_list_link(struct list_head *head)
{
    if (!head)
        return;
    struct list_head *node, *prev;
    prev = head;
    node = head->next;
    while (node) {
        node->prev = prev;
        prev = node;
        node = node->next;
    }
    prev->next = head;
    head->prev = prev; /* GGGG */
}

struct list_head *list_tail(struct list_head *head)
{
    while (head && head->next)
        head = head->next;
    return head;
}

void q_sort(struct list_head *head, bool descend)
{
    if (!head)
        return;
    if (list_empty(head))
        return;
    if (q_size(head) == 1)
        return;

    int i = 0;
#define MAX_NODES 100000
    struct list_head *begin[MAX_NODES];
    struct list_head *result = NULL, *left = NULL, *right = NULL;
    begin[0] = head->next;
    head->prev->next = NULL;
    while (i >= 0) {
        struct list_head *L = begin[i], *R = list_tail(begin[i]);
        if (L != R) {
            struct list_head *pivot = L;
            char *value = list_entry(pivot, element_t, list)->value /* HHHH */;
            struct list_head *p = pivot->next;
            pivot->next = NULL; /* break the list */
            while (p) {
                struct list_head *n = p;
                p = p->next;
                char *n_value =
                    list_entry(n, element_t, list)->value /* IIII */;
                if (strcmp(n_value, value) > 0) {
                    n->next = right;
                    right = n;
                } else {
                    n->next = left;
                    left = n;
                }
            }
            begin[i] = left;
            begin[i + 1] = pivot /* JJJJ */;
            begin[i + 2] = right /* KKKK */;
            left = right = NULL;
            i += 2;
        } else {
            if (L) {
                L->next = result;
                result = L;
            }
            i--;
        }
    }
    head->next = result;
    rebuild_list_link(head);
#undef MAX_NODES
}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
