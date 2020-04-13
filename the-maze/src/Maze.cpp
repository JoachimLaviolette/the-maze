#include "../include/Maze.h"
#include "../include/Constants.h"

void createMaze(Grid* grid) {
	initializeGrid(grid);
	buildMaze(grid);
}

void drawMaze(sf::RenderWindow* window, Grid grid) {
	drawGrid(window, grid);
}

void buildMaze(Grid* grid) {
	Cell currentCell = getCellAt(*grid, 0, 0);
	Cell neighborCell;

	do {
		int testedDir[4] = { 0, 0, 0, 0 };
		int randDir = -1;
		neighborCell.x = -1;
		neighborCell.y = -1; 

		currentCell = getCellAt(*grid, currentCell.x, currentCell.y);

		// First, mark the current cell as visited
		setCellValue(*grid, currentCell, 1);

		printf("\nCurrent cell [%d][%d]\n", currentCell.x, currentCell.y);
		printf("Former cell [%d][%d]\n", currentCell.formerCell->x, currentCell.formerCell->y);
		
		// Then, try to get a neighbor cell
		while ((neighborCell.x == -1 && neighborCell.y == -1) && !isAllDirectionsTested(testedDir)) {
			// Compute a random direction between 0 and 3 (see Constants.h)
			do { randDir = rand() % 4; } while (isDirectionTested(testedDir, randDir));

			// Mark the direction as tested
			testedDir[randDir] = 1;

			// Try to get the neighbor cell in the direction
			tryGetNeighborCell(*grid, currentCell, neighborCell, randDir);
			printf("Neighbor cell [%d][%d]\n", neighborCell.x, neighborCell.y);
		}
		
		// If no visitable neighbor cell found, go back to the former cell
		if (neighborCell.x == -1 && neighborCell.y == -1) {
			printf("Rollbacking\n");
			printf("Trying to rollback to cell at [%d][%d]...\n", currentCell.formerCell->x, currentCell.formerCell->y);
			currentCell = *currentCell.formerCell;
			printf("Rollbacked\n");
		}
		else {
			// Destroy the wall between the current cell and the neighbor cell found 
			if (randDir == RIGHT) destroyWallAt(0, grid, neighborCell.x, neighborCell.y);
			else if (randDir == LEFT) destroyWallAt(0, grid, currentCell.x, currentCell.y);
			else if (randDir == UP) destroyWallAt(1, grid, currentCell.x, currentCell.y);
			else destroyWallAt(1, grid, neighborCell.x, neighborCell.y);

			// And set the new current cell
			setCellFormerCell(*grid, &neighborCell, currentCell);
			currentCell = neighborCell;
			// printf("(%d, %d)\n", currentCell.formerCell->x, currentCell.formerCell->y);
			// printf("New neighbor cell 444 former cell [%d][%d]\n", currentCellFormerCell.x, currentCellFormerCell.y);
		}
		printf("NEXT\n");
	} while (!isAllCellsVisited(grid));
}

int isAllDirectionsTested(int testedDir[4]) {
	for (int x = 0; x < 4; ++x)
		if (testedDir[x] == 0) return 0;

	return 1;
}

int isDirectionTested(int testedDir[4], int dir) {
	return testedDir[dir] == 1;
}