// Chapter 14 Regex
#include <string>
#include <regex>
#include <iostream>
#include <iomanip>
using namespace std;


int main()
{
    string data = "XML tag: <tag-name>the value</tag-name>.";
    cout << "data:              " << data << "\n\n";

    smatch m;   // for returned details od the match
    bool found = regex_search( data,
                               m,
                               regex("<(.*)>(.*)</(\\1)>") );
                    
    // print match details:
    cout << "smatch methods:" << endl;
        cout << "  m.empty():          " << boolalpha << m.empty() << endl;
        cout << "  m.size():           " << m.size() << endl;
    if( found ){
        cout << "  m.str():            " << m.str() << endl;
        cout << "  m.length():         " << m.length() << endl;
        cout << "  m.position():       " << m.position() << endl;
        cout << "  m.prefix().str():   " << m.prefix().str() << endl;
        cout << "  m.suffix().str():   " << m.suffix().str() << endl;
        cout << endl;

        // iterating over all matches (using the match index):
        cout << "\nmatches using indexing:" << endl;
        for( int i=0; i<m.size(); ++i ){
            cout << "  m[" << i << "].str():     " << m[i].str() << endl;
            cout << "  m.str(" << i << "):       " << m.str(i) << endl;
            cout << "  m.position(" << i <<"):   " << m.position(i)
                 << endl;
        }
        cout << "\ncalling m[m.size()]:\n";
        cout << "  m[" << m.size() << "].empty():  " << m[m.size()].str().empty() << endl;
        cout << "  m[" << m.size() << "].str():    " << m[m.size()].str() << endl;
        cout << "  m.str(" << m.size() << "):      " << m.str( m.size() ) << endl;
        cout << "  m.position(" << m.size() << "): " << m.position( m.size() )
             << endl;

        // iterating over all matches (using iterators):
        cout << "\nmatches using iterators:" << endl;
        for( auto pos = m.begin(); pos != m.end(); ++pos ){
            cout << "  " << *pos << "\t";
            cout << "(length: " << pos->length() << ")" << endl;
        }
    }
}
