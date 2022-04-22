#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "bmplib.cpp"
using namespace std;

unsigned char image [SIZE][SIZE];
unsigned char new_matrix[SIZE][SIZE];
void loadimage()
{
    char imagefilename[100];
    cout<<"please enter your file name without any extension: "<<"\n";
    cin>>imagefilename;               //you insert your image's name
    strcat(imagefilename,".bmp");           //it adds an extenstion .bmp to your image
    readGSBMP(imagefilename,image) ;    //it puts your image in a pic of 265*265
}

void saveimage(unsigned char arr[SIZE][SIZE])
{
    char imagefilename[100];
    cout<<"please enter the name of the file you want to save your pic in it: "<<"\n";
    cin>>imagefilename;
    strcat(imagefilename,".bmp");
    writeGSBMP(imagefilename,arr);      //it saves the file
}

void invert_image()
{
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
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
                new_matrix[i][j]=image[j][i] ;
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
               new_matrix[i][j]=image[255-i][255-j];

            }
        }
    }
    else if (degree=="90")
    {
        unsigned char helper_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                /*helper_matrix[i][j]=image[j][255-i];
                new_matrix[i][j]=helper_matrix[255-i][255-j];*/
             // helper_matrix[i][j]=image[255-j][255-i];
              helper_matrix[i][j]=image[255-(255-j)][255-i];         //270//
              new_matrix[i][j]=image[255-(255-(255-j))][255-(255-i)];

            }
        }
    }
    saveimage(new_matrix);
}


void enlarge_image()
{
    int answer;
    cout<<"please choose whether you want to enlarge the 1st or 2nd or 3rd or 4th quarter";
    cout<<"if 1st choose number 1,if 2nd choose number 2,if 3rd choose number 3 and if 4th choose number 4: "<<endl;
    cin >>answer;
    if (answer == 1)
    {
        unsigned char first_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                first_quarter_matrix[i][j]=image[i/2][j/2];
            }
        }
        saveimage(first_quarter_matrix);
    }
    else if (answer == 2)
    {
        unsigned char second_quarter_matrix[SIZE][SIZE];
       // int k=0,l=SIZE/2;
        for (int i=0;i<SIZE/2;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                second_quarter_matrix[i][j]=image[i][j];
            }
        }saveimage(second_quarter_matrix);
       /* for (int i=0;i<SIZE;i+=2)
        {
            for (int j=0;j<SIZE;j+=2)
            {
                image[i][j]=image[i][j+1]=image[i+1][j]=image[i+1][j+1]=second_quarter_matrix[k][l];
                l++;
            }
            l=SIZE/2;
            k++;
        }saveimage(second_quarter_matrix);*/
    }
    else if (answer == 3)
    {
        unsigned char third_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=0;j<SIZE/2;j++)
            {
                third_quarter_matrix[i][j]=image[i][j/2];
            }
        }
        saveimage(third_quarter_matrix);
    }
    else if (answer == 4)
    {
        unsigned char fourth_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                fourth_quarter_matrix[i][j]=image[i][j];
            }
        }
        saveimage(fourth_quarter_matrix);
    }
}

void shuffle_image()
{
    int firstquarter,secondquarter,thirdquarter,fourthquarter;
    cout<<"please enter the number of the first quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4";
    cin>>firstquarter;
    if (firstquarter==1)
    {
        //unsigned char first_quarter_matrix[SIZE][SIZE];
                for (int i = 0; i < 128; i++)
                {
                    for (int j = 0; j < 128; j++)
                    {
                        new_matrix[i][j] = image[i / 2][j / 2];
                    }
                }//saveimage(new_matrix);
    }
    else if (firstquarter==2)
    {
       // unsigned char second_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                image[i][j]=new_matrix[i][j];
            }
        }//saveimage(new_matrix);
    }
    else if (firstquarter==3)
    {
       // unsigned char third_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=0;j<SIZE/2;j++)
            {
                new_matrix[i][j]=image[i][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (firstquarter==4)
    {
       // unsigned char fourth_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
            }
        }//saveimage(new_matrix);
    }
    cout<<"please enter the number of the second quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4";
    cin>>secondquarter;
    if (secondquarter==1)
    {
       // unsigned char first_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i/2][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (secondquarter==2)
    {
        //unsigned char second_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                image[i][j]=new_matrix[i][j];
            }
        }//saveimage(new_matrix);
    }
    else if (secondquarter==3)
    {
       // unsigned char third_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=0;j<SIZE/2;j++)
            {
                new_matrix[i][j]=image[i][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (secondquarter==4)
    {
        //unsigned char fourth_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
            }
        }//saveimage(new_matrix);
    }
    cout<<"please enter the number of the third quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4";
    cin>>secondquarter;
    if (thirdquarter==1)
    {
       // unsigned char first_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i/2][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (thirdquarter==2)
    {
      //  unsigned char second_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                image[i][j]=new_matrix[i][j];
            }
        }//saveimage(new_matrix);
    }
    else if (thirdquarter==3)
    {
        //unsigned char third_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=0;j<SIZE/2;j++)
            {
                new_matrix[i][j]=image[i][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (thirdquarter==4)
    {
       // unsigned char fourth_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
            }
        }//saveimage(new_matrix);
    }
    cout<<"please enter the number of the fourth quarter you want it,if you want it to be the first put 1,"
          "if you want it to be the  second put 2,if you want it to be the third put 3,"
          "and if you want it to be the first put 4";
    cin>>secondquarter;
    if (fourthquarter==1)
    {
      //  unsigned char first_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i/2][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (fourthquarter==2)
    {
       // unsigned char second_quarter_matrix[SIZE][SIZE];
        for (int i=0;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                image[i][j]=new_matrix[i][j];
            }
        }//saveimage(new_matrix);
    }
    else if (fourthquarter==3)
    {
        //unsigned char third_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=0;j<SIZE/2;j++)
            {
                new_matrix[i][j]=image[i][j/2];
            }
        }//saveimage(new_matrix);
    }
    else if (fourthquarter==4)
    {
       // unsigned char fourth_quarter_matrix[SIZE][SIZE];
        for (int i=SIZE/2;i<SIZE;i++)
        {
            for (int j=SIZE/2;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
            }
        }//saveimage(new_matrix);
    }
    saveimage(new_matrix);}
int main()
{
    loadimage();
    shuffle_image();
    return 0;
}