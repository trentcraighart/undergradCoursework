/* CS261- Assignment 1 - Q.1*/
/* Name: Trent Vasquez
 * Date: 7/3
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
  struct student* array;
  array = malloc((sizeof(struct student)) * 10);

     /*Return the pointer*/
  return array;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
IDs being between 1 and 10, scores between 0 and 100*/
  srand(time(NULL));
  int i, scores;
  int idArray[10];

  for(i = 0; i < 10; i++){
    idArray[i] = -1;
  }

  //Generates id's 1-10 in a random order;
  for(i = 0; i < 10; i++){
    int current;
    current = rand() % 10;
    while(idArray[current] != -1){
      if(current == 9){
        current = 0;
      }else{
        current++;
      }
    }
    idArray[current] = i;
  }

  //Generate Students
  for(i = 0; i < 10; i++){
    scores = rand() % 101;
    students[i].id = 0;
    students[i].id = idArray[i];
    students[i].score = scores;
  }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
  int i; 
  for(i = 0; i < 10; i++){
    printf("ID %d Score %d\n", students[i].id, students[i].score);
  }

}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
ten students*/
  int min, max, sum, avg, i;
  min = students[0].score;
  max = students[0].score;
  sum = students[0].score;
  for(i = 1; i < 10; i++){
    if(students[i].score > max){
      max = students[i].score;
    }
    if(students[i].score < min){
      min = students[i].score;
    }
    sum += students[i].score;
  }
  avg = sum / 10;
  printf("Min = %d\nMax = %d\nAvg = %d\n", min, max, avg);     
}

void deallocate(struct student* stud){
  free(stud);
     /*Deallocate memory from stud*/
}

int main(){
    struct student* stud = NULL;
    
    /*Call allocate*/
    printf("Allocate\n");
    stud = allocate();
    /*Call generate*/
    printf("Generate\n");
    generate(stud);
    /*Call output*/
    printf("Output\n");
    output(stud);
    /*Call summary*/
    printf("Summary\n");
    summary(stud);    
    /*Call deallocate*/
    printf("Deallocate\n");
    deallocate(stud);

    return 0;
}

/*
    Question Responses:
*/
