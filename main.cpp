#include "movie.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void displayMenu() {
    cout << "\n--- MovieMender Menu ---\n";
    cout << "1. Sort movies by year\n";
    cout << "2. Sort movies by rating\n";
    cout << "3. Sort movies by genre\n";
    cout << "4. Sort movies by director\n";
    cout << "5. Sort movies by writer\n";
    cout << "6. Filter movies by year\n";
    cout << "7. Filter movies by rating\n";
    cout << "8. Filter movies by genre\n";
    cout << "9. Filter movies by director\n";
    cout << "10. Filter movies by writer\n";
    cout << "11. Give Recommended Movies\n";
    cout << "12. Reset movie list to original order\n";
    cout << "13. Exit\n";
    cout << "Enter your choice: ";
    cout << endl;
}

void displayMovies(vector<Movie>& movies){
  cout << "\n--- Movie List ---\n";
  for(auto movie : movies){
    cout << "Title: " << movie.title << ", Year: " << movie.year << ", Rating: " << movie.rating << "\n";
  }  
}

int main(){

    // calling parsing functions for Movie class

    MovieList ML; // vector of movie objects
    unordered_map<string, double> ratingsMap;
    unordered_map<string, vector<string>> directorMap;
    unordered_map<string, vector<string>> writerMap;
    unordered_map<string, string> namesMap;

    // ratingsMap from title.ratings.tsv
    ML.populateRatingsMap("C:\\Users\\carlo\\CLionProjects\\proj3\\title.ratings.tsv", ratingsMap);

    // directorMap and writerMap from title.crew.tsv
    ML.parseCrewFile("C:\\Users\\carlo\\CLionProjects\\proj3\\title.crew.tsv", directorMap, writerMap);

    // namesMap from name.basics.tsv
    ML.populateNamesMap("C:\\Users\\carlo\\CLionProjects\\proj3\\name.basics.tsv", namesMap);

    // parse title.basics.tsv and create Movie objects
    ML.parseTSV("C:\\Users\\carlo\\CLionProjects\\proj3\\title.basics.tsv", ratingsMap, directorMap, writerMap, namesMap);

    bool exit = false;
  while(!exit){
    displayMenu();
    int choice;
    cin >> choice;
    cin.ignore(); //create a newline buffer

    //call appropriate function based on choice
    switch (choice) {
        case 1: {
            double mtime = ML.sortbyyearmerge();
            //double qtime = ML.sortbyyearquick();
            cout << "Movies sorted by year.\n";
            cout << "Time to sort with mergesort: " << mtime << " seconds" << endl;
            //cout << "Time to sort with quicksort: " << qtime << " seconds" << endl;
            cout << endl;
            break;
        }
        case 2: {
            double mtime = ML.sortbyratingmerge();
            //double qtime = ML.sortbyratingquick();
            cout << "Movies sorted by rating.\n";
            cout << "Time to sort with mergesort: " << mtime << " seconds" << endl;
            //cout << "Time to sort with quicksort: " << qtime << " seconds" << endl;
            cout << endl;
            break;
        }
        case 3: {
            string genre;
            cout << "Enter genre to sort by: " << endl;
            getline(cin, genre);
            double mtime = ML.sortbygenremerge(genre);
            //double qtime = ML.sortbygenrequick(genre);
            cout << "Movies sorted by genre.\n";
            cout << "Time to sort with mergesort: " << mtime << " seconds" << endl;
            //cout << "Time to sort with quicksort: " << qtime << " seconds" << endl;
            cout << endl;
            break;
        }
        case 4: {
            string director;
            cout << "Enter director to sort by: " << endl;
            getline(cin, director);
            double mtime = ML.sortbydirectormerge(director);
            //double qtime = ML.sortbydirectorquick(director);
            cout << "Movies sorted by director.\n";
            cout << "Time to sort with mergesort: " << mtime << " seconds" << endl;
            //cout << "Time to sort with quicksort: " << qtime << " seconds" << endl;
            cout << endl;
            break;
        }
        case 5: {
            string writer;
            cout << "Enter writer to sort by: " << endl;
            getline(cin, writer);
            double mtime = ML.sortbywritermerge(writer);
            //double qtime = ML.sortbywriterquick(writer);
            cout << "Movies sorted by writer.\n";
            cout << "Time to sort with mergesort: " << mtime << " seconds" << endl;
            //cout << "Time to sort with quicksort: " << qtime << " seconds" << endl;
            cout << endl;
            break;
        }
        case 6: {
            string year;
            cout << "Enter minimum year for a movie: " << endl;
            getline(cin, year);
            int yr = stoi(year);
            ML.filterbyyear(yr);
            cout << endl;
            break;
        }
        case 7: {
            string rating;
            cout << "Enter minimum rating for a movie: " << endl;
            getline(cin, rating);
            double rtng = stod(rating);
            ML.filterbyrating(rtng);
            cout << endl;
            break;
        }
        case 8: {
            string genre;
            cout << "Enter specific movie genre: " << endl;
            getline(cin, genre);
            ML.filterbygenre(genre);
            cout << endl;
            break;
        }
        case 9: {
            string director;
            cout << "Enter specific movie director: " << endl;
            getline(cin, director);
            ML.filterbydirector(director);
            cout << endl;
            break;
        }
        case 10: {
            string writer;
            cout << "Enter specific movie writer: " << endl;
            getline(cin, writer);
            ML.filterbywriter(writer);
            cout << endl;
            break;
        }
        case 11: {
            ML.recommend();
            break;
        }
        case 12: {
            ML.reset();
            cout << "Movie list reset to original order.\n";
            break;
        }
        case 13: {
            exit = true;
            cout << "Thank you for using MovieMender. Goodbye!\n";
            break;
        }
        default: {
            cout << "Invalid choice. Please select a different option.\n";
        }
    }

  }

  
  return 0;
}
