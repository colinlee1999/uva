#include <fstream>
#include <ctime>
using namespace std;

ofstream fout("1062_input.txt");

int
main()
{
    srand(time(NULL));
    int N = 100;
    for (int i = 0; i < N; i++)
    {
        int len = rand() % 1000 + 1;
        for (int j = 0; j < len; j++)
            fout << (char)(rand() % 26 + 'A');
        fout << endl;
    }
    fout << "end" << endl;
}
