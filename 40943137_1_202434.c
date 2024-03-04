#include <thread>

#include <iostream>

#include <string>

#include <vector>

#include <stdlib.h> /* 亂數相關函數 */

#include <time.h>   /* 時間相關函數 */


using namespace std;


int s_num = 3;//thread個數

vector<int> bf_state;


void Station(int i, string s)

{

   int backoff_counter;

   if (bf_state[i] == -1) {
        backoff_counter = rand() %7+1;     
        //驗收時 請將上一行改為  backoff_counter = 2;  將輸出結果與程式一併 以一個純文字擋 直接貼在作業繳教區
    }
   else{
       backoff_counter = bf_state[i];
    }


    while(backoff_counter){
        cout << i << ", Backoff Counter = " <<backoff_counter << ", DataQueued" << endl;
        backoff_counter--;
    }
  
   
   
   if (backoff_counter == 0) {

       cout << i << ", Backoff Counter = " <<backoff_counter << ", Data Sent" << endl;

       bf_state[i] = -1;

    }

    else{
       cout <<"STA ID = "<< i << ", BackoffCounter = " << backoff_counter << ", DataQueued"<< endl;
    }


}



int main()

{


   srand( time(NULL) );   /* 產生亂數 */



   vector<thread> threads;



   for(int i = 0; i < s_num; i++){

       bf_state.push_back(-1);

       threads.push_back(thread(Station, i, "test"));

   }  



   for(int i = 0; i < threads.size(); i++){

       //cout << threads[i].get_id() << endl;

       threads[i].join();

    }



   return 0;

}


1, Backoff Counter = 4, DataQueued
1, Backoff Counter = 3, DataQueued
1, Backoff Counter = 2, DataQueued
1, Backoff Counter = 1, DataQueued
1, Backoff Counter = 0, Data Sent
0, Backoff Counter = 6, DataQueued
0, Backoff Counter = 5, DataQueued
0, Backoff Counter = 4, DataQueued
0, Backoff Counter = 3, DataQueued
0, Backoff Counter = 2, DataQueued
0, Backoff Counter = 1, DataQueued
0, Backoff Counter = 0, Data Sent
2, Backoff Counter = 6, DataQueued
2, Backoff Counter = 5, DataQueued
2, Backoff Counter = 4, DataQueued
2, Backoff Counter = 3, DataQueued
2, Backoff Counter = 2, DataQueued
2, Backoff Counter = 1, DataQueued
2, Backoff Counter = 0, Data Sent


** Process exited - Return Code: 0 **


