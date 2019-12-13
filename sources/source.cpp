#include <iostream>
#include <ctime>
#include <vector>
#include <random>

using namespace std;
using std::shuffle;

const int L1 = 256;
const int L3 = 6144;

class CashHit {
public:
    CashHit(size_t size) {
        sizeCash = size * 1024;
        myCash = new char[sizeCash];
        hitIT();
    }

    void clearMemory() {
        delete (myCash);
    }


    void hitIT() {
        random_device rd;
        mt19937 mersenne(rd());
        for (int64_t i = 0; i < sizeCash; i++) {
            //srand(time(0));
            myCash[i] = 0;
            //cout<<myCash[i]<<" ";
        }
    }

    void directionType() {
        size_t start_time = clock();
        for (int64_t i = 0; i < 1000; i++) {
            for (int64_t j = 0; j < sizeCash; j++) {

                myCash[j] = rand() % 256;
            }
        }
        size_t end_time = clock();
        cout << "         duration: " << end_time - start_time << endl;
    }

    void converseType() {
        size_t start_time = clock();
        for (int64_t i = 0; i < 1000; i++) {
            for (int64_t j = sizeCash - 1; j != 0; j--) {
                myCash[j] = rand() % 256;
            }
        }
        size_t end_time = clock();
        cout << "         converse: " << end_time - start_time << endl;
    }

    void randomType() {

        vector <size_t> randomNumbers;
        for (int64_t i = 0; i < sizeCash; i++) {
            randomNumbers.push_back(i);
        }
        shuffle(randomNumbers.begin(), randomNumbers.end(), default_random_engine(0));
        size_t start_time = clock();
        for (int64_t j = 0; j < 1000; j++) {
            for (int64_t i = 0; i < sizeCash; i++) {
                myCash[randomNumbers.at(i)] = rand() % 256;
            }
        }
        size_t end_time = clock();
        cout << "         random: " << end_time - start_time << endl;
    }


    char *myCash;
    int64_t sizeCash;
};

void getExpirimentsCount(vector <size_t> *exp) {
    int n = 1;
    int k = L1;
    while (k / 2 != 1) {
        n++;
        k /= 2;
    }
    exp->push_back(L1 / 2);
    while (pow(2, n) < 1.5 * L3) {
        exp->push_back(pow(2, n));
        n++;
    }
    exp->push_back(1.5 * L3);

}


void showResult() {

    vector <size_t> cashes;
    getExpirimentsCount(&cashes);
    clock();
    cout << "investigation:" << endl
         << " travel_variant:<direction>" << endl
         << " experiments" << endl;

    for (unsigned int64_t i = 0; i < cashes.size(); i++) {
        cout << "  - experiment:" << endl;
        cout << "      number:" << i + 1 << endl
             << "      input_data:" << endl
             << "          buffer_size: <" << cashes[i] << "kb>" << endl
             << "      results:" << endl;

        CashHit exp(cashes[i]);
        exp.directionType();
        exp.clearMemory();

    }
    cout << "investigation:" << endl
         << " travel_variant:<converse>" << endl
         << " experiments" << endl;
    for (unsigned int64_t i = 0; i < cashes.size(); i++) {
        cout << "  - experiment:" << endl;
        cout << "      number:" << i + 1 << endl
             << "      input_data:" << endl
             << "          buffer_size: <" << cashes[i] << "kb>" << endl
             << "      results:" << endl;
        CashHit exp(cashes[i]);
        exp.converseType();
        exp.clearMemory();
    }

    cout << "investigation:" << endl
         << " travel_variant:<random>" << endl
         << " experiments" << endl;

    for (unsigned int64_t i = 0; i < cashes.size(); i++) {
        cout << "  - experiment:" << endl;
        cout << "      number:" << i + 1 << endl
             << "      input_data:" << endl
             << "          buffer_size: <" << cashes[i] << "kb>" << endl
             << "      results:" << endl;

        CashHit exp(cashes[i]);
        exp.randomType();
        exp.clearMemory();
    }
    clock();
    cout << "ТОТАЛ ТАЙМ - " << clock() << endl;
}


int main() {
    showResult();
    // cout<<2/2<<endl;
    return 0;
}
