#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    int line_cnt1;
    int line_cnt2;
    ifstream infile;  // read to open file
    string line;
    double v0[0xFFFFu][2];
    double v1[0xFFFFu][2];
    double distance[0xFFFFu];
    int distance_v2_index[0xFFFFu];

    if (argc < 4) {
        cout << "input error!\r\n" << endl;
        return -1;
    }


    infile.open(argv[1]); //input the name of the file which is opened
    if (!infile.is_open()) {
        cout<<"Can not open the file"<<endl;
        return 0;
    }


    line_cnt1 = 0;
    while(getline(infile, line)){
        if (!line_cnt1) {
            line_cnt1++;
            continue;
        }

        stringstream iss(line);
        char comma;
        iss >> v0[line_cnt1 - 1][0] >> comma >> v0[line_cnt1 - 1][1];

        line_cnt1++;
    }
    infile.close();
    line_cnt1--;

    infile.open(argv[2]); //input the name of the file which is opened
    if (!infile.is_open()) {
        cout<<"Can not open the file"<<endl;
        return 0;
    }

    line_cnt2 = 0;
    while(getline(infile, line)){
        if (!line_cnt2) {
            line_cnt2++;
            continue;
        }

        stringstream iss(line);
        char comma;
        iss >> v1[line_cnt2 - 1][1] >> comma >> v1[line_cnt2 - 1][0];

        line_cnt2++;
    }
    infile.close();
    line_cnt2--;

    if (line_cnt1 != line_cnt2) {
        cout << "Line count does not match!" << endl;
        return -1;
    }

    int i;
    int j;
    double k1;
    double k2;
    double numerator1;
    double denominator1;
    double numerator2;
    double denominator2;
    double distance1;
    double distance2;

    for (i = 0; i < line_cnt1; i++) {
        distance[i] = 0;
        for (j = 1; j < line_cnt1; j++) {
            k1 = 0;
            k2 = 0;

            numerator1   = (v1[j - 1][1] - v0[i][1]);
            denominator1 = (v1[j - 1][0] - v0[i][0]);
            if (abs(denominator1) > 0.0005) {
                k1 = numerator1 / denominator1;
                if (1 == k1) {
                    distance[i] = numerator1 * numerator1 + denominator1 * denominator1;
                    distance_v2_index[i] = j - 1;
                    break;
                }
            }

            numerator2   = (v1[j][1] - v0[i][1]);
            denominator2 = (v1[j][0] - v0[i][0]);
            if (abs(denominator2) > 0.0005) {
                k2 = numerator2 / denominator2;
                 if (1 == k2) {
                    distance[i] = numerator2 * numerator2 + denominator2 * denominator2;
                    distance_v2_index[i] = j;
                    break;
                } else if ((k1 > 0) && (k2 > 0)) {
                    if (    ((k1 > 1) && (k2 < 1))
                         || ((k1 < 1) && (k2 > 1)) ) {
                        distance1 = numerator1 * numerator1 + denominator1 * denominator1;
                        distance2 = numerator2 * numerator2 + denominator2 * denominator2;
                        if (distance1 < distance2) {
                            distance[i] = distance1;
                            distance_v2_index[i] = j - 1;
                        } else {
                            distance[i] = distance2;
                            distance_v2_index[i] = j;
                        }
                        break;
                    }
                }
            }
        }
    }

    int max_distance_index = 0;
    for (i = 1; i < line_cnt1; i++) {
        if (distance[max_distance_index] < distance[i]) {
            max_distance_index = i;
        }
    }

    ofstream outfile;
    outfile.open(argv[3]);
    if (!outfile.is_open()) {
        cout << "Can not open the file" << endl;
        return 0;
    }

    outfile << "x1 = [ ";
    for (i = 0; i < line_cnt1; i++) {
        outfile << setprecision(16) << v0[i][0] << ' ';
    }
    outfile << " ]" << endl;

    outfile << "y1 = [ ";
    for (i = 0; i < line_cnt1; i++) {
        outfile << setprecision(16) << v0[i][1] << ' ';
    }
    outfile << " ]" << endl;

    outfile << "x2 = [ ";
    for (i = 0; i < line_cnt1; i++) {
        outfile << setprecision(16) << v1[i][0] << ' ';
    }
    outfile << " ]" << endl;

    outfile << "y2 = [ ";
    for (i = 0; i < line_cnt1; i++) {
        outfile << setprecision(16) << v1[i][1] << ' ';
    }
    outfile << " ]" << endl;

    outfile << "figure" << endl
            << "hold" << endl
            << "plot(x1, y1, '-b', 'LineWidth', 1)" << endl
            << "plot(x2, y2, '-m', 'LineWidth', 1)" << endl
            << "plot( [ " << v0[max_distance_index][0] << ' ' << v0[max_distance_index][0] << " ], [ "
            << v0[max_distance_index][1] << ' ' << v1[distance_v2_index[max_distance_index]][1] << " ] )" << endl
            << "plot( [ " << v0[max_distance_index][0] << ' ' << v1[distance_v2_index[max_distance_index]][0] << " ], [ "
            << v0[max_distance_index][1] << ' ' << v0[max_distance_index][1] << " ] )" << endl
            << "plot( [ " << v1[distance_v2_index[max_distance_index]][0] << ' ' << v1[distance_v2_index[max_distance_index]][0] << " ], [ "
            << v1[distance_v2_index[max_distance_index]][1] << ' ' << v0[max_distance_index][1] << " ] )" << endl
            << "plot( [ " << v1[distance_v2_index[max_distance_index]][0] << ' ' << v0[max_distance_index][0] << " ], [ "
            << v1[distance_v2_index[max_distance_index]][1] << ' ' << v1[distance_v2_index[max_distance_index]][1] << " ] )" << endl;

    outfile.close();

    cout << "WSNM:" << abs(v0[max_distance_index][0] - v1[distance_v2_index[max_distance_index]][0]) << endl;

    return 0;
}




