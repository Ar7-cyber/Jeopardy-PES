#ifndef JEOPARDY_H
#define JEOPARDY_H

#define TIME_LIMIT 10
#define MIN_SCORE_TO_ADVANCE 9
#define PENALTY_SCORE 10
#define MAX_ROUNDS 3
#define MAX_NAME_LEN 50

// Player Queue Node
typedef struct Player {
    char name[MAX_NAME_LEN];
    int score;
    int active;
    struct Player *next;
} Player;

// Question Linked List Node
typedef struct Question {
    char text[256];
    char answer[100];
    int points;
    struct Question *next;
} Question;

// Queue functions
Player* enqueuePlayer(Player *rear, const char *name);
Player* dequeuePlayer(Player **front);
void freePlayers(Player *front);

// Linked list functions
Question* addQuestion(Question *head, const char *text, const char *answer, int points);
Question* removeQuestion(Question *head, Question *target);
void freeQuestions(Question *head);

// Game functions
void startGame(Player *front, int playerCount);
void playRound(Player *front, int playerCount, int round);
void displayScoreboard(Player *front);
Question* loadQuestions(int round);

#endif