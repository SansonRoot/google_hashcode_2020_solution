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

int pickBook(int index, vector<pair<int,int>> arr,unordered_map<int,int> states);

struct LibraryData{
    int books=0;
    int sign_up_days=0;
    int books_per_day=0;
    bool scan= false;
    vector<pair<int,int>>scannable_books;
};

int main() {

    ifstream is("../f_libraries_of_the_world.txt");
    ofstream os("../o_f_libraries_of_the_world.txt");

    int books_n,lib_n,scan_n,val;

    is>>books_n>>lib_n>>scan_n;

//    cout<<books_n<<endl;

    vector<vector<int>> libraries;

    //contains the books and their values
    vector<pair<int, int>> vpair;

    vector<int> bookValues;

    //storing them in unordered map
    unordered_map<int, int> unorderedMap;

    unordered_map<int, LibraryData> libraries_to_sign_up ;


    //fill up values of books
    for (int i = 0; i <books_n ; ++i) {

        is>>val;

        bookValues.push_back(val);
//
//        pair<int, int> p {val,i};
//
//        vpair.push_back(p);
//
//        unorderedMap[val]=i;

    }

    //fill up libraries books, sign up days and max books to scan

    for (int j = 0; j <lib_n ; ++j) {

        int books,sign_d,max_books;

        is>>books>>sign_d>>max_books;

//        cout<<"books "<<books<<" ";

        LibraryData ld{};

        vector<pair<int,int>> tmp{};

        for (int i = 0; i < books; ++i) {
            int tp;
            is>>tp;

            pair<int, int> p {tp,bookValues[tp]};

            tmp.push_back(p);
        }

        if (sign_d>=scan_n) {

            continue;
        }

        if (sign_d<scan_n){

            ld.books = books;
            ld.sign_up_days = sign_d;
            ld.books_per_day = max_books;
            ld.scan = true;
            ld.scannable_books = tmp;


            libraries_to_sign_up[j]=ld;
        } /*else{

            ld.books = books;
            ld.sign_up_days = sign_d;
            ld.books_per_day = max_books;
            ld.scan = false;
        }*/



    }

    //sort books
//    sort(vpair.begin(),vpair.end(),comparator());

//    cout<<vpair[0].second<<endl;

//    os<<libraries_to_sign_up.size();

    unordered_map<int, int> tracks;

    priority_queue <int> pq;

    unordered_map<int, vector<int>> output{};

    int counter=0;

    for( auto r : libraries_to_sign_up){

        if (r.second.scan){

            int quotient = r.second.books/r.second.books_per_day;

            int days =  quotient +r.second.sign_up_days;

            int d2 = r.second.books/r.second.books_per_day+r.second.sign_up_days;

            //all will be scanned

            if (days+1<=scan_n){

                vector<int> out{};

                for (int i = 0; i <r.second.scannable_books.size() ; ++i) {
                    out.push_back(r.second.scannable_books[i].first);

//                    tracks[r.second.scannable_books[i].first]=1;
                }

                output[r.first]=out;

//                os<<endl;

//                os<<r.first<<" "<<r.second.scannable_books.size()<<endl;

//                for (int i = 0; i < r.second.scannable_books.size(); ++i) {

//                    os<<r.second.scannable_books[i];

//                    if (i+1<r.second.scannable_books.size()){
//                        os<<" ";
//                    }
//
//                }

                counter++;


            }else{

                //create sort pairs
                sort(r.second.scannable_books.begin(),r.second.scannable_books.end(),comparator());

                vector<int> out{};

                int it=0;

//                cout<<"========================"<<endl;
//                cout<<r.first<<" "<<r.second.scannable_books.size()<<endl;
//                cout<<"========================"<<endl;

                for (int j = 0; j < scan_n-(r.second.sign_up_days+1) ; ++j) {

                    for (int i = 0; i < r.second.books_per_day; ++i) {

//                        cout<<"At Counter "<<it<<endl;
//
//                        if (it>=r.second.scannable_books.size())break;
//
//                        int index = pickBook(it,r.second.scannable_books,tracks);
//
//                        cout<<"We dont get here "<<index<<endl;
//
//                        if (index<0){
//
//                            cout<<"Item not found "<<it<<endl;
//
//                            index = r.second.scannable_books[it].first;
//                        }

                        out.push_back(r.second.scannable_books[it].first);
//                        tracks[index]=1;

                        it++;

                    }

                    if (it>=r.second.scannable_books.size())break;

//                    cout<<"Inner loop exits j at "<<j<<endl;

                }

                if (!out.empty()){

                    counter++;

                    output[r.first] = out;

                }

            }

//            scan_n -=r.second.sign_up_days;


        }

    }


    os<<counter;

    for (auto r: output){

        os<<endl;

        os<<r.first<<" "<<r.second.size()<<endl;

        for (int i = 0; i <r.second.size() ; ++i) {

            os<<r.second[i];

            if (i+1<r.second.size()){
                os<<" ";
            }

        }
    }

    is.close();
    os.close();

    cout<<"Done "<<counter;

    return 0;
}


int pickBook(int index, vector<pair<int,int>> arr,unordered_map<int,int> states){

    if (index>=arr.size())
        return -1;

    int it = arr[index].first;

    if (states.find(it)==states.end()) return it;

    cout<<"Executing recursion "<<index<<endl;

    return pickBook(index+1,arr,states);

}