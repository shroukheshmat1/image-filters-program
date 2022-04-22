#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "bmplib.cpp"
using namespace std;

unsigned char image [SIZE][SIZE][RGB];
unsigned char new_matrix[SIZE][SIZE][RGB];

void loadimage()
{
    char imagefilename[100];
    cout<<"please enter your file name without any extension: "<<"\n";
    cin>>imagefilename;               //you insert your image's name
    strcat(imagefilename,".bmp");           //it adds an extenstion .bmp to your image
    readRGBBMP(imagefilename,image) ;    //it puts your image in a pic of 265*265
}

void saveimage(unsigned char arr[SIZE][SIZE][RGB])
{
    char imagefilename[100];
    cout<<"please enter the name of the file you want to save your pic in it: "<<"\n";
    cin>>imagefilename;
    strcat(imagefilename,".bmp");
    writeRGBBMP(imagefilename,arr);      //it saves the file
}

void invert_image()
{
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            for (int k=1;k<=3;k++)
            {
               // new_matrix[i][j][k]=image [i][j][k]=0 || new_matrix[i][j][k] = image [i][j][k]=255;
                new_matrix[i][j][k] = 255 - image[i][j][k];
            }
        }
    }saveimage(new_matrix);
}
void rotate_image()
{
    string degree;
    cout<<"please enter whether you want to rotate the image by 90 degrees or 180 degrees or 270 degrees"<<"\n";
    cin>>degree;
    if (degree=="270")
    {
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                for (int k=1;k<=3;k++)
                {
                    new_matrix[i][j][k]=image[j][i][k] ;
                }
            }
        }

        /*  for (int i=0;i<SIZE;i++)
          {
              for (int j=0;j<(SIZE/2);j++)
              {
                  int temp=image[i][j];
                  image[i][j]=image[i][SIZE-1-j];
                  image[i][SIZE-1-j]=temp;
              }
          }*/
    }
    else if (degree=="180")
    {
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                for (int k = 1; k <= 3; k++)
                {
                    new_matrix[i][j][k]=image[255-i][255-j][k];
                }

            }
        }
    }
    else if (degree=="90")
    {
        unsigned char helper_matrix[SIZE][SIZE][RGB];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                for (int k = 1; k <= 3; k++)
                {
                    /*helper_matrix[i][j]=image[j][255-i];
                new_matrix[i][j]=helper_matrix[255-i][255-j];*/
                    // helper_matrix[i][j]=image[255-j][255-i];
                    helper_matrix[i][j][k]=image[255-(255-j)][255-i][255-k];         //270//
                    new_matrix[i][j][k]=image[255-(255-(255-j))][255-(255-i)][255-(255-k)];
                }
            }
        }
    }
    saveimage(new_matrix);
}

int main() {
    loadimage();
    rotate_image();
    return 0;
}