#include <iostream>
#include <string>
#include <time.h>
#include <cstring>

using namespace std;

class Vig {
public:
    string k;

    Vig(string k) {
        for (int i = 0; i < k.size(); ++i) {
            if (k[i] >= 'A' && k[i] <= 'Z')
                this->k += k[i];
            else if (k[i] >= 'a' && k[i] <= 'z')
                this->k += k[i] + 'A' - 'a';
        }
    }

    string encryptionVig(string t) {
        string output;
        for (int i = 0, j = 0; i < t.length(); ++i) {
            char c = t[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            //added 'A' to bring it in range of ASCII alphabet 65-90 | A-Z
            output += (c + k[j] - 2 * 'A') % 26 + 'A';
            j = (j + 1) % k.length();
        }
        return output;
    }

    string decryptionVig(string t) {
        string output;
        for (int i = 0, j = 0; i < t.length(); ++i) {
            char c = t[i];
            if (c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;
            //added 'A' to bring it in range of ASCII alphabet 65-90 | A-Z
            output += (c - k[j] + 26) % 26 + 'A';
            j = (j + 1) % k.length();
        }
        return output;
    }
};

class RSA {
public:
    string encryptionRSA(string message) {

        int i;
        char str[message.length() + 1];
        strcpy(str, message.c_str());

        //first case for encrypting a string
        for (i = 0; (i < message.length() + 1 && str[i] != '\0'); i++)
            str[i] = str[i] + 2; //the key for encryptionVig is 3 that is added to ASCII value

        return str;
    }

    string decryptionRSA(string message) {
        int i;
        char str[message.length() + 1];
        strcpy(str, message.c_str());

        for (i = 0; (i < message.length() + 1 && str[i] != '\0'); i++)
            str[i] = str[i] - 2; //the key for encryptionVig is 3 that is subtracted to ASCII value

        return str;
    }
};


class Ver {
public:
    string encryptionVer(string message, string key) {
        int i, j;
        int mod = key.size();
        j = 0;
        for (i = key.size(); i < message.size(); i++) {
            key += key[j % mod];
            j++;
        }
        string ans = "";
        for (i = 0; i < message.size(); i++) {
            ans += (key[i] - 'A' + message[i] - 'A') % 26 + 'A';
        }
        return ans;
    }

    string decryptionVer(string message, string key) {
        int t, n, i, j, k, sum = 0;
        j = 0;
        int mod = key.size();
        for (i = key.size(); i < message.size(); i++) {
            key += key[j % mod];
            j++;
        }
        string ans = "";
        for (i = 0; i < message.size(); i++) {
            ans += (message[i] - key[i] + 26) % 26 + 'A';
        }
        return ans;
    }
};


int main() {
    string orig;
    cout << "Enter a message for encryption:\n";
    cin >> orig;
    cout << "Original Message: " << orig << endl;
    cout << "__________________" << endl;

    //Шифр Виженера
    Vig v("KelEncription");
    string encryptV = v.encryptionVig(orig);
    string decryptV = v.decryptionVig(encryptV);
    cout << "***Vigenere Cypher***\n";
    cout << "Encrypted Message: " << encryptV << endl;
    cout << "Decrypted Message: " << decryptV << endl;

    cout << "\n***Cypher RSA***";
    RSA rsa;
    string encryptR = rsa.encryptionRSA(orig);
    string decryptR = rsa.decryptionRSA(encryptR);
    cout << "\nEncrypted string: " << encryptR << endl;
    cout << "Decrypted string: " << decryptR << endl;

    // Шифр Вернама
    cout << "\n***Vernam Cypher***\n";
    string key;
    key = "KE";
    Ver vern;
    string encryptVern = vern.encryptionVer(orig, key);
    string decryptVern = vern.decryptionVer(encryptVern, key);
    cout << "Encrypted Message: " << encryptVern << endl;
    cout << "Decrypted Message: " << decryptVern << endl;

    return 0;
}