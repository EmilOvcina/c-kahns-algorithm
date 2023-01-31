//
// Created by Emil Ovcina on 02/12/2019.
//
#include "cycleDetection.h"
#include<stdio.h>

// Runs Kahn's algorithm on the graph, and outputs 'CYCLE DETECTED!\n'
// if a DAG cannot be created, or the vertices as a list fx. '4, 0, 1, 3, 2\n'
// representing an ordering in the DAG.
// The output is printed to stdout.
// The input may be altered in the process.
void cycleDetection(Graph *g)
{
    LinkedList* L = LinkedList_new();
    LinkedList* S = LinkedList_new();

    for(int i = 0; i < g->numVertices; i++) {
        Vertex* v = g->vertices+i;
        if(!(v->inNeighbours->head)) {
            LinkedList_append(S, &(v->id));
        }
    }
    //Alt virker måske hertil
    while (S->size > 0)
    {
        void *u = LinkedList_popFront(S);
        LinkedList_append(L, u);

        for(int i = 0; i < g->numVertices; i++) {
            Vertex* v = g->vertices + i;
            LinkedListNode *edge = LinkedList_find(v->inNeighbours, u);
            if(edge) {
                if(v->inNeighbours->size == 1) {
                    LinkedList_append(S, &(v->id));
                }
                LinkedList_remove(v->inNeighbours, edge);
                --g->numEdges;
            }
        }  
    }

    if(g->numEdges > 0) {
            printf("%s\n", "CYCLE DETECTED!");
        } else {
            for(LinkedListNode *node = L->head; node && node != L->tail; node = node->next) {
                printf("%d, ", *((int*)node->data));
            }
            printf("%d\n", *((int*)L->tail->data));
        }

    LinkedList_delete(L);
    LinkedList_delete(S);
}
