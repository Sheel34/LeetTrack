char* repeatLimitedString (char* s, int repeatLimit) {

    int hash [26] = {0}, size = 0;
    while (s [size]) {
        ++hash['z' - s [size]];
        ++size;
    }
  
    char* temp = s;
    for (int i = 0; i < 26; ++i) {
        while (hash [i]) {
            *temp = 'z' - i;
            ++temp;
            --hash[i];
        }
    }

    int repeated = 0, next = 0;
    for (int i = 1; i < size; ++i) {
        (s  [i - 1] == s [i]) ? (++repeated) : (repeated = 0);
        if (repeated == repeatLimit) {
        while (next < size && s [i] <= s [next]) ++next;
        
            char temp = s [i];
            s [i] = s [next];
            s [next] = temp;
        }
    }
    return s;
}