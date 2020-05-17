/* CS261- Assignment 1 - Q.3*/
/* Name: Trent Vasquez
 * Date: 7/3
 */

#include <stdio.h>
#include <stdlib.h>



char toUpperCase(char ch){
  /*Convert ch to upper case, assuming it is in lower case currently*/
	return(ch - 32);
}

char toLowerCase(char ch){
  /*Convert ch to lower case, assuming it is in upper case currently*/                          
	return(ch + 32);
}

int stringLength(char s[]) {
   /*Return the length of the string*/
	int i;
	i = 0;
	while(1){
		if(s[i] == '\0'){
			return i;
		}
		i++;
	}
}


void camelCase(char* word){
	/*Convert to camelCase*/
	//remove special characters
	char str[50];

	int underscore, i, j;
	underscore = 1; 
	i = 0;
	j = 0;
	while(word[i] != '\0'){
		if(word[i] > 64 && word[i] < 91){
			str[j] = toLowerCase(word[i]);
			j++;
			i++;
			underscore = 0;
		}else if(word[i] > 96 && word[i] < 123){
			str[j] = word[i];
			i++;
			j++;
			underscore = 0;
		}else if(word[i] == ' '){
			if(underscore == 1){
				i++;
			}else{
				str[j] = '_';
				underscore = 1;
				i++;
				j++;
			}
		}else{
			if(underscore == 1){
				i++;
			}else{
				str[j] = '_';
				underscore = 1;
				i++;
				j++;
			}
		}
	}
	str[j] = '\0';
	if(str[j-1] == '_'){
		str[j-1] = '\0';
	}
	j = 0;
	while(word[j] != '\0'){
		word[j] = str[j];
		j++; 
	}
	j = 0; 

}

int main(){

	/*Read the string from the keyboard*/
	char str[50];
	printf("Input string <50 characters: ");
	fgets(str, 50, stdin);


	
	/*Call camelCase*/
	camelCase(str);
	
	/*Print the new string*/
	printf("%s\n", str);
	
	return 0;
}

/*
    Question Responses:
*/
