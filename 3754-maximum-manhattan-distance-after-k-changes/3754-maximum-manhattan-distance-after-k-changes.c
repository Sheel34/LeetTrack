int maxDistance(char* str, int chanceCnt) {
    static const char dirCombinations[][2] = {
		{'N', 'E'},
		{'N', 'W'},
		{'S', 'E'},
		{'S', 'W'}
	};

	int maxDist = 0;
	for (
		int dirCombinationIdx = 0;
		dirCombinationIdx < sizeof (dirCombinations) / sizeof (dirCombinations[0]);
		dirCombinationIdx += 1
	){
		bool charSet[1 << (CHAR_BIT - 1)];
		memset(&charSet, 0, sizeof (charSet));
		for (
			int dirIdx = 0;
			dirIdx < sizeof (dirCombinations[dirCombinationIdx]) / sizeof (dirCombinations[dirCombinationIdx][0]);
			dirIdx += 1
		){
			charSet[dirCombinations[dirCombinationIdx][dirIdx]] = true;
		}

		int curDist = 0;

		int curChanceCnt = chanceCnt;
		for (int i = 0; str[i] != '\0'; i += 1){
			if (!charSet[str[i]] && !(curChanceCnt >= 1)){
				curDist -= 1;
				continue;
			}

			if (!charSet[str[i]]){
				curChanceCnt -= 1;
			}
			curDist += 1;
			if (curDist > maxDist){
				maxDist = curDist;
			}
		}
	}
	return maxDist;
}