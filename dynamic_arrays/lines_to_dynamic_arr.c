#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define more_lines 1024
#define more_chars 1024

int main(void)
{
	FILE *file = fopen("data.txt", "r"); //r = read mode
	
	if(file == NULL)
	{
		printf("Error opening file.\n");
		return 1;	
	}
	
	char **lines; // **lines is a pointer to a pointer to a char
				// points to 1st element in the arr of pointer to chars
				
		    //alloc space to store 1024 pointers to chars.
	lines = malloc(sizeof(char *) * more_lines); 
	
	//keep track of # of lines read and chars currently read
	// c = store each char read in file
	// size_t store large non - ints.
	size_t total_lines = 0;  
	size_t total_chars = 0;
	char c;
	
	// read chars in file
	do
	{
		c = fgetc(file);
		
		if (ferror(file))
		{
			printf("error reading from file\n");
			return 1;
			
		}
		
		
		if (feof(file)) // reached end of file
		{
			if (total_chars != 0)
			{
				lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
				lines[total_lines][total_chars] = '\0';
				
				total_lines++;
			}
			break;
		}		
		
		if (total_chars == 0)   // a char array of size more_chars
			lines[total_lines] = malloc(more_chars);
			lines[total_lines][total_chars] = c;
			total_chars++;
		
		if (c == '\n') 
		{
			// realloc block of memory to amount of chars needed to store string
		  lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
		  lines[total_lines][total_chars] = '\0';
		  
		  total_lines++;
		  total_chars = 0;
		  
		  
		   //reached max size of arr of pointer to chars
		  // increase size of block of memory		  
		  if (total_lines % more_lines == 0) 
		  {
			  // new array length for arr. of pointer to chars
			  size_t new_size = total_lines + more_lines; 
			  lines = realloc(lines, sizeof(char *) * new_size); 
					//new arr size = amount of elements in more_lines
		  }	  
		} 
		else if (total_chars % more_chars == 0) 
		{
			size_t new_size = total_chars + more_chars;
			lines[total_lines] = realloc(lines[total_lines], new_size);	
		}
	
	} while (true);
	
	lines = realloc(lines, sizeof(char *) * total_lines);
	
	for (size_t i = 0;i < total_lines; i++)
		printf("%s", lines[i]);
	
	for (int i = 0; i < total_lines; i++)
		free(lines[i]);
	free(lines);
	
	fclose(file);
	
	
 return 0;
}

/* 

//char lines[100][1000]; //100 lines up to 1000 chars, stored on stack
							// too many unused columns,


=========Dynamically Allocated Arrays=======

	char * array 	
					  each strings is stored in a block of mem.
 					/
	[0] -> ... string
	[1] -> ... string
	[2] -> ... string
	[3] -> ... string

malloc 	 realloc    realloc
  |			|			|
  1024		2048         3072

... chars...chars.......\n
			|
			malloc to allocate space of 1024 chars
			|
			realloc to SHORTEN the block 
			of memory to what is needed
			
			
			


*/