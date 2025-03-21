/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

 typedef struct item {
    struct item *next [26];
    bool is_end;
} item_t;

item_t trie;

void trie_init () {
    memset ((void *) &trie, 0, sizeof (trie));
}

void trie_insert (char *s) {
    item_t *hdr = &trie;
    for (int i = 0; s [i]; i++) {
        if (hdr -> next [s [i] - 'a'] == NULL)
            hdr -> next [s [i] - 'a'] = (item_t *) calloc (1, sizeof (item_t));
        hdr = hdr -> next [s [i] - 'a'];
    }
    hdr -> is_end = true;
}

bool trie_search (char *s) {
    item_t *hdr = &trie;
    for (int i = 0; s [i]; i++) {
        if (hdr -> next [s [i] - 'a'] == NULL)
            return false;
        hdr = hdr -> next [s [i] - 'a'];
    }
    return hdr->is_end;    
}

void _trie_release (item_t *trie) {
    if (trie) {
        for (int i = 0; i < 26; i++)
            _trie_release (trie -> next [i]);
        free (trie);
    }
}

void trie_release () {
    for (int i = 0; i < 26; i++)
        _trie_release (trie.next [i]);
}

char** findAllRecipes (char** recipes, int recipesSize, char*** ingredients, int ingredientsSize, int* ingredientsColSize, char** supplies, int suppliesSize, int* returnSize) {
    char **ans = (char **) malloc (sizeof (char *) * recipesSize);
    trie_init ();
    for (int i = 0; i < suppliesSize; i++)
        trie_insert (supplies [i]);
    *returnSize = 0;
    bool make_progress = true;
    while (make_progress) {
        make_progress = false;
        for (int i = 0; i < recipesSize; i++) {
            if (trie_search (recipes [i]))
                continue;
            bool can_create = true;
            for (int j = 0; j < ingredientsColSize [i]; j++) {
                if (trie_search (ingredients [i] [j]) == false) {
                    can_create = false;
                    break;
                }
            }
            if (can_create) {
                make_progress = true;
                trie_insert (recipes [i]);
                ans [*returnSize] = (char *) malloc (sizeof (char) * (strlen (recipes [i]) + 1));
                strcpy (ans [*returnSize], recipes [i]);
                *returnSize += 1;
            }
        }
    }
    trie_release ();
    return ans;
}