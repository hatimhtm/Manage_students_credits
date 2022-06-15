/* CSC 2302 - Summer Session
   First Practical Session
   Programmer Name: Hatim EL HASSAK
  
   We use the following students for testing:
   VUCHI Mbifanse MILTON 84101 ASSEM Nasser
   BAGHDADI Hasnae 85757 ABRACHE Jawad
   BALADI Oussama 84606 KETTANI Driss 
   SALIH-ALJ Khadija 101666 TALEI Hanaa
*/

#include<stdio.h>
#include<string.h>

typedef struct{
  char a_name[20];
  char a_email[20];  
}a_info;

typedef struct{
  char s_name[20]; 
  int s_id;
  int n_earned_credits;
  a_info X; 
}s_info;

void fill_array(s_info arr[],int N_students_to_use);
void display_array(s_info arr[],int N_students_to_use);
a_info search_advisor_info(s_info arr[],int N_students_to_use, int idToSearch);
s_info search_student_credits(s_info arr[],int N_students_to_use, int idToSearch);
void clear_screen(void);
void bubble_sort(s_info arr[],int N_students_to_use);
void selection_sort(s_info arr[],int N_students_to_use);
void display_array(s_info arr[],int N_students_to_use);


void menu(void){
  
  printf("\n\n\t\t--------------- Menu to Use-----------------\n");
  printf("\t\t|\t\t\t\t\t   |\n");
  printf("\t\t|1. Fill Array with Data\t\t   |\n");
  printf("\t\t|2. Display Array Content\t\t   |\n");
  printf("\t\t|3. Search for Student Advisor Information |\n");
  printf("\t\t|4. Search for Student Earned Credits\t   |\n");
  printf("\t\t|5. Sort Students by Name(Bubble Sort)\t   |\n");
  printf("\t\t|6. Sort Students by N_ECr(Selection Sort) |\n");
  printf("\t\t|7. QUIT\t\t\t\t   |\n");
  printf("\t\t|\t\t\t\t\t   |\n");
  printf("\t\t--------------------------------------------\n");
  printf("\n\t\tYour Choice Please:");
}
int main(void){

   s_info arr[30], Studentcredit;
   a_info Advisordata;
   int N_students_to_use = 3;
   int choice, idToSearch;
   
   do{
     menu();
     scanf("%d",&choice);
     
     switch(choice){
	
	case 1:
              clear_screen();
              fill_array(arr,N_students_to_use);
	       break;
	case 2:
              clear_screen();
              display_array(arr,N_students_to_use);
	       break;
	case 3:
              clear_screen();
              printf("\n\t\tEnter Student ID to Search: ");
              scanf("%d",&idToSearch);
              Advisordata = search_advisor_info(arr, N_students_to_use, idToSearch);
              if (strcmp(Advisordata.a_email, "Not found") == 0) {
                     printf("\n\t\tStudent was not FOUND\n");
              } else {
                     printf("\n\t\tAdvisor information for %d: \n", idToSearch);
                     printf("\n\t\tAdvisor Name: %s\n", Advisordata.a_name);
                     printf("\n\t\tAdvisor Email: %s\n", Advisordata.a_email);
              }
	       break;
	case 4:
              clear_screen();
              printf("\n\t\tEnter Student ID to Search: ");
              scanf("%d",&idToSearch);
              Studentcredit = search_student_credits(arr, N_students_to_use, idToSearch);
              if (strcmp(Studentcredit.s_name, "Not found") == 0) {
                     printf("\n\t\tStudent was not FOUND\n");
              } else {
                     printf("\n\t\tStudent information for %d: \n", idToSearch);
                     printf("\n\t\tStudent Earned Credits: %d\n", Studentcredit.n_earned_credits);
              }
	       break;
       case 5:
              clear_screen();
              bubble_sort(arr, N_students_to_use);
              display_array(arr,N_students_to_use);
	       break;
	case 6:
              clear_screen();
              selection_sort(arr, N_students_to_use);
              display_array(arr,N_students_to_use);
	       break;
	case 7:printf("\n\t\tYou decided to QUIT\n\n\t\tBYE\n\n\t");
	
	default:printf("\n\t\tThat was a WRONG Choice!\n");
	}
   }while(choice!=7);
return(0);
}

void fill_array(s_info arr[],int N_students_to_use){
  int i;
  for(i = 0 ; i < N_students_to_use ; i++){
       printf("\t\tEnter Student ID: ");
       scanf("%d", &arr[i].s_id);
       printf("\t\tEnter Student Name: ");
       getchar();
       scanf("%[^\n]%*c", arr[i].s_name);
       printf("\t\tEnter Student Earned Credits: ");
       scanf("%d", &arr[i].n_earned_credits);
       printf("\t\tEnter %s's Advisor Name: ", arr[i].s_name);
       getchar();
       scanf("%[^\n]%*c", arr[i].X.a_name);
       printf("\t\tEnter Dr.%s's Email: ", arr[i].X.a_name);
       scanf("%s", arr[i].X.a_email);
       printf("\n");
  }
}

void display_array(s_info arr[],int N_students_to_use){
  int i;
  for(i = 0 ; i < N_students_to_use ; i++){
       printf("\t\tStudent ID: %d\n", arr[i].s_id);
       printf("\t\tStudent Name: %s\n", arr[i].s_name);
       printf("\t\tStudent Earned Credits: %d\n", arr[i].n_earned_credits);
       printf("\t\tStudent Advisor Name: %s\n", arr[i].X.a_name);
       printf("\t\tStudent Advisor Email: %s\n", arr[i].X.a_email);
       printf("\n");
       printf("\t\t--------------------------------------------\n");
       printf("\n");
  }
}

a_info search_advisor_info(s_info arr[],int N_students_to_use, int idToSearch){
  int i;
  a_info flag;
  strcpy(flag.a_email, "Not found");
  for(i = 0 ; i < N_students_to_use ; i++){
       if(arr[i].s_id == idToSearch){
           strcpy(flag.a_name, arr[i].X.a_name);
           strcpy(flag.a_email, arr[i].X.a_email);
           break;
       }
  }
  return(flag);
}

s_info search_student_credits(s_info arr[],int N_students_to_use, int idToSearch){
  int i;
  s_info flag;
  strcpy(flag.s_name, "Not found");
  for(i = 0 ; i < N_students_to_use ; i++){
       if(arr[i].s_id == idToSearch){
              return(arr[i]);
       }
  }
  return(flag);
}

void clear_screen(void){
  int i;
  for(i = 0 ; i < 50 ; i++){
    printf("\n");
  }
}

void bubble_sort(s_info arr[],int N_students_to_use){
  int i, j;
  s_info temp;
  for(i = 0 ; i < N_students_to_use ; i++){
       for(j = N_students_to_use ; j > i ; j--){
            if(arr[j].n_earned_credits > arr[j-1].n_earned_credits){
                 temp = arr[j];
                 arr[j] = arr[j-1];
                 arr[j-1] = temp;
            }
       }
  }
}

void selection_sort(s_info arr[],int N_students_to_use){
  int i, j, max;
  s_info temp;
  for(i = 0 ; i < N_students_to_use ; i++){
       max = i;
       for(j = N_students_to_use ; j > i ; j--){
            if(arr[j].n_earned_credits > arr[max].n_earned_credits){
                 max = j;
            }
       }
       if (max != i){
            temp = arr[i];
            arr[i] = arr[max];
            arr[max] = temp;
       }
  }
}

void display_array_by_advisor(s_info arr[],int N_students_to_use){
  int i;
  for(i = 0 ; i < N_students_to_use ; i++){
       printf("\t\tStudent ID: %d\n", arr[i].s_id);
       printf("\t\tStudent Name: %s\n", arr[i].s_name);
       printf("\t\tStudent Earned Credits: %d\n", arr[i].n_earned_credits);
       printf("\t\tStudent Advisor Name: %s\n", arr[i].X.a_name);
       printf("\t\tStudent Advisor Email: %s\n", arr[i].X.a_email);
       printf("\n");
       printf("\t\t--------------------------------------------\n");
       printf("\n");
  }
}
