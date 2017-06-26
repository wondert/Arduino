#include <iostream>

using namespace std;        // This imports the std library namespace for us. That way we don't have to type std::cout. We can just type cout

string proper_age(string);
string child(string);

int main() {
   string t = child("Daniel");
   string j = proper_age("11");
   cout << "Hello World: " << t << j << endl;

   return 0;
}

string proper_age(string y) {
    string how_old = " He is " + y + " " + "years old!";
    return how_old;
}

string child(string kidsname) {
    string given_name = kidsname + " " + "is his name!";
    return given_name;
}
