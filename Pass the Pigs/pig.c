#include "names.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define SEED 2021

typedef enum { SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER } Position;
const Position pig[7] = { SIDE, SIDE, RAZORBACK, TROTTER, SNOUTER, JOWLER, JOWLER };

int main() {
    int players, finalplayers, roll, gameover;
    char word;
    unsigned int finalseed;
    int score[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    printf("How many players? "); //ask user how many players
    if (scanf("%d%c", &players, &word) != 2 || word != '\n') {
        fprintf(stderr, "Invalid number of players. Using 2 instead. \n");
        fprintf(stderr, "Invalid random seed. Using 2021 instead.\n");
        printf("Random seed: ");
        finalplayers = 2;
        finalseed = 2021;
    } else {
        if (players >= 2 && players <= 10) {
            finalplayers = players; //if use selectes betwenn 2 and 10 then use that4
            printf("Random seed: ");
            scanf("%u", &finalseed); //ask user for seed
            if (finalseed <= 0 || finalseed >= pow(2, sizeof(unsigned int) * 8) - 1) {
                finalseed = 2021;
                //do nothing
                //srand(finalseed);
            }
        } else {
            fprintf(stderr, "Invalid number of players. Using 2 instead. \n");
            printf("Random seed: ");
            scanf("%u", &finalseed);
            finalplayers = 2; //use 2 players and seed 2021 for invalid input and
            //finalseed = 2021; //set seed to 2021
        }
    }

    srand(finalseed);

    for (int i = 0; i < 300; i += 1) {
        if (gameover == 1) {
            break; //break out if player hits 100 points
        }

        for (int i = 0; i < finalplayers; i += 1) {
            if (gameover == 1) {
                break; //break out if player hits 100 points
            }
            printf("%s rolls the pig... ", names[i]);
            roll = TROTTER; //roll between number of 1-6
            while (pig[roll] == RAZORBACK || pig[roll] == TROTTER || pig[roll] == SNOUTER
                   || pig[roll] == JOWLER) //as long as they roll one of the following keep looping
            {
                roll = rand() % 7; //randomize roll again
                if (pig[roll] == SIDE) {
                    printf("pig lands on side ");
                    printf("\n");
                    break;
                }
                if (pig[roll] == RAZORBACK) {
                    printf("pig lands on back ");
                    score[i] += 10;
                }
                if (pig[roll] == TROTTER) {
                    printf("pig lands upright ");
                    score[i] += 10;
                }
                if (pig[roll] == SNOUTER) {
                    printf("pig lands on snout ");
                    score[i] += 15;
                }
                if (pig[roll] == JOWLER) {
                    printf("pig lands on ear ");
                    score[i] += 5;
                }
                if (score[i] >= 100) {
                    printf("\n%s wins with %d points!\n", names[i], score[i]);
                    gameover = 1;
                    break;
                }
            }
        }
    }
}
