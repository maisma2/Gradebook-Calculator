#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>

using namespace std;
struct Assignment{
    string item;
    string itemCategory;
    string activity;
    double gradePoints;
    double possiblePoints;
};

string findSubstring(string input, char startChar, char endChar) {
    size_t startIndex = input.find(startChar);
    if (startIndex == string::npos) {
        // start character not found in input string
        return "";
    }
    startIndex++; // move past the start character
    size_t endIndex = input.find(endChar, startIndex);
    if (endIndex == string::npos) {
        // end character not found in input string
        return "";
    }
    return input.substr(startIndex, endIndex - startIndex);
}
size_t findSubstringInt(string input, char startChar, char endChar) {
    size_t startIndex = input.find(startChar);
    if (startIndex != string::npos) {
        startIndex++; // move past the start character
        size_t endIndex = input.find(endChar, startIndex);
        if (endIndex != string::npos) {
            // end character not found in input string
            return endIndex;
        }
    }
    return -1;
}

int main() {
    string line;
    string gradeBook = "C:\\Users\\maism\\Documents\\GitHub\\CS211\\GradeBookCalc\\cmake-build-debug\\Gradebook\\myGrades.htm"; //file path
    string newGradeBook = "C:\\Users\\maism\\Documents\\GitHub\\CS211\\GradeBookCalc\\cmake-build-debug\\Gradebook\\calcGrades.csv";//copy same file to new area, this is going to be edited
    vector<string> lines; //This will hold all the raw lines of the file
    vector<Assignment> assignments; //each vector is an assignment, an assignment holds item, activity, grade, and status
    vector<string> itemCategories; //holds all the item categories

    ifstream source(gradeBook, ios::in); //open file as read only
    ofstream destination(newGradeBook, ios::out); //open file as write only

    //check that both files are valid
    if (!source || !destination){
        cerr << "Error opening source or creating destination file" << endl;
        return -1;
    }

    //add raw file of gradebook file to vector
    while(source.is_open()){
        while(getline(source, line)){
            lines.push_back(line); //add each line to the vector
        }
        source.close();
    }

    //gets title of the gradebook
    string title = findSubstring(lines[3], '>', '<');
    cout << title << endl;


    regex items(R"(\s*<!--\s*Items Column\s*-->)");
    regex itemCat(R"(<div class="itemCat">(.*?)<\/div>)");
    regex activity(R"(\s*<!--\s*Activity Column\s*-->)");
    regex grade(R"(<span class="grade".*>([\d\.]+)<)");
    regex points(R"(<span class="pointsPossible[^>]*>/(.*)<\/span>)");
    regex status(R"(\s*<!--\s*Status Column\s*-->)");

    vector<int> indexes;
    for (int i = 0; i < lines.size(); i++) {
        //search for the start of the assignment, each thing starts with <!-- Items Column -->
        smatch match;
        if (regex_search(lines[i], match, items)) {
            Assignment temp;
            temp.item = findSubstring(lines[i+2], '>', '<');

            // search for the item category
            for (int j = i; j < lines.size(); j++) {
                if (regex_search(lines[j], match, activity)) {
                    temp.activity = findSubstring(lines[j+3], '>', '<');
                }
                if (regex_search(lines[j], match, grade)) {
                    smatch gradeMatch;
                    if (regex_search(lines[j], gradeMatch, grade)) {
                        string tempGrade = gradeMatch[1];
                        temp.gradePoints = stod(tempGrade);
                    }
                }
                if (regex_search(lines[j], match, points)) {
                    smatch pointsMatch;
                    if (regex_search(lines[j], pointsMatch, points)) {
                        string tempPoints = pointsMatch[1];
                        temp.possiblePoints = stod(tempPoints);
                    }
                }
                if (regex_search(lines[j], match, itemCat)) {
                    smatch itemCatMatch;
                    if (regex_search(lines[j], itemCatMatch, itemCat)) {
                        temp.itemCategory = itemCatMatch[1];
                        if(find(itemCategories.begin(), itemCategories.end(), temp.itemCategory) == itemCategories.end()){
                            itemCategories.push_back(temp.itemCategory);
                        }
                    }
                }
                if (regex_search(lines[j], match, status)) {
                    assignments.push_back(temp);
                    break; // exit the nested loop
                }
            }
        }
    }
        //Parse activity since it fills Upcoming and Ungraded as full points
        for (int i = 0; i < assignments.size(); i++) {
            if (assignments[i].activity == "Submitted" || assignments[i].activity == "Upcoming") {
                //delete the assignment
                assignments.erase(assignments.begin() + i);
            }
        }
        if (destination.is_open()) {
            destination << "Item,Category,Activity,Grade Points,Possible Points" << endl;
            for (int i = 0; i < assignments.size(); i++) {
                destination << assignments[i].item << ","
                         << assignments[i].itemCategory << ","
                         << assignments[i].activity << ","
                         << assignments[i].gradePoints << ","
                         << assignments[i].possiblePoints << endl;
            }
            destination.close();
        }

        else {
             cout << "Unable to open file" << endl;
        }

        //calculate unweighted average

        double unweightedAvg = 0;
        for(int i = 0; i < assignments.size(); i++){
            unweightedAvg += (assignments[i].gradePoints/assignments[i].possiblePoints);
        }
        cout << "Overall unweighted average: " << unweightedAvg << endl;

        cout << "Here are the item categories, in order input the weights and separate with a space" << endl;
        for(int i = 0; i < itemCategories.size(); i++){
            cout << itemCategories[i] << endl;
        }
        string weights;
        getline(cin, weights);
        vector<double> weightsVector;
        double weight;
        //using stringstream to split the string into a vector of doubles
        stringstream ss(weights);
        while(ss >> weight){
            weightsVector.push_back(weight);
        }

        



    return 0;



}
