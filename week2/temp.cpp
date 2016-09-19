#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main()
{
    int case_number = 1;
    while (case_number<100)
    {
        int number_of_chambers;
        int number_of_elements;
        cin >> number_of_chambers;
        if (cin.eof())
        {
            break;
        }
        cin >> number_of_elements;
        vector<int> masses;
        for (int i = 0; i < number_of_elements; i++)
        {
            int mass;
            cin >> mass;
            masses.push_back(mass);
        }
        
        // I have read the book - to be honest - I wouldn't be able to come up
        // with this greedy algorithm myself now

        sort(masses.begin(), masses.end());

        int large_index = masses.size();
        int small_index = large_index - 2 * number_of_chambers;

        double mean = 0;

        for (vector<int>::iterator mi = masses.begin(); mi != masses.end(); mi++)
        {
            mean += *mi;
        }
        mean = mean / number_of_chambers;

        cout << "Set #" << case_number << endl;        
        double imbalance = 0;
        for (int i = 0; i < number_of_chambers; i++)
        {
            double chamber_sum = 0;
            cout << i << ":";
            if (small_index >= 0)
            {
                chamber_sum += masses[small_index];
                cout << " " << masses[small_index];
            }
            if (large_index > 0)
            {
                cout << " " << masses[large_index - 1];
                chamber_sum += masses[large_index - 1];
            }
            double diff = chamber_sum - mean;
            imbalance += (diff > 0 ? diff : -diff);
            small_index++;
            large_index--;
            cout << endl;
        }
        std::cout << std::setprecision(5) << std::fixed;
        cout << "IMBALANCE = " << imbalance << endl;
        cout << endl;

        case_number++;
    }

    return 0;
}