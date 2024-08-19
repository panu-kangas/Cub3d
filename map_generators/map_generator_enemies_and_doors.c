#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WALL '1'
#define SPACE '0'
#define START 'N'
#define FINISH 'F'
#define ENEMY 'A'
#define DOOR 'D'
#define MARKET_SQUARE_SIZE 3

// Function to initialize the maze with walls
void initializeMaze(char **maze, int x, int y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (i == 0 || i == y - 1 || j == 0 || j == x - 1) {
                maze[i][j] = WALL; // Surround the maze with walls
            } else {
                maze[i][j] = WALL; // Fill the maze with walls initially
            }
        }
    }
}

// Function to create random walkable spaces
void createSpaces(char **maze, int x, int y) {
    for (int i = 1; i < y - 1; i += 2) {
        for (int j = 1; j < x - 1; j += 2) {
            maze[i][j] = SPACE; // Create space

            // Randomly remove adjacent walls to create paths
            if (rand() % 2) {
                if (i + 1 < y - 1) maze[i + 1][j] = SPACE;
            } else {
                if (j + 1 < x - 1) maze[i][j + 1] = SPACE;
            }
        }
    }
}

// Function to create random market squares within the maze
void createMarketSquares(char **maze, int x, int y, int numberOfSquares) {
    for (int i = 0; i < numberOfSquares; i++) {
        int squareX, squareY;

        do {
            squareX = rand() % (x - MARKET_SQUARE_SIZE - 2) + 1;
            squareY = rand() % (y - MARKET_SQUARE_SIZE - 2) + 1;
        } while (maze[squareY][squareX] == SPACE); // Ensure it doesn't overlap with existing paths

        // Create a 3x3 market square
        for (int row = 0; row < MARKET_SQUARE_SIZE; row++) {
            for (int col = 0; col < MARKET_SQUARE_SIZE; col++) {
                maze[squareY + row][squareX + col] = SPACE;
            }
        }
    }
}

// Function to place enemies randomly on the map
void placeEnemies(char **maze, int x, int y, int numberOfEnemies) {
    int count = 0;
    while (count < numberOfEnemies) {
        int randX = rand() % (x - 2) + 1;
        int randY = rand() % (y - 2) + 1;

        if (maze[randY][randX] == SPACE) {
            maze[randY][randX] = ENEMY;
            count++;
        }
    }
}

// Function to place doors randomly on the map
void placeDoors(char **maze, int x, int y, int numberOfDoors) {
    int count = 0;
    while (count < numberOfDoors) {
        int randX = rand() % (x - 2) + 1;
        int randY = rand() % (y - 2) + 1;

        if (maze[randY][randX] == SPACE) {
            maze[randY][randX] = DOOR;
            count++;
        }
    }
}

// Function to set start and finish points
void setStartAndFinish(char **maze, int x, int y) {
    maze[1][1] = START; // Top-left inside the maze
    maze[y - 2][x - 2] = FINISH; // Bottom-right inside the maze
}

// DFS function to check if a valid path exists from (x, y) to (finishX, finishY)
int isValidPath(char **maze, int x, int y, int finishX, int finishY, int rows, int cols) {
    // Base cases: check for boundaries and walls
    if (x < 0 || x >= cols || y < 0 || y >= rows || maze[y][x] == WALL || maze[y][x] == 'V') {
        return 0;
    }

    // If we've reached the finish point
    if (x == finishX && y == finishY) {
        return 1;
    }

    // Mark the cell as visited
    maze[y][x] = 'V';  // Mark as visited to avoid cycles

    // Explore in all 4 directions: up, down, left, right
    if (isValidPath(maze, x + 1, y, finishX, finishY, rows, cols)) return 1;
    if (isValidPath(maze, x - 1, y, finishX, finishY, rows, cols)) return 1;
    if (isValidPath(maze, x, y + 1, finishX, finishY, rows, cols)) return 1;
    if (isValidPath(maze, x, y - 1, finishX, finishY, rows, cols)) return 1;

    return 0;
}

// Function to reset visited cells marked by DFS to walkable spaces
void resetVisitedCells(char **maze, int x, int y) {
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (maze[i][j] == 'V') {
                maze[i][j] = SPACE;
            }
        }
    }
}

// Function to display the maze
void displayMazeToFile(char **maze, int x, int y, const char *filename) {
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    // Write the maze to the file
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            fprintf(file, "%c", maze[i][j]);
        }
        fprintf(file, "\n");
    }

    // Close the file
    fclose(file);
}

int main() {
    int x, y, numberOfMarketSquares, numberOfEnemies;
	int	numberOfDoors;
	char *file;
    // User input for maze size
    printf("Enter the size of the maze (x y): ");
    scanf("%d %d", &x, &y);

    // User input for the number of market squares
    printf("Enter the number of market squares: ");
    scanf("%d", &numberOfMarketSquares);

    // User input for the number of enemies
    printf("Enter the number of enemies: ");
    scanf("%d", &numberOfEnemies);

	printf("Enter the filename: ");
    scanf("%s", file);

    // User input for the number of doors
    //printf("Enter the number of doors: ");
    //scanf("%d", &numberOfDoors);

    // Ensure minimum size of the maze (5x5)
    if (x < 5) x = 5;
    if (y < 5) y = 5;

    // Allocate memory for the maze
    char **maze = (char **)malloc(y * sizeof(char *));
    for (int i = 0; i < y; i++) {
        maze[i] = (char *)malloc(x * sizeof(char));
    }

    // Seed the random number generator
    srand(time(NULL));

    int startX = 1, startY = 1;
    int finishX = x - 2, finishY = y - 2;

    int pathExists = 0;

    // Generate maze and ensure a valid path exists
    while (!pathExists) {
        // Initialize maze with walls
        initializeMaze(maze, x, y);

        // Create spaces and paths
        createSpaces(maze, x, y);

        // Create multiple market squares in random positions
        createMarketSquares(maze, x, y, numberOfMarketSquares);

        // Set start (N) and finish (F) points
        setStartAndFinish(maze, x, y);

        // Check if a valid path exists using DFS
        pathExists = isValidPath(maze, startX, startY, finishX, finishY, y, x);

        // Reset visited cells for the next check
        resetVisitedCells(maze, x, y);
    }

    // Place enemies on the map
    placeEnemies(maze, x, y, numberOfEnemies);

    // Place doors on the map
    //placeDoors(maze, x, y, numberOfDoors);

    // Display the valid maze
    displayMazeToFile(maze, x, y, file);

    // Free allocated memory
    for (int i = 0; i < y; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
