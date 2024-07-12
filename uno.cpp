/// AUTHOR: FOINI LORENZO
/// UNO CARD GAME

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#include<time.h>
#include<windows.h>
#define random(x) rand() %x
#define randomize srand ((unsigned)time(NULL))
using namespace std;

// Define variables 
// Define struct for cards
struct card
{
    int color;
    int number;
    card *nextCard;
};
typedef card *cardType; 
cardType deck = NULL; // Deck will contains the cards
cardType wastes = NULL; // Wastes will contains the cards that are discarded by the players

// Char for saving the name of the player
typedef char *name;

// Create a list for the players and their data
struct player
{
    cardType playerHand;
    name playerName;
    int playerCounter;
    player *nextPlayer;
};
typedef player *playerType;
playerType playersList = NULL;

// Create (and set) some variables
int remainingCards = 36; // Number of remaining cards 
int numberWastes = 0; // Number of cards that hev been discarded
int numPlayers; // Number of players
bool win = false;
bool stop = false;

// FUNCTIONS

// Function for creating a random number between 1 and max
int randomNumber(int max)
{
    return(random(max)+1);
}

// Function for setting and changing the color of the text and background
void setColor(unsigned short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

// Function for insert at the end a card
void insertTail(cardType &headCard, cardType &cardToInsert)
{
    // Head is empty
    if(headCard == NULL)
    {
        headCard = cardToInsert;
        cardToInsert->nextCard = NULL;
    }
    else // Head is not empty
    {
        cardType tmp = headCard;
        while(tmp->nextCard != NULL)
        {
            tmp = tmp->nextCard;
        }
        tmp->nextCard = cardToInsert;
        cardToInsert->nextCard = NULL;
    }
}

// CREATE DECK 
// Function for saving the data of a card in a node
void saveCard(cardType &head, int color, int number)
{
    cardType tmp;
    tmp = new card;
    tmp->color = color;
    tmp->number = number;
    insertTail(head, tmp);
}

// Function for loading the deck (ordered) with all the cards
void loadDeck(cardType &deck)
{
    cardType tmp;

    // Red cards
    for(int i=1; i<=8; i++)
    {
        saveCard(deck,192,i);
    }
    
    // Blue cards
    for(int i=1; i<=8; i++)
    {
        saveCard(deck,144,i);
    }

    // Yellow cards
    for(int i=1; i<=8; i++)
    {
        saveCard(deck,224,i);
    }

    // Green cards
    for(int i=1; i<=8; i++)
    {
        saveCard(deck,160,i);
    }

    // Jolly X4
    saveCard(deck,0,9);
    saveCard(deck,0,9);
    saveCard(deck,0,9);
    saveCard(deck,0,9);
}

// VISUALIZATION
// Function for cleaning the screen after the player has press a button
void cleanScreen()
{
    system("pause");
    system("cls");
}

// Function for displaying a colored and pre-fixed length row 
void displayRow(int color, int length)
{
    setColor(color);
    for(int i=0; i<length; i++) cout<<" ";
}

// Function for visualise the first and the last rows of a card
void firstRow(int color)
{
    displayRow(color, 14);
}

// Function for visualise the second and the penultimate rows of a card on front
void secondRowFront(int color)
{
    displayRow(color, 3);
    displayRow(240, 8);
    displayRow(color, 3);
}

// Function for visualise the second and the penultimate rows of a card on back
void secondRowBack()
{
    displayRow(0, 3);
    displayRow(192, 8);
    displayRow(0, 3);
}

// Function that contains all the models of the center of the cards (divided by rows) and allows them to be displayed correctly
void cardBank(int row, int number)
{
    if(number == 1)
    {
        if(row == 2)
        {
            displayRow(240, 2);
            displayRow(0, 3);
            displayRow(240,3);
        }
        if(row>=3 && row<=6)
        {
            displayRow(240, 3);
            displayRow(0, 2);
            displayRow(240,3);
        }
    }
    if(number == 2)
    {
        if(row == 2 || row == 4 || row == 6)
        {
            displayRow(240, 1);
            displayRow(0, 6);
            displayRow(240, 1);
        }
        if(row == 3)
        {
            displayRow(240, 5);
            displayRow(0, 2);
            displayRow(240, 1);
        }
        if(row == 5)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 5);
        }
    }
    if(number == 3)
    {
        if(row == 2 || row == 4 || row == 6)
        {
            displayRow(240, 1);
            displayRow(0, 6);
            displayRow(240, 1);
        }
        if(row == 3 || row == 5)
        {
            displayRow(240, 5);
            displayRow(0, 2);
            displayRow(240, 1);
        }
    }
    if(number == 4)
    {
        if(row == 2 || row == 3)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 2);
            displayRow(0, 2);
            displayRow(240, 1);
        }
        if(row == 4)
        {
            displayRow(240, 1);
            displayRow(0, 6);
            displayRow(240, 1);
        }
        if(row == 5 || row == 6)
        {
            displayRow(240, 5);
            displayRow(0, 2);
            displayRow(240, 1);
        }
    }
    if(number == 5)
    {
        if(row == 2 || row == 4 || row == 6)
        {
            displayRow(240, 1);
            displayRow(0, 6);
            displayRow(240, 1);
        }
        if(row == 3)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 5);
        }
        if(row == 5)
        {
            displayRow(240, 5);
            displayRow(0, 2);
            displayRow(240, 1);
        }
    }
    if(number == 6)
    {
        if(row == 2 || row == 4 || row == 6)
        {
            displayRow(240, 1);
            displayRow(0, 6);
            displayRow(240, 1);
        }
        if(row == 3)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 5);
        }
        if(row == 5)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 2);
            displayRow(0, 2);
            displayRow(240, 1);
        }
    }
    if(number == 7)
    {
        if(row == 2)
        {
            displayRow(240, 1);
            displayRow(0, 6);
            displayRow(240, 1);
        }
        if(row >= 3 && row <= 6)
        {
            displayRow(240, 5);
            displayRow(0, 2);
            displayRow(240, 1);
        }
    }

    // Draw cards
    if(number == 8)
    {
        if(row == 2 || row == 4)
        {
            displayRow(240, 1);
            displayRow(0, 5);
            displayRow(240, 2);
        }
        if(row == 3)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 2);
            displayRow(0, 2);
            displayRow(240, 1);
        }
        if(row == 5 || row == 6)
        {
            displayRow(240, 1);
            displayRow(0, 2);
            displayRow(240, 5);
        }
    }

    // Jolly
    if(number == 9)
    {
        if(row == 2 || row == 3)
        {
            displayRow(192, 3);
            displayRow(240, 2);
            displayRow(144, 3);
        }
        if(row == 4)
        {
            displayRow(240, 8);
        }
        if(row == 5 || row == 6)
        {
            displayRow(224, 3);
            displayRow(240, 2);
            displayRow(160, 3);
        }
    }

    // Back of card
    if(number == 10)
    {
        if(row == 2)
        {
            displayRow(192, 7);
            displayRow(224, 3);
        }
        if(row == 3)
        {
            displayRow(192, 3);
            displayRow(96, 2);
            displayRow(192, 1);
            displayRow(96, 1);
            displayRow(224, 1);
            displayRow(192, 1);
            displayRow(224, 1);
        }
        if(row == 4)
        {
            displayRow(224, 1);
            displayRow(192, 1);
            displayRow(224, 1);
            displayRow(96, 4);
            displayRow(224, 3);
        }
        if(row == 5)
        {
            displayRow(224, 1);
            displayRow(192, 1);
            displayRow(224, 1);
            displayRow(96, 1);
            displayRow(192, 1);
            displayRow(96, 2);
            displayRow(192, 3);
        }
        if(row == 6)
        {
            displayRow(224, 3);
            displayRow(192, 7);
        }
    }
}

// Function that allows you to display a specific row of a card of a given number and color
void displayCard(int row, int number, int color)
{
    // Display a line of the same color as the background on the screen if one stack is lower than the other 
    if(row < 0) displayRow(112, 14);
    else
    {
        // Display the blank under the top card of a pile
        if(row > 8) displayRow(240, 14);
        else
        {
            // Top and Bottom border
            if(row == 0 || row == 8) firstRow(color);
            else
            {
                // Top and bottom front border
                if(row == 1 || row == 7)
                {
                    if(number == 10) secondRowBack();
                    else secondRowFront(color);
                }
                else
                {
                    // Left border
                    displayRow(color, 2);
                    if(number != 10) displayRow(240, 1);
                    
                    // Internal area of the card
                    cardBank(row, number);
                    
                    // Right border
                    if(number != 10) displayRow(240, 1);
                    displayRow(color, 2);
                }
            }
        }
    }
}

// Function that allows you to send a given deck to the screen, grouping the cards into rows of 5 cards each
void displayDeck(cardType deck)
{
    int row, i;
    int numCardsRow = 5;
    cardType tmp1 = deck;
    cardType tmp2;

    // While for display cards
    while(tmp1 != NULL)
    {
        row = 0;
        // While to display all the rows of a series of 5 cards
        while(tmp1 != NULL && row < 9)
        {
            displayRow(112, 1);
            i = 0;
            tmp2 = tmp1;

            // While to display numCardsRow cards per row (or less if there aren't enough)
            while(tmp1 != NULL && i < numCardsRow)
            {
                displayCard(row, tmp1->number, tmp1->color);
                if(i != numCardsRow-1) displayRow(112, 2);
                i++;
                tmp1 = tmp1->nextCard;
            }
            cout<<endl;
            row++;
            if(row != 9) tmp1 = tmp2;
        }
        cout<<endl;
    }
    setColor(112);
}

// Function for displaying the name of the player and his deck
void displayPlayer(playerType player)
{
    cout<<player->playerName<<":"<<endl<<endl;
    displayDeck(player->playerHand);
}

// Funtion used to correctly initialize the rows of a stack to ensure that the base is the same row 
// (the largest row is initialized to 0, the smallest to a negative number such that it reaches 0 when it has to begin to view the map). 
// It is also used to determine how many white lines to display (based on the returned value)
int mas(int &n1, int &n2)
{
    int tmp;
    if(n1 >= n2)
    {
        tmp = n1;
        n2 = n2-n1;
        n1 = 0;
        return tmp;
    }
    else
    {
        tmp = n2;
        n1 = n1-n2;
        n2 = 0;
        return tmp;
    }
}

// Function that displays the stacked cards of the deck (the first one is turned over) and the discards on the screen. 
// The height of the two stacks of cards is also rendered (a bit haphazardly).
void displayStack(cardType deck, cardType wastes, int remainingCard, int numberDiscard)
{
    // Deck first, then discard
    // This way each white layer contains 6 cards
    int row1 = remainingCard/6; 
    int row2 = numberDiscard/6;
    int mass = mas(row1, row2);
    
    // for loop to display the rows of the piles (top card and blank for the cards below)
    for(int i=0; i<9+mass; i++)
    {
        cout<<"  ";
        displayCard(row1, 10, 0);
        displayRow(112, 4);
        displayCard(row2, wastes->number, wastes->color);
        row1++;
        row2++;
        cout<<endl;
        setColor(112);
    }
    cout<<endl<<endl;
}

// Function that displays the first 4 spaces of a line of a card on the screen (used to create the overlapping effect on the opponent's cards)
void displayPartialBack(int row)
{
    if(row == 0 || row == 8)
    {
        displayRow(0, 4);
    }
    if(row == 1 || row == 7)
    {
        displayRow(0, 4);
    }
    if(row == 2 || row == 3)
    {
        displayRow(0, 2);
        displayRow(192, 2);
    }
    if(row == 4 || row == 5)
    {
        displayRow(0, 2);
        displayRow(224, 1);
        displayRow(192, 1);
    }
    if(row == 6)
    {
        displayRow(0, 2);
        displayRow(224, 2);
    }
}

// Function that returns the color of a player's name based on his position in the list of players
int playerColor(int i)
{
    if(i == 1) return 207;
    if(i == 2) return 159;
    if(i == 3) return 239;
    if(i == 4) return 175;
    if(i == 5) return 223;
}

// Function for displaying others players' cards
void displayOpponents(playerType playerList, int playerID, int playersNumber)
{
    playerType tmp = playerList;
    cout<<"OPPENENTS CARDS:"<<endl;
    
    // for loop for displaying the cards of the others players 
    for(int i=1; i<=playersNumber; i++)
    {
        // Avoid current player
        if(i != playerID)
        {
            setColor(playerColor(i));
            cout<<tmp->playerName<<":"<<endl;
            setColor(112);
            // for loop for display the rows of the cards
            for(int row=0; row<9; row++)
            {
                cout<<"  ";
                // for loop to partially display all but one of an opponent's cards
                for(int num=0; num<(tmp->playerCounter)-1; num++) displayPartialBack(row);
                // Dispaly back of the card
                displayCard(row, 10, 0);
                setColor(112);
                cout<<endl;
            }
            cout<<endl;
        }
        tmp = tmp->nextPlayer;
    }
    cout<<endl;
}

// CARDS DISTRIBUTION
// Function that returns the address of a card given its position within the deck (as if it were the index of a vector)
// Checks for not found are not needed because the random will always generate an index that exists in the deck
cardType searchCardByPosition(cardType &deck, int position)
{
    if(deck == NULL) return NULL;
    cardType tmp = deck;
    for(int i=0; i<position; i++) tmp=tmp->nextCard;
    return tmp;
}

// Function that extracts a card from a deck given its position within the deck (starts from 0)
cardType getCardByPosition(cardType &deck, int position)
{
    cardType tmp = searchCardByPosition(deck, position);
    if(tmp != NULL)
    {
        cardType tmp2 = deck;
        if(tmp == deck) deck = deck->nextCard;
        else
        {
            while(tmp2->nextCard != tmp) tmp2=tmp2->nextCard;
            tmp2->nextCard = tmp->nextCard;
        }
    }
    return tmp;
}

// Function for setting jolly's color to black
void resetJolly(cardType &deck)
{
    cardType tmp = deck;
    while(tmp != NULL)
    {
        if(tmp->number == 9) tmp->color = 0;
        tmp = tmp->nextCard;
    }
}

// Function that puts the discard cards, except the top one, into the deck and updates their counters
void shuffle(cardType &deck, cardType &wastes, int &numberWastes, int &numberRemaining)
{
    deck = wastes->nextCard;
    wastes->nextCard = NULL;
    numberRemaining = numberWastes-1;
    numberWastes = 1;
    resetJolly(deck);
}

// Function that randomly draws a card from the main deck and assigns it (at the end) to a given player's deck
void drawCardPlayer(cardType &deck, cardType &player, int &numberRemaining, int &counter, int position, cardType &wastes, int &numberWastes)
{
    cardType drawnCard = getCardByPosition(deck, position);
    
    if(drawnCard == NULL) cout<<"The deck is empty"<<endl;
    else
    {
        insertTail(player, drawnCard);
        numberRemaining--;
        counter++;
    }
    if(numberRemaining == 0)
    {
        shuffle(deck,wastes,numberWastes,numberRemaining);
    }
}

// Function which creates the initial deck (5 cards) for a given player
void loadPlayer(cardType &deck, cardType &player, int &numberRemaining, int &counter, cardType &wastes, int &numberWastes)
{
    for(int i=0; i<5; i++) drawCardPlayer(deck, player, numberRemaining, counter, randomNumber(numberRemaining)-1, wastes, numberWastes);
}

// Function that inserts the first card into the discard pile, checking that it is a number (and not a wild card or a draw card)
void discardFirst(cardType &deck, cardType &wastes, int &numberRemaining, int &numberWastes)
{
    int position;
    cardType tmp;
    
    // Do-while loop for chechking if the extracted card is not a special card
    do
    {
        position=randomNumber(numberRemaining)-1;
        tmp = searchCardByPosition(deck, position);
    }while(tmp->number > 7);
    
    drawCardPlayer(deck, wastes, numberRemaining, numberWastes, position, wastes, numberWastes);
}

// INSERT PLAYERS
// Function for asking hwo many players are gonna play the game
void askNumPlayers(int &n)
{
    do{
        cout<<"Insert number of players (between 2 and 5):"<<endl;
        cin>>n;
      }while(n < 2 || n > 5);

}

// Function for checking of the name is already in use or not
// Return true if free
// Return false if the name si already used
bool checkName(playerType playersList, name playerName)
{
    playerType tmp = playersList;
    while(tmp != NULL)
    {
        if(strcmpi(tmp->playerName, playerName) == 0) return false;
        tmp = tmp->nextPlayer;
    }
    return true;
}

// Void for setting players' name
void setName(name &playerName)
{
    fflush(stdin);
    gets(playerName);
}

// Function that returns the address of the terminator of a given string
name searchTerminator(name playerName)
{
    name tmp = playerName;
    while(strcmp(tmp, "\0")!=0) tmp = tmp+1;
    return tmp;
}

// Function that returns the address of a string containing the name of a new player with checks to avoid repetitions
name askName(int i)
{
    int color;
    bool checkValidity;
    name playerName = new char;
    name c;
    do
    {
        cout<<"Insert player "<<i<<" name: ";
        color = playerColor(i);
        setColor(color);
        setName(playerName);
        checkValidity = checkName(playersList, playerName);
        setColor(112);
        if(checkValidity == false)
        {
            cout<<"Name already in use. Insert surname: ";
            setColor(color);
            // Find the terminator of name and save such address in c
            c = searchTerminator(playerName);
            // Now add a spacke between name and surname 
            *c=' ';
            // Go to next cell
            c++;
            // Save the string starting from the current cell
            setName(c);
            // Check name
            checkValidity = checkName(playersList, playerName);
            setColor(112);
            if(checkValidity == false) cout<<"Invalid name, please insert a new one"<<endl;
        }
    }while(checkValidity == false);
    cout<<endl;
    return playerName;
}

// Function which insert at the end a new node with the data of a new player
void insertTailPlayer(playerType &playersList, playerType &player)
{
    if(playersList == NULL)
    {
        playersList = player;
        player->nextPlayer = NULL;
    }
    else
    {
        playerType tmp = playersList;
        while(tmp->nextPlayer != NULL)
        {
            tmp = tmp->nextPlayer;
        }
        tmp->nextPlayer = player;
        player->nextPlayer = NULL;
    }
}

// Function that creates as many players as those entered by the user and loads them with the relevant data
void createPlayers(playerType &playersList, int playersNumber, int &numberRemaining, cardType &wastes, int &numberWastes)
{
    playerType players;
    for(int i=0; i<playersNumber; i++)
    {
        players=new player;
        players->playerCounter = 0;
        players->playerName = askName(i+1);
        players->playerHand = NULL;
        loadPlayer(deck, players->playerHand, numberRemaining, players->playerCounter, wastes, numberWastes);
        insertTailPlayer(playersList, players);
    }
}

// Function which given the index of the player (start with 1), return its address
playerType searchPlayer(playerType playersList, int num)
{
    playerType tmp = playersList;
    for(int i=1; i<num; i++) tmp=tmp->nextPlayer;
    return tmp;
}

// Function which display the hand of the players
void displayHands(playerType playersList, int numberPlayers)
{
    playerType tmp = playersList;
    for(int i=0; i<numberPlayers; i++)
    {
        displayPlayer(tmp);
        cout<<endl<<endl;
        tmp=tmp->nextPlayer;
    }
}

// GAME
// Function which display a colored -
void coloredStretch()
{
    setColor(121);
    cout<<" - ";
    setColor(112);
}

// Function which display the rules of the game
void rules()
{
    setColor(31);
    cout<<"WELCOME"<<endl;
    setColor(119);
    system("pause");
    setColor(121);
    cout<<"RULES:"<<endl;
    coloredStretch();
    cout<<"You can play with 2/3/4/5 players on this device;"<<endl;
    coloredStretch();
    cout<<"Every player has 5 cards in his hand;";
    coloredStretch();
    cout<<endl<<"A card is shown, it will form the pile of discarded cards;"<<endl;
    coloredStretch();
    cout<<"When it is player's turn, he has to select a card to discard. It must be the same color as the card discarded by the previous player, or it must be the same number, or you can play the 'joker' card which also allows you to change colour; if you don't have any of these cards, you draw a card from the deck and if it is compatible with the one discarded by your opponent, you can discard it, otherwise you skip your turn and move on to the next player;"<<endl;
    coloredStretch();
    cout<<"If a player plays the 'P' card, the next player draws two cards and skips his turn;";

    setColor(113);
    cout<<endl<<endl<<"!!!";
    setColor(112);
    cout<<"The first player that finish his card in the hand wins.";
    setColor(113);
    cout<<"!!!"<<endl<<endl;
    setColor(112);

    system("pause");
    system("cls");
}

// Function which change the color when there is a jolly
void colorJolly(cardType &card)
{
    char *color;
    color = new char;
    do{
        cout<<"Select the color of the jolly (insert red/green/blue/yellow):"<<endl;
        fflush(stdin);
        gets(color);
      }while(strcmpi(color,"red")!=0 && strcmpi(color,"green")!=0 && strcmpi(color,"blue")!=0 && strcmpi(color,"yellow")!=0);
    if(strcmpi(color,"red")==0)
    {
        card->color=192;
    }
    if(strcmpi(color,"blue")==0)
    {
        card->color=144;
    }
    if(strcmpi(color,"green")==0)
    {
        card->color=160;
    }
    if(strcmpi(color,"yellow")==0)
    {
        card->color=224;
    }
}

// Function which controll if the selected card can be discard or not
// If true => The card can be discarded
// If false => The card can't be discarded
bool checkDiscard(int position, cardType playerHand, cardType wastes, bool &stop)
{
    cardType searched = searchCardByPosition(playerHand, position);
    switch(searched->number)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:{
                if(searched->number == wastes->number || searched->color == wastes->color){return true;}
                else{return false;}
                break;
               }
        case 8:{
                // Stop the next players 
                if(searched->number == wastes->number || searched->color == wastes->color)
                {
                    stop=true;
                    return true;
                }
                else{return false;}
                break;
               }
        case 9:{
                colorJolly(searched);
                return true;
                break;
               }
    }
}

// Function that given a position in the form of a string, returns the corresponding number (up to 30 for safety)
int translatePosition(char *strpos)
{
    if(strcmp(strpos, "1")==0) return 1;
    if(strcmp(strpos, "2")==0) return 2;
    if(strcmp(strpos, "3")==0) return 3;
    if(strcmp(strpos, "4")==0) return 4;
    if(strcmp(strpos, "5")==0) return 5;
    if(strcmp(strpos, "6")==0) return 6;
    if(strcmp(strpos, "7")==0) return 7;
    if(strcmp(strpos, "8")==0) return 8;
    if(strcmp(strpos, "9")==0) return 9;
    if(strcmp(strpos, "10")==0) return 10;
    if(strcmp(strpos, "11")==0) return 11;
    if(strcmp(strpos, "12")==0) return 12;
    if(strcmp(strpos, "13")==0) return 13;
    if(strcmp(strpos, "14")==0) return 14;
    if(strcmp(strpos, "15")==0) return 15;
    if(strcmp(strpos, "16")==0) return 16;
    if(strcmp(strpos, "17")==0) return 17;
    if(strcmp(strpos, "18")==0) return 18;
    if(strcmp(strpos, "19")==0) return 19;
    if(strcmp(strpos, "20")==0) return 20;
    if(strcmp(strpos, "21")==0) return 21;
    if(strcmp(strpos, "22")==0) return 22;
    if(strcmp(strpos, "23")==0) return 23;
    if(strcmp(strpos, "24")==0) return 24;
    if(strcmp(strpos, "25")==0) return 25;
    if(strcmp(strpos, "26")==0) return 26;
    if(strcmp(strpos, "27")==0) return 27;
    if(strcmp(strpos, "28")==0) return 28;
    if(strcmp(strpos, "29")==0) return 29;
    if(strcmp(strpos, "30")==0) return 30;
    return 0;
}

// Function for asking the client which card he wants to discard
void askDiscard(int &position, playerType player, cardType wastes, bool &stop)
{
    char *strpos;
    strpos = new char;

    // Check if the player has at least a card that can be discarded or not
    bool check;
    do{
        do{
            cout<<"Insert the position of the card that you want to discard (start from 1):"<<endl;
            fflush(stdin);
            gets(strpos);
            position = translatePosition(strpos);
        }while(position < 1 || position > player->playerCounter);
        position--;
        check = checkDiscard(position, player->playerHand, wastes, stop);
        if(check == false){cout<<"You can't discard such card."<<endl;}
        if(position >= player->playerCounter){cout<<"This position don't exists, you don't have such number of cards."<<endl;}
      }while(check == false);
}

// Function for insert the discarded card in the head of the wastes
void insertHeadWastes(cardType &wastes, cardType &card)
{
    card->nextCard = wastes;
    wastes = card;
}

// Function which controll if a player can discard at least a card
bool checkAtLeastOneCard(playerType player, cardType wastes)
{
    int counter = 0;
    cardType tmp = player->playerHand;
    for(int i=0; i<player->playerCounter; i++)
    {
        if(tmp->number == wastes->number || tmp->color == wastes->color || tmp->number == 9)
        {
            counter++;
        }
        tmp = tmp->nextCard;
    }
    if(counter > 0) return true;
    else return false;
}

// Function for handling the turns of the players
void playerTurn(cardType &deck, cardType &wastes, playerType playersList, bool &win, bool &stop, int &numberRemaining, int &numberWastes, int playerID)
{
    int position;
    playerType player = searchPlayer(playersList, playerID);
    cout<<"Player's turn: ";
    setColor(playerColor(playerID));
    cout<<player->playerName<<endl;
    setColor(112);
    cout<<endl;
    displayOpponents(playersList, playerID, numPlayers);
    displayStack(deck, wastes, numberRemaining, numberWastes);

    // Check if the discarded card is a 'P' card
    if(stop == true)
    {
        stop = false;
        drawCardPlayer(deck, player->playerHand, numberRemaining, player->playerCounter, randomNumber(numberRemaining)-1, wastes, numberWastes);
        drawCardPlayer(deck, player->playerHand, numberRemaining, player->playerCounter, randomNumber(numberRemaining)-1, wastes, numberWastes);
        setColor(124);
        cout<<"Two cards have been added to your hand and you skip this turn."<<endl;
        setColor(112);
        cout<<"Your hand is:"<<endl;
        displayDeck(player->playerHand);
    }
    else
    {
        cout<<"Your hand is:"<<endl;
        displayDeck(player->playerHand);
        
        // Check if the player has at least a card that can be discarded
        if(checkAtLeastOneCard(player, wastes) == true)
        {
            askDiscard(position, player, wastes, stop);
            cardType extracted = getCardByPosition(player->playerHand, position);
            insertHeadWastes(wastes, extracted);
            player->playerCounter--;
            numberWastes++;
        }
        else{
                setColor(121);
                cout<<"None of your cards can be discrarded, so you will draw a new card."<<endl<<endl;
                setColor(112);
                system("pause");
                
                // Draw a card
                drawCardPlayer(deck, player->playerHand, numberRemaining, player->playerCounter, randomNumber(numberRemaining)-1, wastes, numberWastes);
                cout<<"Now your hand is:'"<<endl;
                displayDeck(player->playerHand);
                
                // Check if the card can be discarded
                if(checkDiscard(player->playerCounter-1, player->playerHand, wastes, stop) == true)
                {
                    setColor(122);
                    cout<<"The card you just drew has been discarded."<<endl<<endl;
                    setColor(112);
                    cardType extracted = getCardByPosition(player->playerHand, player->playerCounter-1);
                    insertHeadWastes(wastes, extracted);
                    player->playerCounter--;
                    numberWastes++;
                }
                else{
                        setColor(124);
                        cout<<"The card you just drew cannot be discarded."<<endl<<endl;
                        setColor(112);
                    }
            }
    }
    system("pause");
    system("cls");
    if(player->playerCounter == 0) win = true;
    else
    {
        // Next turn
        cout<<"Now is the turn of ";
        if(player->nextPlayer != NULL)
        {
            setColor(playerColor(playerID+1));
            cout<<player->nextPlayer->playerName<<endl<<endl;
        }
        else
        {
            setColor(playerColor(1));
            cout<<playersList->playerName<<endl<<endl;
        }
        setColor(112);
    }
    system("pause");
    system("cls");
}

// Function which return the address of the player that has won
playerType searchWinner(playerType playersList, playerType &winner, int &position)
{
    int i = 1;
    playerType tmp = playersList;
    while(tmp->playerCounter != 0)
    {
        tmp = tmp->nextPlayer;
        i++;
    }
    position = i;
    winner = tmp;
}

// Function which display messages for the winner
void messageWin(playerType playersList)
{
    playerType winner;
    int positionWinner;
    int color;
    searchWinner(playersList, winner, positionWinner);
    cout<<"CONGRATULATIONS, ";
    color = playerColor(positionWinner);
    setColor(color);
    cout<<winner->playerName;
    setColor(112);
    cout<<" YOU HAVE WON THE GAME!!!"<<endl<<endl;
    cout<<endl<<"Thanks for playing!"<<endl;
    setColor(119);
}

// Function for handling turn in case of win
void game(cardType deck, cardType wastes, playerType playersList, int &numberRemaining, int &numberWastes, bool &stop)
{
    do{
        // First player's turn
        playerTurn(deck, wastes, playersList, win, stop, numberRemaining, numberWastes, 1);
        if(win == false)
        {
            // Second player's turn
            playerTurn(deck, wastes, playersList, win, stop, numberRemaining, numberWastes, 2);
            if(win == false && numPlayers > 2)
            {
                // Third player's turn
                playerTurn(deck, wastes, playersList, win, stop, numberRemaining, numberWastes, 3);
                if(win == false && numPlayers > 3)
                {
                    // Fourth player's turn
                    playerTurn(deck, wastes, playersList, win, stop, numberRemaining, numberWastes, 4);
                    if(win == false && numPlayers > 4)
                    {
                        // Fifth player's turn
                        playerTurn(deck, wastes, playersList, win, stop, numberRemaining, numberWastes, 5);
                    }
                }
            }
        }
    }while(win == false);
    messageWin(playersList);
}

// Function that sends a darker than normal line to the screen given color and length
void displayRow2(int color, int length)
{
    char let=178;
    setColor(color);
    for(int i=0; i<length; i++) cout<<let;
}

// Function that sends a bar line to the screen (true with the shadow, false without)
void i(bool om)
{
    if(om == true) displayRow2(112, 1);
    displayRow(0, 2);
    displayRow(128, 2);
    displayRow(0, 2);
}

// Function which display a row of the u
void u(bool nr)
{
    displayRow(176, 3);
    i(true);
    displayRow(176, 9);
    i(true);
    displayRow(176, 2);
    displayRow2(112, 1);
    displayRow(0, 2);
    displayRow(128, 2);
    if(nr == true) displayRow(0, 2);
}

// Function which display a row of the n
void n()
{
    displayRow2(112, 2);
    displayRow(0, 1);
    displayRow(128, 2);
    displayRow(0, 1);
}

// Function which display a row of the central part of the 0, given two colors
void c(int color1, int color2)
{
    displayRow(240, 1);
    displayRow(color1, 3);
    displayRow(240, 2);
    displayRow(color2, 3);
    displayRow(240, 1);
}

// Function for displaying the title of the game
void title()
{
    displayRow(176, 79);
    cout<<endl;
    displayRow(176, 79);
    cout<<endl;
    displayRow(176, 4);
    displayRow(0, 6);
    displayRow(176, 10);
    displayRow(0, 6);
    displayRow(176, 3);
    displayRow(0, 7);
    displayRow(176, 9);
    displayRow(0, 6);
    displayRow(176, 3);
    displayRow(0, 22);
    displayRow(176, 3);
    cout<<endl;
    u(false);
    displayRow(128, 2);
    displayRow(0, 2);
    displayRow(176, 7);
    i(true);
    displayRow(176, 2);
    displayRow2(112, 1);
    displayRow(0, 2);
    displayRow(128, 18);
    displayRow(0, 2);
    displayRow(176, 3);
    cout<<endl;
    u(false);
    displayRow(128, 4);
    displayRow(0, 1);
    displayRow(176, 6);
    i(true);
    displayRow(176, 2);
    i(true);
    displayRow(0, 10);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    displayRow(0, 1);
    displayRow(128, 2);
    displayRow(0, 1);
    displayRow(176, 5);
    i(true);
    displayRow(176, 2);
    i(true);
    displayRow(240, 10);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    displayRow2(112, 1);
    displayRow(0, 1);
    displayRow(128, 2);
    displayRow(0, 1);
    displayRow(176, 4);
    i(true);
    displayRow(176, 2);
    i(true);
    c(192, 144);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    n();
    displayRow(176, 3);
    i(true);
    displayRow(176, 2);
    i(true);
    c(192, 144);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    displayRow(176, 1);
    n();
    displayRow(176, 2);
    i(true);
    displayRow(176, 2);
    i(true);
    displayRow(240, 10);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    displayRow(176, 2);
    n();
    displayRow(176, 1);
    i(true);
    displayRow(176, 2);
    i(true);
    c(224, 160);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    displayRow(176, 3);
    n();
    i(true);
    displayRow(176, 2);
    i(true);
    c(224, 160);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    u(true);
    displayRow(176, 4);
    n();
    i(false);
    displayRow(176, 2);
    i(true);
    displayRow(240, 10);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    displayRow(176, 3);
    displayRow2(112, 1);
    displayRow(0, 2);
    displayRow(128, 2);
    displayRow(0, 14);
    displayRow(128, 2);
    displayRow(0, 2);
    displayRow(176, 2);
    i(true);
    displayRow(176, 5);
    displayRow2(112, 2);
    displayRow(0, 1);
    displayRow(128, 6);
    displayRow(0, 2);
    displayRow(176, 2);
    i(true);
    displayRow(0, 10);
    i(false);
    displayRow(176, 3);
    cout<<endl;
    displayRow(176, 3);
    displayRow2(112, 1);
    displayRow(0, 2);
    displayRow(128, 18);
    displayRow(0, 2);
    displayRow(176, 2);
    i(true);
    displayRow(176, 6);
    displayRow2(112, 2);
    displayRow(0, 2);
    displayRow(128, 4);
    displayRow(0, 2);
    displayRow(176, 2);
    displayRow2(112, 1);
    displayRow(0, 2);
    displayRow(128, 18);
    displayRow(0, 2);
    displayRow(176, 3);
    cout<<endl;
    displayRow(176, 3);
    displayRow2(112, 1);
    displayRow(0, 22);
    displayRow(176, 2);
    displayRow2(112, 1);
    displayRow(0, 6);
    displayRow(176, 7);
    displayRow2(112, 2);
    displayRow(0, 7);
    displayRow(176, 2);
    displayRow2(112, 1);
    displayRow(0, 22);
    displayRow(176, 3);
    cout<<endl;
    displayRow(176, 3);
    displayRow2(112, 22);
    displayRow(176, 3);
    displayRow2(112, 6);
    displayRow(176, 9);
    displayRow2(112, 7);
    displayRow(176, 3);
    displayRow2(112, 22);
    displayRow(176, 4);
    cout<<endl;
    displayRow(176, 79);
    cout<<endl;
    displayRow(176, 79);
    cout<<endl;
    setColor(112);
}

//int main
int main()
{
    randomize;
    system("color 70");
    cout<<"Before you start, expand the window for a better game's experience."<<endl;
    system("pause");
    system("cls");
    title();
    cout<<endl;

    // Display rules
    rules();

    // Create and load deck
    loadDeck(deck);

    // Insert first card of the wastes
    discardFirst(deck, wastes, remainingCards, numberWastes);

    // Create players (with their names)
    askNumPlayers(numPlayers);
    createPlayers(playersList, numPlayers, remainingCards, wastes, numberWastes);
    cout<<"The hands have been created."<<endl;
    cout<<"Now the game will start."<<endl<<endl;
    system("pause");
    system("cls");

    // Game starts
    game(deck, wastes, playersList, remainingCards, numberWastes, stop);
    system("pause");
}