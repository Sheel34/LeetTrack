typedef unsigned char byte;

#define MOD 1000000007

inline byte calc(bool op,byte color){
    if(op) return (color+1)%3;
    return (color+2)%3;
}

bool check(byte mask1, byte mask2, int m){
    m--;
    byte color1=mask1>>m,color2=mask2>>m;
    if(color1==color2) return false;
    while(m--){
        color1=calc((mask1>>m)&1,color1);
        color2=calc((mask2>>m)&1,color2);
        if(color1==color2) return false;
    }
    return true;
}


int colorTheGrid(int m, int n) {
    byte total=3<<(m-1);
    bool valid[total][total];
    int *dp_prev = malloc(sizeof(int) * total);
    int *dp_next = malloc(sizeof(int) * total);
    for(int i=0;i<total;i++){
        dp_prev[i]=1;
        dp_next[i]=0;
        for(int j=0;j<total;j++){
            valid[i][j]=check(i,j,m);
        }
    }
    for(int k=1;k<n;k++){
        for(int i=0;i<total;i++){
            dp_next[i]=0;
            for(int j=0;j<total;j++){
                if(valid[i][j]) {
                    dp_next[i]+=dp_prev[j];
                    if(dp_next[i]>MOD) dp_next[i]-=MOD;
                }
            }
        }
        int* temp=dp_next;
        dp_next=dp_prev;
        dp_prev=temp;
    }
    int ans=0;
    for(int i=0;i<total;i++){
        ans+=dp_prev[i];
        if(ans>MOD) ans-=MOD;
    }
    free(dp_prev);
    free(dp_next);
    return ans;
}