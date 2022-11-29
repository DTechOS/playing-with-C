#include <stdio.h>
#include <string.h>
// this is really not effective and causes hash collions very easily, just learning for malware

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

/*
Compiled through godbolt explorer, no options, gcc 

api:
        .string "CreateThread"
.LC0:
        .string "%s: 0x00%x\n"
hash_from_string:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32
        mov     QWORD PTR [rbp-24], rdi
        mov     rax, QWORD PTR [rbp-24]
        mov     rdi, rax
        call    strlen
        mov     DWORD PTR [rbp-12], eax
        mov     DWORD PTR [rbp-4], 53
        mov     DWORD PTR [rbp-8], 0
        jmp     .L2
.L3:
        mov     eax, DWORD PTR [rbp-4]
        imul    edx, eax, -1424952673
        mov     eax, DWORD PTR [rbp-8]
        movsx   rcx, eax
        mov     rax, QWORD PTR [rbp-24]
        add     rax, rcx
        movzx   eax, BYTE PTR [rax]
        movsx   eax, al
        add     eax, edx
        and     eax, 16777215
        mov     edx, eax
        mov     eax, DWORD PTR [rbp-4]
        add     eax, edx
        mov     DWORD PTR [rbp-4], eax
        add     DWORD PTR [rbp-8], 1
.L2:
        mov     eax, DWORD PTR [rbp-8]
        cmp     eax, DWORD PTR [rbp-12]
        jl      .L3
        mov     edx, DWORD PTR [rbp-4]
        mov     rax, QWORD PTR [rbp-24]
        mov     rsi, rax
        mov     edi, OFFSET FLAT:.LC0
        mov     eax, 0
        call    printf
        nop
        leave
        ret
main:
        push    rbp
        mov     rbp, rsp
        mov     edi, OFFSET FLAT:api
        call    hash_from_string
        mov     eax, 0
        pop     rbp
        ret

*/
