#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
using namespace std;

void menu()
{
    cout << endl
         << setw(40) << " ** HAMMING CODE : ERROR DETECTION AND ERROR CORRECTION ** " << endl
         << endl;
    cout << endl;
    return;
}

/* used functions and variables:
    int data_len;
    int r_len;
    int encode_len;

    int data_arr[50];
    int r_arr[50];
    int encoded_arr[50];

    void input();
    int validateData();
    int calcRBits();
    void encodeData();
    void outputEncoded();

    hammingcode(){
        data_len=r_len=encode_len=0;
        //*data_arr=new int[data_len];
    }
};
*/

void input(int data_arr[], int data_len)
{
    cout << "-> How many bits does the data have : ";
    cin >> data_len;
    cout << endl;
    cout << "-> Enter the data bits/Messages : ";
    for (int i = data_len; i > 0; i--)
    {
        cin >> data_arr[i];
    }
    cout << endl;
    return;
}

int validateData(int data_arr[], int &data_len)
{
    for (int i = data_len; i > 0; i--)
    {
        if (data_arr[i] != 0 && data_arr[i] != 1)
        {
            return 0;
        }
    }
    return 1;
} // to check if the input data is binary or not

int calcRBits(int data_len)
{
    int lhs, rhs, m = data_len;
    for (int r = 1; r <= m; r++)
    {
        rhs = m + r + 1;
        lhs = pow(2, r);
        if (lhs >= rhs)
        {
            return r;
        }
        else
        {
            continue;
        }
    }
} // calculate the redundant bits that will be created when data is transmitted

void encodeData(int data_arr[], int data_len, int r_arr[], int r_len, int *encoded_arr[])
{

    int encode_len = data_len + r_len;
    // overall length of encoded data
    cout << "--> Length of encoded data : " << encode_len << endl;

    // now creating the encoded data with m+r
    for (int i = 0; i < r_len; ++i)
    {

        // Placing -1 at redundant bits
        // place to identify it later
        int index = pow(2, i) - 1;
        encoded_arr[index] = -1;
    }

    int j = 1;
    // Iterate to update the code
    for (int i = 0; i < (r_len + data_len); i++)
    {
        // Placing msgBits where -1 is absent i.e., except redundant bits all positions are msgBits
        if (encoded_arr[i] != -1)
        {
            encoded_arr[i] = data_arr[j];
            j++;
        }
    }

    for (int i = 0; i < (r_len + data_len); i++)
    {

        // If current bit is not redundant bit then continue
        if (encoded_arr[i] != -1)
            continue;

        int x = log2(i + 1);
        int one_count = 0;

        // Find msg bits containing set bit at x'th position
        for (int j = i + 2;
             j <= (r_len + data_len); ++j)
        {
            if (j & (1 << x))
            {
                if (encoded_arr[j - 1] == 1)
                {
                    one_count++;
                }
            }
        }

        // Generating hamming code for even parity
        if (one_count % 2 == 0)
        {
            encoded_arr[i] = 0;
        }
        else
        {
            encoded_arr[i] = 1;
        }
    }
}

void outputEncoded(int encoded_arr[]; int encoded_len)
{
    for (int i = encode_len - 1; i >= 0; i--)
    {
        if (encoded_arr[i] == -1)
            cout << setw(3) << "__";
        else
            cout << setw(3) << encoded_arr[i];
    }
} // outputs the encoded data

//check bits= r bits
// n = data bits
int detect(int codeword[], int check, int n){
    
    int position = 0;
        cout << "Parity Bits - ";
        for (int i = 0; i < check; i++)
        {
            bool flag = true;
            int x = pow(2, i);
            int bit = codeword[x];
            if (x == 1)
            {
                for (int j = x + 1; j <= (n + check); j++)
                {
                    if (j % 2)
                    {
                        bit ^= codeword[j];
                    }
                }
            }
            else
            {
                for (int k = x + 1; k <= (n + check); k++)
                {
                    if (flag)
                    {
                        bit ^= codeword[k];
                    }
                    if ((k + 1) % x == 0)
                        flag = !flag;
                }
            }
    }

        //prints the hamming code received
        cout << endl<< "Received Codeword/Hamming code :" << endl;
        for (int i = 1; i <= (n + check); i++)
            cout << codeword[i] << " ";
        cout << endl;


        //detect errors in the hamming code 
        if (position != 0)
        {
            cout << "Error at bit : " << position << endl;
            codeword[position] = !codeword[position];
            cout << "Corrected Codeword : " << endl;
            for (int i = 1; i <= (n + check); i++)
                cout << codeword[i] << " ";
            cout << endl;
        }
        else
            cout << "No Error in Received code." << endl;
        
        //printing the final received msg after removing r-bits 
        cout << "Received Message is : ";
        for (int i = 1; i <= (n + check); i++){
            if ((i & (i - 1)) != 0)
                cout << codeword[i] << " ";
        cout << endl;
    }
}



int main()
{
    char ch = 'y';
    int data_len, r_len, ham_len; // stores data bits, redundant bits
    int encoded_len=data_len+r_len;
    int flag;            // for the status of validation
    int data_arr[50];
    int r_arr[50];
    int encoded_arr[50];


    while (ch == 'y' || ch == 'Y')
    {
        menu();
        cout<<endl<<"\t ***************** \n \t SENDER END : "<<endl;

        input(&data_arr, &data_len);             // input the data bits
        flag = validateData(data_arr, data_len); // validate if the data bits consist of 0 and 1 only
        // flag returns 1 for valid data and 0 for invalid data
        if (flag == 1)
        {
            r_len = calcRBits(data_len);
            cout << "--> Hence, " << r_len << " bits are redundant bits which will be created during transmission " << endl
                 << endl;
            encodeData(data_arr, data_len, r_arr, r_len, encoded_arr);
            cout << "\n--> The Hamming code sent is  : ";
            outputEncoded(encoded_arr, encoded_len);
            
            cout<<endl<<"\t ***************** \n \t RECEIVER END : "<<endl;
            cout<<"- Now enter the data received at receiver's end : ";
            input(data_arr, ham_len);             // input the data bits
            validateData(data_arr, ham_len);       //to check if message received only has binary digits
            detect(data_arr, r_len, data_len);             //to check if code received has errors or not
        }
        else
        {
            cout << "!! ERROR : THE ENTERED DATA IS INVALID ! \n\t\t Enter the binary data in form of 0 and 1 !! " << endl
                 << endl;
        }

        cout << endl
             << endl
             << "-> Do you want to continue (y/n) : ";
        cin >> ch;
        cout << endl;
    }
    return 0;
}
