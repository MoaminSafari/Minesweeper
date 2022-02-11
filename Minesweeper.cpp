/*
    MohammadAmin Safari
    400243051
    4001 - SBU
*/


#include <string>
#include <time.h>
#include <math.h>
#include "clui.h"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

char navi;
string mainname;
char** temp = new char*;
char** mainar = new char*;
int row = get_window_rows(), col = get_window_cols();
int len, wid, mines, rowpick = 2, colpick = 3, score;

void deleting(); void fullnames();
bool namematching(); void backupdata();
void restoredata(); int diffnav(); void save();
void aroundcheckfill(); void empty(int i, int j);
void bombpicking(); void flag(int i, int j);bool loadgame();
void Hi(); void menu(); int menunav(); void diffchoose();
void win(); void bubblesort(); void fill(); void leaderboard();
void bombselecter(); void customminetable(); void changename();
bool action(int i, int j); bool winchecker(); void correctfill();
void goodbye(); void temp0fill(); void table(); int cursormove();

struct game // for save and load game
{
    string name;
    int len;
    int wid;
    int mines;
};
game nameandsize[4];

struct leader // for leaderboard
{
    string name;
    int score;
};
leader nameandscore[10];

int main()
{
    init_clui();
    restoredata();
    Hi();
    while(true){
        changename();
        if(namematching())
            break;
        fullnames();
    }
    bool flag1 = true;
    while(flag1){
        menu();
        switch(menunav()){
            case 1:{
                diffchoose();
                switch(diffnav()){
                    case 1:
                        customminetable();
                        break;
                    case 2:
                        continue;
                        break;
                }
                temp0fill();
                bombselecter();
                aroundcheckfill();
                table();
                bool flag2 = true;
                while(flag2){
                    fill();
                    if(winchecker()){
                        win();
                        break;
                    }
                    switch(cursormove()){
                        case 1:{
                            flag2 = false;
                        } break;
                        case 2:{
                            bombpicking();
                            flag2 = false;
                        } break;
                    }
                }
            } break;
            case 2:{
                if(loadgame()){
                    table();
                    bool flag2 = true;
                    while(flag2){
                        fill();
                        if(winchecker()){
                            win();
                            break;
                        }
                        switch(cursormove()){
                            case 1:{
                                flag2 = false;
                            } break;
                            case 2:{
                                bombpicking();
                                flag2 = false;
                            } break;
                        }
                    }
                }
                else
                    continue;
            } break;
            case 3:{
                while(true){
                    changename();
                    if(namematching())
                        break;
                    fullnames();
                }
            } break;
            case 4: leaderboard();
                break;
            case 5: goodbye();
                break;
        }
    }
}
void restoredata()
{
    fstream data("data.txt", ios::in);
    fstream lead("leaderboard.txt", ios::in);
    for(int i=0; i<10; i++){
        if(i<4){
            data >> nameandsize[i].name;
            data >> nameandsize[i].len;
            data >> nameandsize[i].wid;
            data >> nameandsize[i].mines;
        }
        lead >> nameandscore[i].name;
        lead >> nameandscore[i].score;
    }
    lead.close();
    data.close();
}

void Hi()
{
    cursor_to_pos(row/4 - 4, col/2 - 2);
    change_color_rgb(26, 228, 235);
    cout << "Hi!";
}

void changename()
{
    change_color_rgb(165, 235, 26);
    cursor_to_pos(row/4 - 3, col/2 - 2);
    cout << "Enter Your Name:";
    change_color_rgb(211, 235, 26);
    cursor_to_pos(row/4 - 2, col/2 - 2);
    cout << "                    ";
    cursor_to_pos(row/4 - 2, col/2 - 2);
    cin >> mainname;
}

bool namematching() // syncing for leaderboard
{
    for(int i=0; i<10; i++){
        if(nameandscore[i].name == mainname)
            return true;
        if(nameandscore[i].name == "0"){
            nameandscore[i].name = mainname;
            nameandscore[i].score = 0;
            return true;
        }
        if(i == 9){
            return false;
        }
    }
    return false;
}

void fullnames()
{
    cursor_to_pos(row/4 - 1, col/2 - 2);
    cout << "Sorry, The List is Full";
    cursor_to_pos(row/4, col/2 - 2);
    cout << "Please Pick a Name From The List:";
    for(int i=0; i<10; i++){
        cursor_to_pos(row/4 + 1 + i, col/2 - 2);
        cout << i+1 << ")" << nameandscore[i].name;
    }
}

void menu()
{
    backupdata();
    rowpick = 2;
    colpick = 3;
    clear_screen();
    cursor_to_pos(row/4 - 3, col/2 - 2);
    change_color_rgb(138, 144, 255);
    cout << "Minesweeper!";
    change_color_rgb(26, 228, 235);
    cursor_to_pos(row/4 - 2, col/2 - 2);
    cout << "1)New Game";
    change_color_rgb(165, 235, 26);
    cursor_to_pos(row/4 - 1, col/2 - 2);
    cout << "2)Load Game";
    change_color_rgb(211, 235, 26);
    cursor_to_pos(row/4, col/2 - 2);
    cout << "3)Change Name";
    change_color_rgb(255, 194, 89);
    cursor_to_pos(row/4 + 1, col/2 - 2);
    cout << "4)Leaderboard";
    change_color_rgb(255, 126, 117);
    cursor_to_pos(row/4 + 2, col/2 - 2);
    cout << "5)Quit";
    cursor_to_pos(row/4 + 3, col/2 - 2);
    cout << "Your Name: " << mainname;
}

void backupdata() // saving data after opening menu
{
    fstream data("data.txt", ios::out);
    fstream lead("leaderboard.txt", ios::out);
    for(int i=0; i<10; i++){
        if(i<4){
            data << nameandsize[i].name << endl;
            data << nameandsize[i].len << endl;
            data << nameandsize[i].wid << endl;
            data << nameandsize[i].mines << endl;
        }
        lead << nameandscore[i].name << endl;
        lead << nameandscore[i].score << endl;
    }
    lead.close();
    data.close();
}

int menunav()
{
    int i = row/4 - 2, j = col/2 - 2;
    char ch;
    do{
        cursor_to_pos(i, j);
        ch = getch();
        if((ch == 'w' || ch == 'W') && i > row/4 - 2)
            i--;
        else if((ch == 's' || ch == 'S') && i < row/4 + 2)
            i++;
        else if(ch == 13 || ch == 10)
            break;
    }while(true);
    if(i == row/4 - 2)
        return 1;
    else if(i == row/4 - 1)
        return 2;
    else if(i == row/4){
        clear_screen();
        return 3;
    }
    else if(i == row/4 + 1)
        return 4;
    else if(i == row/4 + 2)
        return 5;
    return 0;
}

bool loadgame()
{
    for(int i=0; i<4; i++){
        if(!i){
            clear_screen();
            change_color_rgb(211, 235, 26);
            cursor_to_pos(row/4 - 3, col/2 - 2);
            cout << "name | len | wid | mines";
        }
        cursor_to_pos(row/4 - 2 + i, col/2 - 2);
        cout << i+1 << ")" << nameandsize[i].name << " " << nameandsize[i].len
        << " " << nameandsize[i].wid << " " << nameandsize[i].mines;
    }
    cursor_to_pos(row/4 + 2, col/2 - 2);
    cout << "5)Back";
    cursor_to_pos(row/4 - 2, col/2 - 2);
    int i = row/4 - 2, j = col/2 - 2;
    char ch;
    do{
        cursor_to_pos(i, j);
        ch = getch();
        if((ch == 'w' || ch == 'W') && i > row/4 - 2)
            i--;
        else if((ch == 's' || ch == 'S') && i < row/4 + 2)
            i++;
        else if(ch == 13 || ch == 10)
            break;
    }while(true);
    if(i == row/4 - 2){
        fstream data("data1.txt", ios::in);
        data >> mainname;
        data >> len;
        data >> wid;
        data >> mines;
        mainar = new char*[len];
        temp = new char*[wid];
        for(int i=0; i<len; i++){
            mainar[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> mainar[i][j];
                if(mainar[i][j] == 'e')
                    mainar[i][j] = ' ';
            }
        }
        for(int i=0; i<len; i++){
            temp[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> temp[i][j];
                if(temp[i][j] == 'e')
                    temp[i][j] = ' ';
            }
        }
        data >> score;
        data.close();
        return true;
    }
    else if(i == row/4 - 1){
        fstream data("data2.txt", ios::in);
        data >> mainname;
        data >> len;
        data >> wid;
        data >> mines;
        mainar = new char*[len];
        temp = new char*[wid];
        for(int i=0; i<len; i++){
            mainar[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> mainar[i][j];
                if(mainar[i][j] == 'e')
                    mainar[i][j] = ' ';
            }
        }
        for(int i=0; i<len; i++){
            temp[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> temp[i][j];
                if(temp[i][j] == 'e')
                    temp[i][j] = ' ';
            }
        }
        data >> score;
        data.close();
        return true;
    }
    else if(i == row/4){
        fstream data("data3.txt", ios::in);
        data >> mainname;
        data >> len;
        data >> wid;
        data >> mines;
        mainar = new char*[len];
        temp = new char*[wid];
        for(int i=0; i<len; i++){
            mainar[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> mainar[i][j];
                if(mainar[i][j] == 'e')
                    mainar[i][j] = ' ';
            }
        }
        for(int i=0; i<len; i++){
            temp[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> temp[i][j];
                if(temp[i][j] == 'e')
                    temp[i][j] = ' ';
            }
        }
        data >> score;
        data.close();
        return true;
    }
    else if(i == row/4 + 1){
        fstream data("data4.txt", ios::in);
        data >> mainname;
        data >> len;
        data >> wid;
        data >> mines;
        mainar = new char*[len];
        temp = new char*[wid];
        for(int i=0; i<len; i++){
            mainar[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> mainar[i][j];
                if(mainar[i][j] == 'e')
                    mainar[i][j] = ' ';
            }
        }
        for(int i=0; i<len; i++){
            temp[i] = new char[wid];
            for(int j=0; j<wid; j++){
                data >> temp[i][j];
                if(temp[i][j] == 'e')
                    temp[i][j] = ' ';
            }
        }
        data >> score;
        data.close();
        return true;
    }
    else if(ch == row/4 + 2)
        return false;
    return false;
}

void leaderboard()
{
    bubblesort(); // sorting leaderboard
    for(int i=0; i<5; i++){
        if(!i){
            clear_screen();
            change_color_rgb(255, 212, 133);
        }
        cursor_to_pos(row/6 + i, col/2 - 2);
        cout << i+1 << ")" << nameandscore[i].name << " " << nameandscore[i].score;
    }
    cursor_to_pos(row/6 + 5, col/2 - 2);
    cout << "1)Clear The Leaderboard!";
    cursor_to_pos(row/6 + 6, col/2 - 2);
    cout << "2)Back";
    int i = row/6 + 6, j = col/2 - 2;
    char ch;
    do{
        cursor_to_pos(i, j);
        ch = getch();
        if((ch == 'w' || ch == 'W') && i > row/6 + 5)
            i--;
        else if((ch == 's' || ch == 'S') && i < row/6 + 6)
            i++;
        else if(ch == 13 || ch == 10)
            break;
    }while(true);
    if(i == row/6 + 5)
        for(int j=0; j<10; j++){
            nameandscore[j].name = "0";
            nameandscore[j].score = 0;
        }
}
void diffchoose()
{
    clear_screen();
    change_color_rgb(255, 126, 117);
    cursor_to_pos(row/4 - 2, col/2 - 2);
    cout << "Choose Game Diffculty";
    change_color_rgb(255, 194, 89);
    cursor_to_pos(row/4 - 1, col/2 - 2);
    cout << "1)Easy";
    change_color_rgb(211, 235, 26);
    cursor_to_pos(row/4, col/2 - 2);
    cout << "2)Medium";
    change_color_rgb(165, 235, 26);
    cursor_to_pos(row/4 + 1, col/2 - 2);
    cout << "3)Hard";
    change_color_rgb(26, 228, 235);
    cursor_to_pos(row/4 + 2, col/2 - 2);
    cout << "4)Custom";
    change_color_rgb(130, 159, 255);
    cursor_to_pos(row/4 + 3, col/2 - 2);
    cout << "5)Back";
}

int diffnav()
{
    int i = row/4 - 1, j = col/2 - 2;
    char ch;
    do{
        cursor_to_pos(i, j);
        ch = getch();
        if((ch == 'w' || ch == 'W') && i > row/4 - 1)
            i--;
        else if((ch == 's' || ch == 'S') && i < row/4 + 3)
            i++;
        else if(ch == 13 || ch == 10)
            break;
    }while(true);
    if(i == row/4 - 1){
        len = wid = 5;
        mines = 4;
        return 0;
    }
    else if(i == row/4){
        len = wid = 12;
        mines = 28;
        return 0;
    }
    else if(i == row/4 + 1){
        len = wid = 20;
        mines = 96;
        return 0;
    }
    else if(i == row/4 + 2)
        return 1;
    else if(i == row/4 + 3)
        return 2;
    return 0;
}

void customminetable()
{
    cursor_to_pos(row/4 + 4, 1);
    change_color_rgb(138, 144, 255);
    cout << "Enter The Length and Width Of Table(4<(i,j)<21), Then Number Of Mines:";
    cin >> len >> wid >> mines;
    if(mines >= len*wid || len < 5 || len > 20 || wid < 5 || wid > 20){ // limitation
        cout << "Please Enter The Length and Width Of Table in range of 4 and 21";
        customminetable();
    }
}

void temp0fill() // initialization
{
    mainar = new char*[len];
    temp = new char*[len];
    for(int i=0; i<len; i++){
        temp[i] = new char[wid];
        mainar[i] = new char[wid];
        for(int j=0; j<wid; j++){
            mainar[i][j] = '0';
            temp[i][j] = '0';
        }
    }
}

void bombselecter() // random bomb initialization
{
    srand(time(NULL));
    for(int k=0; k<mines; k++){
        int rani = rand() % (len*wid);
        int ranj = rand() % (len*wid);
        int i = rani / wid, j = ranj / len;
        if(mainar[i][j] == '*'){
            k--;
            continue;
        }
        mainar[i][j] = '*';
    }
}

void aroundcheckfill() // filling non-bomb cells
{
    for(int i=0; i<len; i++){
        for(int j=0; j<wid; j++){
            int bombs = 0;
            if(mainar[i][j] != '*'){
                for(int checki=-1; checki<2; checki++){
                    if(checki+i < 0 || checki+i > len-1)
                        continue;
                    for(int checkj=-1; checkj<2; checkj++){
                        if(checkj+j < 0 || checkj+j > wid-1 || (checki == 0 && checkj == 0))
                            continue;
                        if(mainar[checki+i][checkj+j] == '*')
                            bombs++;
                    }

                }
                if(bombs == 0)
                    mainar[i][j] = ' ';
                else
                    mainar[i][j] = bombs + 48;
            }
        }
    }
}

void table()
{
    clear_screen();
    change_color_rgb(255, 133, 133);
    for(int i=0; i<=len*2; i++){
        cursor_to_pos(i+1, 0);
        if(i % 2 == 0){
            if(i == 0)
                printf("%c", 218);
            else if(i == len*2)
                printf("%c", 192);
            else
                printf("%c", 195);
            if(i == 0)
                for(int j=1; j<wid*4; j++){
                    if(j % 4 == 0)
                        printf("%c", 194);
                    else
                        printf("%c", 196);
                }
            else if(i == len*2)
                for(int j=1; j<wid*4; j++){
                    if(j % 4 == 0)
                        printf("%c", 193);
                    else
                        printf("%c", 196);
                }
            else
                for(int j=1; j<wid*4; j++){
                    if(j % 4 == 0)
                        printf("%c", 197);
                    else
                        printf("%c", 196);
                }
            if(i == 0)

                printf("%c", 191);
            else if(i == len*2)
                printf("%c", 217);
            else
                printf("%c", 180);
        }
        else{
            printf("%c", 179);
            for(int j=1; j<=wid*4; j += 4)
                printf("%c%c%c%c", 32, 32, 32, 179);
        }
    }
    reset_color();
}

void fill()
{
    change_color_rgb(208, 255, 128);
    for(int i=1; i<=len; i++){
        for(int j=1; j<=wid; j++){
            cursor_to_pos((i*2), (j*4)-1);
            if(temp[i-1][j-1] == 'F')
                change_color_rgb(235, 235, 235);
            if(temp[i-1][j-1] == '0')
                change_color_rgb(208, 255, 128);
            if(temp[i-1][j-1] == '1')
                change_color_rgb(190, 110, 255);
            if(temp[i-1][j-1] == '2')
                change_color_rgb(107, 141, 255);
            if(temp[i-1][j-1] == '3')
                change_color_rgb(107, 107, 255);
            if(temp[i-1][j-1] == '4')
                change_color_rgb(128, 255, 128);
            if(temp[i-1][j-1] == '5')
                change_color_rgb(255, 255, 143);
            if(temp[i-1][j-1] == '6')
                change_color_rgb(255, 194, 133);
            printf("%c", temp[i-1][j-1]);
        }
    }
    change_color_rgb(208, 255, 128);
}

bool winchecker()
{
    for(int i=0; i<len; i++)
        for(int j=0; j<wid; j++)
            if((temp[i][j] == '0' || temp[i][j] == 'F') && mainar[i][j] != '*')
                return false;
    return true;
}

int cursormove()
{
    char ch;
    cursor_to_pos(row - 4, col - 25);
    cout << "Mines: " << mines << "                 ";
    cursor_to_pos(row - 3, col - 25);
    cout << "Up: w           ";
    printf("%c", 179);
    cout << " Down: s";
    cursor_to_pos(row - 2, col - 25);
    cout << "Left: a         ";
    printf("%c", 179);
    cout << " Right: d";
    cursor_to_pos(row - 1, col - 25);
    cout << "Open: Space     ";
    printf("%c", 179);
    cout << " Flag: f";
    cursor_to_pos(row, col - 25);
    cout << "Save and Quit: O";
    printf("%c", 179);
    cout << " Quit: Q";
    do{
        cursor_to_pos(rowpick, colpick);
        ch = getch();
        if((ch == 'w' || ch == 'W') && rowpick > 2)
            rowpick -= 2;
        else if((ch == 's' || ch == 'S') && rowpick < len*2)
            rowpick += 2;
        else if((ch == 'a' || ch == 'A') && colpick > 3)
            colpick -= 4;
        else if((ch == 'd' || ch == 'D') && colpick < wid*4 - 1)
            colpick += 4;
        else if(ch == ' '){
            if(action(rowpick/2 - 1, colpick/4))
                return 2;
            return 0;
        }
        else if(ch == 'f' || ch == 'F'){
            flag(rowpick/2 - 1, colpick/4);
            return 0;
        }
        else if(ch == 'o' || ch == 'O'){
            save();
            return 1;
        }
        else if(ch == 'q' || ch == 'Q'){
            deleting();
            return 1;
        }
    }while(true);
}

bool action(int i, int j)
{
    if(mainar[i][j] == '*' && temp[i][j] != 'F')
        return true;
    else if(temp[i][j] == '0'){
        if(mainar[i][j] == ' ')
            empty(i, j);
        temp[i][j] = mainar[i][j];
        return false;
    }
    return false;
}

void flag(int i, int j)
{
    if(temp[i][j] == 'F')
        temp[i][j] = '0';
    else if(temp[i][j] == '0')
        temp[i][j] = 'F';
}

void save()
{
    for(int i=0; i<4; i++){
        if(!i){
            clear_screen();
            change_color_rgb(211, 235, 26);
            cursor_to_pos(row/4 - 3, col/2 - 2);
            cout << "name | len | wid | mines";
        }
        cursor_to_pos(row/4 - 2 + i, col/2 - 2);
        cout << i+1 << ")" << nameandsize[i].name << " " << nameandsize[i].len
        << " " << nameandsize[i].wid << " " << nameandsize[i].mines;
    }
    cursor_to_pos(row/4 + 2, col/2 - 2);
    cout << "Please select one slot";
    cursor_to_pos(row/4 - 2, col/2 - 2);
    int i = row/4 - 2, j = col/2 - 2;
    char ch;
    do{
        cursor_to_pos(i, j);
        ch = getch();
        if((ch == 'w' || ch == 'W') && i > row/4 - 2)
            i--;
        else if((ch == 's' || ch == 'S') && i < row/4 + 1)
            i++;
        else if(ch == 13 || ch == 10)
            break;
    }while(true);
    if(i == row/4 - 2){
        fstream data("data1.txt", ios::out);
        data << mainname << endl;
        data << len << endl;
        data << wid << endl;
        data << mines << endl;
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(mainar[i][j] == ' ')
                    mainar[i][j] = 'e';
                data << mainar[i][j] << " ";
            }
            data << endl;
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(temp[i][j] == ' ')
                    temp[i][j] = 'e';
                data << temp[i][j] << " ";
            }
            data << endl;
        }
        data << score;
        data.close();
        nameandsize[0].name = mainname;
        nameandsize[0].len = len;
        nameandsize[0].wid = wid;
        nameandsize[0].mines = mines;
        deleting();
    }
    else if(i == row/4 - 1){
        fstream data("data2.txt", ios::out);
        data << mainname << endl;
        data << len << endl;
        data << wid << endl;
        data << mines << endl;
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(mainar[i][j] == ' ')
                    mainar[i][j] = 'e';
                data << mainar[i][j] << " ";
            }
            data << endl;
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(temp[i][j] == ' ')
                    temp[i][j] = 'e';
                data << temp[i][j] << " ";
            }
            data << endl;
        }
        data << score;
        data.close();
        nameandsize[1].name = mainname;
        nameandsize[1].len = len;
        nameandsize[1].wid = wid;
        nameandsize[1].mines = mines;
        deleting();
    }
    else if(i == row/4){
        fstream data("data3.txt", ios::out);
        data << mainname << endl;
        data << len << endl;
        data << wid << endl;
        data << mines << endl;
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(mainar[i][j] == ' ')
                    mainar[i][j] = 'e';
                data << mainar[i][j] << " ";
            }
            data << endl;
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(temp[i][j] == ' ')
                    temp[i][j] = 'e';
                data << temp[i][j] << " ";
            }
            data << endl;
        }
        data << score;
        data.close();
        nameandsize[2].name = mainname;
        nameandsize[2].len = len;
        nameandsize[2].wid = wid;
        nameandsize[2].mines = mines;
        deleting();
    }
    else if(i == row/4 + 1){
        fstream data("data4.txt", ios::out);
        data << mainname << endl;
        data << len << endl;
        data << wid << endl;
        data << mines << endl;
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(mainar[i][j] == ' ')
                    mainar[i][j] = 'e';
                data << mainar[i][j] << " ";
            }
            data << endl;
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<wid; j++){
                if(temp[i][j] == ' ')
                    temp[i][j] = 'e';
                data << temp[i][j] << " ";
            }
            data << endl;
        }
        data << score;
        data.close();
        nameandsize[3].name = mainname;
        nameandsize[3].len = len;
        nameandsize[3].wid = wid;
        nameandsize[3].mines = mines;
        deleting();
    }
}

void bombpicking()
{
    cursor_to_pos(row - 8, col - 25);
    change_color_rgb(255, 240, 102);
    cout << "Oh noo!";
    delay(1000);
    cursor_to_pos(row - 7, col - 25);
    cout << "You picked a BOMB!";
    cursor_to_pos(row - 6, col - 25);
    cout << "1)See the correct table";
    cursor_to_pos(row - 5, col - 25);
    cout << "2)Quit";
    cursor_to_pos(row - 6, col - 25);
    int i = row - 6, j = col - 25;
    char ch;
    do{
        cursor_to_pos(i, j);
        ch = getch();
        if((ch == 'w' || ch == 'W') && i > row - 6)
            i--;
        else if((ch == 's' || ch == 'S') && i < row - 5)
            i++;
        else if(ch == 13 || ch == 10)
            break;
    }while(true);
    if(i == row - 6){
        correctfill();
        cursor_to_pos(row - 4, col - 25);
        cout << "Press any key to quit....";
        char chq = getch();
        deleting();
        flush();
    }
    else if(i == row - 5){
        deleting();
        flush();
    }
}

void win()
{
    int sq = sqrt(len*wid);
    if((mines*mines) - sq > 0) // scoring
        for(int i=0; i<10; i++){
            if(mainname == nameandscore[i].name){
                nameandscore[i].score += (mines*mines) - sq;
                break;
            }
            if(nameandscore[i].name == "0" || i == 9){
                nameandscore[i].name = mainname;
                nameandscore[i].score = (mines*mines) - sq;
                break;
            }
        }
    cursor_to_pos(row - 5, col - 25);
    change_color_rgb(133, 255, 255);
    cout << "YEEEES You won!!!";
    delay(1000);
    correctfill();
    cursor_to_pos(row - 4, col - 25);
    change_color_rgb(133, 255, 255);
    cout << "Press any key to quit....";
    char ch = getch();
    deleting();
    flush();
}

void correctfill()
{
    int sq = sqrt(len*wid);
    for(int i=1; i<=len; i++){
        for(int j=1; j<=wid; j++){
            change_color_rgb(255, 240, 102);
            cursor_to_pos((i*2), (j*4)-1);
            delay(25 - sq);
            if(mainar[i-1][j-1] == '*')
                change_color_rgb(150, 225, 255);
            printf("%c", mainar[i-1][j-1]);
        }
    }
}

void goodbye()
{
    clear_screen();
    cursor_to_pos(row/4, col/2);
    cout << "Goodbye :)";
    delay(2000);
    quit();
}

void deleting()
{
    for(int i=0; i<len; i++){
        delete[] mainar[i];
        delete[] temp[i];
    }
        delete[] mainar;
        delete[] temp;
}

void empty(int i, int j) // empty cell opening
{
    for(int checki=-1; checki<2; checki++){
        if(checki+i < 0 || checki+i > len-1)
            continue;
        for(int checkj=-1; checkj<2; checkj++){
            if(checkj+j < 0 || checkj+j > wid-1 || (checki == 0 && checkj == 0))
                continue;
            if(temp[checki+i][checkj+j] == '0'){
                temp[checki+i][checkj+j] = mainar[checki+i][checkj+j];
                if(temp[checki+i][checkj+j] == ' ')
                    empty(checki+i, checkj+j);
            }
        }
    }
}

void bubblesort()
{
    for(int k=0; k<10; k++)
    {
        for(int i=0; i<(9-k); i++)
        {
            if(nameandscore[i].score<=nameandscore[i+1].score)
            {
                leader temp = nameandscore[i];
                nameandscore[i] = nameandscore[i+1];
                nameandscore[i+1] = temp;
            }
        }
    }
}