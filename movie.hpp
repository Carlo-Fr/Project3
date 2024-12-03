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
    vector<string> genre;
    double rating;
    int year;
    vector<string> director;
    vector<string> writer;
public:
    Movie(string titl, vector<string> genres, double rate, int yr, vector<string> drctr, vector<string> wrtr) {
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

    // start of mergesort/quicksort functions, jump to line 125 for class sort functions, past line 297 are filter functions,
    // and recommend function on line 399

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
            bool mv1genre = find(mv1.genre.begin(), mv1.genre.end(), inpgenre) != mv1.genre.end();
            bool mv2genre = find(mv2.genre.begin(), mv2.genre.end(), inpgenre) != mv2.genre.end();
            if (mv1genre && !mv2genre) {
                return true;  // mv1 comes first
            } else if (!mv1genre && mv2genre) {
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
            bool mv1genre = find(mv1.genre.begin(), mv1.genre.end(), inpgenre) != mv1.genre.end();
            bool mv2genre = find(mv2.genre.begin(), mv2.genre.end(), inpgenre) != mv2.genre.end();
            if (mv1genre && !mv2genre) {
                return true;  // mv1 comes first
            } else if (!mv1genre && mv2genre) {
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
            bool mv1drctr = find(mv1.director.begin(), mv1.director.end(), drctr) != mv1.director.end();
            bool mv2drctr = find(mv2.director.begin(), mv2.director.end(), drctr) != mv2.director.end();
            if (mv1drctr && !mv2drctr) {
                // mv1 comes first
                return true;
            }
            else if (!mv1drctr && mv2drctr) {
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
            bool mv1drctr = find(mv1.director.begin(), mv1.director.end(), drctr) != mv1.director.end();
            bool mv2drctr = find(mv2.director.begin(), mv2.director.end(), drctr) != mv2.director.end();
            if (mv1drctr && !mv2drctr) {
                // mv1 comes first
                return true;
            }
            else if (!mv1drctr && mv2drctr) {
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
            bool mv1wrtr = find(mv1.writer.begin(), mv1.writer.end(), wrtr) != mv1.writer.end();
            bool mv2wrtr = find(mv2.writer.begin(), mv2.writer.end(), wrtr) != mv2.writer.end();
            if (mv1wrtr && !mv2wrtr) {
                // mv1 comes first
                return true;
            }
            else if (!mv1wrtr && mv2wrtr) {
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
            bool mv1wrtr = find(mv1.writer.begin(), mv1.writer.end(), wrtr) != mv1.writer.end();
            bool mv2wrtr = find(mv2.writer.begin(), mv2.writer.end(), wrtr) != mv2.writer.end();
            if (mv1wrtr && !mv2wrtr) {
                // mv1 comes first
                return true;
            }
            else if (!mv1wrtr && mv2wrtr) {
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
            bool mvgenre = find(it->genre.begin(), it->genre.end(), gnre) != it->genre.end();
            if (!mvgenre) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            bool mvgenre = find(it->genre.begin(), it->genre.end(), gnre) != it->genre.end();
            if (!mvgenre) {
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
            bool mvdrctr = find(it->director.begin(), it->director.end(), drctr) != it->director.end();
            if (!mvdrctr) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            bool mvdrctr = find(it->director.begin(), it->director.end(), drctr) != it->director.end();
            if (!mvdrctr) {
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
            bool mvwrtr = find(it->writer.begin(), it->writer.end(), wrtr) != it->writer.end();
            if (!mvwrtr) {
                it = mlist.erase(it);
            }
            else {
                it++;
            }
        }
        for (auto it = qlist.begin(); it != qlist.end();) {
            bool mvwrtr = find(it->writer.begin(), it->writer.end(), wrtr) != it->writer.end();
            if (!mvwrtr) {
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
        for (auto it = mlist.begin(); it != mlist.end() && count < 11;) {
            cout << "Recommended Movie " << count << ":" << endl;
            cout << "Title: " << it->title << endl;
            cout << "Year: " << it->year << endl;
            cout << "Rating: " << it->rating << endl;
            cout << "Genres: ";
            for (string g : it->genre) {
                cout << g << ", ";
            }
            cout << endl;
            cout << "Directors: ";
            for (string d : it->director) {
                cout << d << ", ";
            }
            cout << endl;
            cout << endl;
            count++;
        }
    }


};
