#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "cvector.h" //https://github.com/eteran/c-vector

#define size(a) (sizeof(a)/sizeof 0[a]) 

cvector_vector_type(cvector_vector_type(char)) *graph = NULL;
cvector_vector_type(cvector_vector_type(char)) *pathGraph = NULL;

int number = 0;

void Split(char arr[256]) {
	cvector_vector_type(char) *res = NULL;
	char *istr;

	arr = strtok(arr, "\n");
	istr = strtok(arr, " ");
	while (istr != NULL)
	{
		number += 1;
		cvector_push_back(res, istr);
		istr = strtok(NULL, " ");
	}

	cvector_push_back(graph, res);

	/*istr = res[0];
	printf("%s ", istr);
	istr = res[1];
	printf("%s\n", istr);*/
}

void ReadGraph() {
	FILE* f = fopen("graph.txt", "r");
	char line[256];

	while ((fgets(line, 256, f)) != NULL)
	{
		Split(line);
	}
}

int SerchPathGraph() {
	for (int i = 0; i < cvector_size(graph); i++) {
		printf("%s ", graph[i][0]);
		printf("%s\n", graph[i][1]);
	}
	
	return 1;
}

int main() {
	/*cvector_vector_type(char) r = NULL;
	cvector_push_back(r, "a");
	cvector_push_back(r, "b");

	for (int i = 0; i < 10; i++) {
		cvector_push_back(graph, r);
	}

	if (graph[0][1] == (char)"b") {
		printf("true");
	}*/

	ReadGraph();
	SerchPathGraph();

	return 0;
}