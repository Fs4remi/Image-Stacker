// Fatemeh Saremi
// Assignment 2
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_SIZE = 700;        //Largest length for array
typedef int array [MAX_SIZE][MAX_SIZE][3];
void ReadFile(ifstream &file, int colors[MAX_SIZE][MAX_SIZE][3], int &nRows,
              int &nCols, int &brightness, string &header);
int main()
{
    ifstream inputFile;
    ofstream outputFile;

    array colors;                       //Array for pixel values

    //Variables for image header
    int nRows, nCols, brightness;
    string header, imgName;

    cout << "Enter the directory: ";
    cin >> imgName;

    //Testing if a directory with user input name exists
    inputFile.open(imgName + "/" + imgName + "_001" + ".ppm");

    if(inputFile.is_open())             //if a file with the name entered exists, else program exists
    {
        inputFile.close();              //closing the file that was opened to validate user input
        for(int i = 1; i <= 10; i++)    //loop for opening images 1 - 10
        {
            if(i < 10)
            {
                inputFile.open(imgName + "/" + imgName + "_00" + to_string(i) + ".ppm");
            }
            if(i == 10)
            {
                inputFile.open(imgName + "/" + imgName + "_0" + to_string(i) + ".ppm");
            }

            //function to read pixels into the array
            ReadFile(inputFile, colors, nRows, nCols, brightness, header);
            inputFile.close();
        }
        //loop for averaging the array values between 10 images
        for(int r = 0; r < nRows; r++) {
            for(int c = 0; c < nCols; c++){
                for(int color = 0; color < 3; color++) {
                    colors[r][c][color] /= 10;
                }
            }
        }
        outputFile.open(imgName + "_good.ppm");

        outputFile << header << endl;
        outputFile << nRows << " " << nCols << endl;
        outputFile << brightness << endl;

        for(int r = 0; r < nRows; r++) {
            for(int c = 0; c < nCols; c++){
                for(int color = 0; color < 3; color++) {
                    outputFile << colors[r][c][color] << " ";
                }
                outputFile << endl;
            }
        }
        outputFile.close();
    }
    else
    {
        cout << "The directory does not exist." << endl
            << "Program exit." << endl;
    }
    return 0;
}
void ReadFile(ifstream &file, int colors[MAX_SIZE][MAX_SIZE][3], int &nRows,
            int &nCols, int &brightness, string &header)
{
    int temp;

    file >> header;
    file >> nRows >> nCols >> brightness;

    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            for (int color = 0; color < 3; color++) {
                file >> temp;
                colors[r][c][color] += temp;
            }
        }
    }
}