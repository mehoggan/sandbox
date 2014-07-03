/******************/
/* Matthew Hoggan */
/* Comp 222 MW    */
/* Assignment #2  */
/******************/

/*F:\Matthew\CSUN\Fall 2008\Comp 222\Lecture 7 and Assignment 2*/

void DtoIEEE();
void IEEEtoD();

int main() {
	int choice = 0;

	do {
		choice = 0;
		printf("\nFloating-point conversion:\n");
		printf("--------------------------\n");
		printf("1) Decimal to IEEE conversion\n");
		printf("2) IEEE to Decimal Conversion\n");
		printf("3) Exit\n");
		printf("\nEnter selection: ");
		scanf("%d", &choice);
		printf("\n");
		if(choice == 1) DtoIEEE();	
		else if(choice == 2) IEEEtoD();
		else if(choice == 3) ;
	} while(choice != 3);	

	return(0);
}

void DtoIEEE() {
	/*Dont worry about infinity, NAN, denormalized*/
	/*normalize*/
	/*Bias exp*/
	/*Produce mantissa*/
	/*Print out IEEE equivalent*/

	int exp = 0;
	int count = 0;
	float input = 0;
	float mantissa = 0.0;
	float temp_mantissa = 0.0;
	float temp_mantissa2 = 0.0;
	int temp_exp = 0;
	int ieee = 0;
	int sign = 0;
	int array[8];
	int i = 7;

	/*Prompt for decimal number*/
	printf("\nEnter the decimal representation: ");
	scanf("%f", &input);

	/*copy into another variable (var)*/
	mantissa = input;
	
	/*Special case input = 0*/
	if(mantissa == 0) {
		printf("Sign: 0\n");
		printf("Exp:00000000\n");
		printf("Mantisa: 000 0000 0000 0000 0000 0000\n");
		return;
	}
	else {
		/*Produce a sign*/
		if(mantissa > 0) {
			printf("Sign: 0\n");
			sign = 0;
		}
		else {
			printf("Sign: 1\n");
			sign = 1;
		}

		/*Normalize number 1 <= var < 2*/
		/*1. Get absolute value of number*/
		if(mantissa >= 0) {
		}
		else {
			mantissa = mantissa * -1;
		}
		/*2. Actual normalization*/
		temp_mantissa2 = mantissa;
		while(mantissa < 1) {
			mantissa = mantissa*2;
			exp--;
		}
		while(mantissa >= 2.0) {
			/*dividing a base 10 by two will yield the same results if you divide the equivalent by 2*/
			mantissa = mantissa/2.0;
			exp++;
		}
				
		/*Bias exp*/
		printf("Biased exponent: "); 
		if(exp == 0) {
			printf("11111111");
		}
		else {
			exp = exp + 127;
			temp_exp = exp;
			while(exp != 0) {
				array[i--] = exp%2; 
				exp = exp/2;
			}

			for(i = 0; i < 8; i++) {
				if(array[i] != 0 && array[i] != 1) {
						array[i] = 0;
				}
				printf("%d", array[i]);
			}
		}
	
		/*Produce the mantisa*/
		/*take "1" off*/
		temp_mantissa = mantissa - 1.0;
		temp_mantissa2 = mantissa - 1.0;
			
		/*Convert remaining decimal value into binary (mantissa)*/
		printf("\nMantissa: ");
		while(count < 23) {
			temp_mantissa2 = temp_mantissa2 * 2;
			if(temp_mantissa2 >= 1) {	
				printf("1");
				temp_mantissa2 = temp_mantissa2 - 1.0;
			}	
			else {
				printf("0");
			}
			count++;
			if(count == 3 || count == 7 || count == 11 || count == 15 || count == 19) {
				printf(" ");
			}
		}

		/*Print out IEEE*/
		ieee = (sign * 2147483648) + (temp_exp * 8388608) + (temp_mantissa * 8388608);
		printf("\nIEEE HEX: %8x\n", ieee);
	}
}

void IEEEtoD() {
	/*Produce sign*/
	/*Extract*/
	/*Unbias exp*/
	/*Unnormalize*/
	/*Print out decimal equivilant*/
	
	int count = 1;
	int ieee = 0;
	int var = 0;
	int exp = 0;
	double mant = 0.0;
	int sign = 0;
	double dec = 0.0;
	double mult = 0.0;
	double base2exp = 1.0;

	/*Prompt for IEEE number int ieee = 0000000F realy equals 15*/
	printf("Enter the IEEE-754 representation: ");
	scanf("%x", &ieee);
	var = ieee;

	/*Check for + or - 0*/
	if(var == 0) {
		printf("Sign: + \nunbiased exponent:0 \nspecial case: +0\n");
		return;
	}
	if(var == 0x80000000) {
		printf("sign: - \nunbiased exponent:0 \nspecial case: -0\n");
		return;
	}
	/*Check for + or - infinity*/
	if(var == 0x7F800000) {
		/*special case +infinity*/
		printf("Sign: + \nunbiased exponent: 128 \nspecial case: +infinity\n");
		return;
	}
	else if(var == 0xFF800000) {
		/*special case -infinity*/
		printf("Sign: - \nunbiased exponent: 128 \nspecial case: -infinity\n");
		return;
	}
	/*check for normalized*/
	else {
		/*sign = &first bit with one and & the rest with 0*/
		sign = (var & 0x80000000)/2147483648; /*divide by 2^31*/
		if(sign == 1) {
			mult = -1.0;
			printf("Sign=-\n");	
		}
		else {
			mult = 1.0;
			printf("Sign=+\n");	
		}
		/*Next mask exponent bits with 7f800000 to get exponent*/
		exp = (var & 0x7f800000)/8388608; /*divide by 2^23*/
		exp -= 127;
		printf("Unbiased exponent: %d\n", exp);
		/*Next mask mantisa with 007fffff to get mantisa value*/
		mant = (ieee & 0x007fffff)/8388608.0;/*divide by 2^23*/
		mant += 1.0;
		printf("Normalized decimal: %lf\n", mant);
		while(exp > 0) {
			base2exp = base2exp * 2.0;
			printf("base2exp is now %lf\n", base2exp);
			exp--;
		}
		while(exp < 0) {
			base2exp = base2exp / 2.0;
			printf("%d. base2exp is now %lf\n", count++, base2exp);
			exp++;
		}
		printf("Multiplying %lf by %lf by %lf\n", mult, mant, base2exp);
		dec = mult * mant * base2exp;
		printf("Decimal: %lf\n\n", dec);
	}
	/*check for denormalized (DONT WORRY ABOUT IT)*/
	/*NaN an number greater than infinity and -infinity (DONT WORRY ABOUT IT)*/
}


























