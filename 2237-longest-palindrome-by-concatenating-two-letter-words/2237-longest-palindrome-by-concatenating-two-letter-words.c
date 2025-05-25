int longestPalindrome(char** words, int wordsSize) {
    int freq[26][26] = {0};
    int max = 0;
    for (int i = 0; i < wordsSize; i++) {
        if (freq[words[i][1] - 'a'][words[i][0] - 'a'] != 0) {
            freq[words[i][1] - 'a'][words[i][0] - 'a']--;
            max += 4;
        }
        else {
            freq[words[i][0] - 'a'][words[i][1] - 'a']++;
        }
    }
    for (int i = 0; i < 26; i++) {
        if (freq[i][i]) {
            max += 2;
            break;
        }
    }
    return max;
}