#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include "cvector.h"

cvector_vector_type(cvector_vector_type(char))* graph = NULL;
char chars[256][256] = {"a", "b", "s", "d", "f", "g", "h", "j", "k", "l", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "z", "x", "c", "v", "b", "n", "m"};

void CreaterGraphs(int n) {
	for (int i = 0; i < n; i++) {
		char* a = chars[rand() % 26];
		for (int u = 0; u < 3; u++) {
			char* b = chars[rand()%26];
			if (a != b) {
				cvector_vector_type(char)* line = NULL;

				cvector_push_back(line, a);
				cvector_push_back(line, b);

				cvector_push_back(graph, line);
			}
			else {
				u = u - 1;
			}
		}
	}
}

int main() {
	CreaterGraphs(100);

	for (int i = 0; i < cvector_size(graph); i++) {
		printf("%s ", graph[i][0]);
		printf("%s\n", graph[i][1]);
	}

	return 0;
}