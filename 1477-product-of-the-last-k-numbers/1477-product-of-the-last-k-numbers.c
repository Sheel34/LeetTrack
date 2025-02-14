
# define INITIAL_CAPACITY (10)

typedef struct {
    int* nums;
    int capacity;
    int size;
} ProductOfNumbers;


ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* newObj = (ProductOfNumbers*) malloc (sizeof (ProductOfNumbers));
    if (newObj != NULL) {
        newObj -> capacity = INITIAL_CAPACITY;
        newObj -> size = 0;
        newObj -> nums = (int*) malloc (sizeof (int) * newObj -> capacity);
        if (newObj -> nums == NULL) {
            free (newObj);
            newObj = NULL;
        }
    }
    return (newObj);
}

void productOfNumbersAdd (ProductOfNumbers* obj, int num) {
    int *newArr;
    size_t i = 0;
    if (obj != NULL) {
        if (obj -> size < obj -> capacity)
            obj -> nums [obj -> size++] = num;
        else {
            obj -> capacity *= 2;
            newArr = (int*) malloc (sizeof (int) * obj -> capacity);
            if (newArr != NULL) {
                for (i = 0; i < obj -> size; i++)
                    newArr [i] = obj -> nums [i];
                free (obj -> nums);
                obj -> nums = newArr;
                obj -> nums [obj -> size++] = num;
            }
        }
    }
}

int productOfNumbersGetProduct (ProductOfNumbers* obj, int k) {
    int retVal = -1;
    size_t i = 0;
    if ((obj != NULL) && (k <= obj -> size)) {
        retVal = 1;
        for (i = 0; i < k; i++)
            retVal *= obj -> nums [obj -> size - 1 - i];
    }
    return (retVal);
}

void productOfNumbersFree (ProductOfNumbers* obj) {
    free (obj);
}

/**
 * Your ProductOfNumbers struct will be instantiated and called as such:
 * ProductOfNumbers* obj = productOfNumbersCreate();
 * productOfNumbersAdd(obj, num);
 
 * int param_2 = productOfNumbersGetProduct(obj, k);
 
 * productOfNumbersFree(obj);
*/