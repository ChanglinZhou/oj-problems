#include <iostream>  
using namespace std; 

const int MAX = 100; 
bool UsedBalloon[MAX+1]; 

bool CanFactor(int i, int b) 
{ 
    if (b == 1) { // if b is equal to 1, then you needn't find factor for it, because it is not the cared nu                 //mber
        return true; 
    }
    else { 
        while (i <= MAX) { // find a possible factor of b, and the factor is the least one for b 
            if ( (!UsedBalloon[i]) && ((b % i) == 0) ) { 
                break;
            }
            // else deleted by Carmack
            i++;
        }
        
        if (i > MAX) return false; 

        // try the factor i
        // because i is the least factor for b
        // so the least factor of b/i must be larger than i
        if (CanFactor(i+1, b / i)) { 
            return true; 
        }
        else { 
        // i can not be a factor
        // because of selecting wrong factor, so you have to select another factor
        // This is a good search approach
            return CanFactor(i + 1, b);
        }
    } 
} 

//varialbe b is not changed during calling
bool IsPossible(int i, int a, int b) // whether a is winner
{ 
    //if (i > MAX) return false;
    // because of two unequal number, so if a = 1, then b will not be 1. This stops misunderstandings.
    if (a == 1) return (CanFactor(1, b));
    // try to factor b , it is just for generic purpose
   // maybe you will use this function independently

    while (i <= MAX) {
    // find a possible factor of a 
        if ((a % i) == 0) { 
            break; 
        }
        else { 
            i++; 
        } 
    } 
    if (i > MAX) return false; 
    UsedBalloon[i] = true;
    // if a,b are all right, then a is winner
    if (IsPossible(i + 1, a / i, b)) return true; // try a factor i of a

    // if a is wrong, b is right, then you must try another factor sequences of a
    // after all test factors, still false, then you can say a is lying, b is right. so b is winner
    UsedBalloon[i] = false; 
    return (IsPossible(i + 1, a, b)); // try not use i as factor of a 
} 

int GetWinner(int a, int b) 
{ 
    for (int i = 0; i < MAX + 1; i++) { 
        UsedBalloon[i] = false; 
    } 

    if (a < b) { // make sure b is the chanllenge 
        int tmp = a; 
        a = b; 
        b = tmp; 
    }
    
    // if b is not a single number which can be got by only one crashed ballon.
    if (!CanFactor(1, b)) { // chanllenge is lying.There b must greater than 100, if return false
        return a; 
    }
    else if (IsPossible(1, a, b)) { // is it possible? 
        return a; // chanllenge fail. 
    }
    else { 
        return b; // it's impossible, chanllenge win. 
    } 
} 

int main() 
{ 
    int a, b; 

    while (cin >> a >> b) { 
        cout << GetWinner(a, b) << endl; 
    } 
    return 0; 
}

