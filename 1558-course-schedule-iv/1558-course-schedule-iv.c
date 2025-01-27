/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
bool* checkIfPrerequisite (int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    *returnSize = queriesSize;
    bool* result = (bool*) malloc (queriesSize * sizeof (bool));

    bool** isPrerequisite = (bool**) malloc (numCourses * sizeof (bool*));
    
    for (int i = 0; i < numCourses; i++)
        isPrerequisite [i] = (bool*) calloc (numCourses, sizeof (bool));

    for (int i = 0; i < prerequisitesSize; i++) {
        int a = prerequisites [i] [0];
        int b = prerequisites [i] [1];
        isPrerequisite [a] [b] = true;
    }

    for (int k = 0; k < numCourses; k++)
        for (int i = 0; i < numCourses; i++)
            for (int j = 0; j < numCourses; j++)
                if (isPrerequisite [i] [k] && isPrerequisite [k] [j])
                    isPrerequisite [i] [j] = true;
            

    for (int i = 0; i < queriesSize; i++) {
        int u = queries [i] [0];
        int v = queries [i] [1];
        result [i] = isPrerequisite [u] [v];
    }

    for (int i = 0; i < numCourses; i++)
        free (isPrerequisite [i]);

    free (isPrerequisite);

    return result;

}