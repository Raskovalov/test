#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cvector.h" //https://github.com/eteran/c-vector

#define sizeB(a) (sizeof(a)/sizeof 0[a]) 

cvector_vector_type(cvector_vector_type(char))* pathGraph = NULL;
cvector_vector_type(cvector_vector_type(char))* graph = NULL;
cvector_vector_type(char)* edges = NULL;
cvector_vector_type(int)* numberEdges = NULL;

void ReadGraph() {
	FILE* f = fopen("graph.txt", "r");
	char buffer[256];
	char* c = NULL;
	char* c1 = NULL;
	char* c2 = NULL;
	int n = 0;
	int events = 0;
	int ind = 0;

	while ((fgets(buffer, 256, f)) != NULL)
	{
		c = malloc(sizeof(char) * 256);
		c1 = malloc(sizeof(char) * 256);
		cvector_vector_type(char*) line = NULL;
		n = 0;

		for (int i = 0; i < sizeof(buffer); i++) {
			if (buffer[i] != '\0') {
				if (buffer[i] != ' ') {
					if (buffer[i] != '\n') {
						if (events == 0) {
							*(c + n) = buffer[i];
						}
						else {
							*(c1 + n) = buffer[i];
						}
					}
					else {
						*(c1 + n) = '\0';
						n = -1;
						events = 0;
						cvector_push_back(line, c1);
						//printf("%s\n", line[1]);
					}
				}
				else {
					*(c + n) = '\0';
					n = -1;
					events = 1;
					cvector_push_back(line, c);
					//printf("%s ", line[0]);
					if (cvector_size(edges) > 0) {
						c2 = edges[cvector_size(edges) - 1];
						if (strcmp(c, c2)) {
							cvector_push_back(edges, c);
							cvector_push_back(numberEdges, ind);
						}
					}
					else {
						cvector_push_back(edges, c);
						cvector_push_back(numberEdges, ind);
					}
				}
			}
			else {
				break;
			}
			n++;
		}
		ind++;
		cvector_push_back(graph, line);
	}
}

void StartSerchGraph() {
	int events = 0;
	char* c = NULL;
	char* c1 = NULL;
	for (int i = 0; i < cvector_size(graph);i++) {
		c = graph[0][0];
		c1 = graph[i][0];
		if (!strcmp(c, c1)) {
			cvector_vector_type(char*) line = NULL;

			cvector_push_back(line, graph[i][0]);
			cvector_push_back(line, graph[i][1]);

			cvector_push_back(pathGraph, line);
		}
		else {
			break;
		}
	}
}

int SerchGraph() {
	cvector_vector_type(cvector_vector_type(char))* resPathGraph = NULL;
	int eventsUseEdges = 0;
	int eventEdges = 0;
	char* c = NULL;
	char* c1 = NULL;

	for (int p = 0; p < cvector_size(pathGraph); p++) {
		for (int i = 0; i < cvector_size(graph);i++) {
			c = pathGraph[p][cvector_size(pathGraph[p]) - 1];
			c1 = graph[i][0];
			if (!strcmp(c, c1)) { //Проверка на совместимость вершин
				eventsUseEdges = 0;
				eventEdges = 1;

				for (int j = 0; j < cvector_size(pathGraph[p]);j++) {//Проверка на повторы в пути
					c = pathGraph[p][j];
					c1 = graph[i][1];
					if (!strcmp(c, c1)) {
						eventsUseEdges = 1;
					}
				}

				if (eventsUseEdges == 0) {
					cvector_vector_type(char)* line = NULL;
					for (int j = 0; j < cvector_size(pathGraph[p]);j++) {//Добавляем путь в список
						cvector_push_back(line, pathGraph[p][j]);
						//printf("%s -> ", pathGraph[p][j]);
					}
					//printf("%s\n", graph[i][1]);
					cvector_push_back(line, graph[i][1]);
					cvector_push_back(resPathGraph, line);

					c = graph[i][1];
					c1 = graph[cvector_size(graph) - 1][0];
					if (!strcmp(c, c1)) {
						for (int j = 0; j < cvector_size(line);j++) {
							printf("%s -> ", line[j]);
						}

						return 1;
					}
				}
			}
			else {
				if (eventEdges == 1) {
					eventEdges = 0;
					break;
				}
				else {//Переход на нужный индекс
					for (int j = 0; j < cvector_size(edges); j++) {
						c1 = edges[j];
						if (!strcmp(c, c1)) {
							i = numberEdges[j];
							break;
						}
					}
				}
			}
		}
	}

	pathGraph = resPathGraph;
	if (cvector_size(pathGraph) > 0) {
		SerchGraph();
	}

	return 0;
}

int main() {
	size_t start = time(NULL);
	ReadGraph();
	StartSerchGraph();
	SerchGraph();

	printf("\nTime: %lld m.", (time(NULL) - start) / 60);
	printf(" || %lld s.", time(NULL) - start);

	/*for (int i = 0; i < cvector_size(edges); i++) {
		printf("%s ", edges[i]);
		printf("%d\n", numberEdges[i]);
	}*/

	/*for (int i = 0; i < cvector_size(graph);i++) {
		printf("%s ", graph[i][0]);
		printf("%s\n", graph[i][1]);
	}*/

	return 0;
}
