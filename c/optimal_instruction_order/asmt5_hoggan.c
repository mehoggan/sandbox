/***************************/
/*	Matthew Hoggan				*/
/*	Comp 222 MW 3:30-4:45pm	*/
/*	Assignment # 5				*/
/***************************/

#include<stdlib.h>

void EnterInstr();
void In_Order();
void Out_Order();

struct node {
	int originstr;
	int destreg;
	int src1reg;
	int src2reg;
	char op;
} *orig_set = NULL, *new_set = NULL, *best_set = NULL;

typedef struct node instr;

int n = 0;				/*number of instructions*/
int total_delay = 0;	/*= n + 4 */;
int *p;					/*Dynamic array of integers*/
int lowest_delay = 0;
int new_delay = 0;

void print_instr_set(instr *set) {
	int looper = 1;
	for(looper = 1; looper <= n; looper++) {
		printf("\t%d) R%d = R%d %c R%d\n", set[looper].originstr, set[looper].destreg, set[looper].src1reg, set[looper].op, set[looper].src2reg);
	}
}

int calc_delay(instr *set) {
	int looper = 0;
	int total_delay = n + 4;
	int prev_delay = 0;
	int delay = 0;
	int loop1 = 2;
	int loop2;
	int loop3;
	for(loop1 = 2; loop1 <=n; loop1++) {
		for(loop2 = loop1 - 2; loop2 <= loop1 - 1 ; loop2++) {
			if(set[loop2].destreg == set[loop1].src1reg || set[loop2].destreg == set[loop1].src2reg) {
				if(loop1 - loop2 == 2) {
					if(prev_delay == 1) {
						delay = 0;
						prev_delay = 0;
					}
					else if(prev_delay == 0){
						delay = 1;
						prev_delay = 1;
					}
				}
				else if(loop1 - loop2 == 1) {
					delay = 2;
					prev_delay = 1;
				}
			}
			else {
				if(prev_delay == 0) {
					delay = 0;
				}
				prev_delay = 0;
			}
		}
		total_delay += delay;
	}
	return total_delay;
}

void find_opt() {
	int looper = 0;
	int looper2 = 0;
	int looper3 = 0;
	int q = 0;
	new_delay = 0;
	/*create new set based on current array p*/
	for(looper = 1; looper <= n; looper++) {
		q = p[looper - 1];
		/*if this does not work, do it for each register new_set[var].detreg ... .src1reg etc.*/
		new_set[looper] = orig_set[q];
	}
	/*rename*/
	for(looper = 1; looper <= n - 1; looper++) {
		for(looper2 = (looper + 1); looper2 <= n; looper2++) {
			/*check if valid permutation if not exit asap*/
			if(new_set[looper2].destreg == new_set[looper].src1reg ||
				new_set[looper2].destreg == new_set[looper].src2reg) {
				if(new_set[looper].originstr > new_set[looper2].originstr) {
					return;
				}
			}
			/*possibly rename some registers avoid unesscary delays*/
			if(new_set[looper].destreg == new_set[looper2].src1reg ||
				new_set[looper].destreg == new_set[looper2].src2reg ||
				new_set[looper].destreg == new_set[looper2].destreg) {
				if(new_set[looper].originstr > new_set[looper2].originstr) {
					for(looper3 = (looper + 1); looper3 <= n; looper3++) {
						if(new_set[looper].originstr < new_set[looper].originstr) {
							if(new_set[looper].destreg == new_set[looper3].destreg) {
								break;
							}
							if(new_set[looper].destreg == new_set[looper3].src1reg) {
								new_set[looper3].src1reg += 10;
							}
							if(new_set[looper].destreg == new_set[looper3].src2reg) {
								new_set[looper3].src2reg += 10;
							}
						}
					}
					new_set[looper].destreg += 10;
				 }
			}
		}
	}
	/*if valid calc delay and compare with lowest delay*/
	new_delay = calc_delay(new_set);
	if(new_delay < lowest_delay) {
		lowest_delay = new_delay;
		for(looper = 1; looper <= n; looper++) {
			best_set[looper] = new_set[looper];
		}
	}
}

void perm(int i) {
	int k, temp;
	if(i > 1) {
		perm(i - 1);
	}
	else {
		find_opt();
	}
	for(k = 0; k < i; k++) {
		if(i & 1) {
			temp = p[i];
			p[i] = p[k];
			p[k] = temp;
		}
		else {
			temp = p[i];
			p[i] = p[0];
			p[0] = temp;
		}
		if(i > 1) {
			perm(i - 1);
		}
		else {
			find_opt();
		}
	}
}

int main() {
	int looper = 0;
	int option = 0;
	int fastest_delay = 0;
	while(option != 4) {
		printf("\nPipedlined insturctions performance\n");
		printf("-------------------------------------\n");
		printf("1) Enter instructions\n");
		printf("2) Calculate in-order performance\n");
		printf("3) Calculate out-of-order performace\n");
		printf("4) Exit\n");
		printf("\nEnter selection: ");
		scanf("%d", &option);
		if(option == 1) {
			EnterInstr();
		}
		else if(option == 2) {
			int total_delay2 = 0;
			/*Caclulate delay*/
			total_delay2 = calc_delay(orig_set);
			printf("\nTotal number of cycles: %d\n", total_delay2);
		}
		else if(option == 3) {
			/*Caclulate best reordered total cycle count*/
			/*Already initialized the best set under option 1*/
			lowest_delay = calc_delay(orig_set);
			perm(n - 1);
			lowest_delay = calc_delay(best_set);
			printf("\nTotal number of cycles: %d\n", lowest_delay);
			printf("Best order:\n");
			print_instr_set(best_set);
		}
		else if(option == 4) {
			if(new_set != NULL) free(new_set);
			if(orig_set != NULL) free(orig_set);
			if(best_set != NULL) free(best_set);
		}
		else {
			printf("Invalid Input\n");
		}
	}
	return(0);
}


/*
struct node {
	int originstr;
	int destreg;
	int src1reg;
	int src2reg;
	char op;
} *orig_set = NULL, *new_set = NULL, *best_set = NULL;
*/

void EnterInstr() {
	int looper = 0;
	char instr_str[8] = " ";
	printf("\nEnter the number of instructions: ");
	scanf("%d", &n);
	orig_set = (instr*)malloc((n + 1) * sizeof(instr));		/*n + 1 used for when you check for*/
	new_set = (instr*)malloc((n + 1) * sizeof(instr));		/*dependencies two insturctions above from 2*/
	best_set = (instr*)malloc((n + 1) * sizeof(instr));
	p = (int*)malloc(n * sizeof(int));
	for(looper = 0; looper <= n-1; looper++) {
		p[looper] = looper + 1;
	}
	printf("\n");
	for(looper = 1; looper <= n; looper++) {
		printf("%d) ", looper);
		scanf("%s", instr_str);
		orig_set[looper].destreg = (instr_str[1] - '0');
		orig_set[looper].src1reg = (instr_str[4] - '0');
		orig_set[looper].src2reg = (instr_str[7] - '0');
		orig_set[looper].op = (instr_str[5]);
		orig_set[looper].originstr = looper;
		best_set[looper] = orig_set[looper];
	}
	orig_set[0].destreg = -1;
	new_set[0].destreg = -1;
}

void In_Order() {
}
