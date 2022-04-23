#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "bmplib.cpp"
using namespace std;

unsigned char image [SIZE][SIZE];
unsigned char new_matrix[SIZE][SIZE];
unsigned char helper_matrix[SIZE][SIZE];
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
        saveimage(first_quarter_matrix);
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
        } saveimage(second_quarter_matrix);

    }else if (answer == 3)
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
        saveimage(third_quarter_matrix);
    }else if (answer == 4)
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
        saveimage(fourth_quater_matrix);
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
                new_matrix[i][j] = image[i][j];
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
        for (int i=0;i<128;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
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
        for (int i=0;i<128;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
            }
        }//saveimage(new_matrix);
    }
    else if (thirdquarter==2)
    {
        //  unsigned char second_quarter_matrix[SIZE][SIZE];
        for (int i=0;SIZE;i++)
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
        for (int i=0;i<128;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                new_matrix[i][j]=image[i][j];
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


