#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <queue>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
struct Record
{
    int index;
    string organization_id;
    string website;
    string country;
    string description;
    string founded;
    string industry;
    int no_of_employes;
    string name;
};


// FUNCTION PROTOTYEPS

void READ_RECORD(int n,  vector<Record> &record);
int LOAD_DATA();
int MAIN_MENU();
void BUBBLE_SORT( vector<Record> record, int n);
void SELECTION_SORT( vector<Record> record, int n);
void INSERTION_SORT(vector<Record> record, int n);
void MERGE_SORT(vector<Record> record, int start, int end);
void MERGE(vector<Record> record, int start, int mid, int end);
void SWAP(string &a, string &b);
void SWAP_2(int &a, int &b);
void CREATE( vector<Record> record, int n);
int findMinimum(vector<Record> arr, int start, int end);
void COUNTING_SORT(vector<Record> &arr);
void quickSort(vector<Record> arr, int start, int end);
int partition( vector<Record> arr, int start, int end, int pivot);
int heapSort( vector<Record> heapArr, int size);
void heapify(vector<Record> heapArr, int size, int index);
int parentIndex(int i);
int leftChildIndex(int i);
int rightChildIndex(int i);
void swap(int &a, int &b);
void countingSort(vector<Record> &arr, int place);
void radixSort(vector<Record> &arr);
void bucketSort(vector<Record> &arr);
main()
{
    int seletec_sort = 0;
    vector<Record> records;

    while (true)
    {
        int option = LOAD_DATA();
        if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5)
        {
            auto start = high_resolution_clock::now();
            if (option == 1)
            {
                READ_RECORD(100, records);
            }
            else if (option == 2)
            {
                READ_RECORD(1000, records);
            }
            else if (option == 3)
            {
                READ_RECORD(10000, records);
            }
            else if (option == 4)
            {
                READ_RECORD(100000, records);
            }
            else if (option == 5)
            {
                READ_RECORD(500000, records);
            }
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            getch();
            break;
        }
        else
        {
            cout << "invalid input" << endl;
        }
     
    }
    system("cls");
    while (true)
    {
        int n = 0;
        int option = MAIN_MENU();
        if (option == 1)
        {
            // FUNCTION OF BUBBLE SORTING
            auto start = high_resolution_clock::now();
            BUBBLE_SORT(records, records.size());
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
           
        }
        else if (option == 2)
        {
            auto start = high_resolution_clock::now();
            SELECTION_SORT(records, records.size());
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
           
        }
        else if (option == 3)
        {
            auto start = high_resolution_clock::now();
            INSERTION_SORT(records, records.size());
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
           
        }
        else if (option == 4)
        {
            auto start = high_resolution_clock::now();
            MERGE_SORT(records, 0, records.size() - 1);
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
        }
        else if (option == 5)
        {
            auto start = high_resolution_clock::now();
            quickSort(records, 0, records.size() - 1);
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
        }
        else if (option == 6)
        {
            auto start = high_resolution_clock::now();
            COUNTING_SORT(records);
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
        }
        else if (option == 7)
        {
            auto start = high_resolution_clock::now();
            heapSort(records, records.size());
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
        }
        else if (option == 8)
        {
            auto start = high_resolution_clock::now();
            radixSort(records);
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
        }
        else if (option == 9)
        {
            auto start = high_resolution_clock::now();
            bucketSort(records);
            auto end = high_resolution_clock::now();
            auto millisec = duration_cast<milliseconds>(end - start);
            cout << "Time :" << millisec.count() << endl;
            cout << "Press any key to continue :" << endl;
            CREATE(records, records.size());
            getch();
        }
        else 
        {
            cout << "invalid input";
        }
    }
}
void CREATE(vector<Record> record, int n)
{
    // file pointer
    fstream fout;

    // opens an existing csv file or creates a new file.
    fout.open("SORTED.csv", ios::out | ios::app);

    for (int i = 0; i < n; i++)
    {
        fout << record[i].index << ", "<< record[i].organization_id << ", "<< record[i].website << ", "<< record[i].country << ", "<< record[i].description << ", "<< record[i].founded << ", "<< record[i].industry << ", "<< record[i].no_of_employes << ", "<< record[i].name<< "\n";
    }
}
void MERGE_SORT(vector<Record> record, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MERGE_SORT(record, start, mid);
        MERGE_SORT(record, mid + 1, end);
        MERGE(record, start, mid, end);
    }
}

void MERGE(vector<Record> record, int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    int k = 0;
    queue<Record> tempArr;
    while (i <= mid && j <= end)
    {
        if (record[i].no_of_employes < record[j].no_of_employes)
        {
            tempArr.push(record[i]);
            i++;
        }
        else
        {
            tempArr.push(record[j]);
            j++;
        }
    }
    while (i <= mid)
    {
        tempArr.push(record[i]);
        i++;
    }
    while (j <= end)
    {
        tempArr.push(record[j]);
        j++;
    }
    for (int i = start; i <= end; i++)
    {
        record[i] = tempArr.front();
        tempArr.pop();
    }
}
int findMinimum( vector<Record> arr, int start, int end)
{
    int min = arr[start].no_of_employes;
    int minIndex = start;
    for (int x = start; x < end; x++)
    {
        if (min > arr[x].no_of_employes)
        {
            min = arr[x].no_of_employes;
            minIndex = x;
        }
    }
    return minIndex;
}

// insertion sort

void INSERTION_SORT( vector<Record> record, int n)
{
    for (int x = 1; x < n; x++)
    {
        Record key = record[x];
        int y = x - 1;
        while (y >= 0 && record[y].no_of_employes > key.no_of_employes)
        {
            record[y + 1] = record[y];
            y--;
        }
        record[y + 1] = key;
    }
}
void SELECTION_SORT(vector<Record> record, int n)
{
    for (int j = 0; j < n - 1; j++)
    {
        int minIndex = findMinimum(record, j, n);
        // SWAP WITH MINIMUM INDEX
        SWAP_2(record[j].no_of_employes, record[minIndex].no_of_employes);
        SWAP(record[j].organization_id, record[minIndex].organization_id);
        SWAP(record[j].name, record[minIndex].name);
        SWAP(record[j].website, record[minIndex].website);
        SWAP(record[j].country, record[minIndex].country);
        SWAP(record[j].description, record[minIndex].description);
        SWAP(record[j].founded, record[minIndex].founded);
        SWAP(record[j].industry, record[minIndex].industry);
        SWAP_2(record[j].index, record[minIndex].index);
    }
}
void BUBBLE_SORT(vector<Record> record, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (record[j].no_of_employes > record[j + 1].no_of_employes)
            {
                SWAP_2(record[j].no_of_employes, record[j + 1].no_of_employes);
                SWAP(record[j].organization_id, record[j + 1].organization_id);
                SWAP(record[j].name, record[j + 1].name);
                SWAP(record[j].website, record[j + 1].website);
                SWAP(record[j].country, record[j + 1].country);
                SWAP(record[j].description, record[j + 1].description);
                SWAP(record[j].founded, record[j + 1].founded);
                SWAP(record[j].industry, record[j + 1].industry);
                SWAP_2(record[j].index, record[j + 1].index);
            }
        }
    }
}
void COUNTING_SORT(vector<Record> &arr)
{
    int max = arr[0].no_of_employes;
    for (int x = 1; x < arr.size(); x++)
    {
        if (max < arr[x].no_of_employes)
        {
            max = arr[x].no_of_employes;
        }
    }
    vector<int> count(max + 1);
    vector<Record> output(arr.size());
    for (int x = 0; x < arr.size(); x++)
    {
        count[arr[x].no_of_employes]++;
    }
    for (int x = 1; x < count.size(); x++)
    {
        count[x] = count[x - 1] + count[x];
    }
    for (int x = arr.size() - 1; x >= 0; x--)
    {
        int index = count[arr[x].no_of_employes] - 1;
        count[arr[x].no_of_employes]--;
        output[index] = arr[x];
    }
    for (int x = 0; x < output.size(); x++)
    {
        arr[x] = output[x];
    }
}

void quickSort( vector<Record> arr, int start, int end)
{
    if (start < end)
    {
        int pivot = start;
        int mid = partition(arr, start + 1, end, pivot);
        quickSort(arr, start, mid - 1);
        quickSort(arr, mid + 1, end);
    }
}
int partition( vector<Record> arr, int start, int end, int pivot)
{
    int left = start;
    int right = end;
    while (left <= right)
    {
        while (arr[left].no_of_employes < arr[pivot].no_of_employes && left <= end)
            left++;
        while (arr[right].no_of_employes >= arr[pivot].no_of_employes && right >= start)
            right--;
        if (left < right)
            swap(arr[left], arr[right]);
    }
    swap(arr[right], arr[pivot]);
    return right;
}
int heapSort( vector<Record> heapArr, int size)
{
    for (int x = (size / 2) - 1; x >= 0; x--)
    {
        heapify(heapArr, size, x);
    }
    for (int x = size - 1; x > 0; x--)
    {
        swap(heapArr[0], heapArr[x]);
        heapify(heapArr, x, 0);
    }
}
void heapify(vector<Record> heapArr, int size, int index)
{
    int maxIndex;
    while (true)
    {
        int lIdx = leftChildIndex(index);
        int rIdx = rightChildIndex(index);
        if (rIdx >= size)
        {
            if (lIdx >= size)
                return;
            else
                maxIndex = lIdx;
        }
        else
        {
            if (heapArr[lIdx].no_of_employes >= heapArr[rIdx].no_of_employes)
                maxIndex = lIdx;
            else
                maxIndex = rIdx;
        }
        if (heapArr[index].no_of_employes < heapArr[maxIndex].no_of_employes)
        {
            swap(heapArr[index], heapArr[maxIndex]);
            index = maxIndex;
        }
        else
            return;
    }
}
int parentIndex(int i)
{
    return (i - 1) / 2;
}
int leftChildIndex(int i)
{
    return (2 * i) + 1;
}
int rightChildIndex(int i)
{
    return (2 * i) + 2;
}
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
void SWAP_2(int &a, int &b)
{
    int c;
    c = a;
    a = b;
    b = c;
}
void SWAP(string &a, string &b)
{
    string c;
    c = a;
    a = b;
    b = c;
}
void radixSort(vector<Record> &arr)
{
    int max = arr[0].no_of_employes;
    for (int x = 1; x < arr.size(); x++)
    {
        if (max < arr[x].no_of_employes)
        {
            max = arr[x].no_of_employes;
        }
    }
    int place = 1;
    while ((max / place) > 0)
    {
        countingSort(arr, place);
        place = place * 10;
    }
}
void countingSort(vector<Record> &arr, int place)

{
    vector<int> count(10);
    vector<Record> output(arr.size());
    for (int x = 0; x < arr.size(); x++)
    {
        count[(arr[x].no_of_employes / place) % 10]++;
    }
    for (int x = 1; x < count.size(); x++)
    {
        count[x] = count[x - 1] + count[x];
    }
    for (int x = arr.size() - 1; x >= 0; x--)
    {
        int index = count[(arr[x].no_of_employes / place) % 10] - 1;
        count[(arr[x].no_of_employes / place) % 10]--;
        output[index] = arr[x];
    }
    for (int x = 0; x < output.size(); x++)
    {
        arr[x] = output[x];
    }
}
void bucketSort(vector<Record> &arr)
{

    vector<vector<Record>> bucket(arr.size());
    for (int x = 0; x < arr.size(); x++)
    {
        bucket[int(arr[x].no_of_employes / arr.size())].push_back(arr[x]);
    }
    for (int x = 0; x < bucket.size(); x++)
    {
         INSERTION_SORT(bucket[x], bucket[x].size());
    }
    int index = 0;
    for (int x = 0; x < bucket.size(); x++)
    {
        for (int y = 0; y < bucket[x].size(); y++)
        {
            arr[index] = bucket[x][y];
            index++;
        }
    }
}
void READ_RECORD(int n,  vector<Record> &record)
{
    fstream file;
    if (n == 100)
    {
        file.open("organizations-100.csv", ios::in);
    }
    else if (n == 1000)
    {
        file.open("organizations-1000.csv", ios::in);
    }
    else if (n == 10000)
    {
        file.open("organizations-10000.csv", ios::in);
    }
    else if (n == 100000)
    {
        file.open("organizations-100000.csv", ios::in);
    }
    else if (n == 500000)
    {
        file.open("organizations-500000.csv", ios::in);
    }

    // check if file is open
    if (file.is_open())
    {
        cout << "file is open" << endl;
        string line;
        int i = 0;
        int counter = 0;

        while (getline(file, line))
        {
            Record temp;
            if (counter == 0)
            {
                counter++;
                continue;
            }
            stringstream ss(line);
            string word;
            int j = 0;
            while (getline(ss, word, ','))
            {
                if (j == 0)
                {
                    temp.index = stoi(word);
                }
                else if (j == 1)
                {
                    temp.organization_id = word;
                }
                else if (j == 2)
                {
                    temp.website = word;
                }
                else if (j == 3)
                {
                    temp.country = word;
                }
                else if (j == 4)
                {
                    temp.description = word;
                }
                else if (j == 5)
                {
                    temp.founded = word;
                }
                else if (j == 6)
                {
                    temp.industry = word;
                }
                else if (j == 7)
                {
                    temp.no_of_employes = stoi(word);
                }
                else if (j == 8)
                {
                    temp.name = word;
                }
                j++;
            }
            record.push_back(temp);
            i++;
        }

        cout << "RECORD HAS BEEN ENTERED SUCCESSFULLY.." << endl;
        getch();
    }
    else
    {
        cout << "file is not open" << endl;
    }

    file.close();
}
int LOAD_DATA()
{
    cout << "Select one of the following options:" << endl;
    cout << "1. Load 100 Records " << endl;
    cout << "2. Load 1000 Records" << endl;
    cout << "3. Load 10000 Records" << endl;
    cout << "4. Load 100000 Records" << endl;
    cout << "5. Load 5000000 Records" << endl;
    cout << "6. Back" << endl;
    cout << "Enter your option: ";
    int option;
    cin >> option;
    return option;
}
int MAIN_MENU()
{
    cout << "Select one of the following options:" << endl;
    cout << "1. BUBBLE SORTING." << endl;
    cout << "2. SELECTION SORTING." << endl;
    cout << "3. INSERTION SORTING." << endl;
    cout << "4. MERGE SORTING." << endl;
    cout << "5. QUICK SORTING." << endl;
    cout << "6. COUNTING SORTING." << endl;
    cout << "7. HEAP SORTING." << endl;
    cout << "8. RADIX SORTING." << endl;
    cout << "9. BUCKET SORTING." << endl;
    cout << "Enter your option: ";
    int option;
    cin >> option;
    return option;
}
