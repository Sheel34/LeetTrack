int maxDifference(char* s) {
    int x[26];
    x[0] = 0;
    for (int i = 0; i < strlen(s); i++) {
        x[(int) (s[i] - 'a')]++;
    }
    int maxo=0,mine=100;
    for(int i=0;i<26;i++){
            if(x[i]==0){
                continue;
            }
            if(x[i]%2==1){
                maxo=x[i]>maxo?x[i]:maxo;
            }
            if(x[i]%2==0){
                mine=(x[i]<mine)?x[i]:mine;
            }
        }
    return maxo - mine;
}