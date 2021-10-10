/**
*
*   NAME      PATEL MIT KUMAR RAJESHBHAI
*
*   ENTRY N0  2020CSM1016
*
*   PG SOFT ASSIGNMENT 4
*
*   DATE 8-4-2021
*/
#include<bits/stdc++.h>
//#include<files.h>
using namespace std;

struct Test          //structure of data record x=transaction seal ammount y is transaction id id , s is name  and z is category
{
   int x, y, z;
   string s;
};



string rand_string()         // this function rendomly generate string of length 3
   { string s="";
     for(int i=0;i<3;i++)
      {
         s=s+char((rand()%26)+65);
      }
     
      return s;
   
   }
bool Creat_input_file(int N)               // initally  rendomly  generate record in format 
                                                     
                                            /*         | transaction id | ammount | name | category|    */
                                                      
   { int nu_record=N;
      string input_file="input.txt";  // store in input.txt  file
      
      fstream new_file;
      new_file.open(input_file, ios::out);

      for (int i = 0; i < nu_record; i++)
       {
         new_file<<i<<" "<<(rand()%60000)+1<<" "<<rand_string()<<" "<<(rand()%1500)+1<<endl;
       }
      new_file.close();  
    }
    
 bool create_Initial_Runs_for_creat_block(int B)    // B is number of record can be store in one block 
    {
     string input_file="input.txt";
    
      fstream new_file;
      new_file.open(input_file, ios::in);
      
      for(int i=0;!new_file.eof();i++)
       {
         string s=to_string(i)+".txt";             // creat data block each with size B
         
         fstream new_file_2;
         new_file_2.open(s, ios::out);
         
         map <int,Test> mp;
         vector <pair<int,int> > pr;
         for(int j=0;j<B && !new_file.eof();j++)    
         {
            int X,Y,Z;
             string A;
             char ch;
             
             new_file>>Y>>X>>A>>Z;
             if(new_file.eof()){ break;}
             pr.push_back(make_pair(X,Y));         // insert record into vector
             Test tamp;
             tamp.x=X;
             tamp.y=Y;
             tamp.z=Z;
             tamp.s=A;
             mp[Y]=tamp;
             
           }
           
           sort(pr.begin(),pr.end());              // sort block by ammount
          
           for(int j=0;j<pr.size();j++)
            {
               Test tamp=mp[pr[j].second];
               
               new_file_2<<tamp.y<<" "<<tamp.x<<" "<<tamp.s<<" "<<tamp.z<<endl;   // wight back to file in sorted form of size B
            }
        }
     }
 int load_block(string input_file,vector <Test> &tamp_v,int B)   // this function will load one block of record and return vector of record
       {
                  
         fstream new_file;
         new_file.open(input_file, ios::in);
      
         if(new_file)
         {
           for(int j=0;j < B && !new_file.eof();j++)
                   {
                       int X,Y,Z;
                       string A;
                       char ch;
                         
                       new_file>>Y>>X>>A>>Z;                      // read data record from txt file
                       if(new_file.eof()){ break;}
                       Test tamp;
                       tamp.x=X;
                       tamp.y=Y;
                       tamp.z=Z;
                       tamp.s=A;
                       tamp_v.push_back(tamp);                    // insert into tamp_val vector
                       //cout<<X<<" "<<Y<<" "<<A<<" "<<Z<<endl; 
             
                   }
                   
            new_file.close();
            string filename(input_file);
           
            //remove(filename.c_str());     // to see intermediate run files comment this line   111
           
            return 1;       
         }
         
         return 0;
       }
 int write_block(string input_file,vector <Test> tamp_v)   // write vector of record into disk block 
       {
                  
         fstream new_file;
         new_file.open(input_file, ios::in);
      
         if(new_file)
         { 
            for(int i=0;i < tamp_v.size();i++)
                   {
                      new_file<<tamp_v[i].y<<" "<<tamp_v[i].x<<" "<<tamp_v[i].s<<" "<<tamp_v[i].z<<endl; 
             
                   }
            return 1;       
         }
         
         return 0;
       }
 int marge_all_files( int N,int x,int piq,int B)    // this function will  marge intitial files like o.txt,1.txt  etc into intermediate run files run_1_0-0.txt run_1_0-1.txt etc
     { int Totel_Block=x;
       int run=0;                                   
       
       for(int i=0;i<Totel_Block;i=i+N)             // N = M-1 for each M-1 files it try to marge 
           {  run=run+1; 
              
              vector<Test> tamp_val[N];
              priority_queue < pair<int,int> , vector< pair<int,int> >, greater< pair<int,int> > > min_heap;  
                                                                            // heap of size B always so totel size is (M-1)*B(datablocks) + B(heap) = M*B    
                  
              for(int k=0; k<N && i+k<Totel_Block;k++)                      // for each M-1 fles we load first Record pointer into heap
                {
                  string input_file=to_string(i+k)+".txt";
                  if(load_block(input_file,tamp_val[k],B))    
                   {
                     min_heap.push(make_pair(tamp_val[k][0].x,k));
                   }
                }
              vector<int> pointer(N,0);
              
              int block=0,offset=0;              // block is in which block we need to write data and off is how many data is stored in that block
             
              string s="run_"+to_string(piq)+"_"+to_string(i/N)+"-"+to_string(block)+".txt";   
                   
              fstream new_file_2;
              new_file_2.open(s, ios::out);
                   
              while(!min_heap.empty())
               {
                  pair<int,int> tamp=min_heap.top();   // pop the smallest recordpointer into heap
                  min_heap.pop();
                  int y=tamp.second;                   // y represent in which file this record pointer was 
                  int x=pointer[y];                    // x is pointer to data list y 
                  
                  if( x+1 < tamp_val[y].size() )       // if current vector of data is not empty 
                   {  
                     min_heap.push(make_pair(tamp_val[y][x+1].x,y)); //then push next record into heap
                     pointer[y]++;                                    // increased pointer 
                   }
                  
                  if(offset==0)                           // if off is zero means we need new txt file to write ouur data
                  { 
                    string s="run_"+to_string(piq)+"_"+to_string(i/N)+"-"+to_string(block)+".txt";
                    new_file_2<<s;                        // write name of next file into privious file
                    new_file_2.close();                   // close privious file
                    
                    new_file_2.open(s, ios::out);
                    block++;                              // increased value of data Block 
                   }
                  
                  new_file_2<<tamp_val[y][x].y<<" "<<tamp_val[y][x].x<<" "<<tamp_val[y][x].s<<" "<<tamp_val[y][x].z<<endl;   
                                                          // write data record into respactive data block file 
                 
                  offset++;
                  if(offset==B){ offset=0; } 
               }
               
              
           }
           
        return run;
     }
 int marge_all_files_2( int N,int x,int piq,int B) // this function will  marge intermediate files likerun_1_0-0.txt run_1_0-1.txt   etc
                                                      // into intermediate run files run_2_0-0.txt run_2_0-1.txt etc
     { int Totel_Block=x;                            
       int run=0;
       for(int i=0;i<Totel_Block;i=i+N)               // N = M-1 for each M-1 files it try to marge 
           {  
              run=run+1;
              
              vector<int> block_pointer(N,0);
              vector<Test> tamp_val[N];
              priority_queue < pair<int,int> , vector< pair<int,int> >, greater< pair<int,int> > > min_heap;
                                                                          // heap of size B always so totel size is (M-1)*B(datablocks) + B(heap) = M*B
              
              for(int k=0; k<N && i+k<Totel_Block;k++)                      // for each M-1 fles we load first Record pointer into heap
                { 
                  string input_file="run_"+to_string(piq-1)+"_"+to_string(i+k)+"-"+to_string(block_pointer[k])+".txt";
                  block_pointer[k]++;
                   
                   if(load_block(input_file,tamp_val[k],B) && tamp_val[k].size()>0)   
                    {
                      min_heap.push(make_pair(tamp_val[k][0].x,k));
                    }
                }
              vector<int> pointer(N,0);
              
              int block=0,offset=0;                                      // block is in which block we need to write data and off is how many data is stored in that block
                   string s="run_"+to_string(piq)+"_"+to_string(i/N)+"-"+to_string(block)+".txt";
                   fstream new_file_2;
                   new_file_2.open(s, ios::out);
              
              int num_block=0;
              //cout<<"\n"<<piq<<"\n\n\n";
              while(!min_heap.empty())
               {
                  if(offset==0)
                    { string s="run_"+to_string(piq)+"_"+to_string(i/N)+"-"+to_string(block)+".txt";
                      new_file_2<<s;
                      new_file_2.close();
                      //cout<<run<<endl;
                      new_file_2.open(s, ios::out);
                      block++;
                    }
                  
                  pair<int,int> tamp=min_heap.top();              // pop the smallest recordpointer into heap
                  min_heap.pop();                             
                  int y=tamp.second;                               // y represent in which file this record pointer was
                  int x=pointer[y];                                // x is pointer to data list y 
                  int Y=y,X=x;
                  
                  new_file_2<<tamp_val[Y][X].y<<" "<<tamp_val[Y][X].x<<" "<<tamp_val[Y][X].s<<" "<<tamp_val[Y][X].z<<endl;
                                                                        // write data record into respactive data block file 
            
                  if( x+1 < tamp_val[y].size() )                     // if current vector of data is not empty 
                   {  
                     min_heap.push(make_pair(tamp_val[y][x+1].x,y));  //then push next record into heap
                     pointer[y]++;                                     // increased pointer 
                   }
                  else   // if current data record block is been done then we need to load next data pointer
                  {  string input_file="run_"+to_string(piq-1)+"_"+to_string(i+y)+"-"+to_string(block_pointer[y])+".txt";
                     block_pointer[y]++;
                     tamp_val[y].resize(0);
                     
                     if(load_block(input_file,tamp_val[y],B)  && tamp_val[y].size()>0)   //load next data block
                      { 
                        min_heap.push(make_pair(tamp_val[y][0].x,y));                    // push first element of new data block into heap
                        pointer[y]=0;                                                    // set zero to data block pointer   
                      }
                  
                  } 
                  
                 
                  offset++;
                  if(offset==B){ offset=0; } 
                  
               } //cout<<"-------------------------EXIT--------------------"<<endl;
              
           }
        return run;
     }
int marge(int piq,int Totel_Block,int B)
     {
              string s="output.txt";
              fstream new_file_2;
              new_file_2.open(s, ios::out);
              
              for(int k=0;k<Totel_Block;k++)                                                     // read one data block at one time and then write it into output.txt
              {
               string input_file="run_"+to_string(piq)+"_"+to_string(0)+"-"+to_string(k)+".txt"; // name of file
               vector<Test> tamp;
               load_block(input_file,tamp,B);                                                    // load data block into tamp
               for(int i=0;i<tamp.size();i++)
               { 
                new_file_2<<tamp[i].y<<" "<<tamp[i].x<<" "<<tamp[i].s<<" "<<tamp[i].z<<endl;     // write data one by one into output.txt 
               }
               
               }  
              return 1;
     }
     
     
int main()
{ int N,B;
  cout<<"\nEnter Number of Record (N) : ";
  cin>>N;
  Creat_input_file(N);
  
  cout<<"\nEnter Number of Record Per Block (B) : ";
  cin>>B;
  int Totel_Block= N%B==0 ? N/B : N/B+1;
  cout<<"\ntotal block are  "<<Totel_Block<<endl;
  
  create_Initial_Runs_for_creat_block(B);   // create data blocks of each with size B
  
  int M;
  
  cout<<"\nEnter Number of Memory Block in RAM (M) : ";
  cin>>M;
  
  int run;
  int x,i=1;
  run=marge_all_files(M-1,Totel_Block,1,B);  // first marge initial dataset file and convert intermediate run files
  i++;
  while(run>(M-1))                           // this loop is case no 2 if run > M-1 then this loop will run in case 1 this loop will not run 
  {  
     
    run=marge_all_files_2(M-1,run,i,B);      // marge intermediate run and convert into higher level marge
    i++;
  }
  
  run=marge_all_files_2(M-1,run,i,B);        // this loop will finallny sort all data into different datafiles
  
  marge(i,Totel_Block,B);                    // this function will combile all sorted data from different file and write into single output.txt file
  
  return 0;
}
