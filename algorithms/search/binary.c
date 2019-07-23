
int binary_search(int arr[], int n, int elem)
{
    int low = 0, high = n;
    int mid;
    while (low < high) {
        mid = (low + high) / 2;
        if (arr[mid] == elem) {
            return mid;
        } else if (arr[mid] < elem) {
            low = mid;
        } else if (arr[mid] > elem) {
            high = mid;
        }
    }

    return -1;
}
