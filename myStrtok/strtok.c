#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int my_strspn(const char* s, const char* delim) {
	size_t output = 0;
	for (size_t i = 0; i < strlen(delim); i++) {
		for (size_t j = 0; j < strlen(s); j++) {
			int check = delim[i] == s[j];
			if (check == 1){
				if (j < output) output = j;
				break;
			}
		}	
	}	
	return output;
}

int my_strcspn(const char* s, const char* delim) {
	size_t output = 0;
	for (size_t i = 0; i < strlen(delim); i++) {
		for (size_t j = 0; j < strlen(s); j++) {
			int check = delim[i] != s[j];
			if (check == 1){
				if (j < output) output = j;
				break;
			}
		}
	}
	return output;
}

char *my_strtok(char *s, const char *delims) {
    // static variables maintain their value between
    // calls to the function in which they are declared.
    static char *next_token = NULL;
    
    if(s == NULL) {
        // If the first argument is NULL, we're
        // starting from the last token we found.
        s = next_token;
    }
    
    // strspn finds the num chars until first delim
    // then increment start of s to be at that position
    s += my_strspn(s, delims);
    
    // If we're at the end of the string, we're done
    if(*s == '\0') {
        return NULL;
    }
    
    // strcspn finds the num chars until the next non delim
    // then increment start of s to be after those delims
    next_token = s + my_strcspn(s, delims);
    
    // if it is not at the end of the string
    // then covert the last delim into NULL or end string
    if(*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }
    
    return s;
}

int main() {
	
	// strtok will modify its argument,
	// so we can't use a literal directly.
	char *s = strdup("This is  a strtok   test.");

	const char *delims = " ";

	// The first call needs the string we're
	// tokenizing.
	char *tok_start = strtok(s, delims);

	while(tok_start != NULL) {
    	// strtok will add null bytes to our
    	// original string so that the things
    	// it returns are effectively substrings
    	printf("got a token: \"%s\"\n", tok_start);

    	// Subsequent calls operating on the
    	// same string need to pass NULL for
    	// the first argument.
   		tok_start = strtok(NULL, delims);
	}

	free(s);

	return 0;
}
