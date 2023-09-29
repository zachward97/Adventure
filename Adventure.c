#include <stdio.h>

// Function to display the game's introduction and get the player's name
void introduction(char playerName[]) {
    printf("Welcome to the Text Adventure Game!\n");
    printf("What's your name, adventurer? ");
    scanf("%s", playerName);
    printf("Hello, %s! You start with 10 health and 1 potion.\n", playerName);
    printf("Let's begin...\n\n");
}

// Function to display the game's menu and get the player's choice
int menu(int *playerPotions) {
    int choice;
    printf("Choose an option:\n");
    printf("1. Go left\n");
    printf("2. Go right\n");
    printf("3. Use potion\n");
    printf("4. Quit\n");
    printf("Potions: %d\n", *playerPotions);
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Function to handle the fight with a skeleton
void fightSkeleton(int *playerHealth, int *playerPotions, const char *enemyName) {
    int playerDamage = 4;
    int playerCurrentHealth = *playerHealth;
    int enemyHealth = 8;
    int enemyDamage = 2;
    int potionDrop = 1;

    printf("You encountered a menacing %s with %d health!\n", enemyName, enemyHealth);
    printf("You have %d health and %d potions.\n", playerCurrentHealth, *playerPotions);

    while (playerCurrentHealth > 0 && enemyHealth > 0) {
        int choice;
        printf("Choose your action:\n");
        printf("1. Attack with sword\n");
        printf("2. Use potion\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("You attacked the %s with your sword, dealing %d damage!\n", enemyName, playerDamage);
                enemyHealth -= playerDamage;
                break;
            case 2:
                if (*playerPotions > 0) {
                    printf("You used a potion and restored 2 health!\n");
                    playerCurrentHealth += 2;
                    (*playerPotions)--;
                } else {
                    printf("You have no potions left!\n");
                }
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }

        // Enemy's turn
        if (enemyHealth > 0) {
            printf("The %s attacks you, dealing %d damage!\n", enemyName, enemyDamage);
            playerCurrentHealth -= enemyDamage;
        }

        printf("Your health: %d, %s's health: %d\n", playerCurrentHealth, enemyName, enemyHealth);
    }

    if (playerCurrentHealth <= 0) {
        printf("You have been defeated by the %s! Game over.\n", enemyName);
    } else {
        printf("After a fierce battle, you defeated the %s!\n", enemyName);
        printf("The %s dropped %d potion(s) on death.\n", enemyName, potionDrop);
        *playerPotions += potionDrop;
        printf("You now have %d potions.\n", *playerPotions);
    }

    *playerHealth = playerCurrentHealth;
}

// Function to handle the chest encounter
void findChest(int *playerPotions, int *playerGold) {
    printf("You found a chest!\n");

    if (*playerPotions >= 4) {
        printf("Inside the chest, you found 1 gold!\n");
        (*playerGold)++;
        printf("You now have %d gold.\n", *playerGold);
    } else if (*playerPotions >= 3) {
        printf("Inside the chest, you found 1 potion and 1 gold!\n");
        (*playerPotions)++;
        (*playerGold)++;
        printf("You now have %d potions and %d gold.\n", *playerPotions, *playerGold);
    } else {
        int potionsToAdd = *playerPotions + 2 > 5 ? 5 - *playerPotions : 2;
        printf("Inside the chest, you found %d potions!\n", potionsToAdd);
        (*playerPotions) += potionsToAdd;
        printf("You now have %d potions.\n", *playerPotions);
    }
}


// Main game function
void playGame() {
    char playerName[50];
    int playerHealth = 10;
    int playerPotions = 1; // Start with 1 potion
    int choice;

    introduction(playerName);

    while (1) {
        choice = menu(&playerPotions);

        switch (choice) {
            case 1:
                printf("You went left and found a room with a chest!\n");
                printf("You opened the chest and found 2 potions!\n");
                playerPotions += 2;
                printf("You now have %d potions.\n", playerPotions);
                printf("You see a central door and an exit door.\n");
                int roomChoice;
                printf("Choose your action:\n");
                printf("1. Go through the central door\n");
                printf("2. Go through the exit door\n");
                scanf("%d", &roomChoice);
                if (roomChoice == 1) {
                    printf("You entered a mysterious central room...\n");
                    // Add more game logic for the central room here
                } else if (roomChoice == 2) {
                    printf("You decided to leave the room.\n");
                } else {
                    printf("Invalid choice. Please select a valid option.\n");
                }
                break;
            case 2:
                // Implement varying encounters here
                // For example, you can randomly determine the encounter or use a different enemyName
                if (rand() % 2 == 0) {
                    fightSkeleton(&playerHealth, &playerPotions, "skeleton");
                } else {
                    printf("You went right and found a peaceful garden. Nothing happens.\n");
                }
                if (playerHealth <= 0) {
                    printf("Game over, %s! Thanks for playing.\n", playerName);
                    return;
                }
                break;
            case 3:
                if (playerPotions > 0) {
                    printf("You used a potion and restored 2 health!\n");
                    playerHealth += 2;
                    playerPotions--;
                    printf("Your health: %d, Potions left: %d\n", playerHealth, playerPotions);
                } else {
                    printf("You have no potions left!\n");
                }
                break;

            case 4:
                printf("Thanks for playing, %s! Goodbye!\n", playerName);
                return;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }
}

int main() {
    playGame();
    return 0;
}
