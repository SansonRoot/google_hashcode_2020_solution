#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct comparator{
    bool operator()(const pair<int, int>& a,const pair<int, int>& b){
        return a.second > b.second;
    }
};

struct mComparator{
    bool operator()(const pair<int, int>& a,const pair<int, int>& b){
        return a.second > b.second;
    }
};

struct LibraryData{
    int books;
    int sign_up_days;
    int books_per_day;
    bool scan= false;
    vector<int>scannable_books;
};

int main() {

    ifstream is("../e_so_many_books.txt");
    ofstream os("../out_e_so_many_books.txt");

    int books_n,lib_n,scan_n,val;

    is>>books_n>>lib_n>>scan_n;

//    cout<<books_n<<endl;

    vector<vector<int>> libraries;

    //contains the books and their values
    vector<pair<int, int>> vpair;

    //storing them in unordered map
    unordered_map<int, int> unorderedMap;

    unordered_map<int, LibraryData> libraries_to_sign_up ;


    //fill up values of books
    for (int i = 0; i <books_n ; ++i) {

        is>>val;

//        cout<<val<<endl;
//
        pair<int, int> p {val,i};

        vpair.push_back(p);

        unorderedMap[val]=i;

    }

    //fill up libraries books, sign up days and max books to scan

    int counter=0;

    for (int j = 0; j <lib_n ; ++j) {

        int books,sign_d,max_books;

        is>>books>>sign_d>>max_books;

//        cout<<"books "<<books<<" ";

        LibraryData ld{};

        vector<int> tmp{};

        for (int i = 0; i < books; ++i) {
            int tp;
            is>>tp;

            tmp.push_back(tp);
        }

        if (sign_d>scan_n) {

            continue;
        }

        if (sign_d<scan_n){

            ld.books = books;
            ld.sign_up_days = sign_d;
            ld.books_per_day = max_books;
            ld.scan = true;
            ld.scannable_books = tmp;

            counter++;

        } else{

            ld.books = books;
            ld.sign_up_days = sign_d;
            ld.books_per_day = max_books;
            ld.scan = false;
        }

        libraries_to_sign_up[j]=ld;

    }

    //sort books
    sort(vpair.begin(),vpair.end(),comparator());

//    cout<<vpair[0].second<<endl;

    os<<libraries_to_sign_up.size();

    priority_queue <int> pq;

    for( auto r : libraries_to_sign_up){

        if (r.second.scan){

            int days = r.second.books/r.second.books_per_day+r.second.books%r.second.books_per_day+r.second.sign_up_days;

            //all will be scanned

            if (days+1<=scan_n){

                os<<"\n";

                os<<r.first<<" "<<r.second.scannable_books.size()<<"\n";

                for (int i = 0; i < r.second.scannable_books.size(); ++i) {

                    os<<r.second.scannable_books[i];

                    if (i+1<r.second.scannable_books.size()){
                        os<<" ";
                    }

                }

            }else{

                //create sorted pairs

                for (int i = 0; i <r.second.scannable_books.size() ; ++i) {

                    int first = r.second.scannable_books[i];

                    pq.push(vpair[first].second);

                }

                vector<int> out{};

                for (int j = 0; j < scan_n-(r.second.sign_up_days+1) ; ++j) {

                    if(unorderedMap.find(pq.top()) != unorderedMap.end()){
                        out.push_back(unorderedMap[pq.top()]);

                        pq.pop();
                    }

                }

                if (!out.empty()){
                    os<<"\n";

                    os<<r.first<<" "<<out.size()<<"\n";

                    for (int k = 0; k <out.size() ; ++k) {
                        os<<(out[k]);

                        if (k+1<out.size()){
                            os<<" ";
                        }

                    }

                }

            }


        }

    }

    os.close();

    cout<<"Done ";

    return 0;
}
