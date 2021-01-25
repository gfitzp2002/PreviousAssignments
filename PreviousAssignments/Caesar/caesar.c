#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int k;
    //Check to see if array holds one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    //Validate key ensuring all characters decimal digits
    for (int i = 0, n = strlen(argv[1]); i < n;)
    {
        if (isdigit(argv[1][i]))
        {
            i++;
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    //Place key in variable
    k = atoi(argv[1]);
    
    //ask user for plain text input
    string s = get_string("plaintext: ");
    
    //Print output after key is applied.
    printf("ciphertext: ");
    
    //Convert plain text to cipher text using user provided key
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //if character is upper case
        if (islower(s[i]))
        {
            printf("%c", (((s[i] + k) - 97) % 26) + 97);
        }
        //if character is lower case 
        else if (isupper(s[i]))
        {
            printf("%c", (((s[i] + k) - 65) % 26) + 65);
        }
        //if character is neither upper case or lower case
        else
        {
            printf("%c", s[i]);
        }
    }
    //Insert new line after cipher text is printed and end program
    printf("\n");
    return 0;
}
