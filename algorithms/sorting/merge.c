void merge(int arr[], int l, int m, int r) 
{ 
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + i];
    }

    int a = 0, b = 0, c = 0;
    while (a < n1 && b < n2 && c < r) {
        if (L[a] < R[b]) {
            arr[c] = L[a];
            c++;
            a++;
        } else {
            arr[c] = R[b];
            c++;
            b++;
        }
    }

    /*
    * When this code is actually read, it is guaranteed that
    * one of the sub arrays are empty, meaning that the rest
    * of the elements in the other sub array can just be copied
    * as is, since they are already sorted.
    */
    while (a < n1) {
        arr[c] = L[a];
        a++;
        c++;
    }
    while (b < n2) {
        arr[c] = R[b];
        b++;
        c++;
    }
} 

void _merge_sort(int arr[], int l, int r) 
{ 
    if (l < r) { 
        int m = l + (r - l) / 2; 
        _merge_sort(arr, l, m); 
        _merge_sort(arr, m + 1, r); 
        merge(arr, l, m, r); 
    } 
}

// a nicer interface to call
void merge_sort(int arr[], int n)
{
    _merge_sort(arr, 0, n);
}
    /*int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    int L[n1], R[n2]; 

    for (i = 0; i < n1; i++) { 
        L[i] = arr[l + i]; 
    }
    for (j = 0; j < n2; j++) { 
        R[j] = arr[m + 1 + j]; 
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 

    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 

    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    }*/ 

