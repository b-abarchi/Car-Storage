//-------------------------------------
// Bello Abarchi, Leslie Recendiz, Ajwad Sabano, Brian singh, fred zeder, Marcos torres, steve zachari, talal jalabi
// 
//
//-------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define PAUSE system("pause")
#define CLS system("cls")
#define FLUSH myFlush();
#define SIZE 100

typedef struct {
	char model[20];
	char make[20];
	int year;
	float price;

} CARS;

// function prototype
void myFlush();
char getChoice();
void displayMenu();
void loadCars(CARS cars[], int *carCounter);
void save(CARS cars[], int carCounter);
void averageCars(CARS cars[], int *carCounter);
void displayData(CARS cars[], int carCounter);
void getCar(CARS cars[], int carCounter);
void getModel(CARS cars[], int carCounter);
void getMake(CARS cars[], int carCounter);
void getYear(CARS cars[], int carCounter);
void getPrice(CARS cars[], int carCounter);
void displayResults(CARS  cars[], int carCounter);
void myFlush();

main() {
	//Variable Declaration
	char choice;
	int carCounter = 0;
	CARS cars[SIZE];
	FILE *ptr;
	ptr = fopen("StoredCars.bin", "rb");
	if (ptr != NULL)
		loadCars(cars, &carCounter);
	//Menu System
	do {
		choice = getChoice();
		switch (choice) {
		case 'A':
			if (carCounter < 100) {
				getCar(cars, carCounter);
				carCounter++;
			}
			else {
				printf("Cannot enter any more cars\n");
				PAUSE;
			}
			break;
		case 'B':
			if (carCounter > 0) {
				displayResults(cars, carCounter);
			}
			else {
				printf("No cars have been entered yet!\n");
				PAUSE;
			}
			break;
		case 'C':
			if (carCounter > 0) {
				save(cars, carCounter);
				printf("Successfully Saved!\n");
				PAUSE;
			}
			else {
				printf("No cars have been entered yet!\n");
				PAUSE;
			}
			break;
		case 'D':
			if (carCounter > 0) {
				displayData(cars, carCounter);
			}
			else {
				printf("No cars have been entered yet!\n");
				PAUSE;
			}
			break;
		case 'Q':// Quits the program
			printf("\n\tHave a nice day!\n");
			PAUSE;
			break;
		default:
			break;
		}//end switch
	} while (choice != 'Q');

}//end main

void displayMenu() {
	CLS;
	printf("\t=======================================\n");
	printf("\t==         M A I N   M E N U         ==\n");
	printf("\t=======================================\n");
	printf("\t[A] Add new car\n");
	printf("\t[B] Display all cars\n");
	printf("\t[C] save all cars\n");
	printf("\t[D] display total # of cars; avg car price; total price of all cars\n");
	printf("\t[Q]uit \n");
	printf("\tEnter choice: ");
}//end displayMenu


char getChoice() {
	char choice;
	displayMenu();
	scanf(" %c", &choice); FLUSH;

	return toupper(choice);
}//end getChoice

void loadCars(CARS cars[], int *carCounter) {
	FILE *ptr;
	ptr = fopen("StoredCars.bin", "rb");

	if (ptr == NULL) {
		printf("Error Loading cars no cars to load\n");
		PAUSE;
	}
	else {
		fread(cars, sizeof(CARS), SIZE, ptr);
		fread(&*carCounter, sizeof(int), 1, ptr);
	}
	fclose(ptr);
}//end load cars

void save(CARS cars[], int carCounter) {
	FILE *ptr;
	ptr = fopen("StoredCars.bin", "wb");
	if (ptr == NULL) {
		printf("\nError Could not save cars\n");
		PAUSE;
		exit(-1);
	}
	else {
		fwrite(cars, sizeof(CARS), SIZE, ptr);
		fwrite(&carCounter, sizeof(int), 1, ptr);
	}
	fclose(ptr);

}// end save 

void averageCars(CARS cars[], int *carCounter) {
	int avgSales;
	int i;
	for (i = 0; i < SIZE; i++)
	{
		avgSales = (cars[i].price / *carCounter);
	}
	printf("The average car sale is %i", avgSales);
}

void displayData(CARS cars[], int carCounter) {
	CLS;
	int i = 0;
	float averagePrice = 0;
	float totalPrice = 0;

	for (i = 0; i < carCounter; i++) {
		totalPrice += cars[i].price;
	}

	averagePrice = totalPrice / carCounter;

	printf("There are %i car(s)\n", carCounter);
	printf("Average car price: $%.2f\n", averagePrice);
	printf("Price of all cars: $%.2f\n", totalPrice);
	PAUSE;
} //End displayData

void getCar(CARS cars[], int carCounter) {
	getModel(cars, carCounter);
	getMake(cars, carCounter);
	getPrice(cars, carCounter);
	getYear(cars, carCounter);
}

void getModel(CARS cars[], int carCounter) {
	CLS;
	printf("What is the model?\n");
	scanf("%s", cars[carCounter].model); FLUSH;
}

void getMake(CARS cars[], int carCounter) {
	CLS;
	printf("What is the make?\n");
	scanf("%s", cars[carCounter].make); FLUSH;
}


void getYear(CARS cars[], int carCounter) {
	CLS;
	printf("Enter the year of the car: \n");
	scanf("%i", &cars[carCounter].year); FLUSH;
	while (cars[carCounter].year < 1900 || cars[carCounter].year > 2017) {
		CLS;
		printf("Error invalid year\n");
		printf("Enter the year of the car: \n");
		scanf("%i", &cars[carCounter].year); FLUSH;
	}
}

void getPrice(CARS cars[], int carCounter) {
	CLS;
	printf("Enter the price of the car: \n");
	scanf("%f", &cars[carCounter].price); FLUSH;
	while (cars[carCounter].price < 100 || cars[carCounter].price > 50000) {
		CLS;
		printf("Error invalid price\n");
		printf("Enter the price of the car: \n");
		scanf("%f", &cars[carCounter].price); FLUSH;
	}
}

void displayResults(CARS  cars[], int carCounter) {
	CLS;
	int i;
	for (i = 0; i < carCounter; i++) {
		printf("%s , %s \n", cars[i].model, cars[i].make);
		printf("Car Year: %i \n", cars[i].year);
		printf("Car Price: $%.2f \n\n", cars[i].price);
	} // end for
	PAUSE;
} // end displayResults

void myFlush() {
	char nothing;
	while (scanf("%c", &nothing) == NULL);
}