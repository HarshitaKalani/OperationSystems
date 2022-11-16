// #include <bits/stdc++.h>
// using namespace std;
// #include <stdlib.h>

// int mutx=1;
// int x=0;
// int full=0;
// int emty = 10;

// void consumer(){
   
//     mutx-=1;
//     full-=1;
//     emty+=1;
//     printf("Conumer consumes item %d \n" , x);
//     x--;
//     ++mutx;
// }

// void producer(){
//     mutx-=1;
//     full+=1;
//     emty-=1;
//     x++;
//     printf("Producer produces item %d \n", x);
//     ++mutx;
// }
// int main(){
//     int n, i;
//     printf("Press 1 for Producer\nPress 2 for consumer\nPress 0 to exit\n");
//     for(i=1;i>0;i++){
//         printf("Enter your choice: ");
//         cin>>n;
//         switch (n){
//             case 0:
//                 exit(0);
//                 break;
//             case 1:
//                 if((mutx==1) &&(emty!=0)) producer();
//                 else cout<<"Buffer is full!";
//                 break;
//             case 2:
//                 if((mutx==1) && (full!=0)) consumer();
                // else cout<<"Buffer is empty!";
//                 break;
            
//         }
        
//     }
// }