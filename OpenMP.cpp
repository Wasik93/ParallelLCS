#include <iostream>
#include <algorithm>
#include <vector>
#include <omp.h>
using namespace std;

void calculate_P(int**P, int l, int m, string B, char*C){
    #pragma omp parallel 
    {
        #pragma omp for
        for(int i = 0; i < l; i++){
            for(int j = 0; j <= m; j++){
                if(j == 0){
                    P[i][j] = 0;
                }
                else if(C[i] == B[j - 1]){
                    P[i][j] = j;
                }
                else{
                    P[i][j] = P[i][j - 1];
                }
            }
        }
    }
}

void calculate_S(int**S, int n, int m, int**P, string A){
    #pragma omp parallel
    {
        
        for(int i = 0; i <= n; i++){
            #pragma omp for
            for(int j = 0; j <=m; j++ ){
                if(i == 0 || j ==0){
                    S[i][j] = 0;
                }
                else if(P[(int)(A[i - 1]) - 65][j] == 0){
                    S[i][j] = max(S[i - 1][j] , 0);
                }
                else{
                    S[i][j] = max(S[i - 1][j], S[i - 1][P[(int)(A[i - 1]) - 65][j] - 1] + 1);
                }
            }
        }
    }
}

void find_LCS(int **S, int n, int m, string A, string B, bool flag){
    int x = n;
    int y = m;
    vector<char> lcs;
    while(x > 0 && y > 0){
        if(S[x - 1][y - 1] + 1 == S[x][y] && A[x - 1] == B[y - 1]){
            lcs.push_back(A[x - 1]);
            x--;
            y--;
        }
        else{
            if(S[x - 1][y] > S[x][y - 1]){
                x--;
            }
            else{
                y--;
            }
        }
    }
    if(flag == false){
        for(int i = S[n][m] - 1; i >= 0; i--){
            cout << lcs[i];
        }
        cout<<endl;
    }

    if(flag == true){
        int j = 0;
        bool test = false;
        for(int i = S[n][m] - 1; i >=0; i--){
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
        for(int i = S[n][m] - 1; i >=0; i--){
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

void Solve(bool flag){
    string A, B;
    cin >> A >> B;
    int l = 26;
    int n = A.length();
    int m = B.length();
    char * C = new char[26];
    for(int i = 0; i < l; i++){
        C[i] = (char)(65 + i);
    }
    int ** S = new int*[n + 2];
    for(int i = 0; i < n + 2; i++){
        S[i] = new int[m + 2];
    }
    int ** P = new int*[l];
    for(int i = 0; i < l;i++){
        P[i] = new int[m+1];
    }
    omp_set_num_threads(omp_get_num_procs());
    calculate_P(P,l,m,B,C);

    calculate_S(S,n,m,P,A);
    //REMAKE LCS
    cout << S[n][m]<<endl;
    if(S[n][m] != 0){
        find_LCS(S, n, m, A, B, flag);
    }
    
    for(int i = 0; i < l; i++){
        delete[] P[i];
    }
    delete[] P;
    for(int i = 0; i < n + 2; i++){
        delete[] S[i];
    }
    delete[] S;
    delete[] C;
}

int main(int argc,char*argv[]){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int z;
    cin >> z;
    bool flag = false;
    if(argc>1){
        flag = true;
    }
    for(int iz = 0; iz < z; iz++){
        Solve(flag);
    }
    return 0;
}