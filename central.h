void quicksort_central(int *values, int left, int right);
void swap(int* a, int* b);
int partitiona_central(int *arr, int left, int right);

void quicksort_central(int values[], int left, int right){ // T(n)= aT(n/b) + (12n+24)
	if (left < right) { // 2
		int pivot = partition(values, left, right); // 2
		quickSort(values, left, pivot - 1); // O(log n) 12n+20+4
		quickSort(values, pivot + 1, right); // O(log n) 12n+20+4
	}
}

void swap(int* a, int* b){ //3
	int aux = *a; // 1
    *a = *b; // 1
    *b = aux; // 1
}

int partition(int arr[], int left, int right){ //12n+20
	int mid = 0; // 2
	mid = left+(right-left)/2; // 4

    int pivot = arr[mid]; // 2
    swap(&arr[mid], &arr[right]); // 3+3
    
	int i = left-1; // 2
	for(int j = left; j < right; j++) { // 2n-2 ==> 12n-2
        if (arr[j] <= pivot) { //3
            i++; // 1
            swap(&arr[i], &arr[j]); // 3+3
        }
    }
    
    swap(&arr[i + 1], &arr[right]); // 4
    return i + 1; // 2
}

