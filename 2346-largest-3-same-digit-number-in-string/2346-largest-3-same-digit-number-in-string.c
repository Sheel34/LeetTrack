bool contains (const char *haystack, const char *needle) {
    return strstr (haystack, needle) != NULL;
}

char* largestGoodInteger (char* num) {
    static char* patterns [] = {
        "999","888","777","666","555","444","333","222","111","000"
    };
    for (int i = 0; i < 10; i++) 
        if (contains (num, patterns [i])) 
            return patterns [i];
    return "";
}