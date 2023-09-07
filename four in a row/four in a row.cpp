#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

//print header
void header()
{
    cout << "\t     -- Four  In  A  Row --\n" << " ________________________________________________\n\n";
}

//print the array
void print(string array[100][100], int& m, int& n)
{
    header();
    for (int i = 0; i < n; i++)
    {
        if (i==0)
        {
            cout << "\n   ";
        }
        cout << "  " << i << " ";
    }
        
    cout << endl;
    for (short i = 0; i < m; i++)
    {
        for (short j = 0; j < n; j++)
        {
            if (j==0)
            {
                cout << "   |";
            }
            cout<< " " << array[i][j] << " |";
        }
        cout << endl;
    }
}

//check if game is finished
bool finish(string array[100][100], int i, int j, int& p)
{
    int pieces, x, y;
    pieces = p-1;
    x = i;
    y = j;

    //check if there are pieces in the right side of array[i][j]
    while (array[i][j] == array[x][++y]) pieces--;
    if (pieces == 0) return true;
    else y = j;

    //check if there are pieces in the left side of array[i][j]
    while (array[i][j] == array[x][--y]) pieces--;
    if (pieces == 0) return true;
    else
    {
        pieces = p-1;
        y = j;
    }

    //check if there are pieces in the upside of array[i][j]
    while (array[i][j] == array[--x][y]) pieces--;
    if (pieces == 0) return true;
    else x = i;

    //check if there are pieces in the downside of array[i][j]
    while (array[i][j] == array[++x][y]) pieces--;
    if (pieces == 0) return true;
    else
    {
        pieces = p-1;
        x = i;
    }

    //check if there are pieces in right of the main diagonal of array[i][j]
    while (array[i][j] == array[++x][++y]) pieces--;
    if (pieces == 0) return true;
    else
    {
        x = i;
        y = j;
    }

    //check if there are pieces in left of the main diagonal of array[i][j]
    while (array[i][j] == array[--x][--y]) pieces--;
    if (pieces == 0) return true;
    else
    {
        pieces = p-1;
        x = i;
        y = j;
    }

    //check if there are pieces in right of the secondery diagonal of array[i][j]
    while (array[i][j] == array[--x][++y]) pieces--;
    if (pieces == 0) return true;
    else
    {
        x = i;
        y = j;
    }

    //check if there are pieces in left of the secondery diagonal of array[i][j]
    while (array[i][j] == array[++x][--y]) pieces--;
    if (pieces == 0) return true;

    return false;
}

//process the game
void game(string player1, string player2, string array[100][100], int& m, int& n, int& p, int& counter, ofstream& WriteRecord)
{
    system("CLS");
    print(array, m, n);
    int i, j;
	do
	{
        //player 1 turn
		if (counter % 2 == 1) cout << "\n   " << player1 << "'s turn : ";

        //player 2 turn
		else cout << "\n   " << player2 << "'s turn : ";

        cin >> j;
        //wrong entered number
        while (j >= n)
        {
            cout << "\n  The Column Is Out Of Range! please Enter Another Number : ";
            cin >> j;
        }
        while (array[0][j] != " ")
        {
            cout << "\n  The Column Is Full! please Enter Another Number : ";
            cin >> j;
        }
        for (i = m - 1; i >= 0; i--)
        {
            if (array[i][j] == " ")
            {
                //player 1 turn
                if (counter % 2 == 1) array[i][j] = "X";

                //player 2 turn
                else array[i][j] = "O";
                
                counter++;
                break;
            }
        }

        system("CLS");
        print(array, m, n);

	} while (!finish(array, i, j, p) && counter-1 != m*n);
    //player1 wins
    if (finish(array, i, j, p) && counter % 2 == 0 && counter-1 != m * n)
    {
        WriteRecord << " - " << player1 << "  --->  " << pow(n, m) / floor(counter / 2) << endl;
        cout << "\n   *** " << player1 << " Won! ***\n";
    }
    //player2 wins
    else if (finish(array, i, j, p) && counter % 2 == 1 && counter - 1 != m * n)
    {
        WriteRecord << " - " << player2 << "  --->  " << pow(n, m) / floor(counter/2) << endl;
        cout << "\n   *** " << player2 << " Won! ***\n";
    }
    //draw
    else if (!finish(array, i, j, p) && counter - 1 == m*n)
    {
        cout << "\n   *** DRAW ***\n";
    }
}

//start the game
void start(int& m, int& n, int& p, ofstream& WriteRecord)
{
    system("CLS");
    header();
    int counter = 1;
    string array[100][100];

    //array creating
    for (short i = 0; i < m; i++)
    {
        for (short j = 0; j < n; j++)
        {
            array[i][j] = " ";
        }
    }

    string player1, player2;
    cin.ignore();
    cout << "\n  Please Enter First Player's Name :  ";
    getline(cin, player1);
    cout << "\n  " << player1 << "'s Character Is 'X'\n";
    
    cout << "\n  Please Enter Second Player's Name :  ";
    getline(cin, player2);
    cout << "\n  " << player2 << "'s Character Is 'O'\n\n";
    system("pause");
    
    game(player1, player2, array, m, n, p, counter, WriteRecord);
    system("pause");
}

//show the records
void records(ofstream& WriteRecord)
{
    system("CLS");
    header();
    string record;
    ifstream ReadRecord("record.txt");

    while (getline(ReadRecord, record))
    {
        cout << record << endl;
    }

    ReadRecord.close();

    char r;
    cout << "\n   Enter 0 To Return to Menu : ";
    cin >> r;
    while (r != '0')
    {
        cout << "\n   You Entered Wrong Number! Enter Another Number : ";
        cin >> r;
    }
}

//change game setting
void setting(int& m, int& n, int& p)
{
    system("CLS");
    header();

    cout << "  1.Rows: " << m << "       2.Columns: " << n << "       3.Pieces: " << p;
    char s;
    cout << "\n\n Please Enter The Number Of The Parameter You\n Want To Change (Enter 0 To Return To Menu) : ";
    cin >> s;

    //parameter selection
    switch (s)
    {
        //row number change
        case '1':
            cout << "\n Please Enter The Number Of Rows :  ";
            cin >> m;
            break;

        //column number change
        case '2':
            cout << "\n Please Enter The Number Of Columns :  ";
            cin >> n;
            break;

        //piece number change
        case '3':
            cout << "\n Please Enter The Number Of Pieces :  ";
            cin >> p;
            while (p > m&& p > n)
            {
                cout << "\n Imposible Number Of Pieces! Please Enter Another Number : ";
                cin >> p;
            }
            break;

        //return to menu
        case '0':
            return;
    }

    setting(m, n, p);
} 

//exit the game
int exit()
{
    return 0;
}

//choose function
void menu(int& m, int& n,int& p, ofstream& WriteRecord)
{
    system("CLS");
    char function;
    header();
    cout << "  1.Start" << "     2.Records" << "     3.Setting" << "     4.Exit\n";
    cout << "\n  Enter The Number Of The Function You Want : ";
    cin >> function;

    //function selection
    switch (function)
    {
        //start
        case '1':
            start(m, n, p, WriteRecord);
            menu(m, n, p, WriteRecord);
            break;

        //exit
        case '2':
            records(WriteRecord);
            menu(m, n, p, WriteRecord);
            break;

        //record
        case '3':
            setting(m, n, p);
            menu(m, n, p, WriteRecord);
            break;

        //setting
        case '4':
            exit();
            break;
    }

}

int main()
{
    //m=row(arz) , n=column(tool)
    int m = 6, n = 7, p = 4;
    ofstream WriteRecord("record.txt");
    menu(m, n, p, WriteRecord);
}
