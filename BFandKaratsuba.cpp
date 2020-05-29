/* Copyright 2018, John M Lee
 * BruteForce Multiplication and Karatsuba Multiplication
 */


#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
using namespace std;


vector<int> bruteForceMultiply(vector<int>& a, vector<int>& b);

vector<int> addition(vector<int>& a, vector<int>& b);

vector<int> subtraction(vector<int>& a, vector<int>& b);

vector<int> karatsuba(vector<int>& a, vector<int>& b);

string vecStr(vector<int>& a);

int main() {
    string a;
    string b;
    cin >> a;
    cin >> b; // this will take in string

    if (b.length() > a.length()) { // b's length is greater than a
        // difference in digits
        a = string(b.length() - a.length(), '0') + a; // add zeros
    }
    if (a.length() > b.length()) {
        b = string(a.length()-b.length(), '0') + b;
    }

    vector<int> firstVal;
    vector<int> secondVal;

    for (unsigned int i = 0; i < a.length(); ++i) {
        int x = a[i] -'0';
        firstVal.push_back(x);
    }
    for (unsigned int i = 0; i < b.length(); ++i) {
        int y = b[i] -'0';
        secondVal.push_back(y);
    }


    // addition
    vector<int> temp = addition(firstVal,secondVal);


    cout <<"Testing addition" << endl;
    // vector<int> temp;
    string tempS;

    for (vector<int>::iterator i = temp.begin();
            i != temp.end(); ++i) {
    //for (auto i = temp.begin(); i != temp.end(); ++i) {
        tempS += to_string(*i);
    }
    cout << tempS << endl;

    // BFM
    vector<int> temp2 = bruteForceMultiply(firstVal,secondVal);

    string temps2;

    // if all of the contents of the vector is 0 it will push single 0 after making it empty.
    if (all_of(temp2.begin(), temp2.end(), [](int i) { return i == 0; })) {
      temp2.clear();
      temp2.push_back(0);
    }
    else {
      // else it will delete zeros in front 
      while (*temp2.begin() == 0)
          temp2.erase(temp2.begin());
    }
    for (vector<int>::iterator it = temp2.begin();
            it != temp2.end(); ++it) {
        temps2 += to_string(*it);
    }


    cout << "Brute Force: " <<  temps2 << endl;

    // subtraction


    /*
    vector<int> temp3 = subtraction(firstVal,secondVal);

    cout << "testing subtraction" << endl;
    string temps3;

    for (vector<int>::iterator it = temp3.begin();
            it != temp3.end(); ++it)
        temps3 += to_string(*it);

    cout << temps3 << endl;
    */

    // karatsuba

    vector<int> temp4 = karatsuba(firstVal,secondVal);

    string temps4;

    if (all_of(temp4.begin(), temp4.end(), [](int i) { return i == 0; })) {
        temp4.clear();
        temp4.push_back(0);
    }
    else {
      while (*temp4.begin() == 0) {
          temp4.erase(temp4.begin());
        }
    }
    for (vector<int>::iterator it = temp4.begin();
            it != temp4.end(); ++it)
        temps4 += to_string(*it);

    cout << "Karatsuba: " << temps4 << endl;


    return 0;
}

string vecStr(vector<int>& a) {
    string retStr;
    for (vector<int>::iterator it = a.begin();
            it != a.end(); ++it)
        retStr += to_string(*it);

    return retStr;
}


vector<int> addition(vector<int>& a, vector<int>& b) {
    vector<int> res;
    int carry = 0;
    int t1, t2;
    int tempVal;

    if (a.size() > b.size()) {
        int diff = a.size() - b.size();
        while (diff > 0) {
            b.insert(b.begin(), 0);
            diff--;
        }
    }
    if (b.size() >  a.size()) {
        int diff = b.size() - a.size();
        while (diff > 0) {
            a.insert(a.begin(), 0);
            diff--;
        }
    }



    for (unsigned int i = a.size(); i --> 0;) {
      t1 = a.at(i);
      t2 = b.at(i);

      tempVal = t1 + t2;
      if (carry > 0) {
        tempVal = tempVal + carry;
        carry = 0;
      }
      if (tempVal > 9) {
        carry = floor((tempVal/10));
        tempVal = tempVal % 10;
      }
      res.insert(res.begin(), tempVal);
      // res.push_back(tempVal);
      tempVal = 0;
    }


    if (carry != 0) {
        res.insert(res.begin(), carry);
        //res.push_back(carry);
    }

    return res;
}


vector<int> bruteForceMultiply(vector<int>& a, vector<int>& b) {
    vector<int> res;
    vector<int> tempVec;
    int carry = 0;
    int tempVal;
    int count = 0;
    // iterating backwards
    // from 10^0 to 10^i digits

    // pad 0s
    if (a.size() > b.size()) {
        int diff = a.size() - b.size();
        while (diff > 0) {
            b.insert(b.begin(), 0);
            diff--;
        }
    }
    if (b.size() >  a.size()) {
        int diff = b.size() - a.size();
        while (diff > 0) {
            a.insert(a.begin(), 0);
            diff--;
        }
    }

    if (all_of(b.begin(), b.end(), [](int i) {return i == 0;})) {
        res.push_back(0); // push 0 if multiply by 0
        return res; // return
    }
    if (all_of(a.begin(), a.end(), [](int i) {return i == 0;})) {
        res.push_back(0);
        return res;
    }



    for (unsigned int i = a.size(); i --> 0;) {
        for (unsigned int j = b.size(); j --> 0;) {

            tempVal = a[i] * b[j];
            if (carry > 0) {  // if the carry val is greater 0
                tempVal = tempVal + carry;
                carry = 0; // make it zero if carried over.
            }
            if (tempVal > 9) { // greater than 9 = 10, 11, ...
                carry = floor((tempVal/10));
                tempVal = tempVal % 10;
            }
            // using insert to push it front
            tempVec.insert(tempVec.begin(), tempVal);

        } // inner for loop ends

        if (carry > 0) {
            tempVec.insert(tempVec.begin(), carry);
            carry = 0;
        }

        if (res.size() < tempVec.size()) {
            // pad with zero
            int diff = tempVec.size() - res.size();
            while (diff > 0) {
                res.insert(res.begin(), 0);
                diff--;
            }
        }

        res = addition(tempVec,res);
        tempVec.clear();
        count++;
        if (count > 0) {
            int n = count;
            while (n > 0) {
                tempVec.push_back(0);
                n--;
            }
        }

    } // end outer for loop
    if (carry > 0)
        res.insert(res.begin(), carry);

    return res;
}

vector<int> subtraction(vector<int>& a, vector<int>& b) {
    vector<int> res;
    int temp;
    int tempVal;


    // pad with zero if a or b is less than other



    if (a.size() > b.size()) {
        int diff = a.size() - b.size();
        while (diff > 0) {
            b.insert(b.begin(), 0);
            diff--;
        }
    }
    if (b.size() >  a.size()) {
        int diff = b.size() - a.size();
        while (diff > 0) {
            a.insert(a.begin(), 0);
            diff--;
        }
    }

    // swap if a is less than b
    //
    //
    if (all_of(a.begin(), a.end(), [](int i) { return i == 0; })
            && all_of(b.begin(), b.end(), [](int i) { return i == 0; }) ) {
        res.push_back(0);
        return res;
    }
    if (all_of(b.begin(), b.end(), [](int i) { return i == 0; })) {
        res = a;
        return res;
    }
    for (unsigned int i = a.size(); i --> 0;) {
        tempVal = a[i] - b[i];

        if (tempVal < 0) {
            temp = a[i-1];
            tempVal = 10 + tempVal;
            a[i-1] = temp - 1;
        }

        res.insert(res.begin(), tempVal);

    }
     // }

    return res;
}

vector<int> karatsuba(vector<int>& a, vector<int>& b) {

    vector<int> res;
    vector<int> resTemp;

    vector<int> a0,a1,b0,b1;


    vector<int> c2, c0, c1;
    vector<int> temp; // this will be used as temp vec in c1 recursive call

    vector<int> fc1;

    vector<int> aTemp;
    vector<int> bTemp;
    vector<int> midTemp;
    vector<int> midTemp2;

    // i don't need first part of the algorithm ?
    if (a.size() <= 1 || b.size() <= 1) {
        res = bruteForceMultiply(a,b);
        return res;
    }
    else {
        int m = floor(( max(a.size() , b.size()) /2)) ;
       
            if (m == 0) {
                a0.push_back(0);
                a1 = a;
                b0.push_back(0);

                b1 = b;
            }
            else {
                for (unsigned int i = a.size(); i --> (a.size() - m);) { // first m digits
                    // cout << a.at(i) << " i of a goes to a0 " << endl;
                    a0.insert(a0.begin(), a[i]);
                }

                //cout << to_string(a.size() - m) << " a.size() - m" << endl;

                for (int i = (a.size() - m); i --> 0;) { // remaining
                    // cout << a.at(i) << " i of a goes to a1 " << endl;
                    a1.insert(a1.begin(), a[i]);
                }


                for (unsigned int i = b.size(); i --> (b.size() - m);) { // first m digits
                    //cout << b.at(i) << " i of b goes to b0 " << endl;
                    b0.insert(b0.begin(), b[i]);
                }

                //cout << to_string(b.size() - m) << " b.size() - m" << endl;

                for (int i = (b.size() - m); i -->0;) { // remaining
                    //cout << b.at(i) << " i of b goes to b1 " << endl;
                    b1.insert(b1.begin(), b[i]);
                }
            }






        // recursive calls

        c2 = karatsuba(a1, b1);

   
        string ctwo = vecStr(c2);

        // cout << "c2 contains : " << ctwo << ": which is karatsuba (a1, b1)  " << endl;

        c0 = karatsuba(a0, b0);

        string czero = vecStr(c0);
        // cout << "c0 contains : " << czero << ": which is karatsuba (a0, b0) " << endl;

  


        aTemp = addition(a0,a1);

        string aytemp = vecStr(aTemp);
   

        bTemp = addition(b0,b1);



        string beetemp = vecStr(bTemp);


    
        midTemp = karatsuba(aTemp,bTemp);

        string meedteemp = vecStr(midTemp);
        // cout << "midtemp contains : " << meedteemp << ": which is karatsuba ((a0 + a1)  (b0 + b1) )" << endl;

        //cout << " " << endl;
        midTemp2 = subtraction(midTemp,c2);

        string meedteemp2 = vecStr(midTemp2);
        //cout << "midTemp - c2 : " << meedteemp2  << endl;
        //cout << " " << endl;



        c1 = subtraction(midTemp2, c0);

        for (int i = 0; i < 2*m; ++i) {
            // cout << i << " i " << endl;
            c2.push_back(0);
        }


        for (int i = 0; i < m; ++i) {
            // cout << i << " i " << endl;
            c1.push_back(0);
        }

        string ceeone = vecStr(c1);


        res = addition(c2,c1);
        string resS = vecStr(res);


        res = addition(res,c0);
        string resS2 = vecStr(res);
   
        return res;
    }

}
