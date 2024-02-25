#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cvector.h" //https://github.com/eteran/c-vector

#define sizeB(a) (sizeof(a)/sizeof 0[a]) 

cvector_vector_type(cvector_vector_type(char*)) pathGraph = NULL;
cvector_vector_type(cvector_vector_type(char*)) graph = NULL;
cvector_vector_type(char*) useEdges = NULL;

void ReadGraph() {
	FILE* f = fopen("graph.txt", "r");
	char buffer[256];
	int n = 0;
	int i = 0;
	int events = 0;

	while ((fgets(buffer, 256, f)) != NULL)
	{
		char* c = malloc(sizeof(char) * 256);
		char* c1 = malloc(sizeof(char) * 256);
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
				}
			}
			else {
				break;
			}
			n++;
		}
		i++;
		cvector_push_back(graph, line);
	}
}

void StartSerchGraph() {
	int events = 0;
	char* line = NULL;

	for (int i = 0; i < cvector_size(graph);i++) {
		events = 0;

		if (cvector_size(graph[0][0]) == cvector_size(graph[i][0])) {
			for (int j = 0; j < strlen(graph[0][0]); j++) {	//Проверка на совпадение
				if (graph[i][0][j] != graph[0][0][j]) {
					events = 1;
					break;
				}
			}
		}
		else {
			events = 1;
		}
		

		if (events == 0) {
			cvector_vector_type(char*) line = NULL;

			cvector_push_back(line, graph[i][0]);
			cvector_push_back(line, graph[i][1]);

			cvector_push_back(pathGraph, line);
			cvector_push_back(useEdges, graph[i][0]);
		}
	}
}

void SerchGraph() {
	cvector_vector_type(cvector_vector_type(char*)) resPathGraph = NULL;
	cvector_vector_type(char*) resUseEdges = useEdges;
	int eventsUseEdges = 0;
	int eventsUseEdges1 = 0;
	int eventsCoinEdges = 0;

	for (int i = 0; i < cvector_size(graph);i++) {
		eventsUseEdges = 0;

		for (int u = 0; u < cvector_size(useEdges); u++) {//Проверяем на повторение 
			if (useEdges[u] == graph[i][0]) {
				eventsUseEdges = 1;
				break;
			}
		}

		if (eventsUseEdges == 0) {
			for (int j = 0; j < cvector_size(pathGraph); j++) {
				char* c = graph[i][0];
				char* c1 = pathGraph[j][cvector_size(pathGraph[j]) - 1];
				eventsCoinEdges = 0;
				eventsUseEdges1 = 0;

				for (int u = 0; u < cvector_size(pathGraph[j]); u++) {
					if (strlen(graph[i][1]) == strlen(pathGraph[j][u])) {
						for (int g = 0; g < strlen(graph[i][0]); g++) {
							if (graph[i][1][g] == pathGraph[j][u][g]) {
								eventsUseEdges1 = 1;
								break;
							}
						}
					}
				}

				if (eventsUseEdges1 == 0) {
					if (strlen(c) == strlen(c1)) {
						for (int g = 0; g < strlen(c); g++) {
							if (c[g] != c1[g]) {
								eventsCoinEdges = 1;
								break;
							}
						}
					}
					else {
						eventsCoinEdges = 1;
					}


					if (eventsCoinEdges == 0) {
						cvector_vector_type(char*) line = NULL;
						for (int g = 0; g < cvector_size(pathGraph[j]); g++) {
							cvector_push_back(line, pathGraph[j][g]);
							printf("%s -> ", pathGraph[j][g]);
						}
						printf("%s\n", graph[i][1]);
						cvector_push_back(line, graph[i][1]);
						cvector_push_back(resPathGraph, line);
						cvector_push_back(resUseEdges, graph[i][0]);
					}
				}
			}
		}
	}

	pathGraph = resPathGraph;
	useEdges = resUseEdges;
}

int main() {
	ReadGraph();
	StartSerchGraph();
	SerchGraph();

	/*for (int i = 0; i < cvector_size(graph);i++) {
		printf("%s ", graph[i][0]);
		printf("%s\n", graph[i][1]);
	}*/

	return 0;
}
