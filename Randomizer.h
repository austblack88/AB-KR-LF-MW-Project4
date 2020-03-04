//
// Created by ironi on 2/24/2020.
//

#ifndef AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
#define AB_KR_LF_MW_PROJECT4_RANDOMIZER_H

#include <algorithm>
#include <chrono>
#include <cmath>
#include <ostream>
#include <vector>
using namespace std;

template <class T>
class Randomizer {
private:
    vector<T> list;
    unsigned long int LFshuffleSeed;
    unsigned long int KRshuffleSeed;

public:
    Randomizer() {
        LFshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        KRshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
    }

    /*
     * Sort
     * Requires:
     * Modifies:
     * Effects: returns the index of the object to be located
     */
    vector<T> sort(const vector<T> &unsortedList) {
        vector<T> sortedList = unsortedList;
        std::stable_sort(sortedList.begin(), sortedList.end());
        return sortedList;
    }

    /*
     * Find
     * Requires:
     * Modifies:
     * Effects: returns the index of the object to be located
     */
    int find(T object) {
        for (int i = 0; i < list.size(); i++) {
            if (object == list[i]) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Shuffles should return own copies of shuffled vector, NOT void.
     * That way they can be compared together at the same time.
     */

    /*
     * Austin Black's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
    vector<T> ABshuffle() {
        unsigned long int seed;
        vector<T> shuffled = list;
        double result = logisticMap(100, 0.4);
        result *= 1.0*pow(10,4);
        seed = (int)result;


        string seedToString = to_string(seed);
        cout << "seedToString = " << seedToString << endl;

        int seedSquared = pow(seed, 2);
        cout << "seedSquared = " << seedSquared << endl;

        string squaredToString = to_string(seedSquared);
        cout << "squaredToString = " << squaredToString << endl;

        int seedLength = seedToString.length();
        int squareLength = squaredToString.length();

        if (squareLength % 2 != 0) {
            squaredToString += "1";
        }
    }

    /*
     * Logistic Map Function
     * Requires:
     * Modifies:
     * Effects:
     */
    double logisticMap(int iter, double start) {
        vector<double> x (iter+1);
        x[0] = start;
        for (int i = 0; i < iter; i++) {
            x[i+1] = 4*x[i]*(1-x[i]);
        }
        return x[iter];
    }

    /*
     * Kai Morrissey's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
    vector<T> KRshuffle() {
        vector<T> out;
        for(T t : list) {
            out.insert(out.begin() + (out.size() == 0? 0 : (rand() % out.size())), t);
        }
        KRshuffleSeed = chrono::duration_cast<chrono::milliseconds>
                (chrono::system_clock::now().time_since_epoch()).count();
        return out;
    }

    /*
     * Luke Fredrickson's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
    vector<T> LFshuffle() {
        vector<T> scrambled = list;
        unsigned long int first = 1;
        unsigned long int second = LFshuffleSeed;
        unsigned long int current;
        for (int i = 0; i < scrambled.size(); ++i) {
            current = first + second;
            first = second;
            second = current;
            int j = current % scrambled.size();
            // swap objects from current index to random index
            T temp = scrambled[j];
            scrambled[j] = scrambled[i];
            scrambled[i] = temp;
            // update seed
            LFshuffleSeed = current;
        }
        return scrambled;
    }

    /*
     * Megan Work's Algorithm
     * Requires:
     * Modifies:
     * Effects:
     */
    // TODO: Test shuffle algorithm
    vector<T> MWshuffle() {
        vector<T> shuffled = list;
        int size = shuffled.size();
        //for every element, swap with random element in remaining elements
        for(int i = 0; i < size - 1; ++i) {
            int j = i + rand() % (size - i);
            swap(shuffled[i], shuffled[j]);
        }
        return shuffled;
    }


    /*
     * Requires: a scrambled version of the list vector (unique objects which possess equality operators)
     * Modifies: nothing
     * Effects: calculates a randomness score by taking the standard deviation of distance traveled by each object from
     *          its initial position in list and dividing that by the total size of the list;
     */
    double calculateRandomness(const vector<vector<T>> &shuffledVectors) {
        vector<vector<double>> distancesVectors;
        // find the distance each object in the shuffledVectors has moved from its position in list
        for(vector<T> vect : shuffledVectors) {
            vector<double> distances;
            for (int endPos = 0; endPos < shuffledVectors.size(); endPos++) {
                int startPos = find(shuffledVectors[endPos]);
                // if the object is in list calculate and push back how far it moved
                if (startPos != -1) {
                    double distance = abs(endPos - startPos);
                    distances.push_back(distance);
                }
            }
            distancesVectors.push_back(distances);
        }
        return calculateStandardError(distancesVectors);
    }

    /*
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the standard deviation of a vector of doubles
     */
    double calculateStandardError(const vector<vector<double>> &numbers) {
        // SE = sqrt( sum((X-m)^2) / N ) / sqrt(N), where X = number in list, m = mean, N = count of numbers
        double mean = calculateMean(numbers);
        double sumSquaredDistances = 0;
        for (double num : numbers) {
            sumSquaredDistances += (pow((num - mean), 2) / numbers.size());
        }
        double variance = sumSquaredDistances / numbers.size();
        double standardError = sqrt(variance) / sqrt(numbers.size());
        return standardError;
    }

    /*
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the mean value of a vector of doubles
     */
    double calculateMean(const vector<double> &numbers) {
        double mean = 0;
        for (double num : numbers) {
            mean += num;
        }
        return mean /= numbers.size();
    }

    /*
     * GETTER(S)
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the mean value of a vector of doubles
     */
    const vector<T> &getList() const {
        return list;
    }

    /*
     * SETTER(S)
     * Requires: a vector of doubles
     * Modifies: nothing
     * Effects: calculates the mean value of a vector of doubles
     */
    void setList(const vector<T> &list_) {
        list = list_;
    }

    void add(T push) {
        list.push_back(push);
    }

    T get(int index) {
        return list[index];
    }

    friend std::ostream &operator<<(std::ostream &os, const Randomizer<T> &randomizer) {
        for(T obj : randomizer.list) {
            os << obj << endl;
        }
        return os;
    }
};




#endif //AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
