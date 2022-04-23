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
        saveimage(first_quarter_matrix);
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
        } saveimage(second_quarter_matrix);

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
        saveimage(third_quarter_matrix);
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
        saveimage(fourth_quater_matrix);
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
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
                    new_matrix[i][j][k] = image[i][j][k];
                }
            }
        }
    }
    saveimage(new_matrix);}

int main() {
    loadimage();
    shuffle_image();
    return 0;
}