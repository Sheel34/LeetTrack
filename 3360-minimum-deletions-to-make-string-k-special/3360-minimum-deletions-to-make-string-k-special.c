int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int minimumDeletions(char* word, int k) {
    int freq[26] = {};
    int len = strlen(word);
    for(int i=0; i<len; i++){   
        freq[word[i]-'a']++;   
    }

    int index = 0;
    for(int i=0; i<26; i++){
        if(freq[i] !=0 )
            freq[index++] = freq[i];
    }
    qsort(freq, index, sizeof(int), compare); 

    int minDelete = len;   
    int cumulative = 0;    
    for(int i=0; i<index; i++){
        int temp_min = cumulative; 
        for(int j=index-1; j>i; j--){
            if(freq[j] > freq[i]+k)
                temp_min += freq[j] - (freq[i]+k); 
            else break;
        }
        if(temp_min < minDelete)
            minDelete = temp_min;   
        cumulative+=freq[i];
    }
    return minDelete;
}