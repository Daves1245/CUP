static void merge(int *arr, int l, int m, int r) {
    int a, b, c; 

    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    int L[n1], R[n2]; 
  
    for (int i = 0; i < n1; i++) { 
        L[i] = arr[l + i]; 
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[m + 1+ j]; 
    }
  
    a = 0;
    b = 0;
    c = l;
    while (a < n1 && b < n2) { 
        if (L[a] <= R[b]) { 
            arr[c] = L[a]; 
            a++; 
        }
        else { 
            arr[c] = R[b]; 
            b++; 
        }
        c++; 
    } 
  
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
  
static void _merge_sort(int *arr, int l, int r) { 
    if (l < r) { 
        int m = l + (r - l) / 2; 
  
        _merge_sort(arr, l, m); 
        _merge_sort(arr, m+1, r); 
  
        merge(arr, l, m, r); 
    } 
}

void merge_sort(int *arr, size_t len) {
    _merge_sort(arr, 0, len);
}
