#include <iostream>
#include <fstream>
#include <myhtml/api.h>

/*
 * Cloning of MyHtml, a C library for parsing HTML.
 * This handles transcripts to look at what can be changed or improved to reach GPA goals. Improving on Gradebook Calc V1
 */

using namespace std;

struct HTMLParsed {
    string title;
    string body;
};

int main() {
    string filePath;
    int choice = 0;
    cout << "1) Gradebook HTML" << endl << "2) Transcript HTML" << endl;
    cin >> choice;
    cout << "Enter direct path to HTML file: " << endl;
    cin >> filePath;

    if (choice == 1) {

    }
    else if (choice == 2) {

    }
    else {
        cout << "Invalid choice" << endl;
        return 0;
    }

    return 0;
}
