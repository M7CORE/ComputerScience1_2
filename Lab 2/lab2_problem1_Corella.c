#include <stdio.h>
#include <stdlib.h>

//Function Declarations.
//Function that reads data, returns pointer to struct
struct student *readData (FILE *in, int *students, int *quizzes);
//Function that writes data, returns pointer to struct
void writeData (FILE *out, struct student *ptr, int students, int quizzes);

//Struc for each student
typedef struct student{
	char lName[20];
	int assignment;
	int final;
	int *quiz;
	int total;
}student;
	
//Main func
int main(){
	FILE *in;//create input file pointer
	in = fopen("input.txt", "r");//open file to read
	//Variables for readData
	int students, quizzes, i;//Number of students and number of quizzes
	struct student *ptr;//Create pointer for struct array
	if (in != NULL)//call for readData as long as file exists
		ptr = readData(in, &students, &quizzes);
	fclose(in);//close file after reading data
	FILE *out;//create ouptut file
	out = fopen("output.txt", "w");//open output file to write
	writeData(out, ptr, students, quizzes);//call for write
	fclose(out);//close output file after writing
	for (i = 0; i < students; i++)//Free memory for quizzes
		free(ptr[i].quiz);
	free(ptr);//free memory for struct
	
	
}
//Function that reads data from the input file. Takes the input file, the amount students, and the amount of quizzes.
struct student *readData (FILE *in, int *students, int *quizzes){
	struct student *ptr;//pointer to student struct 
	int i, j;
	
	//read number of quizzes and students
	fscanf(in, "%d%d", students, quizzes);
	
	//Dynamically allocate memory for students
	ptr = (struct student*)malloc(*students * (sizeof(struct student)));
	
	for (i = 0; i < *students; i++){
		ptr[i].quiz = (int*)malloc(*quizzes * (sizeof(int)));//allocate memory for the amount of quizzes
		fscanf(in, "%s %d", ptr[i].lName, &ptr[i].assignment);//Scan name and assignment score
		int quizSum = 0;
		for (j = 0; j < *quizzes; j++){
			fscanf(in, "%d", &ptr[i].quiz[j]);//scan quiz grade for amount of quizzes
			quizSum = quizSum + ptr[i].quiz[j];//add quiz scores
		}
		fscanf(in, "%d", &ptr[i].final);//scan final grade
		ptr[i].total = ptr[i].assignment + ptr[i].final + quizSum;//calculate final grade
	}
	//return pointer to first struct
	return ptr;
}

//Function to output highest score to screen and write it to the output file. Takes output file pointer, struct student pointer, number of students, and number of quizzes.
void writeData (FILE *out, student *ptr, int students, int quizzes){
	int i, max;
	max = 0;//index of highest score set to the index of the first score
	for (i = 0; i < students; i++){
		if (ptr[i].total > ptr[max].total)
			max = i;//change index if valued stored is larger than previous value stored.
	}
	fprintf(out, "Name: %s\nAssignment: %d\n", ptr[max].lName, ptr[max].assignment);//Print student name, and assignment grade to the output file.
	printf("Name: %s\nAssignment: %d\n", ptr[max].lName, ptr[max].assignment);//Print student name and assignment grade to the screen.
	fprintf(out, "Quizzes:");
	printf("Quizzes:");
	for (i = 0; i < quizzes; i++){//loop through quizzes and print the grades to the file and screen.
		fprintf(out, " %d", ptr[max].quiz[i]);
		printf(" %d", ptr[max].quiz[i]);
	}
	fprintf(out, "\nFinal Exam: %d\nTotal: %d", ptr[max].final, ptr[max].total);//Print final exam grade and total grade to the output file.
	printf("\nFinal Exam: %d\nTotal: %d\n", ptr[max].final, ptr[max].total);//Print the final exam grade and total grade
}
