// FCAI – Programming 1 – 2022 - Assignment 3
// Program Name: filters.cpp
// Last Modification Date: 6/4/2022
// Author and ID and Group: Rana Taha Hassan  20210132 S25,26 G:A
// Author and ID and Group: Roaa Emad Eldin Muhammad 20210139 S25,26 G:A
// Author and ID and Group: Shrouk Heshmat Abu El-Safa  20210174 S25,26 G:A
// Teaching Assistant: Eng.Mahmoud Fateaha.

#include <iostream>
#include <cstring>
#include <cmath>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char second_image[SIZE][SIZE][RGB];
unsigned char new_matrix[SIZE][SIZE][RGB];

void load_image(){
    char image_filename [100];
    cout  << "Please Enter the Name of the Image without any Extensions: " << endl;
    cin >> image_filename;
    strcat(image_filename, ".bmp"); // Add to it .bmp extension and load image
    readRGBBMP(image_filename, image); // Add it to a 256*256 matrix
}

void load_second_image(){
    char sec_image_file_name[100];
    cout << "Please Enter the Name of Second Image to Merge with, without any Extensions :" << endl;
    cin >> sec_image_file_name;
    strcat(sec_image_file_name, ".bmp");
    readRGBBMP(sec_image_file_name, second_image);
}

void save_image(unsigned char arr[SIZE][SIZE][RGB]){
    char image_filename [100];
    cout << "Please Enter the Name of the Image You Want to Save as: " << endl;
    cin >> image_filename;
    strcat(image_filename, ".bmp"); // Add to it .bmp extension and load image
    writeRGBBMP(image_filename, arr);
}

void lighten_image(){
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            for (int color = 1; color <= 3; color++){
                int pixel_difference = 255 - image[row][col][color];
                int range = pixel_difference / 2;
                image[row][col][color] += range;
            }
        }
    }
}

void darken_image(){
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            for (int color = 1; color <= 3; color++) {
                image[row][col][color] -= (image[row][col][color] / 2);
            }
        }
    }
}

void merge_images(){
    load_second_image();
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            for (int color = 1; color <= 3; color++){
                int average_pixel = (image[row][col][color] + second_image[row][col][color]) / 2;
                image[row][col][color] = average_pixel;
            }
        }
    }
}

void shrink() {
    string choice;
    cout << "Do You Want to Shrink to the (1/2), (1/3) or (1/4)?" << endl;
    cin >> choice;
    if (choice == "1/2") {
        for (int inc = 0, row = 0; row < SIZE; inc++, row += 2) {
            for (int inc2 = 0, col = 0; col < SIZE; inc2++, col += 2) {
                for (int color = 1; color <= 3; color++){
                    image[inc][inc2][color] = image[row][col][color];
                }
            }
        }
        for (int r = 128; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                for (int color = 1; color <= 3; color++){
                    image[r][c][color] = 255;
                }
            }
        }
        for (int r = 0; r < SIZE / 2; r++) {
            for (int c = 128; c < SIZE; c++) {
                for (int color = 1; color <= 3; color++){
                    image[r][c][color] = 255;
                }
            }
        }
    }
    else if (choice == "1/3") {
        for (int inc = 0, row = 0; row < SIZE; inc++, row += 3) {
            for (int inc2 = 0, col = 0; col < SIZE; inc2++, col += 3) {
                for (int color = 1; color <= 3; color++){
                    image[inc][inc2][color] = image[row][col][color];
                }
            }
        }
        // Fill the rest with white
        for (int r = SIZE / 3; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                for (int color = 1; color <= 3; color++){
                    image[r][c][color] = 255;
                }
            }
        }
        for (int r = 0; r < SIZE / 3; r++) {
            for (int c = SIZE / 3; c < SIZE; c++) {
                for (int color = 1; color <= 3; color++){
                    image[r][c][color] = 255;
                }
            }
        }
    }
    else if (choice == "1/4"){
        for (int inc = 0, row = 0; row < SIZE; inc++, row += 4) {
            for (int inc2 = 0, col = 0; col < SIZE; inc2++, col += 4) {
                for (int color = 1; color <= 3; color++) {
                    image[inc][inc2][color] = image[row][col][color];
                }
            }
        }
        for (int r = SIZE / 4; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                for (int color = 1; color <= 3; color++){
                    image[r][c][color] = 255;
                }
            }
        }
        for (int r = 0; r < SIZE / 4; r++) {
            for (int c = SIZE / 4; c < SIZE; c++) {
                for (int color = 1; color <= 3; color++){
                    image[r][c][color] = 255;
                }
            }
        }
    }
}

void blur(){
    double average;
    for (int r = 0; r < SIZE; r++){
        for (int c = 0; c < SIZE; c++){
            for (int color = 1; color <= 3; color++) {
                average = image[r - 2][c - 2][color] + image[r - 2][c - 1][color] + image[r - 2][c][color] + image[r - 2][c + 1][color] + image[r - 2][c + 2][color]
                        + image[r - 1][c - 2][color] + image[r - 1][c - 1][color] + image[r - 1][c][color] + image[r - 1][c + 1][color] + image[r - 1][c + 2][color]
                        + image[r][c - 2][color] + image[r][c - 1][color] + image[r][c][color] + image[r][c + 1][color] + image[r][c + 2][color]
                        + image[r + 1][c - 2][color] + image[r + 1][c - 1][color] + image[r + 1][c][color] + image[r + 1][c + 1][color] + image[r + 1][c + 2][color]
                        + image[r + 2][c - 2][color] + image[r + 2][c - 1][color] + image[r + 2][c][color] + image[r + 2][c + 1][color] + image[r + 2][c + 2][color];
                int new_value = round(average / 25);
                second_image[r][c][color] = new_value;
            }
        }
    }
}

void black_and_white(){
    int avg;
    for (int i = 0 ; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int y = 0; y <3; y++) {
                avg = (image[i][j][0]* 0.299) + (image[i][j][1]* 0.587) + (image[i][j][2]*0.114);
                image[i][j][y] = avg;
                if (avg > 127) {
                    for (int k = 0; k <3; k++) {
                        image[i][j][k] = 255;
                    }
                }
                else {
                    for (int k = 0; k < 3; k++) {
                        image[i][j][k] = 0;
                    }
                }
            }
        }
    }
}

void detect_edges() {
    int choice;
    cout << "please enter part you want to reflect \n1-black and white adges  \n 2-colored edges ";
    cin >> choice;
    if (choice == 1) {
        black_and_white();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int y = 1; y <= 3; y++) {
                    if (image[i][j][y] == image[i][j - 1][y] && image[i][j][y] == image[i][j + 1][y] &&
                        image[i][j][y] == image[i - 1][j][y] && image[i][j][y] == image[i + 1][j][y]) {
                        second_image[i][j][y] = 255;
                    }
                    else {
                        second_image[i][j][y] = 0;
                    }
                }
            }
        }
    }
    else if (choice == 2) {
        int gx, gy;
        int scale;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int y = 1; y <= 3; y++) {
                    gx = (image[i - 1][j - 1][y] * -1) + (image[i][j - 1][y] * -2) + (image[i + 1][j - 1][y] * -1) +
                         (image[i - 1][j + 1][y] * 1) + (image[i][j + 1][y] * 2) + (image[i + 1][j + 1][y] * 1);
                    gy = (image[i - 1][j - 1][y] * 1) + (image[i - 1][j][y] * 2) + (image[i - 1][j + 1][y] * 1) +
                         (image[i + 1][j - 1][y] * -1) + (image[i + 1][j][y] * -2) + (image[i + 1][j + 1][y] * -1);
                    scale = sqrt((gx * gx) + (gy * gy));
                    if (scale > 255) {
                        scale = 255;
                    } else if (scale < 0) {
                        scale = 0;
                    }
                    second_image[i][j][y] = scale;
                }
            }
        }
    }
    else{
        cout << "invalid input please enter 1 or 2 \n";
    }
}

void flip() {
    int direc;
    cout << " choose : 1-horizontally or 2-vertically(v)\n";
    cout << " (1,2):\n";
    cin >> direc;
    if (direc == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int y = 1; y <= 3; y++) {
                    second_image[i][j][y] = image[i][255 - j][y];
                }
            }
        }
    } else if (direc == 2) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int y = 1; y <= 3; y++) {
                    second_image[i][j][y] = image[255 - i][j][y];
                }
            }
        }
    }
    save_image(second_image);
}

void invert_image()
{
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            for (int k=1;k<=3;k++)
            {
                new_matrix[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
    save_image(new_matrix);
}

void mirror (){
    int choice;
    cout <<"please enter part you want to reflect \n1-left \n 2-right \n 3-upper \n 4-lower";
    cin>> choice;
    if (choice==1){
        for (int i=0 ;i<SIZE; i++){
            for (int j=0 ;j<SIZE ;j++)
                for(int y=1;y<=3;y++)
                    image [i][SIZE-j][y]=image[i][j][y];
        }
    }
    else if (choice==2){
        for (int i=0 ;i<SIZE; i++){
            for (int j=0 ;j<SIZE ;j++)
                for(int y=1;y<=3;y++)
                    image [i][j][y]=image[i][SIZE-j][y];
        }
    }
    else if (choice==3){
        for (int i=0 ;i<SIZE; i++){
            for (int j=0 ;j<SIZE ;j++)
                for(int y=1;y<=3;y++)
                    image [SIZE-i][j][y]=image[i][j][y];
        }
    }
    else if (choice==4){
        for (int i=0 ;i<SIZE; i++){
            for (int j=0 ;j<SIZE ;j++)
                for(int y=1;y<=3;y++)
                    image [i][j][y]=image[SIZE-i][j][y];
        }
    }
    else{
        cout<<"invalid input please enter 1 or 2 or 3 or 4\n";
    }
}

void rotate_image() {
    string degree;
    cout << "please enter whether you want to rotate the image by 90 degrees or 180 degrees or 270 degrees" << "\n";
    cin >> degree;
    if (degree == "270") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 1; k <= 3; k++) {
                    new_matrix[i][j][k] = image[j][i][k];
                }
            }
        }
    } else if (degree == "180") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 1; k <= 3; k++) {
                    new_matrix[i][j][k] = image[255 - i][255 - j][k];
                }

            }
        }
    } else if (degree == "90") {
        unsigned char helper_matrix[SIZE][SIZE][RGB];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 1; k <= 3; k++) {
                    helper_matrix[i][j][k] = image[255 - (255 - j)][255 - i][255 - k];         //270//
                    new_matrix[i][j][k] = image[255 - (255 - (255 - j))][255 - (255 - i)][255 - (255 - k)];
                }
            }
        }
    }
}

void shuffle_image()
{
    int firstquarter, secondquarter, thirdquarter, fourthquarter;
    cout << "please enter the number of the first quarter you want it,if you want it to be the first put 1,"
            "if you want it to be the  second put 2,if you want it to be the third put 3,"
            "and if you want it to be the first put 4";
    cin >> firstquarter;
    if (firstquarter == 1)
    {
        for (int i = 0; i<128; i++)
        {
            for (int j = 0; j < 128; j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[i][j][k] = image[i][j][k];
                }
            }
        }
    } else if (firstquarter == 2)
    {
        for (int i = 0,r=0; i < 128; i++,r++)
        {
            for (int j = 128,c=0; c < 128; j++,c++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    } else if (firstquarter == 3)
    {
        for (int i = 128,r=0; r < 128; i++,r++)
        {
            for (int j = 0,c=0; j < 128; j++,c++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    } else if (firstquarter == 4)
    {
        for (int i = 128,r=0; r < 128; i++,r++)
        {
            for (int j = 128,c=0; c < 128; j++,c++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    cout << "please enter the number of the second quarter you want it,if you want it to be the first put 1,"
            "if you want it to be the  second put 2,if you want it to be the third put 3,"
            "and if you want it to be the first put 4";
    cin >> secondquarter;
    if (secondquarter == 1)
    {
        for (int i = 0,r=0; i < 128; r++,i++)
        {
            for (int j = 0,c=128; j < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    } else if (secondquarter == 2)
    {
        for (int i = 0,r=0; i < 128; r++,i++)
        {
            for (int j = 128,c=128; j < 256; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (secondquarter==3)
    {
        for (int i = 128,r=0; r < 128; r++,i++)
        {
            for (int j = 0,c=128; j < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (secondquarter==4)
    {
        for (int i = 128,r=0; r < 128; r++,i++)
        {
            for (int j = 128,c=128; j < 256; j++,c++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    cout<<"please enter the number of the third quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4";
    cin>>thirdquarter;
    if (thirdquarter==1)
    {
        for (int i = 0,r=128; r<256; i++,r++)
        {
            for (int j = 0,c=0; c < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (thirdquarter==2)
    {
        for (int i = 0,r=128; i < 128; i++,r++)
        {
            for (int j = 128,c=0;c < 128; j++,c++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (thirdquarter==3)
    {
        for (int i = 128,r=128; i < 256; r++,i++)
        {
            for (int j = 0,c=0; j < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (thirdquarter==4)
    {
        for (int i = 128,r=128; i < 256; r++,i++)
        {
            for (int j = 128,c=0; c < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    cout<<"please enter the number of the fourth quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4";
    cin>>fourthquarter;
    if (fourthquarter==1)
    {
        for (int i = 0,r=128; i < 128; r++,i++)
        {
            for (int j = 0,c=128; j < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (fourthquarter==2)
    {
        for (int i = 0,r=128; i < 128; i++,r++)
        {
            for (int j = 128,c=128; j < 256; j++,c++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (fourthquarter == 3)
    {
        for (int i = 128,r=128; i < 256; r++,i++)
        {
            for (int j = 0,c=128; j < 128; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    else if (fourthquarter == 4)
    {
        for (int i = 128,r=128; i < 256; r++,i++)
        {
            for (int j = 128,c=128; j < 256; c++,j++)
            {
                for (int k=0;k<3;k++)
                {
                    new_matrix[r][c][k] = image[i][j][k];
                }
            }
        }
    }
    save_image(new_matrix);
}

void enlarge_image()
{
    int answer;
    cout << "please choose whether you want to enlarge the 1st or 2nd or 3rd or 4th quarter";
    cout << "if 1st choose number 1,if 2nd choose number 2,if 3rd choose number 3 and if 4th choose number 4: " << endl;
    cin >> answer;
    if (answer == 1)
    {
        unsigned char first_quarter_matrix[SIZE][SIZE][RGB];
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k=0;k<3;k++)
                {
                    first_quarter_matrix[i][j][k] = image[i / 2][j / 2][k];
                }
            }
        }
        save_image(first_quarter_matrix);
    } else if (answer == 2)
    {
        unsigned char second_quarter_matrix[SIZE][SIZE][RGB];
        for (int k=0,i=0;i<SIZE;k++,i+=2)
        {
            for (int z=0,j=0;j<SIZE;z++,j+=2)
            {
                for (int c=0,r=0;r<3;c++,r+=2)
                {
                    second_quarter_matrix[i][j][r]=image[k][z][c];
                    second_quarter_matrix[i+1][j][r]=image[k][z][c];
                    second_quarter_matrix[i+1][j+1][r]=image[k][z][c];
                    second_quarter_matrix[i][j+1][r]=image[k][z][c];
                }

            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k=0;k<3;k++)
                {
                    second_quarter_matrix[i][j][k] = image[i/2][128+(j/2)][k];
                }
            }
        } save_image(second_quarter_matrix);

    }else if (answer == 3)
    {
        unsigned char third_quarter_matrix[SIZE][SIZE][RGB];
        for (int k=0,i=0;i<SIZE;k++,i+=2)
        {
            for (int z=0,j=0;j<SIZE;z++,j+=2)
            {
                for (int c=0,r=0;r<3;c++,r+=2)
                {
                    third_quarter_matrix[i][j][r]=image[k][z][c];
                    third_quarter_matrix[i+1][j][r]=image[k][z][c];
                    third_quarter_matrix[i+1][j+1][r]=image[k][z][c];
                    third_quarter_matrix[i][j+1][r]=image[k][z][c];
                }
            }
        }
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                for (int k=0;k<3;k++)
                {
                    third_quarter_matrix[i][j][k]=image[128+(i/2)][(j/2)-256][k];
                }
            }
        }
        save_image(third_quarter_matrix);
    }else if (answer == 4)
    {
        unsigned char fourth_quater_matrix[SIZE][SIZE][RGB];
        for (int k=0,i=0;i<SIZE;k++,i+=2)
        {
            for (int z=0,j=0;j<SIZE;z++,j+=2)
            {
                for (int c=0,r=0;r<3;c++,r+=2)
                {
                    fourth_quater_matrix[i][j][r]=image[k][z][c];
                    fourth_quater_matrix[i+1][j][r]=image[k][z][c];
                    fourth_quater_matrix[i+1][j+1][r]=image[k][z][c];
                    fourth_quater_matrix[i][j+1][r]=image[k][z][c];
                }
            }
        }
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                for (int k=0;k<3;k++)
                {
                    fourth_quater_matrix[i][j][k]=image[128+(i/2)][(j/2)-128][k];
                }
            }
        }
        save_image(fourth_quater_matrix);
    }
}


int main() {
    bool condition = true;
    int answer;
    cout << "Welcome to Image Filters Program :)" << endl;
    while (condition){
        cout << "Please Choose a Filter to Apply or 0 to EXIT the Program:" << endl;
        cout << "1.Black and White Filter.\n2.Invert Filter.\n3.Merge Filter.\n4.Flip Filter."
                "\n5.Rotate Image Filter.\n6.Darken and Lighten Image Filter.\n7.Detect Edges Image Filter."
                "\n8.Enlarge Image Filter.\n9.Shrink Image Filter.\n10.Mirror Image Filter."
                "\n11.Shuffle Image Filter.\n12.Blur Image Filter.\n0.Exit." << endl;
        cin >> answer;
        if(answer == 0){
            condition = false;
        }
        else{
            load_image();
            if (answer == 1){
                black_and_white();
                save_image(image);
                continue;
            }
            else if (answer == 2){
                invert_image();
                save_image(image);
                continue;
            }
            else if (answer == 3){
                merge_images();
                save_image(image);
                continue;
            }
            else if (answer == 4){
                flip();
                continue;
            }
            else if (answer == 5){
                rotate_image();
                continue;
            }
            else if (answer == 6){
                char answer2;
                cout << "Do Want to Darken (Enter: d) or Lighten (Enter: l) the Image?" << endl;
                cin >> answer2;
                if (answer2 == 'd'){
                    darken_image();
                    save_image(image);
                    continue;
                }
                else if(answer2 == 'l'){
                    lighten_image();
                    save_image(image);
                    continue;
                }
            }
            else if (answer == 7){
                detect_edges();
                save_image(second_image);
                continue;
            }
            else if (answer == 8){
                enlarge_image();
                continue;
            }
            else if (answer == 9) {
                shrink();
                save_image(image);
                continue;
            }
            else if (answer == 10){
                mirror();
                save_image(image);
                continue;
            }
            else if (answer == 11){
                shuffle_image();
                continue;
            }
            else if (answer == 12){
                blur();
                save_image(second_image);
                continue;
            }
        }
    }
}
