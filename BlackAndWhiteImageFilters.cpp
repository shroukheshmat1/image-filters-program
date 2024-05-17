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

unsigned char image [SIZE][SIZE];
unsigned char second_image[SIZE][SIZE];
unsigned char new_matrix[SIZE][SIZE];
unsigned char submatrix[SIZE][SIZE];

void load_image(){
    char imagefilename [100];
    cout  << "Please Enter the Name of the Image without any Extensions: " << endl;
    cin >> imagefilename;
    strcat(imagefilename, ".bmp"); // Add to it .bmp extension and load image
    readGSBMP(imagefilename, image); // Add it to a 256*256 matrix
}
// To load the second image if merge process is wanted
void load_second_image(){
    char sec_image_file_name[100];
    cout << "Please Enter the Name of Second Image to Merge with, without any Extensions :" << endl;
    cin >> sec_image_file_name;
    strcat(sec_image_file_name, ".bmp");
    readGSBMP(sec_image_file_name, second_image);
}

void save_image(unsigned char arr[SIZE][SIZE]){
    char imagefilename [100];
    cout << "Please Enter the Name of the Image You Want to Save as: " << endl;
    cin >> imagefilename;
    strcat(imagefilename, ".bmp"); // Add to it .bmp extension and load image
    writeGSBMP(imagefilename, arr);
}

void lighten_image(){
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            int pixel_difference = 255 - image[row][col];
            int range = pixel_difference / 2;
            image[row][col] += range;
        }
    }
}

void darken_image(){
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            image[row][col] -= (image[row][col] / 2);
        }
    }
}

void merge_images(){
    load_second_image();
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            int average_pixel = (image[row][col] + second_image[row][col]) / 2;
            image[row][col] = average_pixel;
        }
    }
}

void black_and_white(){
    for (int i = 0 ; i < SIZE; i++){
        for(int j = 0;j < SIZE; j++ ){
            if (image[i][j] > 127)
                image[i][j] = 255;
            else
                image[i][j] = 0;
        }
    }
}

void invert_image()
{
    for (int i=0;i<SIZE;i++){
        for (int j=0;j<SIZE;j++){
            image[i][j] = 255 - image[i][j];
        }
    }
}

void rotate_image()
{
    string degree;
    cout<<"Please Enter Whether You Want to Rotate the Image by 90 Degrees or 180 Degrees or 270 Degrees"<<"\n";
    cin>>degree;
    if (degree=="270"){
        for (int i=0;i<SIZE;i++){
            for (int j=0;j<SIZE;j++){
                new_matrix[i][j]=image[j][i] ;
            }
        }
    }
    else if (degree=="180"){
        for (int i=0;i<SIZE;i++){
            for (int j=0;j<SIZE;j++){
                new_matrix[i][j]=image[255-i][255-j];
            }
        }
    }
    else if (degree=="90"){
        unsigned char helper_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++){
            for (int j=0;j<SIZE;j++){
                helper_matrix[i][j]=image[255-(255-j)][255-i];         //270//
                new_matrix[i][j]=image[255-(255-(255-j))][255-(255-i)];
            }
        }
    }
    save_image(new_matrix);
}

void flip_image() {
    int direc;
    cout << " Do you want to flip it: 1-horizontally or 2-vertically(v)\n";
    cout <<" (1,2):\n";
    cin>>direc;
    if (direc ==1 ){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                submatrix[i][j]=image[i][255-j];
            }
        }
    }
    else if (direc==2){
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                submatrix[i][j]=image[255-i][j];

            }

        }
    }
    save_image(submatrix);
}

void shrink() {
    string choice;
    cout << "Do You Want to Shrink to the (1/2), (1/3) or (1/4)?" << endl;
    cin >> choice;
    if (choice == "1/2") {
        for (int inc = 0, row = 0; row < SIZE; inc++, row += 2) {
            for (int inc2 = 0, col = 0; col < SIZE; inc2++, col += 2) {
                image[inc][inc2] = image[row][col];
            }
        }
        for (int r = 128; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                image[r][c] = 255;
            }
        }
        for (int r = 0; r < SIZE / 2; r++) {
            for (int c = 128; c < SIZE; c++) {
                image[r][c] = 255;
            }
        }
    }
    else if (choice == "1/3") {
        for (int inc = 0, row = 0; row < SIZE; inc++, row += 3) {
            for (int inc2 = 0, col = 0; col < SIZE; inc2++, col += 3) {
                image[inc][inc2] = image[row][col];
            }
        }
        // Fill the rest with white
        for (int r = SIZE / 3; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                image[r][c] = 255;
            }
        }
        for (int r = 0; r < SIZE / 3; r++) {
            for (int c = SIZE / 3; c < SIZE; c++) {
                image[r][c] = 255;
            }
        }
    }
    else if (choice == "1/4"){
        for (int inc = 0, row = 0; row < SIZE; inc++, row += 4) {
            for (int inc2 = 0, col = 0; col < SIZE; inc2++, col += 4) {
                image[inc][inc2] = image[row][col];
            }
        }
        for (int r = SIZE / 4; r < SIZE; r++) {
            for (int c = 0; c < SIZE; c++) {
                image[r][c] = 255;
            }
        }
        for (int r = 0; r < SIZE / 4; r++) {
            for (int c = SIZE / 4; c < SIZE; c++) {
                image[r][c] = 255;
            }
        }
    }
}

void detect() {
    black_and_white();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (image[i][j] == image[i][j - 1] && image[i][j] == image[i][j + 1] && image[i][j] == image[i - 1][j] && image[i][j] == image[i + 1][j]){
                second_image[i][j] = 255;
            }
            else{
                second_image[i][j] = 0;
            }
        }
    }
}

void mirror() {
    int choice;
    cout << "Please Enter the Number of the Part you want to Reflect \n1-Left \n 2-Right \n 3-Upper \n 4-Lower" << endl;
    cin >> choice;
    if (choice == 1){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++)
                image[i][SIZE - j] = image[i][j];
        }
    }
    else if (choice == 2){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0;j < SIZE; j++)
                image[i][j] = image[i][SIZE - j];
        }
    }
    else if (choice == 3){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++)
                image[SIZE - i][j] = image[i][j];
        }
    }
    else if (choice == 4){
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++)
                image[i][j] = image[SIZE-i][j];
        }
    }
    else{
        cout<<"Invalid Input, Please Enter 1 or 2 or 3 or 4\n";
    }
}

void blur(){
    double average;
    for (int r = 0; r < SIZE; r++){
        for (int c = 0; c < SIZE; c++){
            average = image[r - 2][c - 2] + image[r - 2][c - 1] + image[r - 2][c] + image[r - 2][c + 1] + image[r - 2][c + 2]
                      + image[r - 1][c - 2] + image[r - 1][c - 1] + image[r - 1][c] + image[r - 1][c + 1] + image[r - 1][c + 2]
                      + image[r][c - 2]     + image[r][c - 1]     + image[r][c]     + image[r][c + 1]     + image[r][c + 2]
                      + image[r + 1][c - 2] + image[r + 1][c - 1] + image[r + 1][c] + image[r + 1][c + 1] + image[r + 1][c + 2]
                      + image[r + 2][c - 2] + image[r + 2][c - 1] + image[r + 2][c] + image[r + 2][c + 1] + image[r + 2][c + 2];
            int new_value = round(average / 25);
            second_image[r][c] = new_value;
        }
    }
}

void enlarge_image()
{
    int answer;
    cout << "please choose whether you want to enlarge the 1st or 2nd or 3rd or 4th quarter";
    cout << "if 1st choose number 1,if 2nd choose number 2,if 3rd choose number 3 and if 4th choose number 4: " << endl;
    cin >> answer;
    if (answer == 1) {
        unsigned char first_quarter_matrix[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                first_quarter_matrix[i][j] = image[i / 2][j / 2];
            }
        }
        save_image(first_quarter_matrix);
    } else if (answer == 2)
    {
        unsigned char second_quarter_matrix[SIZE][SIZE];
        for (int k=0,i=0;i<SIZE;k++,i+=2)
        {
            for (int z=0,j=0;j<SIZE;z++,j+=2)
            {
                second_quarter_matrix[i][j]=image[k][z];
                second_quarter_matrix[i+1][j]=image[k][z];
                second_quarter_matrix[i+1][j+1]=image[k][z];
                second_quarter_matrix[i][j+1]=image[k][z];
            }
        }
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                second_quarter_matrix[i][j] = image[i/2][128+(j/2)];
            }
        }
        save_image(second_quarter_matrix);

    }
    else if (answer == 3)
    {
        unsigned char third_quarter_matrix[SIZE][SIZE];
        for (int k=0,i=0;i<SIZE;k++,i+=2)
        {
            for (int z=0,j=0;j<SIZE;z++,j+=2)
            {
                third_quarter_matrix[i][j]=image[k][z];
                third_quarter_matrix[i+1][j]=image[k][z];
                third_quarter_matrix[i+1][j+1]=image[k][z];
                third_quarter_matrix[i][j+1]=image[k][z];
            }
        }
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                third_quarter_matrix[i][j]=image[128+(i/2)][(j/2)-256];
            }
        }
        save_image(third_quarter_matrix);
    }
    else if (answer == 4)
    {
        unsigned char fourth_quater_matrix[SIZE][SIZE];
        for (int k=0,i=0;i<SIZE;k++,i+=2)
        {
            for (int z=0,j=0;j<SIZE;z++,j+=2)
            {
                fourth_quater_matrix[i][j]=image[k][z];
                fourth_quater_matrix[i+1][j]=image[k][z];
                fourth_quater_matrix[i+1][j+1]=image[k][z];
                fourth_quater_matrix[i][j+1]=image[k][z];
            }
        }
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                fourth_quater_matrix[i][j]=image[128+(i/2)][(j/2)-128];
            }
        }
        save_image(fourth_quater_matrix);
    }
}

void shuffle_image()
{
    int firstquarter, secondquarter, thirdquarter, fourthquarter;
    cout << "please enter the number of the first quarter you want it,if you want it to be the first put 1,"
            "if you want it to be the  second put 2,if you want it to be the third put 3,"
            "and if you want it to be the first put 4" << endl;
    cin >> firstquarter;
    if (firstquarter == 1){
        for (int i = 0; i<128; i++){
            for (int j = 0; j < 128; j++){
                new_matrix[i][j] = image[i][j];
            }
        }
    }
    else if (firstquarter == 2){
        for (int i = 0,r=0; i < 128; i++,r++){
            for (int j = 128,c=0; c < 128; j++,c++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (firstquarter == 3){
        for (int i = 128,r=0; r < 128; i++,r++){
            for (int j = 0,c=0; j < 128; j++,c++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (firstquarter == 4){
        for (int i = 128,r=0; r < 128; i++,r++){
            for (int j = 128,c=0; c < 128; j++,c++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    cout << "please enter the number of the second quarter you want it,if you want it to be the first put 1,"
            "if you want it to be the  second put 2,if you want it to be the third put 3,"
            "and if you want it to be the first put 4" << endl;
    cin >> secondquarter;
    if (secondquarter == 1){
        for (int i = 0,r=0; i < 128; r++,i++){
            for (int j = 0,c=128; j < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (secondquarter == 2){
        for (int i = 0,r=0; i < 128; r++,i++){
            for (int j = 128,c=128; j < 256; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (secondquarter==3){
        for (int i = 128,r=0; r < 128; r++,i++){
            for (int j = 0,c=128; j < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (secondquarter==4){
        for (int i = 128,r=0; r < 128; r++,i++){
            for (int j = 128,c=128; j < 256; j++,c++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    cout<<"please enter the number of the third quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4" << endl;
    cin>>thirdquarter;
    if (thirdquarter==1){
        for (int i = 0,r=128; r<256; i++,r++){
            for (int j = 0,c=0; c < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (thirdquarter==2){
        for (int i = 0,r=128; i < 128; i++,r++){
            for (int j = 128,c=0;c < 128; j++,c++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (thirdquarter==3){
        for (int i = 128,r=128; i < 256; r++,i++){
            for (int j = 0,c=0; j < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (thirdquarter==4){
        for (int i = 128,r=128; i < 256; r++,i++){
            for (int j = 128,c=0; c < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    cout << "please enter the number of the fourth quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4" << endl;
    cin >> fourthquarter;
    if (fourthquarter == 1){
        for (int i = 0,r=128; i < 128; r++,i++){
            for (int j = 0,c=128; j < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (fourthquarter==2){
        for (int i = 0,r=128; i < 128; i++,r++){
            for (int j = 128,c=128; j < 256; j++,c++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    else if (fourthquarter == 3){
        for (int i = 128,r=128; i < 256; r++,i++){
            for (int j = 0,c=128; j < 128; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }

    else if (fourthquarter == 4){
        for (int i = 128,r=128; i < 256; r++,i++){
            for (int j = 128,c=128; j < 256; c++,j++){
                new_matrix[r][c] = image[i][j];
            }
        }
    }
    save_image(new_matrix);
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
                flip_image();
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
                detect();
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
