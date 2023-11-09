#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <vector>

#define NUM_VERTICES 6

using namespace std;

struct EdgeNode {
    char nodeName;
    EdgeNode* nextNode = NULL;
};

struct GraphVertex {
    char nodeName;
    vector<GraphVertex*> neighbors;
};

struct VertexList {
    char nodeName;
    EdgeNode* adjacencyList = NULL;
    GraphVertex* graphNode = NULL;
    VertexList* nextNode = NULL;
};

EdgeNode* edgeListHead = NULL;
EdgeNode* edgeListTail = NULL;

VertexList* vertexListHead = NULL;
VertexList* vertexListTail = NULL;
VertexList* tempVertexListTail = NULL;

void createVertexList(VertexList* newNode) {
    if (vertexListHead == NULL) {
        vertexListHead = newNode;
        vertexListTail = newNode;
        tempVertexListTail = newNode;
    } else {
        tempVertexListTail->nextNode = newNode;
        tempVertexListTail = newNode;
        vertexListTail = newNode;
    }
}

void createAdjacencyList(EdgeNode* newNode, VertexList* vertexNodeAddr) {
    if (edgeListHead == NULL) {
        vertexNodeAddr->adjacencyList = newNode;
        edgeListHead = newNode;
        edgeListTail = newNode;
    } else {
        edgeListTail->nextNode = newNode;
        edgeListTail = newNode;
    }
}

void traverseAdjacencyList(EdgeNode* baseAddr) {
    while (baseAddr != NULL) {
        printf("%c -> ", baseAddr->nodeName);
        baseAddr = baseAddr->nextNode;
    }
    printf("NULL");
}

void addEdge(GraphVertex* srcVertex, GraphVertex* dstVertex) {
    srcVertex->neighbors.push_back(dstVertex);
    dstVertex->neighbors.push_back(srcVertex);
}

int main() {
    srand(time(NULL));
    bool hasEdge;
    EdgeNode* newEdgeNode = NULL;
    GraphVertex* newGraphVertex = NULL;
    VertexList* newVertexList = NULL;

    tempVertexListTail = vertexListTail;

    for (size_t i = 0; i < NUM_VERTICES; i++) {
        newVertexList = (VertexList*)calloc(1, sizeof(VertexList));
        newVertexList->nodeName = 'A' + i;
        newGraphVertex = (GraphVertex*)calloc(1, sizeof(GraphVertex));
        newGraphVertex->nodeName = 'A' + i;
        newVertexList->graphNode = newGraphVertex;
        createVertexList(newVertexList);

        edgeListHead = NULL;
        edgeListTail = NULL;

        for (size_t j = 0; j < NUM_VERTICES; j++) {
            if (i == j)
                continue;
            else {
                hasEdge = rand() % 2;

                if (hasEdge == true) {
                    newEdgeNode = (EdgeNode*)calloc(1, sizeof(EdgeNode));
                    newEdgeNode->nodeName = 'A' + j;
                    createAdjacencyList(newEdgeNode, newVertexList);
                    addEdge(newGraphVertex, vertexListHead->graphNode);
                }
            }
        }
    }

    printf("Graph Information:\n\n");

    tempVertexListTail = vertexListHead;
    while (tempVertexListTail != NULL) {
        printf("Adjacency List of Node %c: ", tempVertexListTail->nodeName);
        traverseAdjacencyList(tempVertexListTail->adjacencyList);
        printf("\n");
        tempVertexListTail = tempVertexListTail->nextNode;
    }

    printf("\n\nEdges between Nodes:\n\n");

    tempVertexListTail = vertexListHead;

    for (size_t i = 0; i < NUM_VERTICES; i++) {
        edgeListTail = tempVertexListTail->adjacencyList;

        printf("Edges for Node %c: ", tempVertexListTail->nodeName);
        while (edgeListTail != NULL) {
            printf("%c ", edgeListTail->nodeName);
            edgeListTail = edgeListTail->nextNode;
        }
        printf("\n");

        tempVertexListTail = tempVertexListTail->nextNode;
    }

    return 0;
}

