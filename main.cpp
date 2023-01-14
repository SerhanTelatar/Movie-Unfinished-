#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "movie2.h"
#include "movie2.cpp"
#include "strutils.cpp"


void systemFile(ifstream &i, vector<Movie>array){
    Movie movie;
    string fileName;
    cout<<"Please enter the movie list filename: " ;
    cin>>fileName;
    i.open(fileName.c_str());
    while(i.fail()){
        cout<<"Please check filename! Enter a correct movie list filename: ";
        cin>>fileName;
        i.open(fileName.c_str());
    }
    string line;
    string it;
    string what;
    int year;
    while(getline(i, line)){
        istringstream stringStream(line);
        it = " ";
        while(stringStream >> what) {
            if(isdigit(what[0])){
                year = atoi(what);
                movie.setYear(year);
                break;
            }else{
                it += what;
                it += " ";
                movie.setName(it);
            }
        };

        stringStream >>what;
        string gen = what;
        movie.setGenre(gen);
        array.push_back(movie);
        it = " ";
    }
}

void sort(vector<Movie> & array){
    Movie movie;
    int maxNum;
    for(int i = 0; i < array.size() - 1;i++){
        maxNum = i;
        for(int j = i + 1; j < array.size(); j++){
            if(array[j].getYear() > array[i].getYear()){
                maxNum = j;
            }
        }
        movie = array[i];
        array[i].setName(array[maxNum].getName());
        array[maxNum].setName(movie.getName());

        array[i].setGenre(array[maxNum].getGenre());
        array[maxNum].setGenre(movie.getGenre());

        array[i].setYear(array[maxNum].getYear());
        array[maxNum].setYear(movie.getYear());
    }
    int k = 0;
    while(k<array.size()-1){
        int l = k +1;
        while(l<array.size()){
            if(array[k].getYear() == array[l].getYear()){
                string  nameGetter1 = LowerString(array[k].getName());
                string  nameGetter2 = LowerString(array[l].getName());
                if(nameGetter1 > nameGetter2){
                    movie = array[k];
                    array[k].setName(array[l].getName());
                    array[l].setName(movie.getName());

                    array[k].setGenre(array[l].getGenre());
                    array[l].setGenre(movie.getGenre());

                    array[k].setYear(array[l].getYear());
                    array[l].setYear(movie.getYear());
                }
            }
            l++;
        }
        k++;
    }

}

bool yearChecker(vector<Movie>array, int year){
    for(int i = 0; i<array.size();i++){
        if(year == array[i].getYear()){
            return true;
        }
    }
    return false;
}

bool genreChecker(vector<Movie>array, string genre){
    for(int i = 0; i<array.size();i++){
        if(genre == LowerString(array[i].getGenre())){
            return true;
        }
    }
    return false;
}

using namespace std;

int main() {

    vector<Movie>array;
    ifstream input_read;

    cout<<"Welcome to the movie recommender program!"<<endl<<endl;

    systemFile(input_read,array);
    sort(array);

    int action;
    cout<<"Please select your action:"<<endl;
    cout<<"1. Select the genre of the movie that you want to watch"<<endl;
    cout<<"2. Select the year of the movie that you want to watch"<<endl;
    cout<<"3. Exit program"<<endl<<endl;

    cout<<"Enter your choice:"<<endl;
    cin>>action;

    while(true){
        if(action == 1 || action == 2 || action ==3){
            if(action == 1){
                string genre;
                cout<<"Please enter the genre of the movie you want to watch: "<<endl;
                cin>>genre;
                if(genreChecker(array, genre)){
                    cout<<genre<<" movies from newest to oldest:"<< endl;
                    for(int i =0; i< array.size(); i++){
                        if (LowerString(array[i].getGenre()) == LowerString(genre)){
                            cout<< "Movie name:" <<array[i].getName() << "Release Year: " << array[i].getYear() << endl;
                        }
                    }
                }else{
                    cout<<"There are no "<<genre<<" movies!"<<endl;
                }

            }
            if(action == 2){
                string stringYear;
                cout<<"Please enter the year of the movie you want to watch: ";
                cin>>stringYear;
                string shortLine = "-";
                int intYear = atoi(stringYear);
                if(stringYear.find(shortLine) == string::npos){
                    yearChecker(array, intYear);
                    int size = array.size();
                    for(int i =0;i<size; i++){
                        if(array[i].getYear() == intYear){
                            cout <<"Movies released in "<<intYear<<" from A to Z:" << endl;
                            break;
                        }
                    }
                    int j =0;
                    while(j<size){
                        if(array[j].getYear() == intYear){
                            cout<<"Movie name:"<<array[j].getName()<<"Genre: "<<array[j].getGenre()<<endl;
                        }
                        if(yearChecker(array, intYear)){
                            cout<<"There are no movies released in "<<intYear<<"!"<<endl;
                            break;
                        }
                    }
                }else{
                    string shortLine = "-";
                    bool isAnyYearExisted = false;
                    int indexLocation = stringYear.find(shortLine);

                    string firstString = stringYear.substr(0, indexLocation);
                    string secondString = stringYear.substr(indexLocation+1);

                    int firstInt = atoi(firstString);
                    int secondInt = atoi(secondString);

                    int i = 0;
                    while(i<array.size()){
                        if(array[i].getYear() <= secondInt && firstInt <= array[i].getYear()){
                            cout<<"Movies released between the years "<<stringYear<<" from A to Z with decreasing year ordering:"<<endl;
                            break;
                        }
                        i++;
                    }
                    int j = 0;
                    do {
                        if(array[j].getYear() <= secondInt && firstInt <= array[j].getYear()){
                            cout<<"Movie name:"<<array[i].getName()<<"Release Year: "<<array[j].getYear()<<" Genre: "<<array[j].getGenre()<<endl;
                            isAnyYearExisted = true;
                        }
                        if(!isAnyYearExisted){
                            cout<<"There are no movies released between "<<stringYear<<"!"<<endl;
                        }
                        j++;
                    }while (j<array.size());
                }
            }
            if(action == 3){
                break;
            }
        }else{
            cout<<"Invalid action!"<<endl;
        }
        cout<<"Thank you…"<<endl;
    }
}
