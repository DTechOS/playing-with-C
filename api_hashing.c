#include <stdio.h>
#include <string.h>
// this is really not effective cand casues hash collions very easily

char api[] = "CreateThread";


void hash_from_string(char api[]) 
{
	int len = strlen(api);
    unsigned int hash = 0x35;
	 
	
	for (int i = 0; i < len;i++) 
	{
		hash += (hash * 0xab10f29f + api[i]) & 0xffffff;
	} 
	printf("%s: 0x00%x\n", api, hash);
	
	
}

int main() 
{
	hash_from_string(api);
	
	
}
