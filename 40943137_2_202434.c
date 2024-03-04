#include <thread>

#include <iostream>

#include <string>

#include <vector>

#include <stdlib.h> /* 亂數相關函數 */

#include <time.h>   /* 時間相關函數 */


using namespace std;


const int s_num = 3;//thread個數

vector<int> bf_state;//thread狀態

int origin_bf_time[s_num]={0};

void Station(int i, string s)

{

   int backoff_counter;//backoff計數時間

   if (bf_state[i] == -1) {//還未抽號碼
   

        backoff_counter = rand() %3+1; 
        for(int j=0;j<s_num;j++){
            if(backoff_counter==origin_bf_time[j]){
                cout<<"data collosion"<<endl;
                backoff_counter = rand() %3+1;
                origin_bf_time[i]=backoff_counter;
                break;
            }
        }
        //backoff_counter = 2;
        //驗收時 請將上一行改為  backoff_counter = 2;  將輸出結果與程式一併 以一個純文字擋 直接貼在作業繳教區
        origin_bf_time[i]=backoff_counter;
        
    }
   else{//已抽號碼，可能途中切換thrad，回來原本thread執行
       backoff_counter = bf_state[i];
    }
    

    

    
    while(backoff_counter){
        cout <<"STA ID = "<< i << ", BackoffCounter = " << backoff_counter << ", DataQueued"<< endl;
        backoff_counter--;
    }
        
   
   
   if (backoff_counter == 0) {//如果時間到0，則完成傳送

       cout << i << ", Backoff Counter = " <<backoff_counter << ", Data Sent" << endl;

       bf_state[i] = -1;

    }
    else{//如果時間未到0，則顯示還在queue中

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



STA ID = 0, BackoffCounter = 2, DataQueued
STA ID = 0, BackoffCounter = 1, DataQueued
0, Backoff Counter = 0, Data Sent
STA ID = 2, BackoffCounter = 3, DataQueued
STA ID = 2, BackoffCounter = 2, DataQueued
STA ID = 2, BackoffCounter = 1, DataQueued
2, Backoff Counter = 0, Data Sent
STA ID = 1, BackoffCounter = 1, DataQueued
1, Backoff Counter = 0, Data Sent


** Process exited - Return Code: 0 **









