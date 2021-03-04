/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2020. 02. 20.                  *
*   Project name: Cactuses               *
*****************************************/

#include <iostream>
#include <cstdlib>
#include "infile.hpp"
#include "outfile.hpp"

using namespace std;

/* Exercise:
 * There is an input file given, in which there is data regarding cactuses.
 * In each row,  the name, origin, size and colour of the cactus is provided.
 * Write an enumerator, which read the input data, and processes it with 
 * the well known first, next, current and end methods.
 * Implement an output file manager class as well in an object oriented way.
 * With the use of this, collect the cactuses from Mexico into output1.txt,
 * the red cactuses into output2.txt, and the Mexican red cactuses into output3.txt.
 */

int main()
{
    try {
        Infile t("input.txt");
        Outfile o("output.txt");
        Outfile o2("output2.txt");
        Outfile o3("output3.txt");
        // Similar to the structogram on the practice:
        /** t.first();
          * while(!t.end()) {
          *      cout << t.current() << endl;
          *      t.next();
          * }
          */
        // The for-loop version:
        for (t.first(); !t.end(); t.next()){
            if (t.current().home == "Mexico")
                o.write(t.current());
            if (t.current().color == "red")
                o2.write(t.current());
            if (t.current().home == "Mexico" && t.current().color == "red")
                o3.write(t.current());
        }
        o.close();
        o2.close();
        o3.close();
    } catch(Infile::Exception error) {
        cout << "Infile class, open error.\n";
        exit(1);
    } catch(Outfile::Exception error) {
        cout << "Outfile class, open error.\n";
        exit(2);
    }
    return 0;
}
