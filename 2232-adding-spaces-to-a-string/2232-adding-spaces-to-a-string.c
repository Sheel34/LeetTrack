char* addSpaces(char* s, int* spaces, int spacesSize) {

    int len = strlen (s);
    int newLen = len + spacesSize; // Calculate the length of the new string
    char* result = (char*) malloc ((newLen + 1) * sizeof (char)); // Allocate memory for result
    int resIndex = 0, start = 0;

    for (int i = 0; i < spacesSize; i++) {
        int space = spaces [i]; // Copy part of the original string
        strncpy (result + resIndex, s + start, space - start);
        resIndex += space - start;
        result [resIndex++] = ' '; // Add a space
        start = space;
    }
    strcpy (result + resIndex, s + start); // Copy the remaining part
    return result; // Caller should free this memory
}