#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define LIMIT 10
typedef char STRING20[21];
typedef char STRING50[51];

typedef struct {
	STRING20 subjCode[LIMIT];	//ex. CCPROG2
	float units[LIMIT];			//ex. 2.0
	float totalUnits;			//Total Units of the Student
	int totalSubj;				//Total Number of Subjects
	int key;					//For security
} subjectType;

void initializeSubjects(subjectType * subjects) {
	
	int i;
	int tryAgain;
	char cCheck;
	STRING20 cChoice;
	
	system("CLS");
	printf("| GPA CALCULATOR 2020 v. beta1.2\n");
	printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
	
	printf("How many subjects do you have? [Answer with Integers]: ");
	scanf("%d", &subjects->totalSubj);
	
	for (i = 0; i < subjects->totalSubj; i++){
		system("CLS");
		printf("| GPA CALCULATOR 2020 v. beta1.2\n");
		printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
		
		fflush(stdin);
		printf("Enter Subject Code No. %d: ", i + 1);
		gets(subjects->subjCode[i]);
				
		do {
			fflush(stdin);
			printf("Enter Total Units of [%s]: ", subjects->subjCode[i]);
			
			if (scanf("%f%c", &subjects->units[i], &cCheck) != 2 || cCheck != '\n') {	//CHECKS IF INTEGER
			    system("CLS");
				printf("| GPA CALCULATOR 2020 v. beta1.2\n");
				printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
				printf("Enter Subject Code No. %d: %s\n\n", i + 1, subjects->subjCode[i]);
				printf("Invalid Input. Try again.\n");
			    tryAgain = 1;
			}
			else
				tryAgain = 0;
		
		} while (tryAgain == 1);
		
		subjects->totalUnits += subjects->units[i];
	}
		
	printf("\nInitialization Done. Press anything to continue..."); getch();
	
	
	system("CLS");
	printf("| GPA CALCULATOR 2020 v. beta1.2\n");
	printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
	do {
		fflush(stdin);
		printf("Save these settings? [Y/N]: ");
		gets(cChoice);
		
		if (strcmp(cChoice, "Y\0") == 0 || strcmp(cChoice, "y\0") == 0) {
			
			FILE * pSource;
			pSource = fopen("subjects.txt", "wt");
			
			for (i = 0; i < subjects->totalSubj; i++)
				fprintf(pSource, "%s %.1f\n", subjects->subjCode[i], subjects->units[i]);
				
			fclose(pSource);
		}
		else if (strcmp(cChoice, "N\0") == 0 || strcmp(cChoice, "n\0") == 0)
			tryAgain = 0;
		else {
			system("CLS");
			printf("| GPA CALCULATOR 2020 v. beta1.2\n");
			printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
			printf("Invalid Input. Type 'Y' for yes and 'N' for no.\n");
			tryAgain = 1;
		}
	} while (tryAgain == 1);
}

void loadSubjects(FILE * pSource, subjectType * subjects){
	
	//INITIALIZE
	int i = 0;
	subjects->totalUnits = 0;
	
	while((fscanf(pSource, "%s %f", subjects->subjCode[i], &subjects->units[i])) == 2) {	//SCAN SUBJECTS IN TXT FILE
		subjects->totalUnits += subjects->units[i];	//COUNTER - for the total units
		i++;	//INCREMENT
	}
	subjects->totalSubj = i;	//GET i FOR THE NUMBER OF SUBJECTS
			
	printf("\n\nLast settings have now been loaded.\n");
	printf("Press anything to continue..."); getch();
}

void inputGrades(subjectType subjects, subjectType * myGrades) {
	
	int i;
	for (i = 0; i < subjects.totalSubj; i++) {
		system("CLS");
		printf("| GPA CALCULATOR 2020 v. beta1.2\n");
		printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
		printf("         === ENCODE SYSTEM ===\n");
		printf("What's your final grade in [%s]: ", subjects.subjCode[i]);
		strcpy(myGrades->subjCode[i], subjects.subjCode[i]);
		scanf("%f", &myGrades->units[i]);
		myGrades->totalUnits += subjects.units[i] * myGrades->units[i];
	}
	
	myGrades->key = 1;
	printf("\nAll Grades have been entered.\n");
	printf("Press anything to continue..."); getch();
} 

int printGrades(subjectType subjects, subjectType myGrades) {
	
	FILE * pFile;
	STRING20 name;
	STRING50 filename;
	int i;
	
	system("CLS");
	printf("| GPA CALCULATOR 2020 v. beta1.2\n");
	printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
	printf("Enter surname: ");
	gets(name);
	snprintf(filename, sizeof(filename), "grade-assessment-for-[%s].txt", name);
	
	pFile = fopen(filename, "wt");
	
	fprintf(pFile, "STUDENT: %s\n\n", name);
	fprintf(pFile, "SUBJCODE     UNITS\tGRADE\n");
	for (i = 0; i < subjects.totalSubj; i++){
		fprintf(pFile, "%s      %.1f\t%.1f\n", subjects.subjCode[i], subjects.units[i], myGrades.units[i]);
	}
	fprintf(pFile, "\nTOTAL UNITS: %.1f\n", subjects.totalUnits);
	fprintf(pFile, "GPA: %.3f\n", myGrades.totalUnits/subjects.totalUnits);

	fclose(pFile);
	
	printf("\nGrades have now been printed to a txt file.\n\n");
	
	printf("All Data encoded in this system has been locked for confidentiality.\n");
	printf("Press anything to continue..."); getch();
	
	return 0;
}

void showLogo();

int main(){
	
	showLogo();
	printf("\n| Made for De La Salle University students only.\n");
	printf("| Developer: James Louis V. Lemsic | 11942169.\n");
	printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
	printf("Press anything to continue..."); getch();
	
	FILE * pSource;
	subjectType subjects;
	subjectType myGrades;
	
	subjects.totalUnits = 0;
	myGrades.totalUnits = 0;
	myGrades.key = 0;
	
	STRING20 cChoice;
	int tryAgain, loop = 1;
		
	pSource = fopen("subjects.txt", "rt");
	
	if (pSource == NULL) {
		printf("\n\n[subjects.txt] cannot be found.\n");
		printf("Initialize subjects first.\n");
		printf("Press anything to continue..."); getch();
		initializeSubjects(&subjects);
	}
	else {
		loadSubjects(&(*pSource), &subjects);
		fclose(pSource);
	}
	myGrades.totalSubj = subjects.totalSubj;
	
	do {
		system("CLS");                              
		printf("| GPA CALCULATOR 2020 v. beta1.2\n");
		printf("| Lemsic Industries. All rights reserved (c) 2020.\n\n");
		printf("      == MAIN MENU ==\n");
		printf("  |  [A] Encode Grades  \n");
		printf("  |  [B] Print Grades   \n");
		printf("  |  [C] Exit           \n\n");
		do {
			fflush(stdin);
			printf("   CHOICE: ");
			gets(cChoice);
			
			if (strcmp(cChoice, "A\0") == 0 || strcmp(cChoice, "a\0") == 0) {	//ENCODE SYSTEM
				tryAgain = 0;
				inputGrades(subjects, &myGrades);
			}
			else if (strcmp(cChoice, "B\0") == 0 || strcmp(cChoice, "b\0") == 0) {	//VIEW ARROW EXPRESS VISUALLY
				tryAgain = 0;
				
				if (myGrades.key == 1)
					myGrades.key = printGrades(subjects, myGrades);
				else {
					printf("\n         Error 404. Grades not found.\n");
					printf("         Encode Grades first.\n");
					printf("\n         Press anything to continue..."); getch();
				}	
			}
			else if (strcmp(cChoice, "C\0") == 0 || strcmp(cChoice, "c\0") == 0) {	//VIEW ARROW EXPRESS VISUALLY
				tryAgain = 0;
				loop = 0;
			}
			else {
				system("CLS");                              
				printf("GPA CALCULATOR 2020 v. beta1.2\n\n");
				printf("      == MAIN MENU ==\n");
				printf("  |  [A] Encode Grades  \n");
				printf("  |  [B] Print Grades   \n");
				printf("  |  [C] Exit           \n\n");	
				printf("   Invalid Input. Try again.\n");
				tryAgain = 1;
			}
		} while (tryAgain == 1);
	} while (loop == 1);
	
	showLogo();
	printf("\n| Thank you for using the GPA Calculator 2020.\n");
	printf("| Lemsic Industries. All rights reserved c 2020.\n\n");
	printf("Press anything to exit..."); getch();
	
	return 0;
}

void showLogo(){
	
	system("CLS");
	printf("   ______  _______     _               _            _       _             \n");
	printf(" .' ___  ||_   __ \\   / \\             | |          | |     | |            \n");
	printf("/ .'   \\_|  | |__) | / _ \\    ___ __ _| | ___ _   _| | __ _| |_ ___  _ __ \n");
	printf("| |   ____  |  ___/ / ___ \\  / __/ _` | |/ __| | | | |/ _` | __/ _ \\| '__|\n");
	printf("\\ `.___]  |_| |_  _/ /   \\ \\| (_| (_| | | (__| |_| | | (_| | || (_) | |   \n");
	printf("  `._____.'|_____||____| |___\\___\\__,_|_|\\___|\\__,_|_|\\__,_|\\__\\___/|_|   \n");                            
}
