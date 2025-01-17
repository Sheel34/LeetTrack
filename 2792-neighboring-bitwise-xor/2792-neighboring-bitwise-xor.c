bool doesValidArrayExist (int* derived, int derivedSize) {  
    int org [derivedSize];

    for (int i = 1; i < derivedSize; i++) {
        org [i] = derived [i - 1] ^ org [i - 1];
    }

    for (int i = 0; i < derivedSize; i++) {
        int index = (i + 1) % derivedSize;
        if (derived [i] != (org [i] ^ org [index])) return false;
    }
    return true;
}