#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// rock/paper/scissors game
// 2 person game

using namespace std;

ifstream loadFile;
ofstream saveFile;

string gameInformation = "";

int playerInfo [2][3] = {0};

int playerOne_Points = 0;
int playerTwo_Points = 0;

int gamesPlayed = 0;


// function prototypes

string getInfo(ifstream &file);
void saveInfo(ofstream &file);
int convertWord(string word);
void findNumbers(string series);
void displayAndSetArray(int array_one [3], string tag);
void getGameData(int gameData [2][3]);
void setGameData(string game_result);
void displayPointTotal(int one, int two, int playerOne [3], int playerTwo [3]);
string displayGameResult(string playerOne, string playerTwo);
void clearBoard();
void playerStandings(int first [3], int second [3]);
bool validGameStandings(int game_list[2][3]);
void showSeasonResults(int one, int two);
// start of main function
int main(){
	// START UP INFORMATION
	loadFile.open("game_data.txt");
	if(loadFile.is_open() == true){
		gameInformation = getInfo(loadFile);
		loadFile.close();
	}
	//loadFile.close();
	
	findNumbers(gameInformation);
	// "------------------------"
	
	getGameData(playerInfo);
	
	
	// actually play the game
	bool gamePlaying = true;
	
	cout << "3 POINTS FOR WIN, 1 POINT FOR TIE, 0 POINTS FOR A LOSS" << endl;
	cout << "SEASON ENDS ONCE A PLAYER HAS A COLUMN REACH '9' RESULTS (9 WINS OR 9 LOSSES OR 9 TIES)" << endl;
	
	while(gamePlaying == true){
		
		cout << "----------" << endl;
		
		string answerOne = "";
		string answerTwo = "";
		
		string gameResult = "";
		
		cout << "----> Rock/Paper/Scissors <----" << endl;
		cout << "KeyWords --> (rock, paper, scissors, quit, clear_quit)" << endl;
		
		cout << "Player One: " << endl;
		cin >> answerOne;
		// if one of the players has chosen to quit the game
		if(answerOne == "quit" || answerTwo == "quit"){
			cout << "Player Has Chosen To Quit Game (Saving Data)" << endl;
			break;
		}
		// if a player wants to clear the board and quit
		if(answerOne == "clear_quit"){
			cout << "clearing game standings" << endl;
			clearBoard();
			break;
		}
		// clears the board and quit
		cout << "Player Two: " << endl;
		cin >> answerTwo;
		
		if(answerOne == "quit" || answerTwo == "quit"){
			cout << "Player Has Chosen To Quit Game (Saving Data)" << endl;
			break;
		}
		
		if(answerTwo == "clear_quit"){
			clearBoard();
			cout << "clearing game standings" << endl;
		}
		
		gameResult = displayGameResult(answerOne, answerTwo);
		// sets the game data
		setGameData(gameResult);
		// gets the game data
		getGameData(playerInfo);
		
		//if (gamesPlayed > 5){
			//cout << "more than 5 games played..." << endl;
			//break;
		//}
		
		gamesPlayed += 1;
		
		bool seasonEnded = validGameStandings(playerInfo);
		
		if(seasonEnded == 0){
			cout << "SEASON HAS ENDED!" << endl;
			showSeasonResults(playerOne_Points, playerTwo_Points);
			//cout << "Total Games Played --> " << gamesPlayed << endl;
			clearBoard();
			break;
		}
		
	} // end of game playing while loop
	
	// END GAME INFORMATION
	// opens the save game file
	saveFile.open("game_data.txt");
	
	if(saveFile.is_open() == true){
		saveInfo(saveFile);
		saveFile.close();
	}
	
	//saveFile.close();
	// END OF GAME FUNCTIONS (LIKE SAVING PLAYER/GAME INFORMATION)
}

void showSeasonResults(int one, int two){
	
	int first = 0;
	int second = 0;
	
	string place1 = "";
	string place2 = "";
	
	bool gameTied = false;
	
	if(one > two){
		first = one;
		second = two;
		place1 = "Player One";
		place2 = "Player Two";
	}else{
		second = one;
		first = two;
		place1 = "Player Two";
		place2 = "Player One";
	}
	
	if(first == second){
		gameTied = true;
	}
	
	if(gameTied == false){
		cout << "Season Winner --> " << place1 << endl;
		cout << "Points --> " << first << endl;
		cout << "Second Place --> " << place2 << endl;
		cout << "Points --> " << second << endl;
	}else{
		cout << "Season Tied!" << endl;
		cout << "Point Total: " << one << endl;
	}
	
}

bool validGameStandings(int game_list[2][3]){
	
	bool validGame = true;
	
	for(int i = 0; i < 2; i++){
		for(int x = 0; x < 3; x++){
			if(game_list [i][x] >= 9){
				validGame = false;
			}
		}
	}// end of for loops
	
	//cout << "Valid Game: " << validGame << endl;
	return validGame;
}

void clearBoard(){
	cout << "values..." << endl;
	for(int i = 0; i < 2; i++){
		for(int x = 0; x < 3; x++){
			playerInfo[i][x] = 0;
			cout << playerInfo[i][x];
		}
	}
	cout << endl;
	cout << "All information cleared!" << endl;
}

// setting the game data

void setGameData(string game_result){
	string result = game_result;
	
	cout << "Result From Game: " << result << endl;
	
	if(result == "playerOne"){
		playerInfo[0][0] += 1;
		playerInfo[1][1] += 1;
	}
	if(result == "playerTwo"){
		playerInfo[0][1] += 1;
		playerInfo[1][0] += 1;
	}
	if(result == "game_tied"){
		playerInfo[1][2] += 1;
		playerInfo[0][2] += 1;
	}
}

string displayGameResult(string playerOne, string playerTwo){
	
	cout << "----------" << endl;
	
	string result;
	
	if(playerOne == "rock" && playerTwo == "scissors"){
		result = "playerOne";
	}
	if(playerOne == "scissors" && playerTwo == "rock"){
		result = "playerTwo";
	}
	if(playerOne == "scissors" && playerTwo == "paper"){
		result = "playerOne";
	}
	if(playerOne == "paper" && playerTwo == "scissors"){
		result = "playerTwo";
	}
	if(playerOne == "paper" && playerTwo == "rock"){
		result = "playerOne";
	}
	if(playerOne == "rock" && playerTwo == "paper"){
		result = "playerTwo";
	}
	if(playerOne == playerTwo){
		result = "game_tied";
	}
	
	string displayWinner = "";
	
	if(result == "playerOne"){
		displayWinner = "Player One Wins!";
	}
	if(result == "playerTwo"){
		displayWinner = "Player Two Wins!";
	}
	if(result == "game_tied"){
		displayWinner = "Game Is Tied!";
	}
	
	cout << "Result: " << displayWinner << endl;
	
	cout << "----------" << endl;
	
	return result;
	
}

void getGameData(int gameData [2][3]){ // START OF FUNCTION

	int playerOnePoints = 0;
	int playerTwoPoints = 0;
	
	int player_one [3];
	int player_two [3];

	string tag = "WIN";
	int player = 1;
	
	cout << "----------" << endl;
	
	for(int i = 0; i < 2; i++){ // START OF FIRST FOR LOOP
		
		if(i == 0){
			player = 1;
		}else{
			player = 2;
		}
		
		for(int x = 0; x < 3; x++){ // START OF FOR LOOP
		
			if(x == 0){
				tag = "WINS";
			}
			if(x == 1){
				tag = "LOSSES";
			}
			if(x == 2){
				tag = "TIES";
			}
			
			int result = gameData[i][x];
			
			//cout << "Player " << player << " " << tag + " (" << gameData[i][x] << ")" << endl;
			
			if(player == 1){
				
				if(tag == "WINS"){
					playerOnePoints += (result * 3);
				}
				if(tag == "TIES"){
					playerOnePoints += (result * 1);
				}
				
				player_one[x] = gameData[i][x];
				
			}
			
			if(player == 2){
				if(tag == "WINS"){
					playerTwoPoints += (result * 3);
				}
				if(tag == "TIES"){
					playerTwoPoints += (result * 1);
				}
				
				player_two[x] = gameData[i][x];
				
			}
			
		} // END OF INNER FOR LOOP
		
		cout << "----------" << endl;
		
	} // END OF OUTER FOR LOOP
	
	displayPointTotal(playerOnePoints, playerTwoPoints, player_one, player_two);
	
} // END OF FUNCTION

void displayPointTotal(int one, int two, int playerOne [3], int playerTwo [3]){
	
	// total game points
	
	playerOne_Points = one;
	playerTwo_Points = two;
	
	int first = 0;
	int second = 0;
	
	string positionOne = "";
	string positionTwo = "";
	
	if(one > two){
		positionOne = "Player One";
		positionTwo = "Player Two";
		first = one;
		second = two;
	}
	if(two > one){
		positionOne = "Player Two";
		positionTwo = "Player One";
		first = two;
		second = one;
	}
	
	if(one == two){
		cout << "Standings Are Currently Tied: " << "(" << one << ") Point(s)" << endl;
	}else{
		cout << "<---- STANDINGS ---->" << endl;
		cout << "1st --> " << positionOne << " (" << first << ") Point(s) " << endl;
		cout << "2nd --> " << positionTwo << " (" << second << ") Point(s) " << endl;
		cout << "<---- RESULTS ---->" << endl;
		if(first == one){
			playerStandings(playerOne, playerTwo);
		}else{
			playerStandings(playerTwo, playerOne);
		}
	}
	
}

void playerStandings(int first [3], int second [3]){
	cout << "(1st Place)" << endl;
	for(int i = 0; i < 3; i++){
		if(i == 0){
			cout << "Wins: " << first[i] << endl;
		}
		if(i == 1){
			cout << "Losses: " << first[i] << endl;
		}
		if(i == 2){
			cout << "Ties: " << first[i] << endl;
		}
	}
	cout << "(2nd Place)" << endl;
	for(int i = 0; i < 3; i++){
		if(i == 0){
			cout << "Wins: " << second[i] << endl;
		}
		if(i == 1){
			cout << "Losses: " << second[i] << endl;
		}
		if(i == 2){
			cout << "Ties: " << second[i] << endl;
		}
	}
}

void findNumbers(string series){

	int playerOneSpot = 0;
	int playerTwoSpot = 0;
	
	int player_one_array [3];
	int player_two_array [3];

	bool playerOne = true;
	
	string sortedString = "";

	for(int i = 0; i < series.length(); i++){
		char index = series.at(i);
		if(index == '#' || index == '-'){
			// do nothing
			//cout << "break point: " << i << endl;
		}else{
			sortedString += index;
			if(index != '\n'){
				//cout << "index spot: " << i << endl;
				sortedString += ',';
				if(playerOne == true){
					string str = "";
					str += index;
					//cout << "str: " << str << endl;
					if(playerOneSpot < 3){
						player_one_array[playerOneSpot] = convertWord(str);
					}
					playerOneSpot += 1;
				}else{
					string str = "";
					str += index;
					//cout << "str: " << str << endl;
					if(playerTwoSpot < 3){
						player_two_array[playerTwoSpot] = convertWord(str);
					}
					playerTwoSpot += 1;
				}
			}else{
				if(playerOne == true){
					//cout << "switching to player two" << endl;
					playerOne = false;
				}else{
					//cout << "switching to player one" << endl;
					playerOne = true;
				}
			}
		}
	} // end of for loop to determine which characters are integers
	
	displayAndSetArray(player_one_array, "player_one");
	displayAndSetArray(player_two_array, "player_two");
	
	//cout << "sorted string: " << endl << sortedString << endl;
	
}	

// converts words to numbers
int convertWord(string word){
	int number = 0;
	stringstream ss(word);
	// sets the converted value to number, which is then returned
	ss >> number;
	return number;
	
}

void displayAndSetArray(int array_one [3], string tag){
	int placeHolder = 0;
	if(tag == "player_one"){
		placeHolder = 0;
	}
	if(tag == "player_two"){
		placeHolder = 1;
	}
	for(int i = 0; i < 3; i++){
		playerInfo[placeHolder][i] = array_one[i];
	}
}

// gets information from file
string getInfo(ifstream &file){
	
	string returnLine = "";
	
	while(file.eof() == false){
		string line = "";
		getline(file, line);
		if(line == ""){
			break;
		}
		returnLine += (line + "\n");
	}
	return returnLine;
}
// saves information to file
void saveInfo(ofstream &file){
	for(int i = 0; i < 2; i++){
		for(int x = 0; x < 3; x++){
			// determines if we are at the end of the row
			if(x == 2){
				file << playerInfo[i][x] << "#";
			}else{
				file << playerInfo[i][x] << "-";
			}	
		}
		file << endl;
	}
}

// end of game file