#include <iostream>
#include <chrono> 
using namespace std::chrono;

/* assignment: create three functions for a large static array, a large static dynamic array, and a large heap array. Track the time required to call each a large number of times*/

//define three functions
void main2();
void main3();
void main4();

//time variable
using namespace std;
using namespace std::chrono;

//reminder, array size varies based on machine memory, may have to //adjust
//set static variable for array size
const int arraySize = 50000;

/**********************************************************/

int main() {
/**********************************************************/
/*this portion calls the function for a static array and calculates the time. */
  //starts time//
  auto start = high_resolution_clock::now();
  
  //for loop calls function until i reaches 100k calls
  for(int i = 0; i <100000; i++){
    //static int arr1[arraySize];
    main2();
  }
  //stops the time
  auto stop = high_resolution_clock::now(); 
  //calculates time taken
  auto duration5 = duration_cast<nanoseconds>(stop-start).count();
  auto duration = duration_cast<nanoseconds>((stop - start)/100000).count();
  //prints time taken
  cout << "Total time taken by static array: "
         << duration5 << " nanoseconds" << "\n";
  //prints average time taken
  cout << "Average time taken by static array: "
         << duration << " nanoseconds" << "\n";
         
         

/**********************************************************/
/*this portion calls the function for a stack dynamic array and calculates the time. */
//starts time//
  auto start1 = high_resolution_clock::now();
  
  //for loop calls function until i reaches 100k calls
  for(int i = 0; i <100000; i++){
    //int arr2[arraySize];
    main3();
  }
  //stops the time
  auto stop1 = high_resolution_clock::now(); 
  //calculates time taken
  auto duration6 = duration_cast<nanoseconds>(stop1-start1).count();
  auto duration1 = duration_cast<nanoseconds>((stop1 - start1) /100000).count();
  //int avgDuration = int(duration/100000);
  //prints total time taken
  cout << "Total time taken by stack dynamic array: "
         << duration6 << " nanoseconds" << "\n";
  //prints average time taken
  cout << "Average time taken by stack dynamic array: "
         << duration1 << " nanoseconds" << "\n";

/**********************************************************/
/*this portion calls the function for a heap dynamic array and calculates the time */
//starts time//
  auto start2 = high_resolution_clock::now();
  
  //for loop calls function until i reaches 100k calls
  for(int i = 0; i <100000; i++){
    //int *arr3 = new int[arraySize];
    main4();
  }
  //stops the time
  auto stop2 = high_resolution_clock::now(); 
  //calculates total time taken
  auto duration7 = duration_cast<nanoseconds>(stop2-start2).count();
  auto duration2 = duration_cast<nanoseconds>((stop2 - start2)/100000).count();
  //prints total time taken
  //array size must be less than about 99,200
  cout << "Total time taken by heap dynamic array: "
         << duration7 << " nanoseconds" << "\n";
  //prints the average time taken
  cout << "Average time taken by a heap dynamic array: "
         << duration2 << " nanoseconds" << "\n";


  std::cout << "process has finished!\n";
}

/***********************************************************/

void main2(){
  //adding static makes this a static variable since it isnt declared //globally
  static int arr1[arraySize];

}

/***********************************************************/

void main3(){
  //local array is stack dynamic
  int arr2[arraySize];
}

/***********************************************************/

void main4(){
  //pointer array are heap
  int *arr3 = new int[arraySize]; 
}