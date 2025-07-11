int compare(const void* a, const void* b){
    return (*(int**)a)[0] - (*(int**)b)[0];
}

int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    qsort(meetings, meetingsSize, sizeof(meetings[0]), compare);
    
    long long roomAvailableAt[n];
    int roomUsedCount[n];
    for(int i=0; i<n; i++){
        roomAvailableAt[i] = 0;
        roomUsedCount[i] = 0;
    }

    for(int i=0; i<meetingsSize; i++){
        int start = meetings[i][0];
        int end = meetings[i][1];
        int duration = end - start;

        
        int min = 0;
        for(int j=0; j<n; j++){
            if(roomAvailableAt[j] <= start){
                min = j;
                break;
            }

            if(roomAvailableAt[j] < roomAvailableAt[min]){
                min = j;
            }
        }
        if(roomAvailableAt[min] > start){
            roomAvailableAt[min] += duration;
        }
        else{
            roomAvailableAt[min] = end;
        }
        roomUsedCount[min]++;
    }

    int most_used_room = 0;
    for(int i=0; i<n; i++){
        if(roomUsedCount[i] > roomUsedCount[most_used_room]){
            most_used_room = i;
        }
    }

    return most_used_room;
}