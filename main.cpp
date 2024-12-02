#include "movie.hpp"
#include <iostream>

using namespace std;

void displayMenu() {
    cout << "\n--- MovieMender Menu ---\n";
    cout << "1. Sort movies by year\n";
    cout << "2. Sort movies by rating\n";
    cout << "3. Sort movies by genre\n";
    cout << "4. Sort movies by director\n";
    cout << "5. Sort movies by writer\n";
    cout << "6. Reset movie list to original order\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

void displayMovies(vector<Movie>& movies){
  cout << "\n--- Movie List ---\n";
  for(auto movie : movies){
    cout << "Title: " << movie.title << ", Year: " << movie.year << ", Rating: " << movie.rating << "\n";
  }  
}

int main(){
  bool exit = false;
  while(!exit){
    displayMenu();
    int choice;
    cin >> choice;
    cin.ignore(); //create a newline buffer

    //call appropriate function based on choice
    switch (choice){
      case 1:
            movieList.sortbyyear();
            cout << "Movies sorted by year.\n";
            break;
        case 2:
            movieList.sortbyrating();
            cout << "Movies sorted by rating.\n";
            break;
        case 3: {
            string genre;
            cout << "Enter genre to sort by: ";
            cin.ignore(); //newline buffer
            getline(cin, genre);
            movieList.sortbygenre(genre);
            cout << "Movies sorted by genre.\n";
            break;
        }
        case 4: {
            string director;
            cout << "Enter director to sort by: ";
            cin.ignore(); //newline buffer
            getline(cin, director);
            movieList.sortbydirector(director);
            cout << "Movies sorted by director.\n";
            break;
        }
        case 5: {
            string writer;
            cout << "Enter writer to sort by: ";
            cin.ignore(); //newline buffer
            getline(cin, writer);
            movieList.sortbywriter(writer);
            cout << "Movies sorted by writer.\n";
            break;
        }
        case 6:
            movieList.reset();
            cout << "Movie list reset to original order.\n";
            break;
        case 7:
            exit = true;
            cout << "Thank you for using MovieMender. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please select a different option.\n";
        
    }

  }

  
  return 0;
}
