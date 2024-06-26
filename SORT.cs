using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BHB_HotelMangementSystem.BL;
using BHB_HotelMangementSystem.DL;
//using std;
//using  std::chrono;

namespace BHB_HotelMangementSystem
{
    public partial class SORT : Form
    {
        public SORT()
        {
            InitializeComponent();
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void SORT_Load(object sender, EventArgs e)
        {
            List<CheckIn> temp = new List<CheckIn>();
            for(int x= 0; x < CheckInDL.FormList.Count; x++  )
            {
                if (CheckInDL.FormList[x].Status == "CO")
                {
                    temp.Add(CheckInDL.FormList[x]);
                }
            }
            var watch = System.Diagnostics.Stopwatch.StartNew();

            watch.Start();

            if (CheckInDL.Type == 1)// BUBLLE SORT
            {

                CheckInDL.BUBBLE_SORT( ref temp , temp.Count);

            }
            else if(CheckInDL.Type == 2)// SELECTION SORT
            {
                CheckInDL.SELECTION_SORT(ref temp, temp.Count);

            }
            else if (CheckInDL.Type == 3)// INSERTION SORT
            {
                CheckInDL.INSERTION_SORT( ref temp, temp.Count);

            }
            else if (CheckInDL.Type == 4)// MERGE SORT
            {
                CheckInDL.MERGE_SORT(ref temp, 0, temp.Count-1);

            }
            else if (CheckInDL.Type == 5)// HEAP SORT
            {
                CheckInDL.heapSort(ref temp, temp.Count);

            }
            else if (CheckInDL.Type == 6)// QUICK SORT
            {
                CheckInDL.quickSort(ref temp, 0, temp.Count - 1);

            }
            else if (CheckInDL.Type == 7)// COUNTING SORT
            {
                CheckInDL.countingSort(ref temp);

            }
            else if (CheckInDL.Type == 8)// RADIX
            {
                CheckInDL.radixSort(ref temp);

            }
            else if (CheckInDL.Type == 9)// BUCKET SORT
            {
                CheckInDL.bucketSort(ref temp);

            }
            watch.Stop();
            var elapsedMs = watch.ElapsedMilliseconds;
            TimeTaken.Text = elapsedMs.ToString();
            TimeTaken.Visible = true;
            gird.DataSource = temp;
        }
    }
}
