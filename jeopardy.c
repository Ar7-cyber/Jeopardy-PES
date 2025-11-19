#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeopardy.h"

// Queue functions
Player* enqueuePlayer(Player *rear, const char *name) {
    Player *newPlayer = malloc(sizeof(Player));
    if (!newPlayer) return rear;
    strcpy(newPlayer->name, name);
    newPlayer->score = 0;
    newPlayer->active = 1;
    newPlayer->next = NULL;
    if (rear) rear->next = newPlayer;
    return newPlayer;
}

Player* dequeuePlayer(Player **front) {
    if (!*front) return NULL;
    Player *temp = *front;
    *front = (*front)->next;
    temp->next = NULL;
    return temp;
}

void freePlayers(Player *front) {
    while (front) {
        Player *temp = front;
        front = front->next;
        free(temp);
    }
}

// Linked list functions
Question* addQuestion(Question *head, const char *text, const char *answer, int points) {
    Question *newQ = malloc(sizeof(Question));
    if (!newQ) return head;
    strcpy(newQ->text, text);
    strcpy(newQ->answer, answer);
    newQ->points = points;
    newQ->next = head;
    return newQ;
}

Question* removeQuestion(Question *head, Question *target) {
    if (!head || !target) return head;
    if (head == target) {
        Question *next = head->next;
        free(head);
        return next;
    }
    Question *prev = head;
    while (prev->next && prev->next != target) prev = prev->next;
    if (prev->next == target) {
        prev->next = target->next;
        free(target);
    }
    return head;
}

void freeQuestions(Question *head) {
    while (head) {
        Question *temp = head;
        head = head->next;
        free(temp);
    }
}

// Game logic
Question* loadQuestions(int round) {
    Question *head = NULL;
    if (round == 1) {
        head = addQuestion(head, "Which city is PESU located in?", "Bengaluru\n", 10);
        head = addQuestion(head, "How many campuses does PESU have in Bengaluru?", "2\n", 10);
    } else if (round == 2) {
        head = addQuestion(head, "Which PES campus is in EC?", "PESU EC\n", 20);
        head = addQuestion(head, "What is the most economic food in PESU EC?", "Bun Samosa\n", 20);
    } else {
        head = addQuestion(head, "When was PESU established?", "1972\n", 30);
        head = addQuestion(head, "Which stream is popular at PESU?", "CSE\n", 30);
    }
    return head;
}

int checkAnswer(const char *userAnswer, const char *correctAnswer) {
    return strcasecmp(userAnswer, correctAnswer) == 0;
}

void playRound(Player *front, int playerCount, int round) {
    Question *questions = loadQuestions(round);
    Player *current = front;

    while (questions && current) {
        if (!current->active) {
            current = current->next ? current->next : front;
            continue;
        }

        Question *q = questions;
        printf("\n%s's turn:\n%s\n", current->name, q->text);

        time_t start = time(NULL);
        char answer[100];
        printf("Your answer: ");
        fgets(answer, sizeof(answer), stdin);
        time_t end = time(NULL);

        if (difftime(end, start) > TIME_LIMIT) {
            printf("Time's up! Penalty applied.\n");
            current->score -= PENALTY_SCORE;
        } else if (checkAnswer(answer, q->answer)) {
            printf("Correct!\n");
            current->score += q->points;
        } else {
            printf("Incorrect. Correct answer: %s\n", q->answer);
            current->score -= PENALTY_SCORE;
        }

        questions = removeQuestion(questions, q);
        current = current->next ? current->next : front;
    }

    freeQuestions(questions);
}

void startGame(Player *front, int playerCount) {
    for (int round = 1; round <= MAX_ROUNDS; round++) {
        printf("\nStarting Round %d\n", round);
        playRound(front, playerCount, round);

        Player *curr = front;
        while (curr) {
            if (curr->score < MIN_SCORE_TO_ADVANCE) {
                printf("%s did not qualify for next round.\n", curr->name);
                curr->active = 0;
            }
            curr = curr->next;
        }
    }
    displayScoreboard(front);
}

void displayScoreboard(Player *front) {
    printf("\nFinal Scoreboard:\n");
    Player *curr = front;
    while (curr) {
        printf("%s: %d\n", curr->name, curr->score);
        curr = curr->next;
    }
}