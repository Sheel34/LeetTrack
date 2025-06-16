int maximumDifference(int* nums, int numsSize) {
    int n=numsSize;
        int maxD=-1, xMinL=1e9, xMaxR=-1;
        for(int l=0, r=n-1; l<r; l++){
            xMinL=fmin(nums[l], xMinL);
            while(l<r && nums[l+1]>nums[l]){
                l++;
                maxD=fmax(maxD, nums[l]-xMinL);
            }
            xMaxR=fmax(nums[r], xMaxR);
            while(l<r && nums[r-1]<nums[r]){
                r--;
                maxD=fmax(maxD, nums[r]-xMaxR);
            }
            maxD=fmax(maxD, xMaxR-xMinL);
        } 
        return maxD==0?-1:maxD;
}