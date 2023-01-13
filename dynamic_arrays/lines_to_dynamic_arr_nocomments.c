#include <stdio.h>
#include <stblib.h>
#include <stdbool.h>


#define more_lines 1024
#define more_chars 1024

int main(void)
{
	FILE *file = fopen("data.txt", "r");
	if(file == NULL)
	{
		printf("Error opening file.\n");
		return 1;	
	}
	
	char **lines;
	
	lines = malloc(sizeof(char *) * more_lines); 
	size_t total_lines = 0;  
	size_t total_chars = 0;
	char c;
	
	
	do
	{
		c = fgetc(file);
		
		if (ferror(file))
		{
			printf("error reading from file\n");
			return 1;
		}
		
		if (feof(file)) 
		{
			if (total_chars != 0)
			{
				lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
				lines[total_lines][total_chars] = '\0';
				
				total_lines++;
			}
			break;
		}		
		
		if (total_chars == 0)   
			lines[total_lines] = malloc(more_chars);
			lines[total_lines][total_chars] = c;
			total_chars++;
		
		if (c == '\n') 
		{
			
		  lines[total_lines] = realloc(lines[total_lines], total_chars + 1);
		  lines[total_lines][total_chars] = '\0';
		  
		  total_lines++;
		  total_chars = 0;
		  		  
		  if (total_lines % more_lines == 0) 
		  {
			  size_t new_size = total_lines + more_lines; 
			  lines = realloc(lines, sizeof(char *) * new_size); 			
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
	
	
 return 0
}

