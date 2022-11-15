#include <iostream>
#include <stdlib.h>
using namespace std;

class CRC_error_detection
{
public:
	int n, d[15], g[10], k, m;
	int rem[20];
	string str;

public:
	void input();
	void coffecient();
	void codeword();
	int exor(int, int);
	void modulus_2_division();
	void append();
};
void CRC_error_detection ::input()
{
	cout << "-> Enter the number of bits in dataword :";
	cin >> n;
	cout << "Enter the dataword :";
	for (int i = 0; i < n; i++)
	{
		cin >> d[i];
	}
	cout << "Enter the polynomial :";
	cin >> str;
	coffecient();
}
void CRC_error_detection ::coffecient()
{
	k = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (i == 0)
		{
			if (str.substr(i, 1) == "x")
			{
				g[k] = 1;
				k++;
			}
		}
		if (str.substr(i, 1) == "+")
		{
			if (str.substr(i + 1, 1) != "x")
			{
				g[k] = 0;
				k++;
			}
			else
			{
				g[k] = 1;
				k++;
			}
		}
	}
	cout << "CRC generator is :";
	for (int i = 0; i < k; i++)
	{
		cout << g[i] << " ";
	}
	codeword();
}
void CRC_error_detection ::codeword()
{
	m = n + (k - 1);
	cout << endl
		 << "Code word is :";
	for (int i = n; i < m; i++)
	{
		d[i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		cout << d[i] << " ";
	}
}
int CRC_error_detection ::exor(int a, int b)
{
	if (a == b)
		return 0;
	else
		return 1;
}
void CRC_error_detection ::modulus_2_division()
{
	int temp[20];
	for (int i = 0; i < k; i++)
		rem[i] = d[i];
	for (int j = k; j <= m; j++)
	{
		for (int i = 0; i < k; i++)
			temp[i] = rem[i];
		if (rem[0] == 0)
		{
			for (int i = 0; i < k - 1; i++)
				rem[i] = temp[i + 1];
		}
		else
		{
			for (int i = 0; i < k - 1; i++)
				rem[i] = exor(temp[i + 1], g[i + 1]);
		}
		if (j != m)
			rem[k - 1] = d[j];
		else
			rem[k - 1] = 0;
	}
}
void CRC_error_detection ::append()
{
	cout << endl
		 << "CRC :";
	for (int i = 0; i < k - 1; i++)
	{
		cout << rem[i] << " ";
	}
	int p = 0;
	for (int i = n; i < m; i++)
	{
		d[i] = rem[p];
		p++;
	}
	cout << endl
		 << "Transmitted data is :";
	for (int i = 0; i < m; i++)
	{
		cout << d[i] << " ";
	}
	cout << endl
		 << "\n*Data recieved by the receiver*" << endl;
	string ch;
	cout << "\nEnter the type :";
	cin >> ch;
	if (ch == "noisy" || ch == "Noisy")
	{
		int s;
		srand(0);
		s = rand() % m;
		cout << "Before Codeword[" << s << "]=" << d[s] << endl;
		if (d[s] == 0)
			d[s] = 1;
		else
			d[s] = 0;
		cout << "Now Codeword[" << s << "]=" << d[s];
	}
	cout << "\nNow Codeword becomes :";
	for (int i = 0; i < m; i++)
	{
		cout << d[i] << " ";
	}
	modulus_2_division();
	cout << "\nRemainder :";
	for (int i = 0; i < k - 1; i++)
	{
		cout << rem[i] << " ";
	}
	cout << endl;
	int flag = 0;
	for (int i = 0; i < k - 1; i++)
	{
		if (rem[i] != 0)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		cout << "\n received correct data .";
	else
		cout << "\nsome error in data please check and send again.";
}
int main()
{
	cout<<endl<<"\t ** PROGRAM TO IMPLEMENT CYCLIC RENUNDANCY CHECK ** "<<endl<<endl;
	
	CRC_error_detection obj;
	obj.input();
	obj.modulus_2_division();
	obj.append();
	return 0;
}