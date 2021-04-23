//
//  footballQuery.c
//  hw0302
//
//  Created by michaelleong on 17/04/2021.
//

#include "footballQuery.h"
#include <string.h>

//returns -1 when there is a problem
int footballQuery() {
    char fileName[129] = {0};
    FILE *pFile = NULL;
    int choice = 0;
    
    printf("Please open a season record: ");
    fgets(fileName, 129, stdin);
    
    if(fileName[strlen(fileName) - 1] == '\n') {
        fileName[strlen(fileName) - 1] = 0;
    } else {
        //clear the buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    
    //check the extension if .csv
    char *extension = &fileName[strlen(fileName) - 4];
    if(strcmp(extension, ".csv") != 0) {
        printf("file does not have .csv extension\n");
        return -1;
    }
    
    printf("ext: %s\n", extension);
    
    //open the file
    if((pFile = fopen(fileName, "r")) == NULL) {
        printf("file does not exist\n");
        return -1;
    }
    
    //380 games in one season
    gameInfo gameInfoList[380];
    //initialize the list
    initializeGameListInfo(gameInfoList, sizeof(gameInfoList)/sizeof(gameInfoList[0]));
    
    //20 teams in premier league
    teamStats teamStatsList[20];
    //initialize the list
    initializeTeamStatsList(teamStatsList, sizeof(teamStatsList)/sizeof(teamStatsList[0]));
    
    int index = 0;
    int teamListIndex = 0;
    int gameIndex = 0;
    
    char heading[129] = {0};
    fgets(heading, 129, pFile);
    printf("heading: %s\n", heading);
    
    while(!feof(pFile)) {
        readUntilChar(pFile, gameInfoList[gameIndex].date, ',');
        readUntilChar(pFile, gameInfoList[gameIndex].homeTeam, ',');
        readUntilChar(pFile, gameInfoList[gameIndex].awayTeam, ',');
        fscanf(pFile, "%d,%d,%c,%d,%d,%c,", &gameInfoList[gameIndex].homeScoreFT, &gameInfoList[gameIndex].awayScoreFT, &gameInfoList[gameIndex].fullTimeResult, &gameInfoList[gameIndex].homeScoreHT, &gameInfoList[gameIndex].awayScoreHT, &gameInfoList[gameIndex].halfTimeResult);
        readUntilChar(pFile, gameInfoList[gameIndex].referee, ',');
        
        //set the other data in game info
        
        //read until end of the line hehe
        //need to deal with red cards
        char useless[129] = {0};
        fgets(useless, 129, pFile);
        
        //search for home team in list else create a new record
        index = searchNameTeamList(gameInfoList[gameIndex].homeTeam, teamStatsList, sizeof(teamStatsList)/sizeof(teamStatsList[0]));
        if(index == -1) {
            index = teamListIndex++;
        }
        strncpy(teamStatsList[index].name, gameInfoList[gameIndex].homeTeam, strlen(gameInfoList[gameIndex].homeTeam));
        
        
        
        gameIndex++;
    }
    
    while(choice != 8) {
        printf("1) Who is the winner in this season?\n");
        printf("2) Which team gets the most scores?\n");
        printf("3) Which team gets the most red cards?\n");
        printf("4) Which team wins the most games at home?\n");
        printf("5) Which team wins the most games away from home?\n");
        printf("6) Which game has the most scoring gap?\n");
        printf("7) Team information.\n");
        printf("8) Exit\n");
        
        printf("Choice (1-7, 8:exit): ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                //winner of the season
                for(size_t i = 0; i < sizeof(gameInfoList)/sizeof(gameInfoList[0]); i++) {
                    //do smtg
                }
                break;
                
            case 2:
                
                
                break;
                
            default:
                break;
        }
    }
    
    
    fclose(pFile);
    return 1;
}

//search for name in team list
int searchNameTeamList(char *name, teamStats teamStatsList[], size_t teamListSize) {
    for(size_t i = 0; i < teamListSize; i++) {
        if(strcmp(name, teamStatsList[i].name) == 0) {
            return (int)i; //returns the index of the list
        }
    }
    
    return -1; //return -1 if not found
}

int readUntilChar(FILE *pFile, char *result, char stopChar) {
    while(!feof(pFile)) {
        char temp = fgetc(pFile);
        if(temp != stopChar && temp != 0) {
            strncat(result, &temp, 1);
        } else {
            return 1;
        }
    }
    
    return 1;
}

void initializeGameListInfo(gameInfo gameInfoList[], size_t size) {
    for(size_t i = 0; i < size; i++) {
        memset(gameInfoList[i].date, 0, sizeof(gameInfoList[i].date)/sizeof(gameInfoList[i].date[0]));
        memset(gameInfoList[i].awayTeam, 0, sizeof(gameInfoList[i].awayTeam)/sizeof(gameInfoList[i].awayTeam[0]));
        memset(gameInfoList[i].homeTeam, 0, sizeof(gameInfoList[i].homeTeam)/sizeof(gameInfoList[i].homeTeam[0]));
        gameInfoList[i].awayScoreFT = 0;
        gameInfoList[i].awayScoreHT = 0;
        gameInfoList[i].homeScoreFT = 0;
        gameInfoList[i].homeScoreHT = 0;
        gameInfoList[i].fullTimeResult = '0';
        gameInfoList[i].halfTimeResult = '0';
        memset(gameInfoList[i].winner, 0, sizeof(gameInfoList[i].winner)/sizeof(gameInfoList[i].winner[0]));
        memset(gameInfoList[i].loser, 0, sizeof(gameInfoList[i].loser)/sizeof(gameInfoList[i].loser[0]));
        memset(gameInfoList[i].referee, 0, sizeof(gameInfoList[i].referee)/sizeof(gameInfoList[i].referee[0]));
    }
}

void initializeTeamStatsList(teamStats teamStatsList[], size_t size) {
    for(size_t i = 0; i < size; i++) {
        memset(teamStatsList[i].name, 0, sizeof(teamStatsList[i].name)/sizeof(teamStatsList[i].name[0]));
        teamStatsList[i].awayWins = 0;
        teamStatsList[i].awayLoses = 0;
        teamStatsList[i].awayDraws = 0;
        teamStatsList[i].homeWins = 0;
        teamStatsList[i].homeLoses = 0;
        teamStatsList[i].homeDraws = 0;
        teamStatsList[i].totalScores = 0;
        teamStatsList[i].points = 0;
        teamStatsList[i].goalScores = 0;
        teamStatsList[i].goalAgainst = 0;
    }
}
