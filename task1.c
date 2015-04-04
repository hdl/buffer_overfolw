#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void main(int argc, char **argv)
{
    // Assume you do not know the correct secret. Design the data payload for the input buffer to pass the authentication.
    char buffer[] = "123456xx123456"; // Give your malicious payload.
    FILE *badfile;
     /* Save the content to the file "badfile". */
    badfile = fopen("./badfile", "w");
    fwrite(buffer, 600, 1, badfile);
    fclose(badfile);
}
