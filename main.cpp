#include <iostream>
#include <map>
#include <cmath>
#include <cstring>

using namespace std;

void decrypt(char encrypted[], int x) {
    for(int i = 0; encrypted[i] != '\0'; i++) {
        if (encrypted[i] >= 'a' && encrypted[i] <= 'z') {
            encrypted[i] = 'a' + (encrypted[i] - 'a' - x + 26) % 26;
        } else if (encrypted[i] >= 'A' && encrypted[i] <= 'Z') {
            encrypted[i] = 'A' + (encrypted[i] - 'A' - x + 26) % 26;
        }
    }
}

int main() {
    char text[1001];
    map<char, float> e = {{'e', 0.127}, {'t', 0.091}, {'a', 0.082}, {'o', 0.075}, {'i', 0.07}, {'n', 0.067}, {'s', 0.063},
                          {'h', 0.061}, {'r', 0.06}, {'d', 0.043}, {'l', 0.04}, {'u', 0.028}, {'c', 0.028},
                          {'m', 0.024}, {'w', 0.024}, {'f', 0.022}, {'y', 0.02}, {'g', 0.02}, {'p', 0.019}, {'b', 0.015},
                          {'v', 0.01}, {'k', 0.008}, {'x', 0.002}, {'j', 0.002}, {'q', 0.001}, {'z', 0.001}};

    cin.getline(text, 1001);
    char encrypted[1001], decrypted[1001];

    int min_i = -1;
    float min_d = 101;

    for(int k = 1; k <= 26; k++) {
        int c[256] = {0};
        strcpy(encrypted, (char *)text);
        decrypt(encrypted, k);
        for (int i = 0; encrypted[i] != '\0'; i++) {
            if (encrypted[i] >= 'a' && encrypted[i] <= 'z') {
                c[encrypted[i]]++;
            } else if (encrypted[i] >= 'A' && encrypted[i] <= 'Z') {
                c[encrypted[i]-'a'-'A']++;
            }
        }
        float sum = 0;
        for(auto i:e)
            sum += pow((c[i.first] / (float)strlen(encrypted) - i.second), 2) / i.second;

        if (sum < min_d) {
            min_d = sum;
            min_i = k;
            strcpy(decrypted, encrypted);
        }
//        cout<<k<<" "<<sum<<" "<<encrypted<<"\n";
    }

    cout<<"\n"<<"Permutation with the least Chi squared distance: "<<min_i<<"\n";
    cout<<"Decrypted text: "<<decrypted<<"\n";

    return 0;
}