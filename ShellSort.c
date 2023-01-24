#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 
#define N 100000

void ShellSort(int, int*, int*);
void RandGen();
void PartSortedGen();
void SortedGen();
void Read(int*, char*);
int* ShellSequence(int);
int* HibbardSequence(int);
int* KnutSequence(int);
int* SejvikSequence(int);
int* MarcinCiurSequence();
int* FibonacciSequence(int);
int* AllocMemory();
void SequenceTest();
void CompareToOther();
void QuickSort(int*, int, int);
void MergeSort(int*, int, int);
void Merge(int*, int, int, int);
void heapify(int*, int, int);
void PyramidSort(int, int*); 

int main() { 
	int ch;
	while(1){
		printf("1. Testing Shell Sort on different sequences\n");
		printf("2. Comparing Shell Sort with another sort algorithms\n");
		printf("0. Exit\n");
		printf(">> ");
		scanf("%d", &ch);
		switch(ch){
			case 1:
				SequenceTest(); 
 	 			break;
			case 2: 
 	 			CompareToOther();
				break;
			case 0:
				return 0; 
		}
		system("pause");
	}
}

void CompareToOther(){ 
	int i, j;
	int ch = -1;
	int* arr;
	int* sequence;
	double executionTime;
	char fileName[3][30] = {{"src/RandInput.txt"},
	 	 	 	 	 	 	{"src/PartSortedInput.txt"},
	 	 	 	 	 	 	{"src/SortedInput.txt"}};
	char* type_of_sort[3] = {"Random array", "Particullary Sorted Array", "Sorted Array"};
	time_t start, end;
	arr = (int*)malloc(N * sizeof(int));
	if(arr == NULL){
		printf("Allocation memory error\n");
	 	exit(1);
	}
	RandGen();
	PartSortedGen();
	SortedGen();
	
 	while(ch < 0 || ch > 6){
		printf("1. Shell Sequence\n");
		printf("2. Hibbard Sequence\n");
		printf("3. Knut Sequnce\n");
		printf("4. Sejvik Sequence\n");
		printf("5. Marcin - Ciur Sequence\n");
		printf("6. Fibonacci Sequence\n");
		scanf("%d", &ch);
		switch(ch){
		case 1: 
 	 		sequence = ShellSequence(N);
			break;
		case 2: 
 	 		sequence = HibbardSequence(N);
			break;
		case 3: 
	 		sequence = KnutSequence(N); 
 	 		break;
		case 4: 
 	 	 	sequence = SejvikSequence(N);
			break;
		case 5: 
	 		sequence = MarcinCiurSequence(N); 
 	 		break;
		case 6: 
	 		sequence = FibonacciSequence(N); 
	 	 	break; 
	 	} 
	} 
 	 
	printf("Array size: %d\n\n", N); 
 	 
	for(i = 0; i < 3; i++){
		printf("\n%s\n", type_of_sort[i]);
	 	Read(arr, fileName[i]);
		  
	 	 	//shellsort 
 	 	start = clock();
		ShellSort(N, arr, sequence);
		printf("\n"); 
 	 	end = clock();
		executionTime = difftime(end, start) / 1000;
		printf("Shell Sort execution Time: %.3lf\n", executionTime); 
	
	 	 	//quicksort 
 	 	Read(arr, fileName[i]);
		start = clock();
		QuickSort(arr, 0, N-1);
		printf("\n"); 
 	 	end = clock();
		executionTime = difftime(end, start) / 1000;
	 	printf("Quick Sort execution Time: %.3lf\n", executionTime); 
	 	
	 	 	//mergesort 
 	 	Read(arr, fileName[i]);
		start = clock();
		MergeSort(arr, 0, N);
		printf("\n"); 
 	 	end = clock();
		executionTime = difftime(end, start) / 1000;
		printf("Merge Sort execution Time: %.3lf\n", executionTime);
		
	 	//pyramidsort 
		Read(arr, fileName[i]);
		start = clock();
		PyramidSort(N, arr); 
		printf("\n");
		end = clock();
		executionTime = difftime(end, start) / 1000;
		printf("Pyramid Sort execution Time: %.3lf\n", executionTime); 
	} 
}

void QuickSort(int *arr, int first, int last){
	if (first < last){
		int left = first, right = last, middle = arr[(left + right) / 2];
		do{
			while (arr[left] < middle) left++;
			while (arr[right] > middle) right--;
			if (left <= right){
				int tmp = arr[left];
				arr[left] = arr[right];
				arr[right] = tmp;
				left++;
				right--; 
	        } 
	    } while (left <= right); 
	    QuickSort(arr, first, right); 
	    QuickSort(arr, left, last); 
    }
}

void Merge(int* array, int first, int middleIndex, int last){
	int i; 
    int left = first;
	int right = middleIndex + 1;
	int* tempArray = (int*)malloc((last - first + 1) * sizeof(int));
	int index = 0;
    while ((left <= middleIndex) && (right <= last)){
		if (array[left] < array[right]){
	 	 	tempArray[index] = array[left]; 
            left++;
		}
		else{
			tempArray[index] = array[right];
			right++;
        }
		index++; 
    }
	for (i = left; i <= middleIndex; i++){
		tempArray[index] = array[i];
		index++; 
    }   
	for (i = right; i <= last; i++){
		tempArray[index] = array[i];
		index++; 
    }
	for (i = 0; i < (last - first + 1); i++){
		array[first + i] = tempArray[i]; 
    } 
}

void MergeSort(int* arr, int first, int last){
	if (first<last){ 
 	 	int middleIndex = (first + last) / 2;
		MergeSort(arr, first, middleIndex); 
        MergeSort(arr, middleIndex + 1, last); 
        Merge(arr, first, middleIndex, last); 
	} 
}

void PyramidSort(int size, int* arr){
	int i; 
 	for (i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i);
	for (i = size-1; i >= 0; i--) {
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		heapify(arr, i, 0); 
    } 
}

void heapify(int* arr, int size, int i){
	int largest = i; 
	int l = 2*i + 1; 
    int r = 2*i + 2;
	if (l < size && arr[l] > arr[largest])
		largest = l;
	if (r < size && arr[r] > arr[largest])
		largest = r;
	if (largest != i) { 
        int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, size, largest); 
    }  
}

void SequenceTest(){ 
 	int i, j;  	double executionTime;
	time_t start, end;
	int* tempsequence;
	int* arr;
	int* sequences[6]; 
 	 
 	arr = (int*)malloc(N * sizeof(int));
	if(arr == NULL){
		printf("Allocation memory error\n"); 
	 	exit(1); 
	} 
	RandGen(); 
	PartSortedGen(); 
	SortedGen(); 
 	sequences[0] = ShellSequence(N);
	sequences[1] = HibbardSequence(N);
	sequences[2] = KnutSequence(N);
	sequences[3] = SejvikSequence(N);
	sequences[4] = MarcinCiurSequence(N);
	sequences[5] = FibonacciSequence(N);
	
 	printf("Array size: %d\n\n", N);
  	for(i = 0; i < 6; i++){
	    switch(i){
		  	case 0: 
	 	 	 	printf("Shell Sequnce\n"); 
 	 	 	 	break;
			case 1: 
 	 	 		printf("Hibbard Sequnce\n");
				break;
			case 2: 
	 	 		printf("Knut Sequnce\n"); 
 	 	 		break;
			case 3: 
	 	 	 	printf("Sejvik Sequnce\n"); 
	 	 	 	break; 
	 	 	case 4: 
	 	 	 	printf("MarcinCiur Sequnce\n"); 
 	 	 	 	break;
			case 5: 
	 	 	 	printf("Fibonacci Sequnce\n"); 
	 	 	 	break; 
	 	}
 	 	Read(arr, "src/RandInput.txt");
		start = clock();
		ShellSort(N, arr, sequences[i]);
		end = clock();
		executionTime = difftime(end, start) / 1000; 
 	 	printf("Random array\n");
		printf("Execution Time: %.3lf\n", executionTime);
 	 	Read(arr, "src/PartSortedInput.txt");
		start = clock();
		ShellSort(N, arr, sequences[i]);
		end = clock();
		executionTime = difftime(end, start) / 1000;
		printf("Particullary sorted array\n");
		printf("Execution Time: %.3lf\n", executionTime);
 	 	Read(arr, "src/SortedInput.txt");
		start = clock();
		ShellSort(N, arr, sequences[i]);
		end = clock();
 	 	executionTime = difftime(end, start) / 1000;
	 	printf("Sorted array\n"); 
 	 	printf("Execution Time: %.3lf\n", executionTime);
		printf("\n"); 
	} 
}

int* AllocMemory(){
	int* vector = (int*)malloc(50 * sizeof(int));
	if(vector == NULL){
		printf("Allocation memory error!\n"); 
	 	exit(1); 
	} 
	return vector; 
}

int* ShellSequence(int size){ 
	int i;
	int length;
	int temp; 
	int* sequence = AllocMemory(); 
 	 
 	sequence[0] = size/2;
	length = 1;
	i = 0; 
 	while(sequence[i] > 1){
		sequence[++i] = sequence[i - 1] / 2; 
	 	length++; 
	} 
 	sequence[length] = 0;
	return sequence; 
}

int* HibbardSequence(int size){ 
 	int i;
	int temp;
	int length;
	int templength;
	int* sequence = AllocMemory(); 
 	 
 	sequence[0] = 1;
	length = 1;
	i = 0; 
 	while(sequence[i] <= size){
		sequence[++i] = pow(2, i + 1) - 1; 
		length++; 
	} 
 	templength = length;
	for(i = 0; i < length - 1; i++, length--){
	 	temp = sequence[i];
		sequence[i] = sequence[length - 1];
		sequence[length - 1] = temp; 
	} 
 	sequence[templength] = 0;
	return sequence; 
}

int* KnutSequence(int size){
	int i;
	int length;
	int temp;
	int templength; 
	int* sequence = AllocMemory();
	
	sequence[0] = 1; length = 1;
	i = 0;
	while(sequence[i] <= size){
		sequence[++i] = 3*sequence[i - 1] + 1;
		length++; 
	} 
 	templength = length;
	for(i = 0; i < length; i++, length--){
		temp = sequence[i];
		sequence[i] = sequence[length - 1];
		sequence[length - 1] = temp; 
	}
 	sequence[templength] = 0;
	return sequence; 
}

int* SejvikSequence(int size){ 
 	int i;
	int temp;
	int length = 0;
	int templength;
	int* sequence = AllocMemory(); 
  	sequence[0] = 1;
	length = 1;
	i = 0; 
	while(sequence[i] <= size){ 
	 	i++; 
	 	if(i % 2 == 0){ 
	 	 	sequence[i] = 9 * pow(2, i) - 9 * pow(2, i/2) + 1; 
	 	} 
	 	else{ 
	 	 	sequence[i] = 8 * pow(2, i) - 6 * pow(2, (i+1)/2) + 1; 
	 	} 
	 	length++; 
	} 
	templength = length; 
 	for(i = 0; i < length; i++, length--){
		temp = sequence[i];
		sequence[i] = sequence[length - 1];
		sequence[length - 1] = temp; 
	} 
 	sequence[templength] = 0;
	return sequence; 
}

int* MarcinCiurSequence(){
	int* sequence = AllocMemory();
	sequence[0] = 1750;
	sequence[1] = 701;
	sequence[2] = 301; 
	sequence[3] = 132;
	sequence[4] = 57;
	sequence[5] = 23;
	sequence[6] = 10;
	sequence[7] = 4;
	sequence[8] = 1;
	sequence[9] = 0;
	return sequence; 
}

int* FibonacciSequence(int size){ 
 	int i;
	int temp;
	int length = 0;
	int templength;
	int* sequence = AllocMemory(); 
 	 
 	sequence[0] = 1;
	sequence[1] = 2;
	length = 2;
	i = 1; 
 	while(sequence[i] <= size){
		sequence[++i] = sequence[i - 1] + sequence[i - 2]; 
	 	length++; 
	} 
 	templength = length;
	for(i = 0; i < length; i++, length--){
		temp = sequence[i];
		sequence[i] = sequence[length - 1];
		sequence[length - 1] = temp; 
	} 
 	sequence[templength] = 0;
	return sequence; 
}

void RandGen(){
	int i; 
 	FILE* f = fopen("src/RandInput.txt", "w");
	for(i = 0; i < N; i++){
		fprintf(f, "%d ", rand()%N); 
	} 
	fclose(f); 
}

void PartSortedGen(){ 
	int i;
	FILE* fp = fopen("src/PartSortedInput.txt", "w");
	for(i = 0; i < N / 2; i++){
		fprintf(fp, "%d ", i);
	} 
	for(i = N / 2; i < N; i++){
		fprintf(fp, "%d ", rand()%N); 
	}
	fclose(fp); 
}

void SortedGen(){ 
	int i; 
 	FILE* fp = fopen("src/SortedInput.txt", "w");
	for(i = 0; i < N; i++){
		fprintf(fp, "%d ", i); 
	} 
	fclose(fp); 
}

void Read(int* arr, char* fileName){ 
	int i; 
 	FILE* fp = fopen(fileName, "r");
	if(fp == NULL){
		printf("Opening file error\n"); 
	 	exit(1); 
	} 
 	for(i = 0; i < N; i++){
		fscanf(fp, "%d", &arr[i]); 
	} 
}

void ShellSort(int n, int* arr, int* sequence){
	int gap;  
	int i,j,k,temp;     
	for(k = 0; sequence[k] > 0; k++){
		gap = sequence[k];
		for(i = gap; i < n; i++){ 
            for(j = i - gap; j >= 0 && arr[j] > arr[j + gap]; j -= gap) { 
                temp = arr[j];
				arr[j] = arr[j + gap];
				arr[j + gap] = temp; 
            }
        }
    }
}

