/////////////////////////////////////////////////////////////////////
// In this program, it pairs all the possible 9990 4-digit integers,
// (excluding 0000, 1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999),
// and calculate how many iterations are needed for each integer,
// (output as "List_of_Integer.txt").

// At the same time, it also bins how many integers (out of the 9990)
// need 1 iteration, 2 iterations, ... , and 7 iterations.
// (output as "Iteration_Count.txt")
// The maximum iteration to reach Kaprekar's constant (6174) would be 7.
/////////////////////////////////////////////////////////////////////
# include <fstream>
# include <iomanip>
# define Kaprekar_constant 6174
using namespace std;

// to declare functions
int convert_array_to_integer(int* const &);             // to convert the 4-digit-array back to an integer
void convert_integer_to_array(const int &, int* &);     // to split the integer into a 4-digit-array
void ascendingsort(int* &, const int &);                // sort the 4-digit-array in ascending order
void descendingsort(int* const &, int* &, const int &); // sort the 4-digit-array in descending order


/////////////////////////////////////////////////////////////////////////////////////////////////////

int main ()
{
    int size = 4;                   // there are 4-digit integers only.
    int difference;                  // the difference = desc - asc
    int* digit;                     // an array, to save the 4-digit integer individually.
    int* ascending;                 // an array, to save the ascending order of the 4-digit-array.
    int* descending;                // an array, to save the descending order of the 4-digit-array.
    digit = new int [size];
    ascending = new int [size];
    descending = new int [size];

    // This is to calculate how many integers
    // need 1 iteration, 2 iterations, ... , 7 iterations,
    // to achieve the Kaprekar's constant 6174.
    int iteration_1 = 0;
    int iteration_2 = 0;
    int iteration_3 = 0;
    int iteration_4 = 0;
    int iteration_5 = 0;
    int iteration_6 = 0;
    int iteration_7 = 0;

    // Output the results to .txt
    ofstream list_of_integer, iteration_count;
    list_of_integer.open("List_of_Integer.txt"); // To keep how many iterations for each integer.
    iteration_count.open("Iteration_Count.txt"); // To bin how many integers need 1 iteration, 2 iterations, ..., 7 iterations.


    list_of_integer << setw(25) << "Integer" << setw(25) << "Needed Iterations" << endl;

    // for-loop to pair-up all the 9990 possible combinations
    for (int i1 = 0; i1 <= 9; i1++)
        for (int i2 = 0; i2 <= 9; i2++)
            for (int i3 = 0; i3 <= 9; i3++)
                for (int i4 = 0; i4 <= 9; i4++)
                {
                    if (!(i1 == i2 && i1 == i3 && i1 == i4)) // to exclude 0000, 1111, 2222, ... , 9999
                    {
                        // save the digit as an array first
                        digit[0] = i1;
                        digit[1] = i2;
                        digit[2] = i3;
                        digit[3] = i4;

                        // output to "List_of_Integer.txt"
                        list_of_integer << setw(20) << digit[0] << digit[1] << digit[2] << digit[3];

                        int count = 0;
                        do
                        {
                            // copy the digit-array to ascending-array, so that it can be sorted next
                            for (int j = 0; j < size; j++)
                                ascending[j] = digit[j];

                            ascendingsort(ascending, size); // to sort ascending-array
                            descendingsort(ascending, descending, size); // to sort descending-array

                            ///////////////////// difference = desc - asc
                            difference = convert_array_to_integer(descending) - convert_array_to_integer(ascending);
                            ///////////////////// need to split the difference back to array such that we can sort the array during the next enter into the loop
                            convert_integer_to_array(difference, digit);

                            count++;

                        } while (difference != Kaprekar_constant); // to check if Kaprekar's constant has been achieved


                        // output to "List_of_Integer.txt"
                        list_of_integer << setw(20) << count << endl;


                        ///////////////////////////////////////////////////////////////////////////////////////
                        // add to the counter for how many integers
                        // need 1 iteration, 2 iterations, ... , or 7 iterations.
                        ///////////////////////////////////////////////////////////////////////////////////////

                        switch (count)
                        {
                            case 1:
                                iteration_1++;
                                break;
                            case 2:
                                iteration_2++;
                                break;
                            case 3:
                                iteration_3++;
                                break;
                            case 4:
                                iteration_4++;
                                break;
                            case 5:
                                iteration_5++;
                                break;
                            case 6:
                                iteration_6++;
                                break;
                            case 7:
                                iteration_7++;
                                break;
                        };
                    };
                };

    // output to "Iteration_Count.txt"
    iteration_count << "Out of all the possible 9990 integers, " << endl;
    iteration_count << setw(8) << iteration_1 << " integers need 1 iteration." << endl;
    iteration_count << setw(8) << iteration_2 << " integers need 2 iterations." << endl;
    iteration_count << setw(8) << iteration_3 << " integers need 3 iterations." << endl;
    iteration_count << setw(8) << iteration_4 << " integers need 4 iterations." << endl;
    iteration_count << setw(8) << iteration_5 << " integers need 5 iterations." << endl;
    iteration_count << setw(8) << iteration_6 << " integers need 6 iterations." << endl;
    iteration_count << setw(8) << iteration_7 << " integers need 7 iterations." << endl;

    // close the files
    list_of_integer.close();
    iteration_count.close();

    // delete the pointer array
    delete [] digit; digit = NULL;
    delete [] ascending; ascending = NULL;
    delete [] descending; descending = NULL;

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

int convert_array_to_integer(int* const & DIGIT)
{
    return (1000 * DIGIT[0] + 100 * DIGIT[1] + 10 * DIGIT[2] + DIGIT[3]);
}

void convert_integer_to_array(const int & INTEGER, int* & DIGIT)
{
    DIGIT[0] = INTEGER / 1000;
    DIGIT[1] = (INTEGER - 1000 * DIGIT[0]) / 100;
    DIGIT[2] = (INTEGER - 1000 * DIGIT[0] - 100 * DIGIT[1]) / 10;
    DIGIT[3] = (INTEGER - 1000 * DIGIT[0] - 100 * DIGIT[1] - 10 * DIGIT[2]);
}

void ascendingsort(int* & ASCENDING, const int & SIZE)
{
    // performing the selection sort
    for (int j = 0; j < SIZE - 1; j++)
    {
        int index = j;
        for (int k = j + 1; k < SIZE; k++)
        {
            if (ASCENDING[k] <= ASCENDING[index])
                index = k;
        };
        int temp = ASCENDING[j];
        ASCENDING[j] = ASCENDING[index];
        ASCENDING[index] = temp;
    };
}

void descendingsort(int* const & ASCENDING, int* & DESCENDING, const int & SIZE)
{
    for (int j = 0; j < SIZE; j++)
        DESCENDING[j] = ASCENDING[(SIZE - 1) - j];
}
