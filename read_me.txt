/**
*
*   NAME      PATEL MIT KUMAR RAJESHBHAI
*
*   ENTRY N0  2020CSM1016
*
*   PG SOFT ASSIGNMENT 
*
*   DATE 8-4-2021
*/



    Question 1     compile :-    g++ -o problem  problem.cpp
    
                   run     :-    ./probelm
                   
                   
                   
          Note :-
                 1>  to see intermediate generated files comment line no 123  (  remove( input_file ) )         
                 
                 2>  every block has B data record 
                 
                 3>  data are stored in file in following formate
                 
                            /*         | transaction id | ammount | name | category|    */
                       
                       transaction id is unique
                       
                       ammount is in range 1-60000
                       
                       name is length of 3 cheractor
                       
                       category is in range 1-1500
                  
                 4>  intitial data record block are 0.txt , 1.txt , 2.txt ......   etc
                 
                 5>  intermediate run files are in following format
                              
                               run_X_Y-Z.txt
                              
                           X is run pass no 1 ,2 ,3 ...
                           
                           Y is number of different run in pirticular pass
                           
                           Z is represent the offer of blocks in pirticular sorted run because  we can not store all record
                             
                             in sigle fils for every run because of B limits     
