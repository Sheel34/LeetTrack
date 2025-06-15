int maxDiff(int num) {
    int arr[9], index=0;
    while(num>0){
        arr[index++] = num%10;
        num/=10;
    }
    int maxDigit;
    for(int i=index-1; i>=0; i--){
        if(arr[i]!=9){
            maxDigit = arr[i];
            break;
        }
    }
    int minDigit;
    for(int i=index-1; i>=0; i--){
        if(arr[i]>1){
            minDigit = arr[i];
            break;
        }
    }
    int smallest = 1;
    if(minDigit != arr[index-1]){
        smallest = 0;
    }
    int a=0, b=0;
    for(int i=index-1; i>=0; i--){
        if(arr[i] == maxDigit){
            a= a*10 + 9;
        }
        else{
            a = a*10 + arr[i];
        }
        if(arr[i] == minDigit){
            b= b*10 + smallest;
        }
        else{
            b = b*10 + arr[i];
        }
    }
    return a-b;
}