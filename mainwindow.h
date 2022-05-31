#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <bits/stdc++.h>
#include<stdlib.h>
#include <QList>
#include <QMessageBox>
#include <iostream>
#include <algorithm>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool EnteredDataSize(); //to check if the number is entered by the user
    //Sorting Algorithms
    void Bubble(int arr[], int size);
    void quicksort(int a[], int start, int end);
    int partition ( int a[] , int start,int end);
    void mergeSort(int arr[], int start, int end);
    void merge(int arr[], int start, int m, int end);
    //Searching Algorithms
    bool NormalSearch(int x);
    bool BinarySearch(int val, int start, int end);
    bool STLSearch(int x);
    void print(); //to display the numbers on the list

private slots:

    void on_NormalSearch_clicked();
    void on_BinarySearch_clicked();
    void on_STLSearch_clicked();
    void on_Set_Generator_clicked();
    void on_Q_Sort_clicked();
    void on_M_Sort_clicked();
    void on_B_Sort_clicked();
    void on_STL_Sort_clicked();
    void on_find_it_clicked();


private:

    Ui::MainWindow *ui;
    int Data_Size;
    int *arr;
    int *end; //to be used in STL search
    int method;  // to choose the search method
    int sortTime;
    int searchTime;
    int SearchType;
    bool found;
    bool sorted;
    int sortType;

};
#endif // MAINWINDOW_H
