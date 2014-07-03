/******************/
/* Matthew Hoggan */
/* Comp 222 MW    */
/* Assignment #1  */
/******************/

int main() {
	int menu_Selection = 0;
	int number_of_Enhancements = 0;
	float percent_Enhanced = 0;
	float total_percent_Enhanced = 0;
	int speedup_Factor = 0;
	float sum_percen_Enhance_dividedBy_TotalSpeedUpFactor = 0.0;
	float speed_Up = 0; 
	int loop_Counter = 0;
		
	do {
		menu_Selection = 0;
		number_of_Enhancements = 0;
		percent_Enhanced = 0;
		total_percent_Enhanced = 0;
		speedup_Factor = 0;
		sum_percen_Enhance_dividedBy_TotalSpeedUpFactor = 0.0;
		speed_Up = 0; 
		loop_Counter = 0;
		
		printf("Speedup:\n");
		printf("---------\n");
		printf("1) Calculate speed up for one enhancement\n");
		printf("2) Calculate speedup for multiple enhancements \n");
		printf("3) Quit \n\n");
		printf("Enter selection:> ");
		scanf("%d", &menu_Selection);
	
		if(menu_Selection == 1) {
			printf("Enter percent of enhanced code (as fractional number):> ");
			scanf("%f", &percent_Enhanced);
			printf("Enter speedup factor for enhanced code %d:> ", loop_Counter);
			scanf("%f", &speedup_Factor);
			speed_Up = speed_Up + 1/((1 - percent_Enhanced) + (percent_Enhanced/speedup_Factor));
			printf("The total speedup is: %.2f\n", speed_Up);
		}
		else if(menu_Selection == 2) {
			printf("Enter number of enhancements:> ");
			scanf("%d", &number_of_Enhancements);
			for(loop_Counter = 1; loop_Counter <= number_of_Enhancements; loop_Counter++) {
				printf("Enter percent of enhancement %d (as a fractional number):> ", loop_Counter);
				scanf("%f", &percent_Enhanced);
				total_percent_Enhanced = total_percent_Enhanced + percent_Enhanced;
				printf("Enter speedup factor for enhanced code %d:> ", loop_Counter);
				scanf("%d", &speedup_Factor);
				sum_percen_Enhance_dividedBy_TotalSpeedUpFactor = sum_percen_Enhance_dividedBy_TotalSpeedUpFactor + (percent_Enhanced/speedup_Factor);
			}	
			speed_Up = 1/((1 - total_percent_Enhanced)+(sum_percen_Enhance_dividedBy_TotalSpeedUpFactor));
			printf("The total speedup is: %.2f\n", speed_Up);
		}
		else if(menu_Selection == 3) {
		}
		else {
			printf("You entered %d", menu_Selection);
			printf(" the only valid input is 1, 2, or 3\n");
			printf("Quiting the application");
			menu_Selection = 3;
		}
	} while(menu_Selection != 3);
	printf("Goodbye\n\n");
	return 0;
}























































