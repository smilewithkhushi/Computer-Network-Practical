#include <iostream>
#include<iomanip>
#include<cmath>
using namespace std;

void menu(){
cout<<endl<<setw(40)<<" ** HAMMING CODE : ERROR DETECTION AND ERROR CORRECTION ** "<<endl<<endl;
cout<<endl;
return ;
}

class hammingcode{
    int data_len;
    int r_len;
    int encode_len;

    int data_arr[50];
    int r_arr[50];
    int encoded_arr[50];

public:
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
void hammingcode::input(){
    cout<<"-> How many bits does the data have : ";
    cin>>data_len;
    cout<<endl;
    cout<<"-> Enter the data bits/Messages : ";
    for (int i=data_len; i>0; i--){
        cin>>data_arr[i];
    }
    cout<<endl;
    return ;
}

int hammingcode::validateData(){
    for (int i=data_len; i>0; i--){
        if (data_arr[i]!=0 && data_arr[i]!=1){
            return 0;
        }
    }
    return 1;
}//to check if the input data is binary or not


int hammingcode::calcRBits(){
    int lhs, rhs, m=data_len;
    for (int r=1; r<=m; r++){
        rhs=m+r+1;
        lhs=pow(2,r);
        if (lhs>=rhs){
            r_len=r;
            return r;
        }else{
            continue;
        }
    }
}//calculate the redundant bits that will be created when data is transmitted

void hammingcode::encodeData(){

    encode_len=data_len+r_len;
    //overall length of encoded data
    cout<<"--> Length of encoded data : "<<encode_len<<endl;

    //now creating the encoded data with m+r
    for (int i = 0; i < r_len; ++i) {

		// Placing -1 at redundant bits
		// place to identify it later
		int index=pow(2, i) - 1;
		encoded_arr[index] = -1;
	}

    int j = 1;
	// Iterate to update the code
	for (int i = 0; i < (r_len + data_len); i++) {
		// Placing msgBits where -1 is absent i.e., except redundant bits all positions are msgBits
		if (encoded_arr[i] != -1) {
			encoded_arr[i] = data_arr[j];
			j++;
		}
	}

	for (int i = 0; i < (r_len + data_len); i++) {

		// If current bit is not redundant
		// bit then continue
		if (encoded_arr[i] != -1)
			continue;

		int x = log2(i + 1);
		int one_count = 0;

		// Find msg bits containing
		// set bit at x'th position
		for (int j = i + 2;
			j <= (r_len + data_len); ++j) {

			if (j & (1 << x)) {
				if (encoded_arr[j - 1] == 1) {
					one_count++;
				}
			}
		}

		// Generating hamming code for
		// even parity
		if (one_count % 2 == 0) {
			encoded_arr[i] = 0;
		}
		else {
			encoded_arr[i] = 1;
		}
	}

}

void hammingcode :: outputEncoded(){
    for (int i=encode_len-1; i>=0; i--){
            if (encoded_arr[i]==-1)              cout<<setw(3)<<"__";
            else    cout<<setw(3)<<encoded_arr[i];
    }
}//outputs the encoded data

int main(){

    char ch='y';
    hammingcode hc;
    int data_len, r_len; //stores data bits, redundant bits
    int flag; //for the status of validation

    while (ch=='y' || ch=='Y'){
        menu();
        hc.input();                  //input the data bits
        flag=hc.validateData();     //validate if the data bits consist of 0 and 1 only
                                    //flag returns 1 for valid data and 0 for invalid data
        if (flag==1){
            r_len=hc.calcRBits();
            cout<<"--> Hence, "<<r_len<<" bits are redundant bits which will be created during transmission "<<endl<<endl;
            hc.encodeData();
            cout<<"\n--> The Hamming code is  : ";
            hc.outputEncoded();
        }
        else{
            cout<<"!! ERROR : THE ENTERED DATA IS INVALID ! \n\t\t Enter the binary data in form of 0 and 1 !! "<<endl<<endl;
        }


        cout<<endl<<endl<<"-> Do you want to continue (y/n) : ";
        cin>>ch;
        cout<<endl;

    }
    return 0;
}

