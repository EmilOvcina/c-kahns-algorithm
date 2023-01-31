#include<assert.h>
#include"LinkedList.h"
#include<stdio.h>
#include<stdlib.h>


LinkedList *LinkedList_new(void) {
    LinkedList *ll = malloc(sizeof(LinkedList));
    if(!ll) {
        return NULL; //skriv en fejlbesked til stderr
    }
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}

void LinkedList_delete(LinkedList *ll) {
    LinkedListNode *next;
    for(LinkedListNode *node = ll->head; node; node = next) {
        next = node->next;
        free(node);
    }
    free(ll);
}

LinkedListNode *LinkedList_append(LinkedList *ll, void *elem) {
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if(!node) {
        return NULL; //skriv en fejlbesked til stderr
    }
    node->next = NULL;
    node->data = elem;
    if(ll->tail) {//listen er ikke tom
        ll->tail->next = node;
        node->prev = ll->tail;
        ll->tail = node;
    }
    else { //listen er tom
        ll->head = node;
        ll->tail = node;
        node->prev = NULL;
    }
    ++ll->size;
    return node;
}

void *LinkedList_popFront(LinkedList *ll) {
    if(ll->size == 0) { //hvis listen er tom
        return NULL; //skriv en fejlbesked til stderr
    }
    if(ll->head == ll->tail) { //hvis der kun er et element
        ll->tail = NULL;
    }
    LinkedListNode *node = ll->head;
    void *element = node->data;
    ll->head = node->next;
    //node->next->prev = NULL;
    free(node);
    --ll->size;
    return element;
}

LinkedListNode *LinkedList_find(LinkedList *ll, void *elem) {
    for(LinkedListNode *node = ll->head; node; node = node->next) {
        if(node->data == elem) {
            return node;
        }
    }
    return NULL;
}

void *LinkedList_remove(LinkedList *ll, LinkedListNode *node) {
    assert(ll);
    assert(node);
    void *data = node->data;
    if(!node->prev) { //første element
        ll->head = node->next;
        //node->next->prev = NULL;
    }
    else { //der er elementer før dette
        node->prev->next = node->next;
    }
    if(!node->next) { // sidste node i listen
        ll->tail = node->prev;
    }
    else {
        node->next->prev = node->prev;
    }
    --ll->size;
    free(node);
    return data;
}