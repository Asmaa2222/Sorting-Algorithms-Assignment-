#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QList>
#include <algorithm>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
 {
ui->setupUi(this);
srand(time(NULL));

 }


MainWindow::~MainWindow()
{
delete []arr;
delete ui;
delete end;
}

bool MainWindow::EnteredDataSize()
{
    if((ui->sizeEDIT->text())=="")
    {
        QMessageBox::warning(
                    this,
                    tr("Error"),
                    tr("No Size entered"));
        ui->DisplaySize->setText("");
        return false;
    }
    return true;
}
void MainWindow::Bubble(int arr[], int size)
{


    int i, j;
    for (i = 0; i < size - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp;
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
           }
}
int MainWindow::partition ( int a[] , int start,int end)
{
    //assign the last element to pivot
    int pivot = a[end];
    int pIndex = start; // partition index
    for (int i= start; i<end;i++)
    {
        if (a[i]< pivot)
        {
            swap(a[i], a[pIndex]);
            pIndex++;
        }
    }
    swap (a[pIndex],a[end]);
    return pIndex;
}
void MainWindow::quicksort(int a[], int start, int end)
{
    if (start<end)
    {
        int pIndex = partition(a, start, end);
        quicksort(a,start,pIndex-1);
        quicksort(a,pIndex+1,end);
    }
}
void MainWindow::merge(int arr[], int start, int m, int end) {
  int i = start; // start of first half
  int j = m + 1; // start of second half
  int k = start;

  /* create temp array */
  int temp[Data_Size];

  while (i <= m && j <= end) {
    if (arr[i] <= arr[j]) {
      temp[k] = arr[i];
      i++;
      k++;
    } else {
      temp[k] = arr[j];
      j++;
      k++;
    }

  }

  /* Copy the remaining elements of first half, if there are any */
  while (i <= m) {
    temp[k] = arr[i];
    i++;
    k++;

  }

  /* Copy the remaining elements of second half, if there are any */
  while (j <= end) {
    temp[k] = arr[j];
    j++;
    k++;
  }

  /* Copy the temp array to original array */
  for (int p = start; p <= end; p++) {
    arr[p] = temp[p];
  }
}

/* start is for left index and end is right index of the
   sub-array of arr to be sorted */
void MainWindow::mergeSort(int arr[], int start, int end) {
  if (start< end) {
    // find midpoint
    int m = (start+ end) / 2;

    // recurcive mergesort first and second halves
    mergeSort(arr, start, m);
    mergeSort(arr, m + 1, end);

    // merge
    merge(arr, start, m, end);
  }
}


bool MainWindow::NormalSearch(int x)
{
  for (int i=0;i<Data_Size;i++)
  {
      if (arr[i]==x)
      {
         return true;
      }
  }
  return false;
}

bool MainWindow::BinarySearch(int val, int start, int end) {
    if (start > end) return false;

    int mid = (start + end) / 2;
    if (val == arr[mid]) return true;

    if (val > arr[mid]) return BinarySearch(val, mid + 1, end);
    return BinarySearch(val, start, mid - 1);
}


bool MainWindow:: STLSearch(int x)
{
   // arr+Data_Size==find(arr, arr+Data_Size, x))
    end= arr+Data_Size;
    if (end == std::find(arr, end, x))
    {
        return false;
    }
    return true;
}

void MainWindow::print()
{
for (int i=0; i<Data_Size;i++){
    ui->listWidget->addItem(QString::number(arr[i]));
}
}

void MainWindow::on_NormalSearch_clicked()
{
    if (EnteredDataSize())
    {
        method = 1;
        ui->searchMethod->setText("Using: Normal Search");
    }
}



void MainWindow::on_BinarySearch_clicked()
{
    if (EnteredDataSize())
    {
        method = 2;
        ui->searchMethod->setText("Using: Binary Search ");
    }
}


void MainWindow::on_STLSearch_clicked()
{
    if (EnteredDataSize())
    {
        method = 3;
        ui->searchMethod->setText("Using: STL Search ");
    }
}




void MainWindow::on_Set_Generator_clicked()
{
    ui->listWidget->clear();


if(EnteredDataSize())
{

    Data_Size= (ui->sizeEDIT->text()).toInt();
arr= new int [Data_Size];
for (int i=0; i<Data_Size;i++){
    arr[i]= rand()%500;

    ui->listWidget->addItem(QString::number(arr[i]));
}
sorted = false;
   method = 0, sortType = 0;
   sortTime = 0, searchTime = 0;
ui->DisplaySize->setText("The Dataset size is: "+  QString::number(Data_Size));
method=0;
ui->arrayStatus->setText("Unsorted Array");
ui->sortingType->setText("");
ui->searchMethod->setText("");
}
}


void MainWindow::on_Q_Sort_clicked() //Quick Sort
{
   if(EnteredDataSize())
     {
// timing
         chrono::steady_clock::time_point now = chrono::steady_clock::now();
          quicksort(arr,0,Data_Size-1);

          chrono::steady_clock::time_point then = chrono::steady_clock::now();
          sortTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();
          ui->listWidget->clear();

         print();
               sorted = true;
           sortType = 1;
          ui->arrayStatus->setText("Array is Sorted");

          ui->sortingType->setText("Sorting Using QuickSort");
     }
}


void MainWindow::on_M_Sort_clicked() //Merge Sort
{
    if(EnteredDataSize())
    {
     chrono::steady_clock::time_point now = chrono::steady_clock::now();

mergeSort(arr,0,Data_Size-1);
chrono::steady_clock::time_point then = chrono::steady_clock::now();
sortTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();

ui->listWidget->clear();
print();
sorted = true;
       sortType = 2;
       ui->arrayStatus->setText("Array is Sorted");

       ui->sortingType->setText("Sorting Using Merge Sort");
   }

}


void MainWindow::on_B_Sort_clicked() //Bubble Sort
{
if(EnteredDataSize())
{
 chrono::steady_clock::time_point now = chrono::steady_clock::now();

Bubble(arr,Data_Size);
chrono::steady_clock::time_point then = chrono::steady_clock::now();
sortTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();

ui->listWidget->clear();
print();
sorted = true;
       sortType = 3;
       ui->arrayStatus->setText("Array is Sorted");

       ui->sortingType->setText("Sorting Using Bubble Sort");
   }
}




void MainWindow::on_STL_Sort_clicked()
{
    if(EnteredDataSize())
    {
     chrono::steady_clock::time_point now = chrono::steady_clock::now();
     sort(arr,arr+Data_Size);
     chrono::steady_clock::time_point then = chrono::steady_clock::now();
     sortTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();
 ui->listWidget->clear();
print();

sorted = true;
       sortType = 3;
       ui->arrayStatus->setText("Array is Sorted");

       ui->sortingType->setText("Sorting Using STL Sort");

}
}


void MainWindow::on_find_it_clicked()
{
    QString num = ui->num_find->text();

    if (num == "") {
        QMessageBox::warning(
            this,
            tr("Error"),
            tr("No Number entered") );
    }
    else {

        // timing
        chrono::steady_clock::time_point now = chrono::steady_clock::now();

        if (method == 1) found = NormalSearch(num.toInt());
        if (method == 2) found = BinarySearch( 0, Data_Size - 1,num.toInt());
        if(method==3) found=STLSearch(num.toInt());

        chrono::steady_clock::time_point then = chrono::steady_clock::now();
        searchTime = chrono::duration_cast<chrono::nanoseconds>(then - now).count();

        // display
        string message;
        if (found) {
            message = "The item exists in the list and the time needed to find it in Nanoseconds is: " +
                       to_string(searchTime) + " and the Sorting Time was " + to_string(sortTime);
        } else {
            message = "The item doesn't exists in the list and the time needed to run the search in Nanoseconds is: " +
                           to_string(searchTime) + " and the Sorting Time was " + to_string(sortTime);
        }

        QMessageBox::information(
            this,
            tr("Success"),
            tr(message.c_str()));
    }
}







