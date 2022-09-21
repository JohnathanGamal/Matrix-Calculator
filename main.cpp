#include <iostream>
#include <cmath>
using namespace std;

long long determ(int *ptr, int rows, int columns);
void inverse (int* ptr, long double* ptr_inv, int rows, int columns, long long determinant);
long long approx (long double x);
void operation (int *ptrA, int *ptrB, int Arows, int Acolumns, int Brows, int Bcolumns, char op);
void input (int* ptr, int rows, int columns);


int main()
{
    int x = 0;
    int Arows, Acolumns, Brows, Bcolumns;
    //Specifying the dimensions
    cout << "Please enter dimensions of Matrix A:\n";
    cin >> Arows >> Acolumns;
    cout << "Please enter dimensions of Matrix B:\n";
    cin >> Brows >> Bcolumns;
    int Amat[Arows][Acolumns], Bmat[Brows][Bcolumns];

    //Elements of Matrix A
    cout << "Please enter values of Matrix A:\n";
    input(&Amat[0][0], Arows, Acolumns);

    //Elements of Matrix B
    cout << "Please enter values of Matrix B:\n";
    input(&Bmat[0][0], Brows, Bcolumns);


    while (x != 7)
    {
        cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):\n";
        cin >> x;
        if (x == 1)
        //Addition
        {
            if ((Arows == Brows) && (Acolumns == Bcolumns))
            {
                operation(&Amat[0][0], &Bmat[0][0], Arows, Acolumns, Brows, Bcolumns, '+');
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }

        }
        else if (x == 2)
        {
            //Subtraction
            if ((Arows == Brows) && (Acolumns == Bcolumns))
            {

                operation(&Amat[0][0], &Bmat[0][0], Arows, Acolumns, Brows, Bcolumns, '-');

            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }

        }
        else if (x == 3)
        {
            if (Acolumns == Brows)
            {
                operation(&Amat[0][0], &Bmat[0][0], Arows, Acolumns, Brows, Bcolumns, 'x');

            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }

        }
        if (x == 4)
        {
            // Pointer to first element in the matrix in order to pass it to the function
            int* ptr = & Bmat[0][0];

            /*
            Failure to get inverse is due to:
            - No of rows is not equal to no of columns
            - Determinant = 0
            And to multiply A with inverse B, A columns must be equal to Brows
            */
            long long determinant_value = determ(ptr, Brows, Bcolumns);
            if((determ(ptr, Brows, Bcolumns) != 0) && (Brows == Bcolumns) && (Acolumns == Brows))
            {
                long double Binverse[Brows][Bcolumns];
                //Getting the inverse from function inverse
                //By passing pointer to 1st element and no. of rows and columns as well as determinant value
                inverse(ptr, &Binverse[0][0], Brows, Bcolumns, determinant_value);


                //Multiplying matrix A by inverted matrix B
                long double sum = 0;
                for (int i = 0; i < Arows; i++)
                {
                    for (int j = 0; j < Bcolumns; j++)
                    {
                        sum = 0;
                        for(int k = 0; k < Acolumns; k++)
                        sum += Amat[i][k] * Binverse[k][j];
                        cout << approx(sum) << " ";
                    }
                    cout << endl;
                }


            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
        if (x == 5)
        {

            if (Arows == Acolumns)
            {
                 int* ptr = & Amat[0][0];
                 cout << determ(ptr, Arows, Acolumns) << endl;
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
        if (x == 6)
        {

            if (Brows == Bcolumns)
            {
                 int* ptr = & Bmat[0][0];
                 cout << approx(determ(ptr, Brows, Bcolumns)) << endl;
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }


    }
    cout << "Thank you!";
}











long long determ(int *ptr, int rows, int columns)
{
    if(rows == 1)
    {
        return *ptr;
    }
    long long det = 0;
    if(rows == 2)
    {   //finding determinant for 2x2 matrix
        det = ptr[0] * ptr[3] - ptr[1] * ptr[2];
        return det;
    }
    //Re-Assembling the matrix in a 2D array from its pointer
    int arr[rows][columns];
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                arr[i][j]= ptr[i*columns +j];

            }
        }
        int small[rows - 1][columns - 1];
        for(int k = 0; k < columns; k++)
            {
                for (int i = 1; i < rows; i++)
                {
                    int l = 0;
                    for (int j = 0; j < columns ; j++)
                        if( j != k)
                        {
                            small[i-1][l] = arr[i][j];
                            l++;
                        }

                }
                //Sign rule
                if(k % 2 == 0)
                {
                    det += arr[0][k]* determ(&small[0][0], rows - 1, columns - 1);
                }
                else
                    det -= arr[0][k]* determ(&small[0][0], rows - 1, columns - 1);

            }
            return det;
}

void inverse (int* ptr, long double* ptr_inv, int rows, int columns, long long determinant)
{
    //assembling the matrix in a 2D array from the pointer
        int arr[rows][columns];
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                arr[i][j]= ptr[i*columns +j];

            }
        }
        /*Declaring two arrays, one for the inverse(final result)
        And one for the minor(to be sent to determinant function)
        */
        int minor[rows - 1][columns - 1];
        //looping through elements of the original array to get cofactor for each one

        int minor_row, minor_column;
        for(int k = 0; k < rows; k++)
        {
             for(int l = 0; l < columns; l++)
            {
                minor_row = 0, minor_column = 0;
                // looping through elements of the original array to gather elements for the minor array
                for(int i = 0; i < rows; i++)
                {
                    for(int j = 0; j < columns; j++)
                    {
                        //Extracting elements from the original array to minor array
                        if((i != k) && (j != l))
                        {
                            //incrementing the index of rows for minor array when we reach last column
                            if(minor_column == columns - 1)
                            {
                                minor_column = 0;
                                minor_row += 1;
                            }
                            minor[minor_row][minor_column] = arr[i][j];
                            //incrementing the index of columns while staying in the same row
                            minor_column++;

                        }


                    }
                }
                int a = rows - 1;
                if((k+l) % 2 == 0)
                {
                     ptr_inv[k + l*columns] = (determ(&minor[0][0], a, a))/(long double)determinant;
                }
                else
                {
                     ptr_inv[k + l*columns] = -(determ(&minor[0][0], a, a))/(long double)(determinant);

                }
            }
        }
        return;
}

long long approx (long double x)
{
    if (x < 0)
        {
            if((long long)(x - 0.5) == -0)
                return 0;
            else
                return (long long)(x - 0.5);
        }
    if (x > 0)
        return (long long)(x + 0.5);

    //In case x equals 0
    return x;
}


//Function for addition, subtraction and multiplication
void operation (int *ptrA, int *ptrB, int Arows, int Acolumns, int Brows, int Bcolumns, char op)
{
    //In case of addition
    if (op == '+')
    {
        for (int i = 0; i < Arows; i++)
        {
            for (int j = 0; j < Acolumns; j++)
            {
                cout << ptrA[i * Acolumns + j] + ptrB[i * Acolumns + j] << " ";
            }
            cout << endl;
        }
    }
    //In case of subtraction
    else if (op == '-')
    {
        for (int i = 0; i < Arows; i++)
        {
            for (int j = 0; j < Acolumns; j++)
            {
                cout << ptrA[i * Acolumns + j] - ptrB[i * Acolumns + j] << " ";
            }
            cout << endl;
        }
    }
    //In case of multiplication
    else if (op == 'x')
    {
        long double sum;
        for (int i = 0; i < Arows; i++)
                {
                    for (int j = 0; j < Bcolumns; j++)
                    {
                        sum = 0;
                        for(int k = 0; k < Acolumns; k++)
                        sum += ptrA[i * Acolumns + k] * ptrB[k* Bcolumns + j];
                        cout << approx(sum) << " ";
                    }
                    cout << endl;
                }
    }

}
//Getting input from user to the array
void input (int* ptr, int rows, int columns)
{
     for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cin >> ptr[i * columns + j];
        }
    }

}
