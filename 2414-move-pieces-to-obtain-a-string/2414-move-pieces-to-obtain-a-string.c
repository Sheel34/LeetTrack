bool canChange(char* start, char* target) {
    
    const int n = strlen (start);
    for (register int i = 0, j = 0; i < n || j < n ; i++, j++) {

        while(i < n && start [i] == '_') i++;
        while(j < n && target [j] == '_') j++;

        char c = start [i];
        if (c != target [j]) return 0;
        if (c == 'L' && i < j) return 0;
        if (c == 'R' && i > j) return 0;
    }

    return 1;
}