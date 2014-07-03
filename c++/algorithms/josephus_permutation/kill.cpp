#include <iostream>
#include <string>

#define P 2000000
#define S 2
#define I 1

using namespace std;

int people[2][P];
int order[P];
int counted = 0;

bool check_for_death()
{
	bool all_dead = true;
	for(int x = 0; x < P; x++)
	{
		if(people[1][x] == 1)
		{
			all_dead = false;
		}
	}
	return all_dead;	
}

int main(){
	for(int x = 0; x < P; x++)
	{
		people[0][x]=(x+1);
		people[1][x]=(1);
	}

	int count = S;
	
	for(int x = I; x < P; x++)
	{
		//cout << "X is now " << x;
		while(people[1][x] == 0)
		{
			if(x == P - 1)
			{
				x = -1;
			}		
			x++;
			//cout << "\n Person " << x << " IS DEAD " << endl;
		}
		if(people[1][x] != 0)
		{
			//cout << " Person " << (x + 1) << " is still alive" << endl;
			count--;	
		}
		if(count == 0)
		{
			cout << "KILLED PERSON " << (x + 1) << endl;
			count = S;
			people[1][x] = 0;
		}
		if(x == P - 1)
		{
			x = -1;
		}
		if(check_for_death())
		{
			break;
		}
	}
}