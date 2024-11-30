void quicksort_central(int *values, int left, int right);
void swap(int* a, int* b);
int partitiona_central(int *arr, int left, int right);

void quicksort_central(int *values, int left, int right) {
	if (left < right) {
		int pivot = partitiona_central(values, left, right);
		quicksort_central(values, left, pivot - 1);
		quicksort_central(values, pivot + 1, right);	
	}
}

void swap(int* a, int* b){
	int aux = *a;
    *a = *b;
    *b = aux;
}

int partitiona_central(int *arr, int left, int right){
	int mid = 0;
	mid = left+(right-left)/2;

    int pivot = arr[mid];
    swap(&arr[mid], &arr[right]);
    
	int i = left-1;
	for(int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}
