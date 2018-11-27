#include "contact.h"

//Peter Wilson; this project creates a contact database.


/////////////////////////////////////////////////////////////////////////////////////////////
// add a new contact to your list of contacts
//	   1. Make sure a contact by that name does not exist (print an error message and exit if it exists)
//	   2. Add a new contact with that name (add-at-front)
Contact* addContact(Contact *myContacts, char *contactName) {

	Contact *temp = myContacts;
	if (temp != NULL){
		while( temp != NULL ){
			if (strcmp( temp -> name , contactName) == 0){
				printf("\n\tERROR DUPLICATE CONTACT NAMES\n");
				return myContacts;
			}
			temp = temp -> next;
		}
	}

	Contact *newContact;
	newContact = malloc( sizeof(Contact) );
	newContact->name = malloc( sizeof(char)* strlen(contactName) + 1 );
	strcpy(newContact -> name, contactName);
	newContact -> information = NULL;
	newContact -> next = myContacts;

	return newContact;

}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new piece of inforamtion to the specified contact
//   1. Make sure a contact by that name exists (so you can add information to it)
//   2. If the informational item already exists, update the information's value to the new value
//   3. Otherwise, add the piece of information to the end of the contact's information list (add-at-end)

void addInformation(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {

	while ( myContacts != NULL){
	if (strcmp(myContacts -> name, contactName) == 0){
		Info * newTerm = malloc(sizeof ( Info));
		newTerm -> name = malloc (sizeof(char)* strlen(infoName)+ 1 );
		newTerm -> value = malloc (sizeof(char)* strlen(infoValue)+ 1 );
		strcpy(newTerm -> name, infoName);
		strcpy(newTerm -> value, infoValue);
		newTerm -> next = NULL;
		if (myContacts -> information == NULL){
			myContacts -> information = newTerm;
			return;
		}
		Info * hold = myContacts -> information;
		while(hold -> next != NULL){
			if ( strcmp( hold -> name, infoName) == 0){
				strcpy( hold -> value , infoValue);
				return;
			}
			hold = hold -> next;
		}
		hold -> next = newTerm;
		return;
	}
	myContacts = myContacts -> next;
}
return;

}


/////////////////////////////////////////////////////////////////////////////////////////////
// prints all the information for a given contact
//	1. Make sure a contact with that name exists
//	2. Print the name of the contact
//	3. print all the informational items <name|value> associated with that contact
void printContact(Contact *myContacts, char *contactName) {
	while ( myContacts != NULL){
		if (strcmp(myContacts -> name, contactName)==0){
			printf("%s\n", myContacts -> name);
			Info *temp;
			temp = myContacts -> information;
			while ( temp != NULL){
				printf("\t< %s | %s >\n", temp -> name, temp -> value);
				temp = temp -> next;
			}

		}
			myContacts = myContacts -> next;

	}

	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// returns the size of a given contact list
//	Iterate through the contact list to count the number of contacts, return that count
int count(Contact *myContacts) {
	int x = 0;
	while (myContacts != NULL){
		x = x + 1;
		myContacts = myContacts -> next;
	}
	return x;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// prints all your contacts
//	For each contact
//	   a.  Print the name of the contact
//	   b.  Print all the <information name|information value> pairs in that contact
//	Note: this code can call other functions as needed
void print(Contact *myContacts) {
	while ( myContacts != NULL){
		printf("%s\n", myContacts -> name);
		Info *temp;
		temp = myContacts -> information;
		while ( temp != NULL){
			printf("< %s | %s >\n", temp -> name, temp -> value);
			temp = temp -> next;
		}
		myContacts = myContacts -> next;
	}
	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// add a new contact (in alphabetical order)
//	1. Make sure a contact by that name does not exist
//	2. Add a new contact with that name (add-in-order)
Contact *addContactOrdered(Contact *myContacts, char *contactName) {
	Contact * holder = myContacts;
		while( holder != NULL ){
			if (strcmp( holder -> name , contactName) == 0){
				printf("\n\tERROR DUPLICATE CONTACT NAMES\n");
				return myContacts;
			}
			holder = holder -> next;
		}

	//allocate new node
	Contact *newContact = malloc( sizeof (Contact)) ;
	newContact -> name = malloc (sizeof(char)* strlen(contactName)+ 1 );
	strcpy(newContact -> name , contactName);
	newContact -> information = NULL;
	newContact -> next = NULL;

	//special case
	if ( myContacts == NULL){
		return newContact;
	}
	//special case 2
	if ( strcmp( contactName, myContacts -> name) < 0){
		newContact -> next = myContacts;
		return newContact;
	}

	//regular algorithm
	Contact * prev = myContacts;
	Contact * curr = myContacts -> next;
	while ( curr && strcmp( curr -> name, contactName) < 0){
		prev = curr;
		curr = curr -> next;
	}
	prev -> next = newContact;
	newContact -> next = curr;
	return myContacts;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// adds a new info to the specified contact (in alphabetical order)
//	1. Make sure a contact by that name exists (so you can add an info to it)
//	2. If the informational item already exists, update the item (replace its value with the new value)
//	3. Otherwise, add the new info to the contact (add-in-order)
void addInformationOrdered(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {

	while ( myContacts != NULL){
	if (strcmp(myContacts -> name, contactName) == 0){
		Info * newTerm = malloc(sizeof ( Info));
		newTerm -> name = malloc (sizeof(char)* strlen(infoName)+ 1 );
		newTerm -> value = malloc (sizeof(char)* strlen(infoValue)+ 1 );
		strcpy(newTerm -> name, infoName);
		strcpy(newTerm -> value, infoValue);
		newTerm -> next = NULL;
		if (myContacts -> information == NULL){
			myContacts -> information = newTerm;
			return;
		}
		Info * hold = myContacts -> information;
		if ( strcmp(infoName, hold -> name) < 0){
			hold -> next = myContacts -> information;
			return;
		}
		Info * prev = hold;
		Info * curr = hold -> next;
		while ( curr && strcmp(curr -> name, infoName) < 0 ){
			prev = curr;
			curr = curr -> next;
		}
	prev -> next = newTerm;
	newTerm -> next = curr;
	return;

}

myContacts = myContacts -> next;
}


	return;
}


/////////////////////////////////////////////////////////////////////////////////////////////
// remove information from a contact
//	1. Make sure a contact with that name exists
//	2. Make sure the informational item exists in that contact
//	3. Remove that piece of information from the contact
void removeInformation(Contact *myContacts, char *contactName, char *infoName) {
	//special case; Empty list
	if (myContacts == NULL){
		return;
	}

	//normal cases

	if(strcmp(myContacts -> name, contactName) == 0){
		Info * temp = myContacts -> information;
			if( strcmp( temp -> name, infoName) == 0){
				free(temp);
				return;
			}
			//creating temporary holders
			Info *last = temp;
			Info *current = temp -> next;
			while (strcmp(current -> name, infoName) != 0){
				last = current;
				current = current -> next;
			}
			if ( current == NULL){
				return;
			}
			last -> next = current -> next;
			free(current);
			return;
	}


	Contact * last = malloc(sizeof(Contact));
	last = myContacts;

	Contact * current = myContacts -> next;

	while (strcmp(current -> name, contactName) != 0){
		last = current;
		current = current -> next;
	}
	if (current == NULL){return;}
	Info * holder = current -> information;
	Info * laster = holder;
	Info * curt = holder -> next;
	while ( strcmp( curt -> name, infoName) != 0){
		laster = curt;
		curt = curt -> next;
	}
	if (curt == NULL){
		return;
	}
	laster-> next = curt -> next;
	free (curt);
	return;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// remove a contact (and all the informational items for that contact)
//	1. Make sure a contact with that name exists
//	2. Remove that contact
Contact *removeContact(Contact *myContacts, char *contactName) {
	if ( myContacts == NULL){
		return myContacts;
	}
	if ( strcmp( myContacts -> name, contactName) == 0){
		Contact *temp = myContacts -> next;
		free(myContacts);
		return temp;
	}
	Contact *prev = myContacts;
	Contact *current = myContacts -> next;
	while (strcmp( current -> name, contactName) != 0){
		prev = current;
		current = current -> next;
	}
	if ( current == NULL) return myContacts;

	prev -> next = current -> next;
	free(current);

	return myContacts;


}
