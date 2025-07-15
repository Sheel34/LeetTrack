bool isVowel (char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

bool isValid (char* word) {
    bool hasVowel = false;
    bool hasConsonant = false;
    bool hasInvalidChar = false;
    for(int i = 0; word [i]; i++) {
        if(isalnum (word [i])) {
            if(isalpha (word [i])) {
                if(isVowel (word [i]))
                    hasVowel = true;
                else
                    hasConsonant = true;
            }
        } else {
            hasInvalidChar = true;
            break;
        }
    }
    return (strlen (word) > 2 && hasVowel && hasConsonant && !hasInvalidChar);
}