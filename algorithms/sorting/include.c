
// handy trick - use pointers instead of passing array refernce
// and indeces
void swap(int * a, int * b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
