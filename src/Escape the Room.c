/*
 ============================================================================
 Name        : Escape.c
 Author      : Andrew Parise
 Version     : 0.1
 Copyright   : 
 Description : Escape the Room text based game
 ============================================================================
 */

//imports
#include <stdio.h>
#include <stdlib.h>

//method declarations
void askEnterQuestion(void);
int enterenceRiddle(void);
void investigate(void);
int gameController(void);
void askEnterQuestion(void);
void rotateLeft(void);
void rotateRight(void);
char canMove(int spaceNo);
void moveForward(void);
int getUserInput(void);

//global vars
int curSpace = 36;
char curDirection = 'W';
char runGame = 'Y';

//Continuity vars
char isOpen51 = '0';
char isOpen62 = '0';
char isOpen13 = '0';
char isOpen14 = '0';
char isOpen64 = '0';


///Player inventory
char hasKey = '0';
char hasVase = '0';
char hasVaseWater = '0';
char hasSymbol = '0';
char hasVaseLid = '0';
char hasJug = '0';
char hasJugWater = '0';
char hasCrowbar = '0';


int main(void) {
	printf("You are an adventurer, far from home. \nYou are deep in a strange forest, weary from your travels.\n");
	printf("Up ahead you see a cottage with what appears to be a fire going inside.\n");
	getchar();
	char doApproach = ' ';
	while((doApproach != 'Y') || (doApproach != 'N')){
		printf("Approach the house? (Y/N): ");
		scanf("%s", &doApproach);
		if(doApproach == 'Y'){
			printf("You approach the front door of the house.\n");
			getchar();
			printf("The door is locked, with no visible handle.\n");
			getchar();
			printf("Looking around, you notice a sign that is covered with dirt beside the door.");
			getchar();
			askEnterQuestion();
			gameController();
			return EXIT_SUCCESS;
		}else if(doApproach == 'N'){
			printf("You walk past the house and continue on your journey. \n Maybe next time the player would be more adventurous...");
			return EXIT_SUCCESS;
		}
	}


	return EXIT_SUCCESS;
}

int gameController(void){
	//main thread that controls the game

	while(runGame == 'Y'){
		int selection = getUserInput();
		if(selection == 1){
			//investigate
			//printf("debug- investigate calling-");
			investigate();
		}else if(selection == 2){
			//Walk Forward
			moveForward();
		}else if(selection == 3){
			//turn right
			rotateRight();
		}else if(selection == 4){
			//turn left
			rotateLeft();
		}
	}
	return 0;

}

void rotateLeft(void){
	//rotates the player to the left
	if(curDirection == 'N'){
		curDirection = 'W';
	}else if(curDirection == 'W'){
		curDirection = 'S';
	}else if(curDirection == 'E'){
		curDirection = 'N';
	}else if(curDirection == 'S'){
		curDirection = 'E';
	}
}

void rotateRight(void){
	//rotates the player to the right
	if(curDirection == 'N'){
		curDirection = 'E';
		printf("You look to the right (You are now facing East).");
		getchar();
	}else if(curDirection == 'W'){
		curDirection = 'N';
		printf("You look to the right (You are now facing North).");
		getchar();
	}else if(curDirection == 'E'){
		curDirection = 'S';
		printf("You look to the right (You are now facing South).");
		getchar();
	}else if(curDirection == 'S'){
		curDirection = 'W';
		printf("You look to the right (You are now facing West).");
		getchar();
	}
}

char canMove(int spaceNo){
	//checks to see if a game object is in the way of where the player wishes to move
	//prints out a message if there is a collision
	//return "1" if you can move; "0" if you can't
	if(spaceNo == 66 || spaceNo == 56){
		printf("There is a stove in the way. Movement failed.");
		getchar();
		return '0';
	}else if(spaceNo == 64){
		printf("There is a chest in the way. Movement failed.");
		getchar();
		return '0';
	}else if(spaceNo == 46){
		printf("There is a sink in the way. Movement failed.");
		getchar();
		return '0';
	}else if(spaceNo == 62 || spaceNo == 61 || spaceNo == 51 || spaceNo == 13 || spaceNo == 14){
		printf("There is a box in the way. Movement failed.");
		getchar();
		return '0';
	}else if(spaceNo == 43 || spaceNo == 44){
		printf("There is a table in the way. Movement failed.");
		getchar();
		return '0';
	}else if(spaceNo == 11 || spaceNo == 12){
		printf("There is a bookshelf in the way. Movement failed.");
		getchar();
		return '0';
	}else if(spaceNo == 16){
		printf("There is a frozen table in the way. Movement failed.");
		getchar();
		return '0';
	}else if((spaceNo > 66 || spaceNo < 11) || (spaceNo > 16 && spaceNo < 21) || (spaceNo > 26 && spaceNo < 31)|| (spaceNo > 36 && spaceNo < 41)|| (spaceNo > 46 && spaceNo < 51)|| (spaceNo > 56 && spaceNo < 61)){
		printf("There is a wall in the way. Movement failed.");
		getchar();
		return '0';
	}
	return '1';
}

void moveForward(void){
	//moves the player forward
	if(curDirection == 'N'){
		//is a valid move
		if(canMove(curSpace - 10) == '1'){
			curSpace = curSpace - 10;
			printf("You walk forward.");
			getchar();
			return;
		}


	}else if(curDirection == 'E'){
		int anticipatedMove = curSpace + 1;
		char canUserMove = canMove(anticipatedMove);
		if(canUserMove == '1'){
			curSpace = curSpace + 1;
			printf("You walk forward.");
			getchar();
			return;
		}
	}else if(curDirection == 'W'){
		int anticipatedMove = curSpace - 1;
		char canUserMove = canMove(anticipatedMove);
		if(canUserMove == '1'){
			curSpace = curSpace - 1;
			printf("You walk forward.");
			getchar();
			return;
		}

	}else if(curDirection == 'S'){
		if(canMove(curSpace + 10) == '1'){
			curSpace = curSpace - 1;
			printf("You walk forward.");
			getchar();
			return;
		}
	}else{
		//if this path is reached then something got messed up with the direction, so set it to West and hope the player doesnt notice
		curDirection = 'E';
		return;
	}
}

void investigate(void){
	//investigate what is in front of the user
	int floorSpaceNo = curSpace;
	char direction = curDirection;
	if(floorSpaceNo == 36){
		if(direction == 'E'){
			if(hasKey == '1'){
				//if the player has the key to the door
				printf("The door is in front of you. You use the key on the lock and the door swings open.\n");
				getchar();
				printf("Congratulations, you have solved the puzzle!");
				runGame = 'N';
				return;

			}else{
				printf("The door is in front of you, but there isn't any handle to open it with. \nOnly a key hole is visible.");
				getchar();
				return;
			}

		}else if(direction == 'S'){
			printf("There is a sink in front of you.");
			getchar();
			if(hasVaseWater == '1'){
				printf("There is nothing of value on it.\n");
				getchar();
				return;
			}else if(hasVase == '1'){
				if(hasVaseLid == '1' && hasVaseWater == '0'){
					printf("You fill the vase up with water.\n");
					printf("You put the vase lid on the vase.\n");
					hasVaseWater = '1';
					getchar();
					return;
				}
			}else{
				if(hasJug == '1' && hasJugWater == '0'){
					printf("You fill the jug up with water.\n");
					hasJugWater = '1';
					getchar();
					return;
				}
			}
		}
	}else if(floorSpaceNo == 21 || floorSpaceNo == 22){
		if(direction == 'N'){
			printf("You search the bookshelf, but find nothing of value.");
			getchar();
			return;
		}
	}else if(floorSpaceNo == 31){
		if(direction == 'W'){
			printf("A mysterious painting is on the wall.\n");
			if(hasSymbol == '1'){
				if(hasVaseLid == '1'){
					printf("The opening where the painting was remains open.");
					getchar();
					return;
				}else{
					printf("You place the symbol into the opening.\n");
					printf("The painting swings open to reveal a secret compartment! \n");
					getchar();
					printf("A lid to a vase lies inside. You pick it up.\n");
					hasVaseLid = '1';
					getchar();
					return;
				}

			}else{
				printf("You note that there is an opening beside the painting in the \n shape of a peculiar symbol.\n");
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 41){
		if(direction == 'S'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen51 == '1'){
					printf("The crate is open and empty.");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen51 = '1';
					getchar();
					printf("The crate is empty!\n");
					getchar();
					return;
				}

			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 52){
		if(direction == 'W'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen51 == '1'){
					printf("The crate is open and empty.");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen51 = '1';
					getchar();
					printf("The crate is empty!\n");
					getchar();
					return;
				}

			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}else if(direction == 'S'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen62 == '1'){
					printf("The crate is open and empty");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen62 = '1';
					getchar();
					printf("The crate has a jug in it!\n");
					printf("You pick up the jug.\n");
					hasJug = '1';
					getchar();
					return;
				}
			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 63){
		if(direction == 'W'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen62 == '1'){
					printf("The crate is open and empty");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen62 = '1';
					getchar();
					printf("The crate has a jug in it!\n");
					printf("You pick up the jug.\n");
					hasJug = '1';
					getchar();
					return;
				}
			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}else if(direction == 'E'){
			printf("There is a chest in front of you.\n");
			if(isOpen64 == '1'){
				printf("The chest is open and empty.\n");
				getchar();
				return;
			}else{
				if(hasJugWater == '1'){
					printf("You place the jug of water on the scale.\n");
					getchar();
					printf("*click*\n");
					printf("[the chest swings open]\n");
					isOpen64 = '1';
					getchar();
					printf("You find a vase inside.\n");
					printf("As you pick it up, you notice something inside.\n");
					printf("If I could just find a way of getting this object out!\n");
					hasVase = '1';
					getchar();
					return;
				}else{
					if(hasJug == '1'){
						printf("You place the jug on the scale.\n");
						getchar();
						printf("Nothing appears to happen. Maybe it needs to weigh more?\n");
						getchar();
						return;
					}else{
						printf("You notice a scale beside the chest. \nI should find something to put on it!\n");
						getchar();
						return;
					}
				}
			}
		}
	}else if(floorSpaceNo == 54){
		if(direction == 'S'){
			printf("There is a chest in front of you.\n");
			if(isOpen64 == '1'){
				printf("The chest is open and empty.\n");
				getchar();
				return;
			}else{
				if(hasJugWater == '1'){
					printf("You place the jug of water on the scale.\n");
					getchar();
					printf("*click*\n");
					printf("[the chest swings open]\n");
					isOpen64 = '1';
					getchar();
					printf("You find a vase inside.\n");
					printf("As you pick it up, you notice something inside.\n");
					printf("If I could just find a way of getting this object out!\n");
					hasVase = '1';
					getchar();
					return;
				}else{
					if(hasJug == '1'){
						printf("You place the jug on the scale.\n");
						getchar();
						printf("Nothing appears to happen. Maybe it needs to weigh more?\n");
						getchar();
						return;
					}else{
						printf("You notice a scale beside the chest. \nI should find something to put on it!\n");
						getchar();
						return;
					}
				}
			}
		}else if(direction == 'N'){
			printf("There is a table in front of you.\n");
			if(hasCrowbar == '1'){
				printf("There is nothing of value on the table.\n");
				getchar();
				return;
			}else{
				printf("There is a crowbar on the table!\n");
				printf("You pick it up!\n");
				printf("This might be useful for opening crates.\n");
				hasCrowbar = '1';
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == '65'){
		if(direction == 'W'){
			printf("There is a chest in front of you.\n");
			if(isOpen64 == '1'){
				printf("The chest is open and empty.\n");
				getchar();
				return;
			}else{
				if(hasJugWater == '1'){
					printf("You place the jug of water on the scale.\n");
					getchar();
					printf("*click*\n");
					printf("[the chest swings open]\n");
					getchar();
					printf("You find a vase inside.\n");
					printf("As you pick it up, you notice something inside.\n");
					printf("If I could just find a way of getting this object out!\n");
					hasVase = '1';
					getchar();
					return;
				}else{
					if(hasJug == '1'){
						printf("You place the jug on the scale.\n");
						getchar();
						printf("Nothing appears to happen. Maybe it needs to weigh more?\n");
						getchar();
						return;
					}else{
						printf("You notice a scale beside the chest. \nI should find something to put on it!\n");
						getchar();
						return;
					}
				}
			}
		}else if(direction == 'E'){
			printf("There is a stove in front of you.");
			getchar();
			printf("There is nothing of value on it.\n");
			getchar();
			return;
		}


	}else if(floorSpaceNo == 45){
		if(direction == 'W'){
			printf("There is a table in front of you.\n");
			if(hasCrowbar == '1'){
				printf("There is nothing of value on the table.\n");
				getchar();
				return;
			}else{
				printf("There is a crowbar on the table!\n");
				printf("You pick it up!\n");
				printf("This might be useful for opening crates.\n");
				hasCrowbar = '1';
				getchar();
				return;
			}
		}else if(direction == 'E'){
			printf("There is a sink in front of you.");
			getchar();
			if(hasVaseWater == '1'){
				printf("There is nothing of value on it.\n");
				getchar();
				return;
			}else if(hasVase == '1'){
				if(hasVaseLid == '1' && hasVaseWater == '0'){
					printf("You fill the vase up with water.\n");
					printf("You put the vase lid on the vase.\n");
					hasVaseWater = '1';
					getchar();
					return;
				}
			}else{
				if(hasJug == '1' && hasJugWater == '0'){
					printf("You fill the jug up with water.\n");
					hasJugWater = '1';
					getchar();
					return;
				}
			}

		}

	}else if(floorSpaceNo == 34){
		if(direction == 'S'){
			printf("There is a table in front of you.\n");
			if(hasCrowbar == '1'){
				printf("There is nothing of value on the table.\n");
				getchar();
				return;
			}else{
				printf("There is a crowbar on the table!\n");
				printf("You pick it up!\n");
				printf("This might be useful for opening crates.\n");
				hasCrowbar = '1';
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 55){
		if(direction == 'E'){
			printf("There is a stove in front of you.");
			getchar();
			printf("There is nothing of value on it.\n");
			getchar();
			return;
		}
	}else if(floorSpaceNo == 24){
		if(direction == 'N'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen14 == '1'){
					printf("The crate is open and empty.");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen14 = '1';
					getchar();
					printf("The crate contains a strangely shaped wooden symbol!\n");
					getchar();
					printf("You take it with you.\n");
					hasSymbol = '1';
					return;
				}

			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 15){
		if(direction == 'W'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen14 == '1'){
					printf("The crate is open and empty.");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen14 = '1';
					getchar();
					printf("The crate contains a strangely shaped wooden symbol!\n");
					getchar();
					printf("You take it with you.\n");
					hasSymbol = '1';
					return;
				}

			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}else if(direction == 'E'){
			printf("There is a frozen table in front of you.\n");
			if(hasKey == '1'){
				printf("There is nothing of value on the frozen table.\n");
				getchar();
				return;
			}else{
				if(hasVaseWater == '1'){
					printf("You place the vase on the table and begin to wait...\n");
					getchar();
					printf("...");
					getchar();
					printf("......");
					getchar();
					printf(".........");
					printf("[the vase shatters and a shiny key is left in the shards]\n");
					printf("Maybe this key will unlock the door!\n");
					printf("You pick up the key!");
					hasKey = '1';
					getchar();
					return;
				}else{
					printf("[the temperature drops significantly as you approach the table.]\n");
					printf("Perhaps this would be useful for freezing something?");
					getchar();
					return;
				}
			}
		}
	}else if(floorSpaceNo == 26){
		printf("There is a frozen table in front of you.\n");
		if(hasKey == '1'){
			printf("There is nothing of value on the frozen table.\n");
			getchar();
			return;
		}else{
			if(hasVaseWater == '1'){
				printf("You place the vase on the table and begin to wait...\n");
				getchar();
				printf("...");
				getchar();
				printf("......");
				getchar();
				printf(".........");
				printf("[the vase shatters and a shiny key is left in the shards]\n");
				printf("Maybe this key will unlock the door!\n");
				printf("You pick up the key!");
				hasKey = '1';
				getchar();
				return;
			}else{
				printf("[the temperature drops significantly as you approach the table.]\n");
				printf("Perhaps this would be useful for freezing something?");
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 23){
		if(direction == 'N'){
			printf("There is a crate in front of you.\n");
			if(hasCrowbar == '1'){
				if(isOpen13 == '1'){
					printf("The crate is open and empty.");
					getchar();
					return;
				}else{
					printf("You use the crowbar to pry open the crate.\n");
					isOpen13 = '1';
					getchar();
					printf("The crate is empty!\n");
					getchar();
					return;
				}

			}else{
				printf("If you had a way of opening this, there may be something useful inside.\n");
				getchar();
				return;
			}
		}
	}else if(floorSpaceNo == 33){
		if(direction == 'S'){
			printf("There is a table in front of you.\n");
			getchar();
			printf("There is nothing of value on the table.\n");
			getchar();
			return;
		}
	}else if(floorSpaceNo == 42){
		if(direction == 'E'){
			printf("There is a table in front of you.\n");
			getchar();
			printf("There is nothing of value on the table.\n");
			getchar();
			return;
		}
	}else if(floorSpaceNo == 53){
		if(direction == 'N'){
			printf("There is a table in front of you.\n");
			getchar();
			printf("There is nothing of value on the table.\n");
			getchar();
			return;
		}
	}

	puts("There is nothing to investigate.");
	return;
}


int getUserInput(void){
	//prompts the user to make a decision - called each turn
	char userInput = ' ';
	printf("What would you like to do?\n");
	printf("(1) - Investigate\n");
	printf("(2) - Walk Forward\n");
	printf("(3) - Turn to the Right\n");
	printf("(4) - Turn to the Left\n");
	printf("> ");
	scanf("%c", &userInput);
	//printf("error: user entered %c", userInput);
	if(userInput == '1'){
		return 1;
	}else if(userInput == '2'){
		return 2;
	}else if(userInput == '3'){
		return 3;
	}else if(userInput == '4'){
		return 4;
	}

	return 2;

}

void askEnterQuestion(void){
	//this is the riddle asked to start the game

	while(enterenceRiddle() != 1){
		printf("The door remains locked. Please try again.\n");
		getchar();
	}
	printf("You have successfully answered the riddle.\n");
	printf("The door swings open, inviting you inside. \n");
	getchar();
	printf("As you step into the small house, the door slams behind you.\n");


}

int enterenceRiddle(void){
	//asks the riddle for the specified questionNo
	//questionNo can be 1-4
	printf("You wipe the grime off of a sign, revealing a riddle: \n");
	getchar();
	srand((unsigned)time(0));
	int randNo = (rand()%10) + 1;
	if(randNo < 3){
		char response = ' ';
		while((((response != '1') || (response != '2'))) || ((response != '3') || (response != '4'))){
			char correctAnswer = '3';
			printf("'The more you have of it, the less you see. What is it?' \n");
			printf("(1) - Fire\n");
			printf("(2) - Water\n");
			printf("(3) - Darkness\n");
			printf("(4) - Sight\n");
			printf("> ");
			scanf("%s", &response);
			if(response == correctAnswer){
				return 1;
			}else{
				return 0;
			}
		}
	}else if(randNo < 6){
		char response = ' ';
		while((((response != '1') || (response != '2'))) || ((response != '3') || (response != '4'))){
			char correctAnswer = '2';
			printf("'I am seen in the water if seen in the sky, \nI am in the rainbow, a jay’s feather,and lapis lazuli. What am I?' \n");
			printf("(1) - Wind\n");
			printf("(2) - Blue\n");
			printf("(3) - Clarity\n");
			printf("(4) - Time\n");
			printf("> ");
			scanf("%s", &response);
			if(response == correctAnswer){
				return 1;
			}else{
				return 0;
			}
		}
	}else{
		char response = ' ';
		while((((response != '1') || (response != '2'))) || ((response != '3') || (response != '4'))){
			char correctAnswer = '3';
			printf("'I build up castles.\n I tear down mountains. \n I make some men blind,\n I help others to see.\n What am I?' \n");
			printf("(1) - Wind\n");
			printf("(2) - a Hole\n");
			printf("(3) - Sand\n");
			printf("(4) - Time\n");
			printf("> ");
			scanf("%s", &response);
			if(response == correctAnswer){
				return 1;
			}else{
				return 0;
			}
		}
	}

	return 0;
}



