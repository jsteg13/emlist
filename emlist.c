#include "emlist.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// TODO would a static array backed implementation be useful, too?

LinkedList* emlist_create() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    emlist_initialize(list);
    return list;
}

void emlist_destroy(LinkedList* list) {
    if(list != NULL) {
        free(list);
    }
}

void emlist_initialize(LinkedList* list) {
    list->head = NULL;
}

bool emlist_contains(LinkedList* list, void* value) {
    LinkedListIterator iterator = emlist_iterator(list);
    LinkedListElement* candidate = NULL;
    while((candidate = emlist_iterator_next(&iterator)) != NULL) {
        if(candidate->value == value) {
            return true;
        }
    }
    return false;
}

bool emlist_insert(LinkedList* list, void* value) {
    LinkedListElement* element = (LinkedListElement*) malloc(
            sizeof(LinkedListElement));
    if(element != NULL) {
        element->value = value;
        element->next = NULL;
        if(emlist_is_empty(list)) {
            list->head = element;
        } else {
            LinkedListIterator iterator = emlist_iterator(list);
            LinkedListElement* current = NULL;
            while((current = emlist_iterator_next(&iterator)) != NULL
                    && current->next != NULL) {
                continue;
            }
            current->next = element;
        }
    }
}

bool emlist_remove(LinkedList* list, void* value) {
    LinkedListElement* prev = NULL;
    LinkedListElement* next = NULL;
    LinkedListIterator iterator = emlist_iterator(list);
    while((next = emlist_iterator_next(&iterator)) != NULL) {
        if(next->value == value) {
            if(prev == NULL) {
                list->head = next->next;
            } else {
                prev->next = next->next;
            }
            free(next);
            return true;
        }
        prev = next;
    }
    return false;
}

int emlist_size(LinkedList* list) {
    int size = 0;
    LinkedListIterator iterator = emlist_iterator(list);
    LinkedListElement* element = NULL;
    while((element = emlist_iterator_next(&iterator)) != NULL) {
        ++size;
    }
    return size;
}

bool emlist_is_empty(LinkedList* list) {
    return list->head == NULL;
}

LinkedListIterator emlist_iterator(LinkedList* list) {
    LinkedListIterator iterator;
    iterator.next = list->head;
    return iterator;
}

LinkedListElement* emlist_iterator_next(LinkedListIterator* iterator) {
    LinkedListElement* next = iterator->next;
    iterator->next = next != NULL ? next->next : NULL;
    return next;
}
