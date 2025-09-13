int maxFreqSum (char* s) {
    int freq [26], maxVowel = 0, maxConso = 0;
        for (char c = 0; c < strlen (s); c++) {
            int i = s [c] - 'a';
            freq [i]++;
            if (s [c] == 'a' || s [c] == 'e' || s [c] == 'i' || s [c] == 'o' || s [c] == 'u')
                maxVowel = fmax (maxVowel, freq [i]);
            else
                maxConso = fmax (maxConso, freq [i]);
        }
        return maxVowel + maxConso;
}