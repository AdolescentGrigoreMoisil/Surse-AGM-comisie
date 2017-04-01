/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest 
Evaluator*/

#include <bits/stdc++.h>

using namespace std ;

void result(string msg,int p) {
    cerr << msg ; 
    cout << p ; 
    exit(0);
}
int main(){
    srand (time(NULL)) ;
    ifstream fin ("maxim2.out") ;
    if (!fin.is_open()) {
        result ("Fisier de iesire corupt", 0) ;
    }
    ifstream gin ("maxim2.ok") ;
    if (!gin.is_open()) {
        result ("Fisierul ok al comisiei este busit", 0) ;
    }
    double a ;
    double b ; 
    try {
        fin >> a; 
    }catch (exception e) {
        result ("Eroare la citirea rezultatului din sursa participantului\n", 0) ;
    }
    if (!(gin >> b)) {
        result ("Evaluator busit!", 0) ; 
    }
    if (fabs(a - b) <= 0.0000001) {
        result ("Pe barosaneala!", 5) ;
    }
    vector <string> Messages ;
    Messages.push_back ("Sa fie blat?") ;
    Messages.push_back ("Nu foarte pe barosaneala...") ;
    Messages.push_back ("Call $Sorin") ;
    Messages.push_back ("N-am fost noi, boss") ; 
    random_shuffle(Messages.begin(), Messages.end()) ;
    result (Messages[0], 0) ;
    return 0;
}
