#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include<cmath>
#include <vector>
#include <queue>
using namespace std;

typedef struct save_process{
	int sID, sCPU_Burst, sArrival_Time, sPriority, sCPU_Burst_2, snum ;
} sprocess ;

typedef struct cout_time{
	int cID, W_Time, T_Time ;
} couttime ;

bool fff(vector<sprocess> array);
string Cout_now_ID_fun(int now_ID) ;
vector<sprocess> Bubble_Sort (vector<sprocess> array, int length);
vector<couttime> Bubble_Sort_2 (vector<couttime> array, int length);
vector<sprocess> Bubble_Sort_3 (vector<sprocess> array, int length);
vector<sprocess> Bubble_Sort_4 (vector<sprocess> array, int length);
vector<sprocess> Bubble_Sort_5 (vector<sprocess> array, int length);
vector<sprocess> Bubble_Sort_6 (vector<sprocess> array, int length);

int main() {
	cout << "Welcome To OS Project two !" << endl ;
	int c = -1,total = 0 , method = -1, time_slice = -1,go_out = -1 ;
	string input = "",output = "", junk = "" ;
	cout << "Please input file name (do not add .txt):";
	cin >> input ;
	output = input+"_output.txt" ;
	input += ".txt" ;
	fstream fin(input.c_str()), fin_out(output.c_str(), ios::out) ;
	vector<sprocess> v1;
	if(!fin){    cout << "File not found." << endl;   }
	else {
      fin >> method >> time_slice ;
	  for (int i = 0 ; i < 6 ; i++ ) fin >> junk ;
	  
      while(!fin.eof()) {
      	total++ ;
        sprocess add ;
		fin >> add.sID >> add.sCPU_Burst >> add.sArrival_Time >> add.sPriority ;
		add.sCPU_Burst_2 = add.sCPU_Burst ;
		add.snum = 0 ;
		v1.push_back(add) ;	
	  }

      vector<couttime> All_mone_time, All_mtwo_time , All_mfive_time, All_mfour_time, All_mthree_time;
      if ( method == 1 || method == 6 ) {
        int now_ID = -1, end_time = -1, start_time = -1 ;
        sprocess now_ID_process ;
	    go_out = total ;
	    couttime cout_time_save ; 
	    queue<sprocess> q1;
	    vector<sprocess> watch;
	    fin_out << "==    FCFS==" << endl ;
	    for (int i = 0 ; true ; i++ )  {
	  	  if (go_out == 0 ) break ;
	  	  for (int j = 0 ; j < total ; j++) 
		    if ( v1[j].sArrival_Time == i ) watch.push_back(v1[j]) ;
          if ( watch.size() > 1 ) watch = Bubble_Sort(watch, watch.size()) ; 
          if ( watch.size() > 0 )
            for (int j = 0 ; j < watch.size() ; j++) q1.push(watch[j]) ;
          if ( now_ID == -1 ) {
            if ( q1.size() != 0 ) now_ID_process = q1.front(), now_ID = now_ID_process.sID, end_time = i + now_ID_process.sCPU_Burst,start_time = i, q1.pop() ;
          }
          else {
        	if ( i == end_time ) {
        	  go_out-- ;
			  cout_time_save.cID = now_ID, cout_time_save.T_Time = i - now_ID_process.sArrival_Time  , cout_time_save.W_Time = start_time - now_ID_process.sArrival_Time ;
			  All_mone_time.push_back(cout_time_save);	
        	  if (go_out == 0 ) break ;
			  if ( q1.size() != 0 ) now_ID_process = q1.front(), now_ID = now_ID_process.sID, end_time = i + now_ID_process.sCPU_Burst,start_time = i, q1.pop() ;
			  else now_ID = -1, end_time = -1 ;
		    }
		  }
	
		  if ( now_ID == -1 ) fin_out << "-" ;
		  else if ( now_ID >= 10 ) fin_out << Cout_now_ID_fun(now_ID) ;
		  else fin_out << now_ID ;
		  watch.clear();
	    }
        fin_out << endl ;
        All_mone_time = Bubble_Sort_2(All_mone_time, All_mone_time.size()) ;
        //fin_out << endl ;
        //for ( int i= 0; i < All_mone_time.size() ; i++ ) fin_out << All_mone_time[i].cID << " " << All_mone_time[i].W_Time << " " << All_mone_time[i].T_Time << endl ;
      } // method 1
      
      if ( method == 2 || method == 6 ) {
      	int now_ID = -1, start_time = -1, time_slice_save = time_slice ;
        sprocess now_ID_process ;
	    go_out = total ;
	    couttime cout_time_save ; 
	    vector<sprocess> watch, save_input_watch;
	    fin_out << "==      RR==" << endl ;
	    for (int i = 0 ; true ; i++ )  {
	  	  for (int j = 0 ; j < total ; j++) 
		    if ( v1[j].sArrival_Time == i ) save_input_watch.push_back(v1[j]) ;
		  save_input_watch = Bubble_Sort_6(save_input_watch, save_input_watch.size()) ;
		  for (int l = 0 ; l < save_input_watch.size() ; l++ ) watch.push_back(save_input_watch[l]) ;
		  save_input_watch.clear() ;
		  
		  if ( watch.size() != 0 ) {
		  	if ( watch[0].sID >= 10 ) fin_out << Cout_now_ID_fun(watch[0].sID) ;
		    else fin_out << watch[0].sID ;
		  	watch[0].sCPU_Burst-- ;
		  	time_slice_save-- ;
		  	if (watch[0].sCPU_Burst == 0) {
	          go_out-- ;
	          cout_time_save.cID = watch[0].sID, cout_time_save.T_Time = i - watch[0].sArrival_Time +1 , cout_time_save.W_Time = cout_time_save.T_Time - watch[0].sCPU_Burst_2 ;
			  All_mtwo_time.push_back(cout_time_save);	
	          watch.erase(watch.begin());
	          time_slice_save = time_slice;
	          if (go_out == 0 ) break ;
	        }
	        else {
          	  if ( time_slice_save == 0 ) {
                save_input_watch.push_back(watch[0]) ; 
          	  	watch.erase( watch.begin() ) ;
		        time_slice_save = time_slice ;
		      }
		    }
		  }
		  else {
		  	fin_out << "-" ;
		  	time_slice_save = time_slice ;
		  } 
	    }
	    fin_out << endl ;
	    All_mtwo_time = Bubble_Sort_2(All_mtwo_time, All_mtwo_time.size()) ;
        //fin_out << endl ;
        //for ( int i= 0; i < All_mtwo_time.size() ; i++ ) fin_out << All_mtwo_time[i].cID << " " << All_mtwo_time[i].W_Time << " " << All_mtwo_time[i].T_Time << endl ;
	  } // method 2
      
      if ( method == 3 || method == 6 ) {
      	int now_ID = -1, start_time = -1 ;
        sprocess now_ID_process ;
	    go_out = total ;
	    couttime cout_time_save ; 
	    vector<sprocess> watch;
	    fin_out << "==    PSJF==" << endl ;
	    for (int i = 0 ; true ; i++ )  {
	  	  for (int j = 0 ; j < total ; j++) 
		    if ( v1[j].sArrival_Time == i ) watch.push_back(v1[j]) ;
		  if (now_ID != -1) {
		  	watch[0].sCPU_Burst-- ;
	        if (watch[0].sCPU_Burst == 0) {
	          go_out-- ;
	          cout_time_save.cID = now_ID, cout_time_save.T_Time = i - now_ID_process.sArrival_Time  , cout_time_save.W_Time = cout_time_save.T_Time - now_ID_process.sCPU_Burst_2 ;
			  All_mthree_time.push_back(cout_time_save);	
	          watch.erase(watch.begin());
	          if (go_out == 0 ) break ;
	          now_ID = -1 ; 
	        }
		  }  
		    
          watch = Bubble_Sort_5(watch, watch.size()) ; 
          if ( watch.size() != 0 ) now_ID_process = watch[0], now_ID = now_ID_process.sID, start_time = i ;
	      
		  if ( now_ID == -1 ) fin_out << "-" ;
		  else if ( now_ID >= 10 ) fin_out << Cout_now_ID_fun(now_ID) ;
		  else fin_out << now_ID ;

	    }
	    fin_out << endl ;
	    All_mthree_time = Bubble_Sort_2(All_mthree_time, All_mthree_time.size()) ;
        //fin_out << endl ;
        //for ( int i= 0; i < All_mthree_time.size() ; i++ ) fin_out << All_mthree_time[i].cID << " " << All_mthree_time[i].W_Time << " " << All_mthree_time[i].T_Time << endl ;
	  } // method 3
      
      if ( method == 4 || method == 6 ) {
      	int now_ID = -1, end_time = -1 , start_time = -1 ;
        sprocess now_ID_process ;
	    go_out = total ;
	    couttime cout_time_save ; 
	    vector<sprocess> watch;
	    fin_out << "==Non-PSJF==" << endl ;
	    for (int i = 0 ; true ; i++ )  {
	  	  for (int j = 0 ; j < total ; j++) 
		    if ( v1[j].sArrival_Time == i ) watch.push_back(v1[j]) ;
		  watch = Bubble_Sort_4(watch, watch.size()) ;  
		    
		  if (now_ID != -1) {
	        if (i == end_time ) {
	          go_out--; 
	          cout_time_save.cID = now_ID, cout_time_save.T_Time = i - now_ID_process.sArrival_Time  , cout_time_save.W_Time = cout_time_save.T_Time - now_ID_process.sCPU_Burst_2 ;
			  All_mfour_time.push_back(cout_time_save);
			  if (go_out == 0 ) break ;	
	          now_ID = -1 ; 
	        }
		  }  
		  if (now_ID == -1) 
            if ( watch.size() != 0 ) now_ID_process = watch[0], now_ID = now_ID_process.sID,end_time = i + now_ID_process.sCPU_Burst, start_time = i, watch.erase(watch.begin()); ;
	      
		  if ( now_ID == -1 ) fin_out << "-" ;
		  else if ( now_ID >= 10 ) fin_out << Cout_now_ID_fun(now_ID) ;
		  else fin_out << now_ID ;

	    }
	    fin_out << endl ;
	    All_mfour_time = Bubble_Sort_2(All_mfour_time, All_mfour_time.size()) ;
        //fin_out << endl ;
        //for ( int i= 0; i < All_mfour_time.size() ; i++ ) fin_out << All_mfour_time[i].cID << " " << All_mfour_time[i].W_Time << " " << All_mfour_time[i].T_Time << endl ;
	  } // method 4
       
      if ( method == 5 || method == 6 ) {
      	int now_ID = -1, start_time = -1 ;
        sprocess now_ID_process ;
	    go_out = total ;
	    couttime cout_time_save ; 
	    vector<sprocess> watch;
	    fin_out << "== Priority==" << endl ;
	    for (int i = 0 ; true ; i++ )  {
	  	  for (int j = 0 ; j < total ; j++) 
		    if ( v1[j].sArrival_Time == i ) watch.push_back(v1[j]) ;
		  if (now_ID != -1) {
		  	watch[0].sCPU_Burst-- ;
		  	if ( fff( watch ) == true )
		  	  watch[0].snum++ ;
	        if (watch[0].sCPU_Burst == 0) {
	          go_out-- ;
	          cout_time_save.cID = now_ID, cout_time_save.T_Time = i - now_ID_process.sArrival_Time  , cout_time_save.W_Time = cout_time_save.T_Time - now_ID_process.sCPU_Burst_2 ;
			  All_mfive_time.push_back(cout_time_save);	
	          watch.erase(watch.begin());
	          if (go_out == 0 ) break ;
	          now_ID = -1 ; 
	        }
		  }  
		    
          watch = Bubble_Sort_3(watch, watch.size()) ; 
          if ( watch.size() != 0 ) now_ID_process = watch[0], now_ID = now_ID_process.sID, start_time = i ;
	      
		  if ( now_ID == -1 ) fin_out << "-" ;
		  else if ( now_ID >= 10 ) fin_out << Cout_now_ID_fun(now_ID) ;
		  else fin_out << now_ID ;

	    }
	    fin_out << endl ;
	    All_mfive_time = Bubble_Sort_2(All_mfive_time, All_mfive_time.size()) ;
        //fin_out << endl ;
        //for ( int i= 0; i < All_mfive_time.size() ; i++ ) fin_out << All_mfive_time[i].cID << " " << All_mfive_time[i].W_Time << " " << All_mfive_time[i].T_Time << endl ;
	  } // method 5
	  
	  fin_out << "===========================================================" << endl << endl ;
	  fin_out << "Waiting Time" << endl ;
	  if ( method == 6 )  fin_out << "ID" << "\t" << "FCFS" << "\t" << "RR" << "\t"<< "PSJF" << "\t" << "NPSJF"<<"\t"<<"Priority" << endl ;
	  else if ( method == 5 ) fin_out << "ID" << "\t" << "Priority" << endl ;
	  else if ( method == 4 ) fin_out << "ID" << "\t" << "NPSJF" << endl ;
	  else if ( method == 3 ) fin_out << "ID" << "\t" << "PSJF" << endl ;
	  else if ( method == 2 ) fin_out << "ID" << "\t" << "RR" << endl ;
	  else if ( method == 1 ) fin_out << "ID" << "\t" << "FCFS" << endl ;
	  fin_out << "===========================================================" << endl ;
	  if ( method == 6 )  {
	  	for ( int i= 0; i < All_mfive_time.size() ; i++ ) 
		  fin_out << All_mfour_time[i].cID << "\t"<< All_mone_time[i].W_Time << "\t" << All_mtwo_time[i].W_Time << "\t" << All_mthree_time[i].W_Time << "\t" << All_mfour_time[i].W_Time << "\t" << All_mfive_time[i].W_Time << endl ;
	  }
	  else if ( method == 5 ) 
	    for ( int i= 0; i < All_mfive_time.size() ; i++ ) 
		  fin_out << All_mfive_time[i].cID << "\t" << All_mfive_time[i].W_Time << endl ;
	  else if ( method == 4 ) 
	    for ( int i= 0; i < All_mfour_time.size() ; i++ ) 
		  fin_out << All_mfour_time[i].cID << "\t" << All_mfour_time[i].W_Time << endl ;
	  else if ( method == 3 ) 
	    for ( int i= 0; i < All_mthree_time.size() ; i++ ) 
		  fin_out << All_mthree_time[i].cID << "\t" << All_mthree_time[i].W_Time << endl ;
	  else if ( method == 2 ) 
	    for ( int i= 0; i < All_mtwo_time.size() ; i++ ) 
		  fin_out << All_mtwo_time[i].cID << "\t" << All_mtwo_time[i].W_Time << endl ;
	  else if ( method == 1 ) 
	    for ( int i= 0; i < All_mone_time.size() ; i++ ) 
		  fin_out << All_mone_time[i].cID << "\t" << All_mone_time[i].W_Time << endl ;
	  fin_out << "===========================================================" << endl << endl ;
	  fin_out << "Turnaround Time" << endl ;
	  if ( method == 6 )  fin_out << "ID" << "\t" << "FCFS" << "\t" << "RR" << "\t"<< "PSJF" << "\t" << "NPSJF"<<"\t"<<"Priority" << endl ;
	  else if ( method == 5 ) fin_out << "ID" << "\t" << "Priority" << endl ;
	  else if ( method == 4 ) fin_out << "ID" << "\t" << "NPSJF" << endl ;
	  else if ( method == 3 ) fin_out << "ID" << "\t" << "PSJF" << endl ;
	  else if ( method == 2 ) fin_out << "ID" << "\t" << "RR" << endl ;
	  else if ( method == 1 ) fin_out << "ID" << "\t" << "FCFS" << endl ;
	  fin_out << "===========================================================" << endl ;
	  if ( method == 6 )  {
	  	for ( int i= 0; i < All_mfive_time.size() ; i++ ) 
		  fin_out << All_mfour_time[i].cID << "\t"<< All_mone_time[i].T_Time << "\t" << All_mtwo_time[i].T_Time << "\t" << All_mthree_time[i].T_Time << "\t" << All_mfour_time[i].T_Time << "\t" << All_mfive_time[i].T_Time << endl ;
	  }
	  else if ( method == 5 ) 
	    for ( int i= 0; i < All_mfive_time.size() ; i++ ) 
		  fin_out << All_mfive_time[i].cID << "\t" << All_mfive_time[i].T_Time << endl ;
	  else if ( method == 4 ) 
	    for ( int i= 0; i < All_mfour_time.size() ; i++ ) 
		  fin_out << All_mfour_time[i].cID << "\t" << All_mfour_time[i].T_Time << endl ;
	  else if ( method == 3 ) 
	    for ( int i= 0; i < All_mthree_time.size() ; i++ ) 
		  fin_out << All_mthree_time[i].cID << "\t" << All_mthree_time[i].T_Time << endl ;
	  else if ( method == 2 ) 
	    for ( int i= 0; i < All_mtwo_time.size() ; i++ ) 
		  fin_out << All_mtwo_time[i].cID << "\t" << All_mtwo_time[i].T_Time << endl ;
	  else if ( method == 1 ) 
	    for ( int i= 0; i < All_mone_time.size() ; i++ ) 
		  fin_out << All_mone_time[i].cID << "\t" << All_mone_time[i].T_Time << endl ;
	  fin_out << "===========================================================" << endl ;
    }
    
    
    
    fin_out.close() ;
    fin.close();
	return 0 ;
}

string Cout_now_ID_fun(int now_ID) {
	if ( now_ID == 10 ) return "A" ;
	else if ( now_ID == 11 ) return "B" ;
	else if ( now_ID == 12 ) return "C" ;
	else if ( now_ID == 13 ) return "D" ;
	else if ( now_ID == 14 ) return "E" ;
	else if ( now_ID == 15 ) return "F" ;
	else if ( now_ID == 16 ) return "G" ;
	else if ( now_ID == 17 ) return "H" ;
	else if ( now_ID == 18 ) return "I" ;
	else if ( now_ID == 19 ) return "J" ;
	else if ( now_ID == 20 ) return "K" ;
	else if ( now_ID == 21 ) return "L" ;
	else if ( now_ID == 22 ) return "M" ;
	else if ( now_ID == 23 ) return "N" ;
	else if ( now_ID == 24 ) return "O" ;
	else if ( now_ID == 25 ) return "P" ;
	else if ( now_ID == 26 ) return "Q" ;
	else if ( now_ID == 27 ) return "R" ;
	else if ( now_ID == 28 ) return "S" ;
	else if ( now_ID == 29 ) return "T" ;
	else if ( now_ID == 30 ) return "U" ;
	else if ( now_ID == 31 ) return "V" ;
	else if ( now_ID == 32 ) return "W" ;
	else if ( now_ID == 33 ) return "X" ;
	else if ( now_ID == 34 ) return "Y" ;
	else if ( now_ID == 35 ) return "Z" ;
}

vector<sprocess> Bubble_Sort (vector<sprocess> array, int length) {
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (array[j].sID > array[j + 1].sID)
                swap(array[j], array[j + 1]);
    return array ;
}

vector<couttime> Bubble_Sort_2 (vector<couttime> array, int length) {
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j)
            if (array[j].cID > array[j + 1].cID)
                swap(array[j], array[j + 1]);
    return array ;
}

vector<sprocess> Bubble_Sort_3 (vector<sprocess> array, int length) {
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j) {
            if (array[j].sPriority > array[j + 1].sPriority)
                swap(array[j], array[j + 1]);
            else if ( array[j].sPriority == array[j + 1].sPriority ) {
            	if ( array[j].snum > array[j + 1].snum ) swap(array[j], array[j + 1]);
            	else if (array[j].snum == array[j + 1].snum ) {
            	
            	  if ( array[j].sArrival_Time > array[j + 1].sArrival_Time ) swap(array[j], array[j + 1]);
            	  else if ( array[j].sArrival_Time == array[j + 1].sArrival_Time ) {
            	    if ( array[j].sID > array[j + 1].sID ) swap(array[j], array[j + 1]);	
				  }  
				  
			    }
			}
        }
    return array ;
}

vector<sprocess> Bubble_Sort_4 (vector<sprocess> array, int length) {
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j) {
            if (array[j].sCPU_Burst > array[j + 1].sCPU_Burst ) swap(array[j], array[j + 1]);
            else if ( array[j].sCPU_Burst == array[j + 1].sCPU_Burst ) {
            	if ( array[j].sArrival_Time > array[j + 1].sArrival_Time ) swap(array[j], array[j + 1]);
            	else if ( array[j].sArrival_Time == array[j + 1].sArrival_Time ) {
            	  if ( array[j].sID > array[j + 1].sID ) swap(array[j], array[j + 1]);	
				}
			}
        }
    return array ;
}

vector<sprocess> Bubble_Sort_5 (vector<sprocess> array, int length) {
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j) {
            if (array[j].sCPU_Burst > array[j + 1].sCPU_Burst )
                swap(array[j], array[j + 1]);
            else if ( array[j].sCPU_Burst == array[j + 1].sCPU_Burst ) {
            	if ( array[j].sCPU_Burst < array[j].sCPU_Burst_2 && array[j+1].sCPU_Burst == array[j+1].sCPU_Burst_2 )
            	  swap(array[j], array[j + 1]);
            	else if ( array[j].sCPU_Burst == array[j].sCPU_Burst_2 && array[j+1].sCPU_Burst == array[j+1].sCPU_Burst_2 ) {
            	  if ( array[j].sArrival_Time > array[j + 1].sArrival_Time ) swap(array[j], array[j + 1]);
            	  else if ( array[j].sArrival_Time == array[j + 1].sArrival_Time ) {
            	    if ( array[j].sID > array[j + 1].sID ) swap(array[j], array[j + 1]);	
				  }  
			    }
			}
        }
    return array ;
}

vector<sprocess> Bubble_Sort_6 (vector<sprocess> array, int length) {
	for (int i = length - 1; i > 0; --i)
        for (int j = 0; j < i; ++j) {
        	if ( array[j].sCPU_Burst < array[j].sCPU_Burst_2 && array[j+1].sCPU_Burst == array[j+1].sCPU_Burst_2 )
        	  swap(array[j], array[j + 1]);
        	else
              if (array[j].sID > array[j + 1].sID )
                swap(array[j], array[j + 1]);            
        }
    return array ;
}

bool fff(vector<sprocess> array) {
	for (int i = 1 ; i < array.size() ; i++) {
	  if ( array[0].sPriority == array[i].sPriority )	return true ;
	}
	return false ;
}
