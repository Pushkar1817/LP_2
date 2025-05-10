#include<iostream>
#include<vector>

using namespace std;

void selectionSort(vector<int>&arr){
    int n = arr.size();
    for(int i = 0 ;i< n ;i++){
        int minInd = i;

        for(int j = i+1 ; j<n ;j++){
            if(arr[j] < arr[minInd])
                minInd = j;
        }

        swap(arr[i],arr[minInd]);
    }
}

void printArray(const vector<int>&arr){
    for(int i = 0 ;i< arr.size() ;i++){
        cout<<arr[i]<<" ";      
    }
    cout<<endl;
}

int main ()
{
    vector<int>arr = {4,5,2,54,36,56,7,78,3};
    cout<<"Before Sort : ";
    printArray(arr);
    cout<<"After Sort : ";
    selectionSort(arr);
    printArray(arr);
    return 0;
}