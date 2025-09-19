typedef struct {
    int rows;
    char **keys;
    int *values;
    int size;
    int capacity;
} Spreadsheet;


Spreadsheet* spreadsheetCreate (int rows) {
    Spreadsheet* obj = malloc (sizeof (Spreadsheet));
    obj -> rows = rows;
    obj -> size = 0;
    obj -> capacity = 100;
    obj -> keys = malloc (sizeof (char*) * obj -> capacity);
    obj -> values = malloc (sizeof (int) * obj -> capacity);
    return obj;
}

void spreadsheetSetCell (Spreadsheet* obj, char* cell, int value) {
    for (int i = 0; i < obj -> size; ++i) {
        if (strcmp (obj -> keys [i], cell) == 0) {
            obj -> values [i] = value;
            return;
        }
    }
    if (obj -> size == obj -> capacity) {
        obj -> capacity *= 2;
        obj -> keys = realloc (obj -> keys, sizeof (char*) * obj -> capacity);
        obj -> values = realloc (obj -> values, sizeof (int) * obj -> capacity);
    }
    obj -> keys [obj -> size] = strdup (cell);
    obj -> values [obj -> size] = value;
    obj -> size++;
}

void spreadsheetResetCell (Spreadsheet* obj, char* cell) {
    for (int i = 0; i < obj -> size; ++i) {
        if (strcmp (obj -> keys [i], cell) == 0) {
            free (obj -> keys [i]);
            for (int j = i; j < obj -> size - 1; ++j) {
                obj -> keys [j] = obj -> keys [j + 1];
                obj -> values [j] = obj -> values [j + 1];
            }
            obj -> size--;
            return;
        }
    }
}

int spreadsheetGetValue (Spreadsheet* obj, char* formula) {
    formula++;
    char *plus = strchr (formula, '+');
    *plus = '\0';
    char *a = formula;
    char *b = plus + 1;
    int getVal (char* str) {
        for (int i = 0; str [i]; i++) {
            if (!isdigit (str [i])) {
                for (int j = 0; j < obj -> size; ++j) {
                    if (strcmp (obj -> keys [j], str) == 0)
                        return obj -> values [j];
                }
                return 0;
            }
        }
        return atoi (str);
    }
    return getVal (a) + getVal (b);
}

void spreadsheetFree (Spreadsheet* obj) {
    for (int i = 0; i < obj -> size; ++i)
        free(obj -> keys [i]);
    free (obj -> keys);
    free (obj -> values);
    free (obj);
}

/**
 * Your Spreadsheet struct will be instantiated and called as such:
 * Spreadsheet* obj = spreadsheetCreate(rows);
 * spreadsheetSetCell(obj, cell, value);
 
 * spreadsheetResetCell(obj, cell);
 
 * int param_3 = spreadsheetGetValue(obj, formula);
 
 * spreadsheetFree(obj);
*/