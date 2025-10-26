typedef struct {
    long long* bal;
    int n;
} Bank;

bool valid (Bank* obj, int acc) {
    return acc > 0 && acc <= obj -> n;
}

Bank* bankCreate (long long* balance, int balanceSize) {
    Bank* obj = (Bank*) malloc (sizeof (Bank));
    obj -> n = balanceSize;
    obj -> bal = (long long*) malloc (sizeof (long long) * balanceSize);
    for (int i = 0; i < balanceSize; i++)
        obj -> bal [i] = balance [i];
    return obj;
}

bool bankTransfer (Bank* obj, int account1, int account2, long long money) {
    if (!valid (obj, account1) || !valid (obj, account2) || obj -> bal [account1 - 1] < money)
        return false;
    obj -> bal [account1 - 1] -= money;
    obj -> bal [account2 - 1] += money;
    return true;
}

bool bankDeposit (Bank* obj, int account, long long money) {
    if (!valid (obj, account))
        return false;
    obj -> bal [account - 1] += money;
    return true;
}

bool bankWithdraw(Bank* obj, int account, long long money) {
    if (!valid(obj, account) || obj->bal[account - 1] < money)
        return false;
    obj->bal[account - 1] -= money;
    return true;
}

void bankFree(Bank* obj) {
    free(obj->bal);
    free(obj);
}

/**
 * Your Bank struct will be instantiated and called as such:
 * Bank* obj = bankCreate(balance, balanceSize);
 * bool param_1 = bankTransfer(obj, account1, account2, money);
 
 * bool param_2 = bankDeposit(obj, account, money);
 
 * bool param_3 = bankWithdraw(obj, account, money);
 
 * bankFree(obj);
*/