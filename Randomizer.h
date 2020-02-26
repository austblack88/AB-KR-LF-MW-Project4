//
// Created by ironi on 2/24/2020.
//

#ifndef AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
#define AB_KR_LF_MW_PROJECT4_RANDOMIZER_H

#include <vector>
#include <ostream>

using namespace std;

template <class T>
class Randomizer {

    vector<T> list;

public:
    void sort();

    // returns the index of the object to be located
    int find(T object) {
        for (int i = 0; i < list.size(); i++) {
            if (object == list[i]) {
                return i;
            }
        }
        return -1;
    }

    //Shuffles should return own copies of shuffled vector, not void
    //That way they can be compared together at the same time

    void ABshuffle();

    void KRshuffle();

    void LFshuffle();

    void MWshuffle();

    // calculates the standard deviation of distance traveled by each object from its initial position (=ID)
    double calculateRandomness(vector<T> randomizedList) {
        vector<int> distanceMoved;
        // find the distance each object in the randomizedList has moved from its position in list
        for (int endPos = 0; endPos < randomizedList.size(); endPos++) {
            int startPos = find(randomizedList[endPos]);
            // if the object is in list calculate and push back how far it moved
            if (startPos != -1) {
                int distance = abs(endPos - startPos);
                distanceMoved.push_back(distance);
            }
        }
        // TODO: calculate SD of distanceMoved
    }

    const vector<T> &getList() const {
        return list;
    }

    void setList(const vector<T> &list_) {
        list = list_;
    }

    void add(T push) {
        list.push_back(push);
    }

    T get(int index) {
        return list[index];
    }



    friend std::ostream &operator<<(std::ostream &os, const Randomizer<T> &randomizer);
};




#endif //AB_KR_LF_MW_PROJECT4_RANDOMIZER_H
