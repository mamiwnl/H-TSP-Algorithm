#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


//struct for points
 	 typedef struct point {
    	int id;
   		int xCoor;
    	int yCoor;
  } point;


//global variables
    int inputSize;
	point *gen;
	int **adjMatrix;


//this function reading the integer in text file and creating a point struct and pointer refering the starting point of this struct array.
	point *createStruct(FILE *fp) {
     int id, xCoor, yCoor;
    //memory allocating for point
     point *input = malloc(sizeof(point));
    
     if (input == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }
    
     int index = 0;
    
    //reading integers and put them point struct array
     while (fscanf(fp, "%d %d %d", &id, &xCoor, &yCoor) == 3) {
    	//reallocating memory until all points are read.
        point *temp = realloc(input, (index + 1) * sizeof(point));
        if (temp == NULL) {
            fprintf(stderr, "Error reallocating memory\n");
            free(input);
            return NULL;
        }
        input = temp;
        input[index].id = id;
        input[index].xCoor = xCoor;
        input[index].yCoor = yCoor;
        index++;
    }
     inputSize = index;
     return input;
}

//dealallocating input pointer
	void freeStruct(point *input) {
     free(input);
}


  //creating adjacency matrix for all points	
	void createAdjMatrix(int rows, int cols) {
    int i, j;

    // Check if rows and cols equal to inputSize, if not, adjust them accordingly
    if (rows != inputSize || cols != inputSize) {
        rows = inputSize;
        cols = inputSize;
    }
	//allocating memory like 2d array
    adjMatrix = malloc(rows * sizeof(int *));
    for (i = 0; i < rows; i++) {
        adjMatrix[i] = malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            if (i < j)
            		//calculating distance between two points
                adjMatrix[i][j] = round(sqrt(pow((gen[i].xCoor - gen[j].xCoor), 2) + pow((gen[i].yCoor - gen[j].yCoor), 2)));
            else if (i == j)
                adjMatrix[i][j] = 0;
            else
                adjMatrix[i][j] = adjMatrix[j][i];
        }
    }
}


	//deallocating adjMatrix to avoid memory error
  void freeAdjMatrix(int rows) {
    int i;
    for (i = 0; i < rows; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
}

   //greedy tsp algorithm  
 int **greedyTSP(int **adjMatrix, int n) {
    int i, j, k,z;
    //allocating memories
    int *testTour1 = malloc(n * sizeof(int));
    int *testTour2 = malloc(n * sizeof(int));
    bool *visited = calloc(inputSize, sizeof(bool));
    int distanceTour1;
    int distanceTour2;

	// initial starting point is 0 calculating half-tsp
    testTour1[0] = 0;
    visited[0] = true;
    for (i = 1; i < n; i++) {
        int best = -1;
        for (j = 0; j < inputSize; j++) {
            if (!visited[j] && (best == -1 || adjMatrix[testTour1[i - 1]][j] < adjMatrix[testTour1[i - 1]][best])) {
                best = j;
            }
        }
        testTour1[i] = best;
        visited[best] = true;
    }
    //setting visited false for reuse the visited pointer
    memset(visited, 0, inputSize * sizeof(bool));
    //testour distance for comparison
    distanceTour1 = tourDistance(testTour1, n);


	// initial starting point is 1 calculating half-tsp
    testTour2[0] = 1;
    visited[1] = true;
    for (i = 1; i < n; i++) {
        int best = -1;
        for (j = 0; j < inputSize; j++) {
            if (!visited[j] && (best == -1 || adjMatrix[testTour2[i - 1]][j] < adjMatrix[testTour2[i - 1]][best])) {
                best = j;
            }
        }
        testTour2[i] = best;
        visited[best] = true;
    }
        //setting visited false for reuse the visited pointer
    memset(visited, 0, inputSize * sizeof(bool));
    //testour distance for comparison
    distanceTour2 = tourDistance(testTour2, n);

	// to find out which is a good starting point
    for (k = 2; k < inputSize; k++) {
			
		//if test tour 2 distance  is less than tour 1, changing test tour 1
        if (distanceTour2 < distanceTour1) {
        
        	//this loop for decrease the execution time
        	//example: if there will be 4 starting points we first check if it is in the best tour
			//if it is in the tour we choose the next point. Because already using 2opt algorithm points will be swap.
			//checking until we get to the point not found in the tour
          	for(z=0;z<n;z++){	
             if (testTour2[z] == k){
             k++;
         	 z=0;
         	 
		 }
		 else continue;
}

          //setting testour1 is empty for reusing
            memset(testTour1, 0, n * sizeof(int));
            //starting point is k
            testTour1[0] = k;
            visited[k] = true;
            for (i = 1; i < n; i++) {
                int best = -1;
                for (j = 0; j < inputSize; j++) {
                    if (!visited[j] && (best == -1 || adjMatrix[testTour1[i - 1]][j] < adjMatrix[testTour1[i - 1]][best])) {
                        best = j;
                    }
                }
                testTour1[i] = best;
                visited[best] = true;
            }
            //distance tour 1 is changed because tour is changed
            distanceTour1 = tourDistance(testTour1, n);
              //setting visited false for reuse the visited pointer
            memset(visited, false, inputSize * sizeof(bool));
        }
        //if test tour 1 distance  is less than or equal tour 2, changing test tour 2
        else {
        	
        	
        	//this loop for decrease the execution time
        	//example: if there will be 4 starting points we first check if it is in the best tour
			//if it is in the tour we choose the next point. Because already using 2opt algorithm points will be swap.
			//checking until we get to the point not found in the tour	
        	 	for(z=0;z<n;z++){	
             if (testTour1[z] == k){
             k++;
         	 z=0;

		 }
		 else continue;
}
 
       
            memset(testTour2, 0, n * sizeof(int));
            //starting point is k
            testTour2[0] = k;
            visited[k] = true;
            for (i = 1; i < n; i++) {
                int best = -1;
                for (j = 0; j < inputSize; j++) {
                    if (!visited[j] && (best == -1 || adjMatrix[testTour2[i - 1]][j] < adjMatrix[testTour2[i - 1]][best])) {
                        best = j;
                    }
                }
                testTour2[i] = best;
                visited[best] = true;
            }
             //distance tour 2 is changed because tour is changed
            distanceTour2 = tourDistance(testTour2, n);
             //setting visited false for reuse the visited pointer
            memset(visited, false, inputSize * sizeof(bool));
        }
    }

	//checking which tour is better and return the best tour
    if (distanceTour1 < distanceTour2) {
        free(testTour2);
        free(visited);
        return testTour1;
    }
    else {
        free(testTour1);
        free(visited);
        return testTour2;
    }
}

//deallocaitng tour
void freeGreedyTSP(int *tour) {
    free(tour);
}

//calculating tour distance 
int tourDistance(int *tour, int n) {
    int distance = 0;
    int i;
    for (i = 0; i < n - 1; i++) {
        distance += adjMatrix[tour[i]][tour[i + 1]];
    }
    distance += adjMatrix[tour[n - 1]][tour[0]];
    return distance;
}


	//two-opt algorithm for decraese the tour distance
int* two_opt(int* tour, int **adjMatrix, int n_cities) {
    int improved = 1;
    int i, j, k;
    int* best_tour = calloc(n_cities, sizeof(int));
    memcpy(best_tour, tour, n_cities * sizeof(int));
    while (improved) {
        improved = 0;
        for (i = 1; i < n_cities - 2; i++) {
            for (j = i + 1; j < n_cities; j++) {
                if (j - i == 1) {
                    continue;
                }
                int* new_tour = malloc(n_cities * sizeof(int));
                memcpy(new_tour, tour, n_cities * sizeof(int));
                int* temp_tour = malloc((j - i) * sizeof(int));
                for (k = 0; k < j - i; k++) {
                    temp_tour[k] = tour[j - 1 - k];
                }
                for (k = i; k < j; k++) {
                    new_tour[k] = temp_tour[k - i];
                }
                free(temp_tour);
                int new_distance = tourDistance(new_tour, n_cities);
                if (new_distance < tourDistance(best_tour, n_cities)) {
                    memcpy(best_tour, new_tour, n_cities * sizeof(int));
                    improved = 1;
                }
                free(new_tour);
            }
        }
        memcpy(tour, best_tour, n_cities * sizeof(int));
    }
    return best_tour;
}


//deallocating memory 
void freeTwoOpt(int* tour) {
    free(tour);
}


int main(int argc, char* argv[]) {
    int i;
    char fileName[32];
	int j;
	
	//asking input file name
    printf("What is the input file name: ");
    scanf("%s", fileName);

    FILE* fp = fopen(fileName, "r");
   	//writing file name
 	FILE* fp1=fopen("test-output-3.txt","w");
 	
 	//if file not found
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
	
	//gen pointing the starting point of point struct array
    gen = createStruct(fp);
    fclose(fp);
    //creating adjmatrix
    createAdjMatrix(inputSize, inputSize);
    //half size tsp
    int halfSize = ceil(inputSize / 2);
    int* tour = greedyTSP(adjMatrix, halfSize);

	//optimizing the tour with two-opt algorithm
    int* optimize = two_opt(tour, adjMatrix, halfSize);
    
    //printing tour distance
    printf("%d\n", tourDistance(optimize, halfSize));
    fprintf(fp1,"%d\n", tourDistance(optimize, halfSize));
    //printing tour
    for (i = 0; i < halfSize; i++) {
        printf("%d\n", optimize[i]);
        fprintf(fp1,"%d\n", optimize[i]);
    }
    fprintf(fp1,"\n");
	//deallocating memory to avoid to memory error
    freeStruct(gen);
    freeAdjMatrix(inputSize);
    freeGreedyTSP(tour);
    freeTwoOpt(optimize);
    return 0;
}

