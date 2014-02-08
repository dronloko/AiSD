// Copyright 2013 <DronLoko>

#include<iostream>
#include<algorithm>

using std::swap;
using std::cin;
using std::cout;
using std::endl;

struct date {
    int day;
    int month;
    int year;
    int flag;  // started meeting=1,didn't started to meet=0,finished meeting=-1
};

// quick sorting for dates
void QuickSort(date *a, int begin, int end, bool (*less)(const date &, const date &)) {
    int l = begin;
    int r = end;
    date middle = a[(begin+end)/2];
    do {
        while (less(a[l], middle)) l++;
        while (less(middle, a[r])) r--;
        if (l <= r) {
            swap(a[l], a[r]);
            l++;
            r--;
        }
    } while (l <= r);
    if (r > begin)
        QuickSort(a, begin, r, less);
    if (l < end)
        QuickSort(a, l, end, less);
}
bool dateless(const date &date1, const date &date2) {  // date1 < date2 ?
    if (date1.year < date2.year) return true;
    if (date1.year > date2.year) return false;
    if (date1.month < date2.month) return true;
    if (date1.month > date2.month) return false;
    if (date1.day < date2.day) return true;
    if (date1.day > date2.day) return false;
    if (date1.flag < date2.flag) return true;
    return false;
}
date *readdates(int n) {
    date *a = new date[2*n];               // Array to enter dates for n persons
    for (int i = 0; i < n; ++i) {          // Cycle to enter dates for n persons
        cin >> a[2*i].day;                 // day of birthday
        cin >> a[2*i].month;               // month of birth
        cin >> a[2*i].year;                // year of birth
        a[2*i].year += 18;                 // year of start meeting
        a[2*i].flag = 1;                   // flag = started meetings (18 years)
        cin >> a[2*i+1].day;               // day of death
        cin >> a[2*i+1].month;             // month of death
        cin >> a[2*i+1].year;              // year of death
        a[2*i+1].flag = -1;                // flag = finished meetings (died)
        if (dateless(a[2*i+1], a[2*i])) {  // if died before 18 years old?
            a[2*i+1].flag = 0;             // will not consider this human
            a[2*i].flag = 0;               // will not consider this human
        }
        a[2*i].year += (80-18);            // years = 80 years old
        if (dateless(a[2*i], a[2*i+1])) {  // if end of meeting before 80 years
            a[2*i+1] = a[2*i];             // year of death (for meetings) =
                                           // = year of finish meeting
            a[2*i+1].flag = -1;            // flag = finished meetings(80 years)
        }
        a[2*i].year -= (80-18);            // year of birth
    }
    return a;
}
int count_people(date *dates, int length) {
    int s = 0, smax = 0;
    for (int i = 0; i < length; ++i) {
        s += dates[i].flag;
        if (s > smax) smax = s;
    }
    return smax;
}
int main() {
    int n;
    cin >> n;
    date *dates = readdates(n);
    QuickSort(dates, 0, 2*n-1, dateless);
    cout << count_people(dates, 2*n) << endl;
}

