/* CSC 2302 - Summer Session
   First Practical Session
   Programmer Name: Hanaa Talei (Part1) 
*/

// For you to know what you have to do read the comments that starts with --->

#include<stdio.h>
#include<string.h>

typedef struct{
  char a_name[40];
  char a_email[40];  
}a_info;

typedef struct{
  char s_name[40];
  int s_id;
  int n_earned_credits;
  a_info X; 
}s_info;

void fillArray(s_info arr[40], FILE *infp, int *count);
void displayArray(FILE * infp);
a_info SearchAdvisorInfo(s_info arr[40], int count, int idToSearch);
int Search_Ncrd(s_info arr[40], int count, int idToSearch);
void menu(void);
s_info selection_sorting(s_info arr[40], int count);
void classification(s_info arr[40], int count);

int main(void){

  s_info arr[40];
  a_info AdvisorData;
  int n_crd, count = 0;
  int choice, toSearch;
  FILE *infp;
  infp = fopen("data.txt", "r");

  if (!infp){
    printf("Error opening file\n");
    return 0;
  }
      
  do{
    menu(); 
    scanf("%d",&choice); 
     
    switch(choice){
	    case 1:
        displayArray(infp);
	      break;
	    case 2:
        fillArray(arr, infp, &count);
        printf("\t\t%d", count);
	      break;
	    case 3:
        printf("\n\t\tInput ID of the student to Search For:");
	      scanf("%d",&toSearch); 
	      AdvisorData = SearchAdvisorInfo(arr, count, toSearch);
	      if(strcmp(AdvisorData.a_name,"NotFound")==0)
	      printf("\n\t\tSORRY! Student was not FOUND\n");
        else{
			  printf("\n\t\t Advisor Information for %d:\n",toSearch);
			  printf("\n\t\tAdvisor Name:%s\n\t\tEmail:%s\n",AdvisorData.a_name,AdvisorData.a_email);
        }
			  break;
	    case 4:
        printf("\n\t\tInput ID of the student to Search For:");
	      scanf("%d",&toSearch); 
	      n_crd = Search_Ncrd(arr, count, toSearch);
	      if(n_crd == -1)
			  printf("\n\t\tSORRY! Student was not FOUND\n");
	      else
	      printf("\n\t\t%d currently earned %d credit(s)\n",toSearch,n_crd); 
	      break;
      case 5: 
        selection_sorting(arr, count);
	      break;
	    case 6:
        classification(arr, count);
	      break;
	    case 7:printf("\n\t\tYou decided to QUIT\n\n\t\tBYE\n\n\t"); 
	      break;	                   
	    default:printf("\n\t\tThat was a WRONG Choice!\n");	 
    }   
  }while(choice!=7);
  fclose(infp);
return(0);
}

//--> You need to change this function so that the array is filled with data in the file!
//-->File is already open in the main function

void displayArray(FILE *infp){
  char line[50];
  while(fgets(line, 50, infp) != NULL){
    printf("\t\t%s", line);
  }
}

void fillArray(s_info arr[40], FILE *infp, int *count){
  char line[40], temp;
  int i = 0;
  fseek(infp, 0, 0);
  while (!feof(infp)) {
    fscanf(infp, "%d", &arr[i].s_id);
    fscanf(infp, " %c", &temp);
    fgets(arr[i].s_name, 40, infp);
    fscanf(infp, "%d", &arr[i].n_earned_credits);
    fscanf(infp, " %c", &temp);
    fgets(arr[i].X.a_name, 40, infp);
    fgets(arr[i].X.a_email, 40, infp);
    fgets(line, 40, infp);
    i++;
    (*count)++;
  }
}

a_info SearchAdvisorInfo(s_info arr[40], int count, int idToSearch){
  int i; 
  a_info flag; 
  strcpy(flag.a_name,"NotFound");
  
  for(i = 0; i < count; i++){
    if(arr[i].s_id == idToSearch)//Found
      return(arr[i].X);
  }
  return(flag);
}

int Search_Ncrd(s_info arr[40], int count, int idToSearch){
  int i; 
  
  for(i=0 ;i < count ;i++){
    if(arr[i].s_id == idToSearch)//Found
      return(arr[i].n_earned_credits);
  }
  return(-1);//return any random number that can't be a n_crd
}

s_info selection_sorting (s_info arr[40], int count){
  int i, j, max;
  s_info temp;
  for(i = 0; i < count; i++){
    max = i;
    for(j = count; j > i; j--){
      if(arr[j].n_earned_credits > arr[max].n_earned_credits)
        max = j;
    }
    if (max != i){
      temp = arr[i];
      arr[i] = arr[max];
      arr[max] = temp;
    }
  }
  for (int k = 0; k < count; k++) {
    printf("\t\t%d\n\t\t%s\t\t%d\n\t\t%s\t\t%s", arr[k].s_id, arr[k].s_name, arr[k].n_earned_credits, arr[k].X.a_name, arr[k].X.a_email);
    printf("\t\t----------------\n");
  }
  return(arr[0]);
}

void classification (s_info arr[40], int count){
  int i, flagfresh = 0, flagsophomore = 0, flagjunior = 0, flagsenior = 0;
  FILE *fresh, *shophomore, *junior, *senior;
  for(i = 0; i < count; i++){
    if(arr[i].n_earned_credits < 30){
      while (flagfresh == 0) {
        fresh = fopen("freshmane.txt", "w");
        flagfresh = 1;
      }
      fprintf(fresh, "%d\n", arr[i].s_id);
      fprintf(fresh, "%s", arr[i].s_name);
      fprintf(fresh, "%d\n", arr[i].n_earned_credits);
      fprintf(fresh, "%s", arr[i].X.a_name);
      fprintf(fresh, "%s", arr[i].X.a_email);
      fprintf(fresh, "----------------\n");
    }else if(arr[i].n_earned_credits < 60 && arr[i].n_earned_credits >= 30) {
      while (flagsophomore == 0) {
        shophomore = fopen("sophomore.txt", "w");
        flagsophomore = 1;
      }
      fprintf(shophomore, "%d\n", arr[i].s_id);
      fprintf(shophomore, "%s", arr[i].s_name);
      fprintf(shophomore, "%d\n", arr[i].n_earned_credits);
      fprintf(shophomore, "%s", arr[i].X.a_name);
      fprintf(shophomore, "%s", arr[i].X.a_email);
      fprintf(shophomore, "----------------\n");
    }else if(arr[i].n_earned_credits < 90 && arr[i].n_earned_credits >= 60) {
      while (flagjunior == 0) {
        junior = fopen("junior.txt", "w");
        flagjunior = 1;
      }
      fprintf(junior, "%d\n", arr[i].s_id);
      fprintf(junior, "%s", arr[i].s_name);
      fprintf(junior, "%d\n", arr[i].n_earned_credits);
      fprintf(junior, "%s", arr[i].X.a_name);
      fprintf(junior, "%s", arr[i].X.a_email);
      fprintf(junior, "----------------\n");
    }else if(arr[i].n_earned_credits >= 90) {
      while (flagsenior == 0) {
        senior = fopen("senior.txt", "w");
        flagsenior = 1;
      }
      fprintf(senior, "%d\n", arr[i].s_id);  
      fprintf(senior, "%s", arr[i].s_name);
      fprintf(senior, "%d\n", arr[i].n_earned_credits);
      fprintf(senior, "%s", arr[i].X.a_name);
      fprintf(senior, "%s", arr[i].X.a_email);
      fprintf(senior, "----------------\n");
      }
  }
fclose(fresh);
fclose(shophomore);
fclose(junior);
fclose(senior);
}
//--> I changed the menu Options. 
//--> You need to change main and functions if needed
//--> Once you load students data to an array, use the array data but not the file data
//--> for option 6, you need to use a function that will use the array and produce at most four files
//--> files should be called Freshmen.txt, Sophomore.txt, Junior.txt, Senior.txt
//--> File should contain the name and the id of the students who meet the requirement down
//-->Freshman 0-29 crd hours
//-->Sophomore 30-59 
//-->Junior 60-89 
//-->Senior 90 or more crd hours
//--> Do not create the file till you find a student meeting the requirement

void menu(void){
  
  printf("\n\n\t\t--------------- Menu to Use-------------------\n");
  printf("\t\t|\t\t\t\t\t     |\n");
  printf("\t\t|1. View the content of the file\t     |\n");
  printf("\t\t|2. Load data from file to array\t     |\n");
  printf("\t\t|3. Search for a Student Advisor Information |\n");
  printf("\t\t|4. Search for Student Earned Credits\t     |\n");
  printf("\t\t|5. Sort Students by N_ECr(Selection Sort)   |\n");
  printf("\t\t|6. Classify Students Academically\t     |\n");
  printf("\t\t|7. QUIT\t\t\t\t     |\n");
  printf("\t\t|\t\t\t\t\t     |\n");
  printf("\t\t----------------------------------------------\n");
  printf("\n\t\tYour Choice Please: ");
}
