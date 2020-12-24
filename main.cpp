/*****************
16-Queen-Problem.
*****************/

#include <iostream>
#include <math.h>
#include <time.h>

#define maxIteration 500000

using namespace std;

void parentInitialization(int p[][16], int *p_count, int *p_size)
{
	srand(time(NULL)); //using time as seed for rand()
	
	/*number set for parent declaration and initialization*/
    int p_set[*p_size]; 
	for(int i=0; i<(*p_size); i++)
		p_set[i] = i;
	
    for(int l=0; l<(*p_count); l++)
    {
        int j; //random index
        int temp; //temporay variable
        
		/*randomly swapping the number set*/
        for(int i=0; i<(*p_size); i++)
        {
            j = rand()%(*p_size); //random initialization of j index
            temp = p_set[i]; 
            p_set[i] = p_set[j];
            p_set[j] = temp;
        }
        
		/*copying the randomly swapped number set to parents*/
        for(int k=0; k<(*p_size); k++)
        {
            p[l][k] = p_set[k];
        }
    }
}

void printParent(int p[][16], int fitnessArray[], int *i, int *p_size)
{
    cout << "P" << (*i) << ": ";
    for(int j=0; j<(*p_size); j++)
    {
        cout << p[*i][j] << " "; //printing out the parent
    }
    cout << "-> fitness: " << fitnessArray[*i] << endl; //printing out the fitness of the parent
}

void printGeneration(int p[][16], int fitnessArray[], int *p_count, int *p_size)
{
    for(int i=0; i<(*p_count); i++)
    {
        cout << "P" << i << ": ";
        for(int j=0; j<(*p_size); j++)
        {
            cout << p[i][j] << " "; //printing out the parent
        }
        cout << "-> fitness: " << fitnessArray[i] << endl; //printing out the fitness of the parent
    }
    cout << endl;
}

void displayBoard(int p[], int *index, int *p_size)
{
    cout << "Chess Board Configuration: " << endl;
	
	/*initializing the board array*/
    char a[*p_size][*p_size]; 
    for(int i=0; i<(*p_size); i++)
        for(int j=0; j<(*p_size); j++)
            a[i][j] = '-';
			
    /*placing the queens at the optimal positions*/
    for(int i=0; i<(*p_size); i++)
    {
        for(int j=0; j<(*p_size); j++)
        {
            if(p[i]==j)
                a[i][j] = 'Q';
        }
    }
            
	/*displays the chess board*/
    for(int i=0; i<(*p_size); i++)
    {
        for(int j=0; j<(*p_size); j++)
            cout << a[i][j];
        cout << endl;
    }
}

int fitnessFunction(int p[], int *p_size)
{
    int fitness = 0; 
	int temp = 1;
	for(int i=0; i<(*p_size); i++)
	{
		if(i+1<(*p_size))
		{
    		for(int j=i+1; j<(*p_size); j++) //searching downwards
    		{
    			if(p[j]==p[i]) //comparing the elements in the lower rows
    				fitness++;
    			if(p[j]==p[i]+temp&&p[i]<(*p_size)-1) //comparing with diagonal 1
    				fitness++;
    			if(p[j]==p[i]-temp&&p[i]>0) //comparing with diagonal 2
    				fitness++;
    			temp++; //increamenting the temp variable
    		}
		}
		temp = 1; //resetting temp varaible
		if(i-1>=0)
		{
    		for(int j=i-1; j>=0; j--) //searching upwards
    		{
    			if(p[j]==p[i]) //comparing the elements in the lower rows
    				fitness++;
    			if(p[j]==p[i]-temp&&p[i]>0) //comparing with diagonal 1
    				fitness++;
    			if(p[j]==p[i]+temp&&p[i]<(*p_size)-1) //comparing with diagonal 2
    				fitness++;
    			temp++; //increamenting the temp variable
    		}
		}
		temp = 1; //resetting the temp varaible
	}
	
	return fitness; //returns the fitness value
}  

void tournamentSelection(int fitnessArray[], int *p_count, int *index) //3-way tournament selection
{
    int temp1, temp2, temp3;
    int temp;
    
    temp1 = rand()%(*p_count);
    do
    {
        temp2 = rand()%(*p_count);
        temp3 = rand()%(*p_count);
	}while(temp2==temp1||temp3==temp1||temp2==temp3);
    
    temp = fitnessArray[temp1] <= fitnessArray[temp2] ? temp1 : temp2;
    *index = temp <= fitnessArray[temp3] ? temp : temp3;
}

void mutation(int c[], int *p_size, float *Pm) //swap mutation
{
	float p;
	int index;
	int temp;
	for(int i=0; i<(*p_size); i++)
	{
		p = ((float)rand()/(float)(RAND_MAX));
		do
		{
			index = rand()%(*p_size);
		}while(index==i);
		
		if(p<=(*Pm))
		{
			temp = c[i];
			c[i] = c[index];
			c[index] = temp;
		}
	}		
}

void pmx(int a[], int b[], int *p_size, float *Pm)
{
    int l = *p_size;
	int left = rand()%l, right = rand()%l;
	if(left > right){
		int tmp = left; left = right; right = tmp;
	}
	bool done0,done1;
	int c[l], d[l];
	for(int i=0; i<l; i++)
	{
	    c[i] = a[i];
	    d[i] = b[i];
	}
	int tmp;
	for(int i = left;i<=right;i++)
	{
		done0 = done1 = false;
		for(int j = 0; j<l; j++)
		{
			if((done0 = (c[j] == b[i]))) c[j] = c[i]; //Mapping selected region
			if((done1 = (d[j] == a[i]))) d[j] = d[i];
			if(done0 && done1) break;
		}
	}
	for(int i = 0 ; i<l ; i++)
	{
		if((i>=left) && (i<=right)) {
			tmp = a[i];
			a[i] = b[i];
			b[i] = tmp;
		}else{
			a[i] = c[i];
			b[i] = d[i];
		}
	}
	
	mutation(a, p_size, Pm);
	mutation(b, p_size, Pm);
}

void parentSelection(int p[][16], int child[][16], int fitnessArray[], int childrenFitness[], int *p_count, int *p_size)
{
    int parentIndex = 0;
    for(int i=0; i<(*p_count); i++)
    {
        if(fitnessArray[i]<3 || childrenFitness[i]<3) //Checking for elitism
        {
            if(childrenFitness[i]<fitnessArray[i])
            {
                fitnessArray[i] = childrenFitness[i];
                for(int j=0; j<(*p_size); j++) 
                    p[i][j] = child[i][j];
            }
        }
        else
        {
			/*picks the best parent for the next generation*/
            parentIndex = rand()%2;
            if(parentIndex==1)
            {
                if(childrenFitness[i]<fitnessArray[i])
                {
                    fitnessArray[i] = childrenFitness[i];
                    for(int j=0; j<(*p_size); j++)
                    {
                        p[i][j] = child[i][j];
                    }
                }
            }
        }
    }
}

void nextGeneration(int p[][16], int fitnessArray[], int *p_count, int *p_size, float *Pm)
{
	int child[*p_count][16];
	int childrenFitness[*p_count];
	int index;
	int i1=10;
	int i2=8;
	
	/*mating pool creation using tournament selection*/
    for(int i=0; i<(*p_count); i++)
	{
		tournamentSelection(fitnessArray, p_count, &index);
		for(int j=0; j<(*p_size); j++)
		{
			child[i][j] = p[index][j];
		}
	}
	
	for(int i=0; i<(*p_count); i=i+2)
	    pmx(&child[i][0], &child[i+1][0], p_size, Pm);
	    
	/*fitness calculation of parents*/
	for(int i=0; i<(*p_count); i++)
        childrenFitness[i] = fitnessFunction(&child[i][0], p_size);
        
    parentSelection(p, child, fitnessArray, childrenFitness, p_count, p_size);
}

int main()
{
    /*declaration and initialization of variables*/
    
    int p_size = 16; //initialization of phenotype size
    int p_count = 200; //initialization of number of parents in each generation
    int bitSize = 3; //initialization of genotype size
    int iteration = 1; //initialization of number of iteration for the GA
	int fitnessArray[p_count]; //initialization of fitnessArray
	int maxFitness;
	
	/*mutation percentage*/
    float Pm = 1/((float)p_count) + 1/((float)p_size); //mutation percentage = 1/(pop_size) plus 1/(chromosome_len)
	
	cout << "Algorithm details -" << endl;
	cout << "Parent size: " << p_size << endl;
	cout << "Number of parents: " << p_count << endl;
    cout << "Mutation Rate: " << Pm << endl; 
	cout << "Maximum Number of iterations: " << maxIteration << endl << endl;
    
    int p[p_count][16]; //declaration of parents 
    
    parentInitialization(p, &p_count, &p_size); //random initialization of first generation parents
    
    /*fitness calculation of parents*/
		for(int i=0; i<p_count; i++)
		    fitnessArray[i] = fitnessFunction(&p[i][0], &p_size);
		    
    /*displays the initialized generation*/
    cout << "Generation 0 (initialized Parents)" << ": " << endl;
    printGeneration(p, fitnessArray, &p_count, &p_size); //prints the entire generation
    
    
    /*main GA loop*/
    while(iteration<=maxIteration)
    {
		/*fitness calculation of parents*/
		for(int i=0; i<p_count; i++)
		    fitnessArray[i] = fitnessFunction(&p[i][0], &p_size); 
			
		/*creating next generation*/
        nextGeneration(p, fitnessArray, &p_count, &p_size, &Pm);
        
		/*searching for the optimal solution*/
        for(int i=0; i<p_count; i++)
        {
            if(fitnessArray[i]==0)
            {
				cout << endl;
                cout << "Generation Number: " << iteration << endl;
                cout << "Optimal solution is reached!" << endl;
                printParent(p, fitnessArray, &i, &p_size);
                cout << endl;
                displayBoard(&p[i][0], &i, &p_size);
                cout << endl<< "Ending the Program..." << endl; 
                exit(0);
            }
        }
		
		maxFitness = fitnessArray[0];
		for(int i=1; i<p_count; i++)
			maxFitness = maxFitness > fitnessArray[i] ? fitnessArray[i] : maxFitness;
			
		cout << "Generation " << iteration << " max fitness -> " << maxFitness << endl;
        
        iteration++;
    }
    
	return 0;
}