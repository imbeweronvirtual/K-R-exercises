#include <stdio.h>
#include <string.h>
#include <time.h>

int atSign = 0; // variable to store how many at signs we have in email adress, so we need
                // only one sign in e-mail adress, if greater or lower we know that email is invalid

int beginIndex; // varible to store beginning of domain, so we can import only domain in a function

int endIndex; // variable to store end of domain, so it's just easier to import only domain in a function and to read

int emailInQuotes(char const *email) {   // in e-mail adress we're allowing to do spaces, but only if
                                        // email is in the quotes, so we check this by that function

    size_t length = strlen(email); // we need length of the string, so we can check first and last letter     
    
    if (length > 1 && email[0] == '"' && email[length - 1] == '"') // if first and last letters are "
    {                                                               // we return 1(also true in boolean)
        return 1;
    } else                                                          // if not - we return 0(false in boolean)
    {
        return 0;
    }
    

    
}

int checkDomainValidation(char const *email, int beginIndex, int endIndex) { // importing full e-mail and indexes of domain
    int local_lastLetter = -1; // a place to store last character, by default -1 so we don't have
                    //problems with ASCII
    int dotSign = 0; // varible to store dots, so we can check that we have at least one dot in domain
    char local_domain[50]; // variable to store domain with a length of 50, because we don't want to have
                            //problems with buffer overflow and the domain can't be that long
    size_t local_copyLength = endIndex - beginIndex; // we check the length of the domain, so we don't have
                                                    //problems with buffer overflow if domain is longer than 50
    if (local_copyLength >= sizeof(local_domain)) { // if domain is longer than 50, we return 0
        printf("Overflow protection\n");
        return 0;
    }
    strncpy(local_domain, email + beginIndex, endIndex - beginIndex); // now we copy only domain to local_domain without @
                                                                        // sign
    local_domain[endIndex - beginIndex] = '\0'; // manually add null character to the end of the string 
    for (size_t i = 0; local_domain[i] != '\0'; i++) // checking all characters in domain
    {
        if (local_domain[i] == '.' && local_lastLetter == '.') { // if we have two dots in a row, we return 0
            printf("Code finished, domain not valid. Code 6\n");
            return 0;
        }
        if (local_domain[i] != '.' && (local_domain[i] < 97 || local_domain[i] > 122)) // if the character is not a dot
                                                                                       // and not a [a-z] return 0
        {
            printf("Code finished, domain not valid. Code 7\n");
            return 0; 
        }
        if (local_domain[i] == '.') {    // if we have a dot, we count it in dotSign
            dotSign++;
        }
        
        local_lastLetter = local_domain[i]; // we store last letter in local_lastLetter
        
    }

    if (dotSign == 0) { // if it was'n any dots in domain, we return 0
        printf("Code finished, domain not valid. Code 8\n");
        return 0;
    }
    printf("Domain is valid!\n");   // if everything is okay, we return 1
    return 1;
    
}

int checkMainValidation(char const *email, int endIndex) { // we import full e-mail and START index of domain
    //the variables name is endIndex, because it's end of the main, but we import start of the domain(start of the domain
    // is logicaly end of the main without @ sign)
    char local_main[50]; // variable to store main with a length of 50, because we don't want to have
                            //problems with buffer overflow and the main can't be that long
    size_t local_copyLength = endIndex - 1; // we check the length of the main, so we don't have
                                                    //problems with buffer overflow if main is longer than 50, we also
                                                    //subtract 1, because we don't want to have @ sign in main
    if (local_copyLength >= sizeof(local_main)) { // if main is longer than 50, we return 0
        printf("Overflow protection\n");
        return 0;
    }
    strncpy(local_main, email, endIndex - 1); // now we copy only main to local_main without @ sign(we subtract 1, because
                                                // we don't want to have @ sign in main, see explanation above)
    local_main[endIndex - 1] = '\0';
    for (size_t i = 0; local_main[i] != '\0'; i++) // checking all characters in main
    {
        if (local_main[i] == ' ' && emailInQuotes(local_main) == 0) { // we're allowed to have spaces in main, but only if
                                                                    // main is in the quotes, so we check this by emailInQuotes
            printf("Code finished, main not valid. Code 9\n");
            return 0;
        }
        if (local_main[i] != ' ' && (local_main[i] < 33 || local_main[i] > 126)) { // if the character is not a space
                                                                                    // and not a [a-zA-Z0-9\^_=\!#\$%&\(\)\*\+\-\.:'/\?@ ] return 0
            printf("Code finished, main not valid. Code 10\n");
            return 0;
        } 
    }
    printf("Main is valid!\n");
    return 1;
}

int main()
{

    int lastLetter = -1; // a place to store last character, by default -1 so we don't have
    //problems with ASCII
    int currentLetter; // a place to store current character
    const char email[] = "this.the.fourty.nine.signs.e-mail.and.it.is.valid@it.s.the.fourty.nine.signs.domain.and.it.is.valid"; //we're inputing e-mail adress here
    size_t lengthOfEmail = strlen(email); // we need length of the string, so we can check first and last letter
    
    if (email[0] == '.' || email[lengthOfEmail - 1] == '.') { // the first and last letter can't be a dot
        printf("Code finished, email not valid. Code 0\n");
        return 0;
    }
for (size_t i = 0; email[i] != '\0'; i++) // checking all characters in e-mail adress, this is first check to find 
                                        // easiest mistakes
{
    currentLetter = email[i]; // we store current letter in currentLetter
    switch (currentLetter)
    {
    case '@': 
            if (lastLetter == '@' || lastLetter == '.') // so two @ signs in a row or @ sign after dot is not allowed
            {
                printf("Code finished, email not valid. Code 1\n");
                return 0;
            } else if (lastLetter == -1) // if @ sign is first letter, we return 0(if last letter is -1, it means that
                                        // @ sign is first letter)
            {
                printf("Code finished, email not valid. Code 2\n");
            return 0;
            } else { // if everything is okay and we found @ sign, we increment atSign and store last letter
                atSign++;
                lastLetter = currentLetter;
                beginIndex = i + 1;  // we store the beginning of the domain, so we can import only domain or main part 
                                    // of the e-mail adress in a function
                endIndex = lengthOfEmail; // we store the end of the domain, so it's just easier to import only domain
                                        // part in a function
            }
            if (atSign > 1) // if we have more than one @ sign, we return 0
            {
            printf("Code finished, email not valid. Code 3\n");
            return 0;
            }
        lastLetter = currentLetter; // we store last letter
        break;
    case '.': 
        if (lastLetter == '@'){ // if we have a dot after @ sign, we return 0
            printf("Code finished, email not valid. Code 4\n");
            return 0;
        }
        lastLetter = currentLetter;
        break;    
    default:
    lastLetter = currentLetter; // by default we just store last letter
        break;
    }
}

if (atSign == 0) { // if we didn't find @ sign in the string, we return 0
    printf("Code finished, email not valid. Code 5\n");
    return 0;
}



if (checkDomainValidation(email, beginIndex, endIndex) && checkMainValidation(email, beginIndex)) { // if domain
                                                                                                    // and main are valid
                                                                                                    // we return 1
    printf("Email is valid!\n"); 
    return 1;
}
printf("Code finished, email not valid. Code 8\n");
return 0;
}

