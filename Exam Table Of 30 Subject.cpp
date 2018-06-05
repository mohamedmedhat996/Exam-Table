//Name : Mohamed Medhat Abd El-hay Tawfiq
//Section : 3
#include <iostream>
#include <stdlib.h>
using namespace std;

int student_table[100][30] = {0}, confilect_table[30][30] = {0},exam_table[30][30]= {0} , Exams_index[30] = {0};
int number_of_days=0;

//Generate random registration matrix
void Generate_Random_Registration ()
{
    int counter , i , random_column ;
    for(i=0 ; i<= 99 ; i++)
    {   counter = 0;
        while (counter < 5)
        {   random_column = rand() % 30;
            if(student_table[i][random_column] == 0)
            {student_table[i][random_column] = 1; 
                 counter++;
            }
        }
    }
}
//Print random registration matrix
void Print_Registration_Matrix()
{
    cout << "Generate random registration matrix : \n";
    for(int i=0; i<=99 ; i++)
    {   for(int h=0 ; h<30 ; h++)
            cout<< student_table[i][h] << "   ";
        cout<< "\n";
    }
}
//Obtain conflict matrix
void Conflict_Matrix()
{
    int i , number_of_student;
    for(i=0 ; i<30 ; i++)
    {   int r=0;
        while(r<=i)
        {   number_of_student=0;
            for(int h=0 ; h<99 ; h++)
            {   if(student_table[h][i] == 1 && student_table[h][r] ==1)
                    number_of_student++;
            }
            confilect_table[i][r] = confilect_table[r][i] = number_of_student; 
            r++;
        }
    }
}
//Print conflict matrix
void Print_Conflict_Matrix()
{
    cout<< "\nObtain conflict matrix : \n";
    for(int i=0; i<30 ; i++)
    {   for(int h=0 ; h<30 ; h++)
            cout<< confilect_table[i][h] << "   ";
        cout<< "\n";
    }
}
//Initialization to 30*30 matrix and fill it with (-1)
void Initialize_Matrix()
{
    for(int i=0; i<30 ; i++)
        for(int h=0 ; h<30 ; h++)
            exam_table[i][h] = -1;
}
//Initialization to array with size 30 and fill it with (-1)
//Then put in it number of subject which will have a exam day
void Exam_Array()
{
    for(int h=0 ; h<30 ; h++)
        Exams_index[h] = -1;

    for(int i=0 ; i<30 ; i++)
        if(confilect_table[i][i] != 0)
            Exams_index[i]=i;
}
//Put a subject in level of matrix and loop on the other subject to take which is can be put with this subject
void Days_Without_Optimization()
{
    for(int level=0 ;level<30 ; level++)
    {
        for(int exam=0;exam<30;exam++)
        {
            if(exam_table[level][0]==-1) // if level (day) is empty in matrix
            {
                if(Exams_index[exam]!=-1) // check array of number of subject which will have a exam day
                {
                    exam_table[level][0]=Exams_index[exam]; // then put number of subject in this day in matrix
                    Exams_index[exam]=-1; // then remove the number of subject for the array to avoid take it again
                }
            }
            else // if day is not empty in matrix
            {   int i=0,y=0 , x,z;
                // check which subject did not conflict with in this subjects in this level and put in them together
                while(exam_table[level][i]!=-1 && Exams_index[exam]!=-1)
                {
                    x=exam_table[level][i];
                    z=Exams_index[exam];
                    if(confilect_table[x][z]==0){y++;}
                    i++;
                }
                if(i==y && i!=0)
                    {   exam_table[level][i]=z;
                        Exams_index[exam]=-1;}
            }
        }
    }
}
//Print exam days matrix
void Print_Days_Matrix()
{
    for(int i=0; i<30 ; i++)
    {   int x =0;
        for(int h=0 ; h<30 ; h++)
        {   if(exam_table[i][h]!=-1)
            {   cout<< exam_table[i][h] << " ";
                x++;
            }
        }
        if(x!=0) cout<< "\n";
    }
}
//The possibilities of each subject with others
void Possibilities_Subjects()
{
    //here i look to subject no one choose it and remove it from possibilities by fill it's row with (-1)
    for(int i=0;i<30;i++)
    {
        if(confilect_table[i][i]==0)
        {   int x=0;
            while(x<30)
                confilect_table[i][x]=-1;}
    }
    //then put in each subject's row the possibilities
    for(int i=0; i<30 ; i++)
    {   int r=0;
        for(int h=0 ; h<30 ; h++)
            {   if(confilect_table[i][h]==0)
                {   exam_table[i][r]=h;
                    r++;}}}
}
//Shift the deleted element right
void shift (int i ,int x , int y)
{
    int z;
    z=exam_table[i][x];
    exam_table[i][x]=exam_table[i][y];
    exam_table[i][y]=z;
}
//Delete the chosen element form the possibilities of other subjects
void delete_element(int element)
{
    for(int i=0;i<30;i++)
    {
        for(int h=0;h<30;h++)
        {
            if(exam_table[i][h]==element)
            {
                exam_table[i][h]=-1;
                int x=h;
                while(exam_table[i][x+1]!=-1)
                {   shift(i,x,x+1);
                    x++;}}}}
}
//Optimize element by look first to the subject which have more conflict with others
//row which will fill with (-2) mean this subject will have a exam day
//row which will fill with (-3) mean this subject will be with other subject is exam day
void Optimize ()
{
    for(int i=0;i<30;i++)
    {
        // if the subject is conflict with all other subjects so we will make a exam day to it alone
        if(exam_table[i][0]==-1)
        {
            number_of_days++;
            int x=0;
            while(x<30)
            {   exam_table[i][x]=-2;// this subject will have a exam day and fill this row with (-2) to avoid take it again
                x++;
            }
             cout<<i<<"\n";
        }
        // if the subject is conflict with all other subjects except one subject so we will make a day to them together
        else if(exam_table[i][1]==-1)
        {
            number_of_days++;
            int y = exam_table[i][0];
            delete_element(y);
            int x=0;
            while(x<30)
            {   exam_table[i][x]=-2; //// this subject will have a exam day and fill this row with (-2) to avoid take it again
                exam_table[y][x]= -3;// this subject will be with other subject is exam day and fill this row with (-3) to avoid take it again
                x++;
            }
            cout<< i << " " << y << "\n";
            i=0;
        }
        // if the subject is conflict with all other subjects except two subjects
        else if (exam_table[i][2]==-1)
        {
            int z =exam_table[i][0];
            int y =exam_table[i][1];
            // check if the two subjects did not conflict together then put the three subjects together in exam day
            if(confilect_table[z][y]==0)
            {
                number_of_days++;
                delete_element(z);
                delete_element(y);
                int x=0;
                while(x<30)
                {   exam_table[i][x]=-2;
                    exam_table[y][x]= -3;
                    exam_table[z][x]=-3;
                    x++;
                }
                cout<< i << " " << y << " " << z <<"\n";
                i=0;
            }
        }
        // if the subject is conflict with all other subjects except three subjects
        else if (exam_table[i][3]==-1)
        {
            int z =exam_table[i][0];
            int y =exam_table[i][1];
            int t =exam_table[i][2];
            // check if the three subjects did not conflict together then put the four subjects together in exam day
            if(confilect_table[z][y]==0 && confilect_table[t][z]==0 && confilect_table[t][y]== 0)
            {
                number_of_days++;
                delete_element(z);
                delete_element(y);
                delete_element(t);
                int x=0;
                while(x<30)
                {   exam_table[i][x]=-2;
                    exam_table[y][x]= -3;
                    exam_table[z][x]=-3;
                    exam_table[t][x]=-3;
                    x++;
                }
                cout<< i << " " << y << " " << z << " " << t <<"\n";
                i=0;
            }
            // check if the two subjects from the three subjects did not conflict together then put the three subjects together in exam day
            else if(confilect_table[z][y]==0)
            {
                number_of_days++;
                delete_element(z);
                delete_element(y);
                int x=0;
                while(x<30)
                {   exam_table[i][x]=-2;
                    exam_table[y][x]= -3;
                    exam_table[z][x]=-3;
                    x++;
                }
                cout<< i << " " << y << " " << z <<"\n";
                i=0;
            }
            else if(confilect_table[z][t]==0)
            {
                number_of_days++;
                delete_element(z);
                delete_element(t);
                int x=0;
                while(x<30)
                {   exam_table[i][x]=-2;
                    exam_table[t][x]= -3;
                    exam_table[z][x]=-3;
                    x++;
                }
                cout<< i << " " << t << " " << z <<"\n";
                i=0;
            }
            else if(confilect_table[t][y]==0)
            {
                number_of_days++;
                delete_element(t);
                delete_element(y);
                int x=0;
                while(x<30)
                {   exam_table[i][x]=-2;
                    exam_table[y][x]= -3;
                    exam_table[t][x]=-3;
                    x++;
                }
                cout<< i << " " << y << " " << t <<"\n";
                i=0;
            }
        }
    }
}
int main()
{
    Generate_Random_Registration(); // Generating random registration matrix
    Print_Registration_Matrix();
    Conflict_Matrix();  // Generating Obtain conflict matrix
    Print_Conflict_Matrix();
    Initialize_Matrix(); // Generating (exam_table) 30*30 matrix and fill it with (-1)
    Exam_Array();  // Generating array and fill it with (-1) Then put in it number of subject which will have a exam day
    Days_Without_Optimization();
    cout<< "\nExam days without optimization : \n";
    Print_Days_Matrix();
    int counter=0;
    for(int i=0;i<30;i++)
    {
        if(exam_table[i][0]!=-1)counter++;
    }
    cout<<"\nNumber of exam days without optimization : " << counter <<"\n";
    Initialize_Matrix(); // fill (exam_table) 30*30 matrix and fill it with (-1) to use it again
    Exam_Array();  // Generating array and fill it with (-1) Then put in it number of subject which will have a exam day
    Possibilities_Subjects(); // Generate which subjects can be taken with each subject
    cout<< "\nPossibilities of each subject with others : \n";
    Print_Days_Matrix();
    cout <<"\nExam days with optimization : \n";
    Optimize(); // Not a general solution Optimization
    cout<<"\nNumber of exam days with optimization : " << number_of_days <<"\n";

}
