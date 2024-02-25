#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void Solve(bool flag)
{
    string A, B;
    cin >> A >> B;
    int k1 = A.length();
    int k2 = B.length();
    int **tab = new int *[k1];
    for (int i = 0; i < k1; i++)
    {
        tab[i] = new int[k2];
    }
    char **chars = new char *[k1];
    for (int i = 0; i < k1; i++)
    {
        chars[i] = new char[k2];
    }
    bool flag1 = false;
    for (int i = 0; i < k2; i++)
    {
        if (flag1 == false)
        {
            if (A[0] == B[i])
            {
                flag1 = true;
                tab[0][i] = 1;
                chars[0][i] = 'x';
            }
            else
            {
                tab[0][i] = 0;
                chars[0][i] = '<';
            }
        }
        else
        {
            tab[0][i] = 1;
            chars[0][i] = '<';
        }
    }
    flag1 = false;
    for (int i = 0; i < k1; i++)
    {
        if (flag1 == false)
        {
            if (B[0] == A[i])
            {
                flag1 = true;
                tab[i][0] = 1;
                chars[i][0] = 'x';
            }
            else
            {
                tab[i][0] = 0;
                chars[i][0] = '^';
            }
        }
        else
        {
            tab[i][0] = 1;
            chars[i][0] = '^';
        }
    }
    for (int i = 1; i < k1; i++)
    {
        for (int j = 1; j < k2; j++)
        {
            if (A[i] == B[j])
            {
                tab[i][j] = tab[i - 1][j - 1] + 1;
                chars[i][j] = 'x';
            }
            else
            {
                if (tab[i - 1][j] >= tab[i][j - 1])
                {
                    chars[i][j] = '^';
                    tab[i][j] = tab[i - 1][j];
                }
                else
                {
                    chars[i][j] = '<';
                    tab[i][j] = tab[i][j - 1];
                }
            }
        }
    }
    cout << tab[k1 - 1][k2 - 1] << endl;
    if (tab[k1 - 1][k2 - 1] > 0)
    {
        vector<char> lcs;
        int x = k1 - 1, y = k2 - 1;
        while (x >= 0 && y >= 0)
        {
            if (chars[x][y] == 'x')
            {
                lcs.push_back(A[x]);
                x = x - 1;
                y = y - 1;
            }
            else if (chars[x][y] == '^')
            {
                x = x - 1;
            }
            else if (chars[x][y] == '<')
            {
                y = y - 1;
            }
        }
        int l = lcs.size();
        if(flag == false){
        for (int i = l - 1; i >= 0; i--)
        {
            cout << lcs[i];
        }
        cout << endl;
        lcs.clear();
        }
    
    if(flag == true){
        int j = 0;
        bool test = false;
        for(int i = tab[k1 - 1][k2 - 1] - 1; i >=0; i--){
            while(A[j] != lcs[i]){
                j++;
                if(j == A.length()){
                    cout<<"LCS DOESN'T WORK\n";
                    test = true;
                }
            }
            j++;
        }
        if(test == false){
            cout<< "lcs is a substring of A\n";
        }
        j = 0;
        test = false;
        for(int i = tab[k1 - 1][k2 - 1] - 1; i >=0; i--){
            while(B[j] != lcs[i]){
                j++;
                if(j == B.length()){
                    cout<<"LCS DOESN'T WORK\n";
                    test = true;
                }
            }
            j++;
        }
        if(test == false){
            cout<< "lcs is a substring of B\n";
        }
    
    }
    }


    for (int i = 0; i < k1; i++)
    {
        delete[] tab[i];
    }
    delete[] tab;
    for (int i = 0; i < k1; i++)
    {
        delete[] chars[i];
    }
    delete[] chars;
}

int main(int argc,char *argv[]){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int z;
    cin >> z;
    bool flag = false;
    if(argc > 1){
        flag = true;
    }
    while(z--){
        Solve(flag);
    }
    return 0;
}