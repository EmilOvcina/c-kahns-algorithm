//
// Created by Emil Ovcina on 02/12/2019.
//

#include "Graph.h"
#include<stdio.h>
#include <stdlib.h>

// Allocates and constructs a new graph with n vertices.
// Returns a pointer to the new graph, or NULL on error.
// Post: the caller owns the graph.
Graph* graph_new(int size)
{
    Graph* newGraph = malloc(sizeof(Graph));
    if(!newGraph) return NULL;
    newGraph->vertices = calloc(size , sizeof(Vertex));
    newGraph->numVertices = size;
    for(int i = 0; i < size; i++) {
        newGraph->vertices[i].id = i;
        newGraph->vertices[i].inNeighbours = LinkedList_new();
        newGraph->vertices[i].outNeighbours = LinkedList_new(); 
    }
    newGraph->numEdges = 0;
    return newGraph;
}

// Adds an edge from the i'th to the j'th vertex (0-indexed).
void Graph_addEdge(Graph *g, int i, int j) {
    ++g->numEdges;
    Vertex* v1 = g->vertices + i;
    Vertex* v2 = g->vertices + j;
    LinkedList_append(v1->outNeighbours, &(v2->id));
    LinkedList_append(v2->inNeighbours, &(v1->id));
}

// Reads a graph from the given file and returns a newly
// constructed Graph representing it.
// Returns a pointer to the read graph, or NULL on error.
// Post: the caller owns the graph.
Graph *Graph_read(const char *filename) {
    FILE *stream;
    stream = fopen(filename, "r");

    //få mSize
    char* first = NULL;
    size_t firstLine = 0;
    getline(&first, &firstLine, stream);

    int mSize = atoi(first);

    if(mSize == 0){
        return NULL;
    }
    Graph* graph = graph_new(mSize);
    char* lineptr = NULL;
    size_t line = 0;

    for(int i = 0; i < mSize && getline(&lineptr, &line, stream); i++){
        for(int j = 0; j < mSize ; j++){
            char c = lineptr[j];
            int number = atoi(&c);
            if (number == 1){
                Graph_addEdge(graph, i, j);
            }
        }
    }
    free(lineptr);
    free(first);
    fclose(stream);
    return graph;
}

// Deallocates the given graph and all its associated memory.
void Graph_delete(Graph *g) {
    for(int i = 0; i < g->numVertices; i++) {
        LinkedList_delete(g->vertices[i].inNeighbours);
        LinkedList_delete(g->vertices[i].outNeighbours);
    }
    free(g->vertices);
    free(g);
}

// Prints some useful information about the given graph.
void Graph_print(Graph *g) {
    printf("Number of verticies: %d\n", g->numVertices);
    printf("Number of edges: %d\n", g->numEdges);
}