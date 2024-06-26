using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using BHB_HotelMangementSystem.BL;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.ListView;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Security.Cryptography;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Collections.Specialized;

namespace BHB_HotelMangementSystem.DL
{
    class CheckInDL
    {
        private static List<CheckIn> formList = new List<CheckIn>();
        private static int type;
        internal static List<CheckIn> FormList { get => formList; set => formList = value; }
        public static int Type { get => type; set => type = value; }

        public static void addIntoList(CheckIn r)
        {
            FormList.Add(r);
        }

        public static void addIntoFile(CheckIn s , string path)
        {
            StreamWriter f = new StreamWriter(path,true);
            f.WriteLine(s.Status+","+ s.Gid + "," + s.Name + "," + s.Addres + "," + s.Contact + "," + s.Email + "," + s.Gender + "," + s.Adult + "," + s.Children + "," + s.InDate + "," + s.OutDate + "," + s.Days + "," + s.RoomNo + "," + s.Troom + "," + s.Sroom + "," + s.RoomRate + "," + s.Sdiscount + "," + s.Tdiscount + "," + s.DiscountRate + "," + s.Balance);
            f.Flush();
            f.Close();
        }

        public static bool  loadForms(string path)
        {
            if (File.Exists(path))
            {
                StreamReader f = new StreamReader(path);
                string record;
                while ((record = f.ReadLine()) != null)
                {
                    string[] rec = record.Split(',');
                    string statu = rec[0];
                    int Gid = int.Parse(rec[1]);
                    string name = rec[2];   // NAME
                    string addres = rec[3]; // ADREESS OF GUEST
                    string contact = rec[4]; // CONTACT OF THE GUEST
                    string email = rec[5];  // EMAIL OF THE GUEST
                    string gender = rec[6]; // GENDER OF THE GUEST
                    int adult = int.Parse(rec[7]);
                    int children = int.Parse(rec[8]);
                    string inDate = rec[9];  // CHECK IN DATE
                    string outDate = rec[10]; // reservation form mai check out date
                    int days = int.Parse(rec[11]);
                    int roomNO = int.Parse(rec[12]);
                    string Troom = rec[13]; // ROOM TYPE
                    string Sroom = rec[14]; // STATUS OF THE ROOM
                    int roomRate = int.Parse(rec[15]);
                    string Sdiscount = rec[16]; // DISCOUNT STATUS
                    string Tdiscount = rec[17]; // DISCOUNT TYPE
                    int discountRate = int.Parse(rec[18]);
                    double balance = double.Parse(rec[19]);
                    CheckIn s = new CheckOut(statu,Gid, name, addres, contact, email, gender, adult,children, inDate, outDate, days, roomNO, Troom, Sroom, roomRate, Sdiscount, Tdiscount, discountRate, balance);
                    addIntoList(s);
                }
                f.Close();
                return true;
            }
            else
            {
                return false;
            }
        }
        public static bool isExist(CheckIn s)
        {
            int count = 0;
            foreach(CheckIn a in FormList)
            {
                if(a.Status == s.Status && a.Name == s.Name)
                {
                    return true;
                }
                else
                {
                    count++;
                }
            }
            if (count == FormList.Count)
            {
                return false;
            }
            return false;
        }
        public static void BUBBLE_SORT( ref List<CheckIn> checkOut, int n)
        {
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - i - 1; j++)
                {
                    if (checkOut[j].Balance > checkOut[j + 1].Balance)
                    {
                        CheckIn temp = checkOut[j + 1];
                        checkOut[j + 1] = checkOut[j];
                        checkOut[j] = temp;


                    }
                }
            }
        }

        public static void SELECTION_SORT(/*Record record[]*/ref  List<CheckIn> checkOut, int n)
        {
            for (int j = 0; j < n - 1; j++)
            {
                int minIndex = findMinimum(ref checkOut, j, n);
                // SWAP WITH MINIMUM INDEX
                CheckIn temp = checkOut[minIndex];
                checkOut[minIndex] = checkOut[j];
                checkOut[j] = temp;

            }
        }
        static int findMinimum(/*Record record[]*/ref List<CheckIn> checkOut, int start, int end)
        {
            double min = checkOut[start].Balance;
            int minIndex = start;
            for (int x = start; x < end; x++)
            {
                if (min > checkOut[x].Balance)
                {
                    min = checkOut[x].Balance;
                    minIndex = x;
                }
            }
            return minIndex;
        }
        public static void INSERTION_SORT(ref List<CheckIn> checkOut, int n)
        {
            for (int x = 1; x < n; x++)
            {
                CheckIn key = checkOut[x];
                int y = x - 1;
                while (y >= 0 && checkOut[y].Balance > key.Balance)
                {
                    checkOut[y + 1] = checkOut[y];
                    y--;
                }
                checkOut[y + 1] = key;
            }
        }
        public static void MERGE_SORT(ref List<CheckIn> checkOut, int start, int end)
        {
            if (start < end)
            {
                int mid = (start + end) / 2;
                MERGE_SORT(ref checkOut, start, mid);
                MERGE_SORT(ref checkOut, mid + 1, end);
                MERGE(ref checkOut, start, mid, end);
            }
        }

        static void MERGE(ref List<CheckIn> checkOut, int start, int mid, int end)
        {
            int i = start;
            int j = mid + 1;
            int k = 0;
            Queue<CheckIn> tempArr = new Queue<CheckIn> ();

            while (i <= mid && j <= end)
            {
                if (checkOut[i].Balance < checkOut[j].Balance)
                {
                    tempArr.Enqueue(checkOut[i]);
                    i++;
                }
                else
                {
                    tempArr.Enqueue(checkOut[j]);
                    j++;
                }
            }
            while (i <= mid)
            {
                tempArr.Enqueue(checkOut[i]);
                i++;
            }
            while (j <= end)
            {
                tempArr.Enqueue(checkOut[j]);
                j++;
            }
            for (int z = start; z <= end; z++)
            {
                checkOut[z] = tempArr.Peek();
                tempArr.Dequeue();
            }
        }
        public static void heapSort(ref List<CheckIn> checkOut, int size)
        {
            for (int x = (size / 2) - 1; x >= 0; x--)
            {
                heapify(ref checkOut, size, x);
            }
            for (int x = size - 1; x > 0; x--)
            {
                CheckIn temp = checkOut[0];
                checkOut[0] = checkOut[x];
                checkOut[x] = temp;
                //swap( checkOut[0],  checkOut[x]);
                heapify(ref checkOut, x, 0);
            }
            
        }
        static void heapify(ref List<CheckIn> checkOut, int size, int index)
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
                    if (checkOut[lIdx].Balance >= checkOut[rIdx].Balance)
                        maxIndex = lIdx;
                    else
                        maxIndex = rIdx;
                }
                if (checkOut[index].Balance < checkOut[maxIndex].Balance)
                {
                    CheckIn temp = checkOut[index];
                    checkOut[index] = checkOut[maxIndex];
                    checkOut[maxIndex] = temp;
                    //swap( checkOut[index],  checkOut[maxIndex]);
                    index = maxIndex;
                }
                else
                    return;
            }
        }
        public static void quickSort(ref List<CheckIn> checkOut, int start, int end)
        {
            if (start < end)
            {
                int pivot = start;
                int mid = partition(ref checkOut, start + 1, end, pivot);
                quickSort(ref checkOut, start, mid - 1);
                quickSort(ref checkOut, mid + 1, end);
            }
        }
        static int partition(ref List<CheckIn> checkOut, int start, int end, int pivot)
        {
            int left = start;
            int right = end;
            while (left <= right)
            {
                while (checkOut[left].Balance < checkOut[pivot].Balance && left <= end)
                    left++;
                while (checkOut[right].Balance >= checkOut[pivot].Balance && right >= start)
                    right--;
                if (left < right)
                {
                    CheckIn temp = checkOut[left];
                    checkOut[left] = checkOut[right];
                    checkOut[right] = temp;
                }
                   
                    //swap(checkOut[left], checkOut[right]);
            }
            CheckIn tempp = checkOut[right];
            checkOut[right] = checkOut[pivot];
            checkOut[pivot] = tempp;
            //swap(  checkOut[right],  checkOut[pivot]);
            return right;
        }
        public static void countingSort(ref List<CheckIn> checkOut)
        {
            double max = checkOut[0].Balance;
            for (int x = 1; x < checkOut.Count; x++)
            {
                if (max < checkOut[x].Balance)
                {
                    max = checkOut[x].Balance;
                }
            }

            int[] count = new int[(int)max +1];
            int n = count.Length;
            CheckIn[] output = new CheckIn[checkOut.Count];
            int a = output.Length;
            //List<int> count = new List<int>((int)max+1);
            //List<CheckIn> output = new List<CheckIn>(checkOut.Count);
            for (int x = 0; x < checkOut.Count; x++)
            {
                count[(int)checkOut[x].Balance]++;
            }
            for (int x = 1; x < n; x++)
            {
                count[x] = count[x - 1] + count[x];
            }
            for (int x = checkOut.Count - 1; x >= 0; x--)
            {
                int index = count[(int)checkOut[x].Balance] - 1;
                count[(int)checkOut[x].Balance]--;
                output[index] = checkOut[x];
            }
            for (int x = 0; x < output.Length; x++)
            {
                checkOut[x] = output[x];
            }
        }
        public static void radixSort(ref List<CheckIn> checkOut)
        {
            double max = checkOut[0].Balance;
            for (int x = 1; x < checkOut.Count; x++)
            {
                if (max < checkOut[x].Balance)
                {
                    max = checkOut[x].Balance;
                }
            }
            int place = 1;
            while ((max / place) > 0)
            {
                countingSort(ref checkOut, place);
                place = place * 10;
            }
        }
        static void countingSort(ref List<CheckIn> checkOut, int place)

        {
            //List<int> count = new List<int>(10);
            //List<CheckIn> output = new List<CheckIn>(checkOut.Count);
            int[] count = new int[10];
            CheckIn[] output = new CheckIn[checkOut.Count];
            for (int x = 0; x < checkOut.Count; x++)
            {
                count[((int)checkOut[x].Balance / place) % 10]++;
            }
            for (int x = 1; x < count.Length; x++)
            {
                count[x] = count[x - 1] + count[x];
            }
            for (int x = checkOut.Count - 1; x >= 0; x--)
            {
                int index = count[((int)checkOut[x].Balance / place) % 10] - 1;
                count[((int)checkOut[x].Balance / place) % 10]--;
                output[index] = checkOut[x];
            }
            for (int x = 0; x < output.Length; x++)
            {
                checkOut[x] = output[x];
            }
        }
        public static void bucketSort(ref List<CheckIn> checkOut)
        {
            double max = checkOut[0].Balance;
            double min = checkOut[0].Balance;
            for (int x = 1; x < checkOut.Count; x++)
            {
                if (max < checkOut[x].Balance)
                {
                    max = checkOut[x].Balance;
                }
                if ( checkOut[x].Balance < min)
                {
                    min = checkOut[x].Balance;
                }
            }
            List<CheckIn>[] bucket = new List<CheckIn>[(int)(max - min) + 1];
            for (int x = 0; x < bucket.Length; x++)
            {
                bucket[x] = new List<CheckIn>();
            }
            for (int x = 0; x < checkOut.Count(); x++)
            {
                bucket[(int)(checkOut[x].Balance - min)].Add(checkOut[x]);
            }
            
            int index = 0;
            for (int x = 0; x < bucket.Length; x++)
            {
                for (int y = 0; y < bucket[x].Count; y++)
                {
                    checkOut[index] = bucket[x][y];
                    index++;
                }
            }

        }
        static int parentIndex(int i)
        {
            return (i - 1) / 2;
        }
        static int leftChildIndex(int i)
        {
            return (2 * i) + 1;
        }
        static int rightChildIndex(int i)
        {
            return (2 * i) + 2;
        }
        static void swap(ref CheckIn a, ref CheckIn b)
        {
            CheckIn temp = a;
            a = b;
            b = temp;
        }
        static void SWAP_2(   int a,    int b)
        {
            int c;
            c = a;
            a = b;
            b = c;
        }
        static void SWAP_3(  double a,  double b)
        {
            double c;
            c = a;
            a = b;
            b = c;
        }
        static void SWAP( string a,   string b)
        {
            string c;
            c = a;
            a = b;
            b = c;
        }

    }
}
