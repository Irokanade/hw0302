//
//  footballQuery.h
//  hw0302
//
//  Created by michaelleong on 17/04/2021.
//

#ifndef footballQuery_h
#define footballQuery_h

#include <stdio.h>

typedef struct _gameInfo {
    char date[11]; //xxxx-xx-xx 10 chars and null character
    char awayTeam[129]; //away team name
    char homeTeam[129]; // home team name
    int awayScoreFT; //fulll time score
    int awayScoreHT; //half time score
    int homeScoreFT;
    int homeScoreHT;
    char fullTimeResult; //full time result
    char halfTimeResult; //half time result
    char winner[129]; //if draw is false then assign winner
    char loser[129]; //if draw is flase then assign loser
    char referee[129]; //referee
} gameInfo;
    
typedef struct _teamStats {
    char name[129];
    int awayWins;
    int awayLoses;
    int awayDraws;
    int homeWins;
    int homeLoses;
    int homeDraws;
    int totalScores;
    int points;
    int goalScores; //total scores they scored
    int goalAgainst; //total score they took from opponent
} teamStats;


int footballQuery(void);
int searchNameTeamList(char *name, teamStats teamStatsList[], size_t teamListSize);
int readUntilChar(FILE *pFile, char *result, char stopChar);
void initializeGameListInfo(gameInfo gameInfoList[], size_t size);
void initializeTeamStatsList(teamStats teamStatsList[], size_t size);

#endif /* footballQuery_h */
