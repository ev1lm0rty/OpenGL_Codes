#include<iostream>
using namespace std;
void red();
void yellow();
void green();
void credits()
{
    red();
    cout<<"Made by: mrjoker05"<<endl;
    cout<<"Follow me on Github: "<<"https://github.com/mrjoker05"<<endl;
}

void choice()
{
    int choice;
    green();

    cout << "Choose from the following: "<<endl;
    cout << "0. Credits" <<endl;
    cout << "1. DDA" <<endl;
    cout << "2. Bresenham" <<endl;
    cout << "3. Flood Fill" <<endl;
    cout << "4. Boundary Fill" <<endl;
    cout << "5. Line Clip" <<endl;
    cout << "6. 2-D" <<endl;
    cout << "7. 3-D" <<endl;
    cout << "8. Curves" <<endl;
    
    cin >> choice;

    switch(choice)
    {
        case 0:
            credits();
            break;
        case 1:
            system("./dda");
              break;
        case 2:
            system("./bres");
            break;
        case 3:
            system("./flood");
            break;
        case 4:
            system("./boundary");
            break;
        case 5:
            system("./line");
            break;
        case 6:
            system("./2d");
            break;
        case 7:
            system("./3d");
            break;
        case 8:
            system("./curves");
            break;
        default:
            cout <<"Wrong choice..."<<endl;
            exit(0);
    }
}

int main()
{
  yellow();
  system("figlet -f slant Computer Graphics");
  choice();
  return 0;
}
