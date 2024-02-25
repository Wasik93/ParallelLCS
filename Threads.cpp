#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <pthread.h>
#include <condition_variable>
#include <chrono>
using namespace std;

int THREAD_NUMBER = thread::hardware_concurrency();
pthread_barrier_t barrier;
string A,B;
int l,m,n;
char * C;
int ** S;
int ** P;
int ** row;

void* calculate_P(void* threadid){
    int id = *((int*) threadid);
    for(int i = id; i < l; i = i + THREAD_NUMBER){
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
    return 0;
}

void* calculate_S(void* threadid){
    int id = *((int*) threadid);
    for(int i = 0 ; i<= n; i++){
        for(int j = id; j <= m; j = j + THREAD_NUMBER ){
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
        pthread_barrier_wait(&barrier);
    }
    return 0;
}

void find_LCS(bool flag){
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
        cout<<'\n';
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
    cin >> A >> B;
    l = 26;
    n = A.length();
    m = B.length();
    C = new char[26];
    for(int i = 0; i < l; i++){
        C[i] = (char)(65 + i);
    }
    S = new int*[n + 2];
    for(int i = 0; i < n + 2; i++){
        S[i] = new int[m + 2];
    }
    P = new int*[l];
    for(int i = 0; i < l;i++){
        P[i] = new int[m+1];
    }
    
    
    vector<pthread_t> threads(THREAD_NUMBER);
    vector<int> T(THREAD_NUMBER);
    for(int i = 0 ; i < THREAD_NUMBER;i++){
        T[i] = i;
    }
    for(int i = 0; i < THREAD_NUMBER; i++){
        pthread_create(&threads[i], NULL, calculate_P, &T[i]);
    }
    for (auto& th : threads) {
        pthread_join(th, NULL);
    }
    vector<pthread_t> threads2(THREAD_NUMBER);
    for(int j = 0; j < THREAD_NUMBER; j++) {
        pthread_create(&threads2[j], NULL, calculate_S, &T[j]);
    }
    for (auto& th2 : threads2) {
        pthread_join(th2, NULL);
    }

    //REMAKE LCS
    cout << S[n][m]<<endl;
    if(S[n][m] != 0){
        find_LCS(flag);
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
    if(argc > 1){
        flag = true;
    }
    row = new int*[THREAD_NUMBER];
    for(int i = 0; i < THREAD_NUMBER; i++){
        row[i] = new int[m];
    }
    pthread_barrier_init (&barrier, NULL, THREAD_NUMBER);
    for(int iz = 0; iz < z; iz++){
        Solve(flag);
    }
    for(int i = 0; i < THREAD_NUMBER; i++){
        delete[] row[i];
    }
    delete[] row;
    return 0;
}