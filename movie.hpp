#ifndef PROJ3_MOVIE_HPP
#define PROJ3_MOVIE_HPP

#endif //PROJ3_MOVIE_HPP
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <chrono>
using namespace std;

class Movie {
public:
    string title;
    unordered_map<string, bool> genre;
    double rating;
    int year;
    unordered_map<string, bool> director;
    unordered_map<string, bool> writer;
public:
    Movie(string titl, unordered_map<string, bool> genres, double rate, int yr, unordered_map<string, bool> drctr, unordered_map<string, bool> wrtr) {
        title = titl;
        genre = genres;
        rating = rate;
        year = yr;
        director = drctr;
        writer = wrtr;
    }
};

class MovieList {
private:
    vector<Movie> mlist;
    vector<Movie> qlist;
    vector<Movie> original;
    int size;
public:
    MovieList() {
        size = 0;
    }
    void insert(Movie mv) {
        mlist.push_back(mv);
        qlist.push_back(mv);
        original.push_back(mv);
        size++;
    }
    void reset() {
        mlist = original;
        qlist = original;
    }

    // start of mergesort/quicksort functions, jump to line 131 for class sort functions, past line 285 are filter functions

    void merge(vector<Movie>& list, int left, int mid, int right, function<bool(const Movie&, const Movie&)> comparator) {
        int leftside = mid - left + 1;
        int rightside = right - mid;
        vector<Movie> l;
        vector<Movie> r;
        for (int i = 0; i < leftside; i++) {
            l.push_back(list[left + i]);
        }
        for (int j = 0; j < rightside; j++) {
            r.push_back(list[mid + j + 1]);
        }
        int i = 0;
        int j = 0;
        int z = left;
        while (i < leftside && j < rightside) {
            if (comparator(l[i], r[j])) {
                list[z] = l[i];
                i++;
            }
            else {
                list[z] = r[j];
                j++;
            }
            z++;
        }
        while (i < leftside) {
            list[z] = l[i];
            i++;
            z++;
        }
        while (j < rightside) {
            list[z] = r[j];
            j++;
            z++;
        }
    }
    void mergesort(vector<Movie>& list, int start, int end, function<bool(const Movie&, const Movie&)> comparator) {
        if (start < end) {
            int mid = start + (end - start) / 2;
            mergesort(list, start, mid, comparator);
            mergesort(list, mid + 1, end, comparator);
            merge(list, start, mid, end, comparator);
        }
    }

    int part(vector<Movie>& list, int low, int high, function<bool(const Movie&, const Movie&)> comparator) {
        Movie piv = list[high];
        int swpindex = low - 1;
        for (int i = low; i <= high - 1; i++) {
            if (comparator(list[i], piv)) {
                swpindex++;
                swap(list[swpindex], list[i]);
            }
        }
        swap(list[swpindex + 1], list[high]);
        return swpindex + 1;
    }

    void quicksort(vector<Movie>& list, int low, int high, function<bool(const Movie&, const Movie&)> comparator) {
        if (low < high) {
            int prt = part(list, low, high, comparator);
            quicksort(list, low, prt - 1, comparator);
            quicksort(list, prt + 1, high, comparator);
        }
    }

    // end of merge/quicksort functions

    double sortbyyearmerge() {
        auto compareyear = [](const Movie& mv1, const Movie& mv2) {
            return mv1.year > mv2.year;
        };
        auto starttime = chrono::high_resolution_clock::now();
        mergesort(mlist, 0, size - 1, compareyear);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbyyearquick() {
        auto compareyear = [](const Movie& mv1, const Movie& mv2) {
            return mv1.year > mv2.year;
        };
        auto starttime = chrono::high_resolution_clock::now();
        quicksort(qlist, 0, size - 1, compareyear);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbyratingmerge() {
        auto comparerating = [](const Movie& mv1, const Movie& mv2) {
            return mv1.rating > mv2.rating;
        };
        auto starttime = chrono::high_resolution_clock::now();
        mergesort(mlist, 0, size - 1, comparerating);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbyratingquick() {
        auto comparerating = [](const Movie& mv1, const Movie& mv2) {
            return mv1.rating > mv2.rating;
        };
        auto starttime = chrono::high_resolution_clock::now();
        quicksort(qlist, 0, size - 1, comparerating);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbygenremerge(const std::string& inpgenre) {
        auto comparegenre = [&inpgenre](const Movie& mv1, const Movie& mv2) -> bool {
            if (mv1.genre.count(inpgenre) && !mv2.genre.count(inpgenre)) {
                return true;  // mv1 comes first
            } else if (!mv1.genre.count(inpgenre) && mv2.genre.count(inpgenre)) {
                return false; // mv2 comes first
            } else {
                return false; // Maintain previous order if neither matches
            }
        };
        auto starttime = chrono::high_resolution_clock::now();
        mergesort(mlist, 0, size - 1, comparegenre);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbygenrequick(const std::string& inpgenre) {
        auto comparegenre = [&inpgenre](const Movie& mv1, const Movie& mv2) -> bool {
            if (mv1.genre.count(inpgenre) && !mv2.genre.count(inpgenre)) {
                return true;  // mv1 comes first
            } else if (!mv1.genre.count(inpgenre) && mv2.genre.count(inpgenre)) {
                return false; // mv2 comes first
            } else {
                return false; // Maintain previous order if neither matches
            }
        };
        auto starttime = chrono::high_resolution_clock::now();
        quicksort(qlist, 0, size - 1, comparegenre);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbydirectormerge(const string& drctr) {
        auto comparedirector = [&drctr](const Movie& mv1, const Movie& mv2) -> bool {
            if (mv1.director.count(drctr) && !mv2.director.count(drctr)) {
                // mv1 comes first
                return true;
            }
            else if (!mv1.director.count(drctr) && mv2.director.count(drctr)) {
                // mv2 comes first
                return false;
            }
            else {
                // if neither have target, maintain previous order
                return false;
            }
        };
        auto starttime = chrono::high_resolution_clock::now();
        mergesort(mlist, 0, size - 1, comparedirector);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbydirectorquick(const string& drctr) {
        auto comparedirector = [&drctr](const Movie& mv1, const Movie& mv2) -> bool {
            if (mv1.director.count(drctr) && !mv2.director.count(drctr)) {
                // mv1 comes first
                return true;
            }
            else if (!mv1.director.count(drctr) && mv2.director.count(drctr)) {
                // mv2 comes first
                return false;
            }
            else {
                // if neither have target, maintain previous order
                return false;
            }
        };
        auto starttime = chrono::high_resolution_clock::now();
        quicksort(qlist, 0, size - 1, comparedirector);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbywritermerge(string& wrtr) {
        auto comparewriter = [&wrtr](const Movie& mv1, const Movie& mv2) {
            if (mv1.writer.count(wrtr) && !mv2.writer.count(wrtr)) {
                // mv1 comes first
                return true;
            }
            else if (!mv1.writer.count(wrtr) && mv2.writer.count(wrtr)) {
                // mv2 comes first
                return false;
            }
            else {
                // if neither have target, maintain previous order
                return false;
            }
        };
        auto starttime = chrono::high_resolution_clock::now();
        mergesort(mlist, 0, size - 1, comparewriter);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }
    double sortbywriterquick(string& wrtr) {
        auto comparewriter = [&wrtr](const Movie& mv1, const Movie& mv2) {
            if (mv1.writer.count(wrtr) && !mv2.writer.count(wrtr)) {
                // mv1 comes first
                return true;
            }
            else if (!mv1.writer.count(wrtr) && mv2.writer.count(wrtr)) {
                // mv2 comes first
                return false;
            }
            else {
                // if neither have target, maintain previous order
                return false;
            }
        };
        auto starttime = chrono::high_resolution_clock::now();
        quicksort(qlist, 0, size - 1, comparewriter);
        auto endtime = chrono::high_resolution_clock::now();
        chrono::duration<double> time = endtime - starttime;
        return time.count();
    }

    // filter functions

    //filter to specific year
    void filterbyyear(int yr) {
        for (auto it = mlist.begin(); it != mlist.end();) {
            if (it->year != yr) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            if (it->year != yr) {
                it = qlist.erase(it);
            }
            else {
                it++;
            }
        }
    }
    // filter with minimum rating
    void filterbyrating(double rtng) {
        for (auto it = mlist.begin(); it != mlist.end();) {
            if (it->rating < rtng) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            if (it->rating < rtng) {
                it = qlist.erase(it);
            }
            else {
                it++;
            }
        }
    }
    //filter to specific genre
    void filterbygenre(string& gnre) {
        for (auto it = mlist.begin(); it != mlist.end();) {
            if (!it->genre.count(gnre)) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            if (!it->genre.count(gnre)) {
                it = qlist.erase(it);
            }
            else {
                it++;
            }
        }
    }
    //filter to specific director
    void filterbydirector(string& drctr) {
        for (auto it = mlist.begin(); it != mlist.end();) {
            if (!it->director.count(drctr)) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            if (!it->director.count(drctr)) {
                it = qlist.erase(it);
            }
            else {
                it++;
            }
        }
    }
    //filter to specific writer
    void filterbywriter(string& wrtr) {
        for (auto it = mlist.begin(); it != mlist.end();) {
            if (!it->writer.count(wrtr)) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            if (!it->writer.count(wrtr)) {
                it = qlist.erase(it);
            }
            else {
                it++;
            }
        }
    }

    // Recommend basic function
    void recommend() {
        int count = 1;
        for (auto it = mlist.begin(); it != mlist.end();) {
            cout << "Recommended Movie " << count << ":" << endl;
            cout << "Title: " << it->title << endl;
            cout << "Year: " << it->year << endl;
            cout << "Rating: " << it->rating << endl;
            cout << "Genres: ";
            for (auto it2 = it->genre.begin(); it2 != it->genre.end();) {
                cout << it2->first << ", ";
            }
            cout << endl;
            cout << "Directors: ";
            for (auto it3 = it->director.begin(); it3 != it->director.end();) {
                cout << it3->first << ", ";
            }
            cout << endl;
            cout << endl;
        }
    }


};
