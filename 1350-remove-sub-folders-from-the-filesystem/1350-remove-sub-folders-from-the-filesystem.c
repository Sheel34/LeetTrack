/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int compare (const void *a, const void *b) {
    return strlen (*(const char **) a) - strlen (*(const char **) b);
}

char** removeSubfolders (char** folder, int folderSize, int* returnSize) {
    qsort (folder, folderSize, sizeof (char *), compare);
    char **result = (char **) malloc (folderSize * sizeof (char *));
    int resultCount = 0;
    for (int i = 0; i < folderSize; i++) {
        char *dir = folder[i];
        int isSubfolder = 0;
        int dirLen = strlen (dir);
        for (int j = 0; j < resultCount; j++) {
            int resLen = strlen (result [j]);
            if (resLen < dirLen && strncmp (result [j], dir, resLen) == 0 && dir [resLen] == '/') {
                isSubfolder = 1;
                break;
            }
        }
        if (!isSubfolder)
            result [resultCount++] = dir;
    }
    *returnSize = resultCount;
    return result;
}