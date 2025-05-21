unsigned char row[25];
unsigned char col[25];

int test(char c,int n) {
    if(c=='r') {
        return row[n>>3]&(1<<(n&7));
    }
    else {
        return col[n>>3]&(1<<(n&7));
    }
}

void set(char c,int n) {
    if(c=='r') {
        row[n>>3]|=1<<(n&7);
    }
    else {
        col[n>>3]|=1<<(n&7);
    }
}


void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int i,j;
    int m=matrixSize;
    int n=matrixColSize[0];
    memset(row,0,sizeof(row));
    memset(col,0,sizeof(col));
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++) {
            if(matrix[i][j]==0) {
                set('r',i);
                set('c',j);
            }
        }
    }
    for(i=0;i<m;i++) {
        if(test('r',i)) {
            for(j=0;j<n;j++) {
                matrix[i][j]=0;
            }
        }
    }
    for(i=0;i<n;i++) {
        if(test('c',i)) {
            for(j=0;j<m;j++) {
                matrix[j][i]=0;
            }
        }
    }
}