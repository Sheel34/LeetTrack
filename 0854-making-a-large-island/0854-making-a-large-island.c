#define WATER 0
#define LAND 1

typedef struct {
    int r;
    int c;
} point_t;

int exploreIsland(int r, int c, int island_id, int **grid, int nrow, int ncol);

int largestIsland(int** grid, int gridSize, int* gridColSize) {
    int max_island = gridSize * (*gridColSize);
    int *islands = (int *) malloc ((max_island + 2) * sizeof (int));
    if (islands == NULL) {
        exit (EXIT_FAILURE);
    }
    memset (islands, 0, max_island + 2);

    int island_id = 2;

    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < (*gridColSize); ++c) {
            if (grid [r] [c] == LAND) {
                islands [island_id] = exploreIsland (r, c, island_id, grid, gridSize, *gridColSize);
                ++island_id;
            }
        }
    }

    if (island_id == 2) {
        free (islands);
        return 1;
    }

    if (island_id == 3) {
        int total = gridSize * (*gridColSize);
        int the_land_size = islands [2] + 1;
        int num_lands = fmin (total, the_land_size);
        free (islands);
        return num_lands;
    }

    int max_size = 1;
    int directions [4] [2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < (*gridColSize); ++c) {
            if (grid [r] [c] != WATER) {
                continue;
            }

            int seen [island_id];
            memset (seen, 0, sizeof (seen));
            int curr_size = 1;

            for (int d = 0; d < 4; ++d) {
                int rr = r + directions [d] [0];
                int cc = c + directions [d] [1];

                if (rr < 0 || rr >= gridSize || cc < 0 || cc >= (*gridColSize) || grid [rr] [cc] <= LAND) {
                    continue;
                }

                int id = grid [rr] [cc];
                if (seen [id] == 0) {
                    curr_size += islands [id];
                    seen [id] = 1;
                }
            }

            max_size = fmax (max_size, curr_size);
        }
    }

    free (islands);

    return max_size;
}

int exploreIsland (int r, int c, int island_id, int **grid, int nrow, int ncol) {

    int land_size = 0;
    int directions [4] [2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    point_t queue [nrow * ncol];
    int front = 0, rear = 0;

    queue [rear++] = (point_t) {r, c};
    grid [r] [c] = island_id;

    while (front < rear) {
        point_t p = queue [front++];
        ++land_size;

        for (int d = 0; d < 4; ++d) {
            int rr = p.r + directions [d] [0];
            int cc = p.c + directions [d] [1];

            if (rr < 0 || rr >= nrow || cc < 0 || cc >= ncol || grid [rr] [cc] != LAND) {
                continue;
            }

            grid [rr] [cc] = island_id;
            queue [rear++] = (point_t) {rr, cc};
        }
    }
    return land_size;
}