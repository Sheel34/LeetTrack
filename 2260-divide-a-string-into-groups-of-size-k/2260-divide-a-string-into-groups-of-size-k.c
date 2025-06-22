/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#pragma GCC optimize ("O3", "unroll-loops")

char** divideString(char* s, int k, char fill, int* returnSize) {
    const int n=strlen(s), q=n/k, r=n%k;
    *returnSize=q+(r>0);
    char** ans=(char**)malloc(*returnSize*sizeof(char*));
    for(int i=0; i<q; i++){
        ans[i]=(char*)malloc(k+1);
        for(int j=0; j<k; j++)
            ans[i][j]=s[i*k+j];
        ans[i][k]='\0';
    }
    if (r>0){
        ans[q]=(char*)malloc(k+1);
        for(int i=q*k; i<n; i++)
            ans[q][i-q*k]=s[i];
        memset(ans[q]+n-k*q, fill, k-r);
        ans[q][k]='\0';
    }
    return ans;
}