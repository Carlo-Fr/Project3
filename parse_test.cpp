#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Movie class definition
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

// functions for parsing

// movie ratings from title.ratings.tsv
void populateRatingsMap(const string& filename, unordered_map<string, double>& ratingsMap) {
    ifstream file(filename);
    string line;

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
        string tconst, averageRatingStr;
        stringstream ss(line);

        // Parse the tconst and averageRating columns
        getline(ss, tconst, '\t');
        getline(ss, averageRatingStr, '\t');

        // convert averageRatingStr to double and store in the map
        double rating = stod(averageRatingStr);
        ratingsMap[tconst] = rating;
    }
}


// populate namesMap from names.basics.tsv
void populateNamesMap(const string& filename, unordered_map<string, string>& namesMap) {
    ifstream file(filename);
    string line;

    // skip header
    getline(file, line);

    while (getline(file, line)) {
        string nconst, primaryName;
        stringstream ss(line);
        getline(ss, nconst, '\t');
        getline(ss, primaryName, '\t');

        // nconst to primaryName
        namesMap[nconst] = primaryName;
    }
}

// parse the title.crew.tsv file and retrieve the names for director and writer
void parseCrewFile(const string& filename, unordered_map<string, vector<string>>& directorMap, unordered_map<string, vector<string>>& writerMap) {
    ifstream file(filename);
    string line;

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
        string tconst, directorIds, writerIds;
        stringstream ss(line);
        getline(ss, tconst, '\t');
        getline(ss, directorIds, '\t');
        getline(ss, writerIds, '\t');

        // Parse the director and writer tconsts (split by commas)
        vector<string> directors;
        stringstream directorStream(directorIds);
        string director;
        while (getline(directorStream, director, ',')) {
            if (director != "\\N") {
                directors.push_back(director);
            }
        }

        vector<string> writers;
        stringstream writerStream(writerIds);
        string writer;
        while (getline(writerStream, writer, ',')) {
            if (writer != "\\N") {
                writers.push_back(writer);
            }
        }

        // store directors and writers for each movie
        directorMap[tconst] = directors;
        writerMap[tconst] = writers;
    }
}

// parse the title.basics.tsv and create Movie objects
void parseTSV(const string& filename, const unordered_map<string, double>& ratingsMap,
              const unordered_map<string, vector<string>>& directorMap, const unordered_map<string, vector<string>>& writerMap,
              const unordered_map<string, string>& namesMap, vector<Movie>& movies) {
    ifstream file(filename);
    string line;

    // Skip the header
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres;
        double rating = 0.0;
        int year = 0;

        // Parse the columns
        getline(ss, tconst, '\t'); // tconst
        getline(ss, titleType, '\t'); // titleType
        getline(ss, primaryTitle, '\t'); // primaryTitle
        getline(ss, originalTitle, '\t'); // skipped
        getline(ss, isAdult, '\t'); // skipped
        getline(ss, startYear, '\t'); // year
        year = (startYear == "\\N") ? 0 : stoi(startYear); // If year is missing, set it to 0
        getline(ss, endYear, '\t'); // skipped
        getline(ss, runtimeMinutes, '\t'); // skipped
        getline(ss, genres, '\t'); // genres

        // Ensure the titleType is "movie"
        if (titleType == "movie") {

            // rating from ratingsMap
            auto itRating = ratingsMap.find(tconst);
            if (itRating != ratingsMap.end()) {
                rating = itRating->second;
            }

            // directors from directorMap
            vector<string> directors;
            auto itDir = directorMap.find(tconst);
            if (itDir != directorMap.end()) {
                directors = itDir->second;
            }

            // changes name id to actual name
            for (int i = 0; i < directors.size(); i++) {
                auto itDirName = namesMap.find(directors[i]);
                if (itDirName != namesMap.end()) {
                    directors[i] = itDirName->second;
                }
            }

            // writers from writerMap
            vector<string> writers;
            auto itWri = writerMap.find(tconst);
            if (itWri != writerMap.end()) {
                writers = (itWri->second);
            }

            // changes name id to actual name
            for (int i = 0; i < writers.size(); i++) {
                auto itWriName = namesMap.find(writers[i]);
                if (itWriName != namesMap.end()) {
                    writers[i] = itWriName->second;
                }
            }

            // genre
            vector<string> genresV;
            stringstream genreStream(genres);
            string genreName;
            while (getline(genreStream, genreName, ',')) {
                genresV.push_back(genreName);  // add genres to list
            }

            // Movie object and add it to the movies vector
            movies.emplace_back(primaryTitle, genresV, rating, year, directors, writers);
        }

    }
}

int main() {
    vector<Movie> movies;
    unordered_map<string, double> ratingsMap;
    unordered_map<string, vector<string>> directorMap;
    unordered_map<string, vector<string>> writerMap;
    unordered_map<string, string> namesMap;

    // ratingsMap from title.ratings.tsv
    populateRatingsMap("title.ratings.tsv", ratingsMap);

    // directorMap and writerMap from title.crew.tsv
    parseCrewFile("title.crew.tsv", directorMap, writerMap);

    // namesMap from name.basics.tsv
    populateNamesMap("name.basics.tsv", namesMap);

    // parse title.basics.tsv and create Movie objects
    parseTSV("title.basics.tsv", ratingsMap, directorMap, writerMap, namesMap, movies);



    // optional: tests output
    for (const auto& movie : movies) {
            cout << "Title: " << movie.title << ", Year: " << movie.year << ", Rating: " << movie.rating << endl;
            cout << "Genres: ";
            for (const auto& g : movie.genre) {
                cout << g << " ";
            }
            cout << endl;
            cout << "Directors: ";
            for (const auto& d : movie.director) {
                cout << d << " ";
            }
            cout << endl;
            cout << "Writers: ";
            for (const auto& w : movie.writer) {
                cout << w << " ";
            }
            cout << endl << endl;
    }

    return 0;
}
