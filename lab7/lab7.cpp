// lab7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>

using namespace std;

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort  
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place  
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}



void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray  
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array  
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element  
        swap(&arr[min_idx], &arr[i]);
    }
}
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void gnomeSort(int arr[], int n)
{
    int index = 0;

    while (index < n) {
        if (index == 0)
            index++;
        if (arr[index] >= arr[index - 1])
            index++;
        else {
            swap(arr[index], arr[index - 1]);
            index--;
        }
    }
    return;
}
int shellSort(int arr[], int n)
{
    // Start with a big gap, then reduce the gap 
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (int i = gap; i < n; i += 1)
        {
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location 
            arr[j] = temp;
        }
    }
    return 0;
}
struct Node
{
    int key;
    struct Node* left, * right;
};

// A utility function to create a new BST Node 
struct Node* newNode(int item)
{
    struct Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Stores inoder traversal of the BST 
// in arr[] 
void storeSorted(Node* root, int arr[], int& i)
{
    if (root != NULL)
    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

/* A utility function to insert a new
   Node with given key in BST */
Node* insert(Node* node, int key)
{
    /* If the tree is empty, return a new Node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) Node pointer */
    return node;
}

// This function sorts arr[0..n-1] using Tree Sort 
void treeSort(int arr[], int n)
{
    struct Node* root = NULL;

    // Construct the BST 
    root = insert(root, arr[0]);
    for (int i = 1; i < n; i++)
        root = insert(root, arr[i]);

    // Store inoder traversal of the BST 
    // in arr[] 
    int i = 0;
    storeSorted(root, arr, i);
}


// A utility function to print an array of size n  
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void choose(int sort)
{
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr) / sizeof(arr[0]);
    switch (sort)
    {
    case 1:

        cout << "Array before sorting: \n";
        printArray(arr, n);

        shellSort(arr, n);

        cout << "\nArray after sorting: \n";
        printArray(arr, n);
        break;
    case 2:
        
        selectionSort(arr, n);
        cout << "Sorted array: \n";
        printArray(arr, n);
        break;
    case 3:
       
        bubbleSort(arr, n);
        cout << "Sorted array: \n";
        printArray(arr, n);
        break;
    case 4:
        
          
            gnomeSort(arr, n);
            printArray(arr, n);

        break;
    case 5:
        

        treeSort(arr, n);

        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        break;
    case 6:
        

        insertionSort(arr, n);
        printArray(arr, n);
        break;
    
        
    }
}

// Driver code  
int main()
{
    int sort = 0;
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    cout << "choose method of sort:\n"
        "1 - quick sort \n"
        "2 - selection sort \n"
        "3 - buble sort \n"
        "4 - gnome sort \n"
        "5 - tree sort\n"
        "6 - shell sort\n";
    cin >> sort;
    choose(sort);
    
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
