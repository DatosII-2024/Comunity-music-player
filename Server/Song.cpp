//
// Created by erick on 15/02/24.
//



#include "iostream"
#include "Song.h"
using namespace std;


Song::Song(string _Name, string _Album, string _Artist, int _Year, string _Adress) {
    Name = _Name;
    Adress = _Adress;
    Album = _Album;
    Artist = _Artist;
    Year = _Year;

}

string Song::getName() {
    cout<<Name<<endl;
    return Name;
}
string Song::getAlbum() {
    cout<<Album<<endl;
    return Album;
}
string Song::getArtis(){
    cout<<Artist<<endl;
    return Artist;
}
int Song::getYear() {
    cout<<Year<<endl;
    return Year;
}
int main(){
    Song s = Song("What lies Beaneth","Not","Braking Benjamin",2011,"alksdjkjakds");
    s.getYear();
    s.getAlbum();
    s.getName();
    s.getArtis();

    return 0;
}