#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <QPushButton>
#include <QRandomGenerator>
#include <QColor>
#include <QtWidgets>
#include <QPainter>
#include <cmath>
#include <cstdio>
#include <memory>
#include <fstream>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QPainterPath>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <bitset>
#include <QStandardItemModel>
#include <set>


using namespace std;


string mintermsTxt = "minterms.txt" ;
string dontcaresTxt = "dontcares.txt";
string pythonScript = "mg.py" ;

int circleX = 50 ;
int circleY = 50 ;

int row1 = 130 ;
int row2 = 180 ;
int row3 = 240 ;
int row4 = 290 ;

int col1 = 140 ;
int col2 = 210 ;
int col3 = 300 ;
int col4 = 370 ;

int col5 = 570 ;
int col6 = 640 ;
int col7 = 730 ;
int col8 = 800 ;

int totalCornerRadius = 20;

int totalX5_1    = 140 ;
int totalX5_2    = 570 ;
int totalY5      = 130 ;
int totalWidth5  = 300 ;
int totalHeight5 = 220 ;

int totalX4      = 140 ;
int totalY4      = 130 ;
int totalWidth4  = 300 ;
int totalHeight4 = 220 ;

int totalX3      = 140 ;
int totalY3      = 130 ;
int totalWidth3  = 310 ;
int totalHight3  = 110 ;

int totalX2      = 140 ;
int totalY2      = 130 ;
int totalWidth2  = 310 ;
int totalHeight2 = 55  ;


QString result ;
QString resultPy ;
QString SOPphrase;

bool drawCircle ;
bool drawComplete ;
bool allSelect ;
bool isMinButtonPushed ;

vector<int>    mintermNumber;
vector<string> minterms;

int nv ; //varable number

string A1 = "A"  ;
string B1 = "B"  ;
string C1 = "C"  ;
string D1 = "D"  ;
string E1 = "E"  ;
string A0 = "A'" ;
string B0 = "B'" ;
string C0 = "C'" ;
string D0 = "D'" ;
string E0 = "E'" ;


string decToBin(int n)
{
    if ( n == 0 )
        return n+"";

    if ( n % 2 == 0 )
        return decToBin(n / 2) + "0";
    else
        return decToBin(n / 2) + "1";
}

string pad(string bin)
{
    int max=nv-bin.length();
    for(int i=0; i<max; i++)
        bin="0"+bin;
    return bin;
}

string extractNumbers(const std::string& input) {
    stringstream ss;
    for (char c : input) {
        if (isdigit(c)) {
            ss << c;
        } else if (c == ' ') {
            ss << ' ';
        }
    }
    return ss.str();
}

string toValidResult(const string& inputString) {
    set<string> stringSet;

    string delimiter = "+";
    size_t pos = 0;
    string token;
    string mutableInput = inputString;
    while ((pos = mutableInput.find(delimiter)) != std::string::npos) {
        token = mutableInput.substr(0, pos);
        stringSet.insert(token);
        mutableInput.erase(0, pos + delimiter.length());
    }
    stringSet.insert(mutableInput);


    string combinedString;
    for (const string& str : stringSet) {
        combinedString += str + "+";
    }

    return combinedString.substr(0, combinedString.length() - 1);
}


bool isNumber(const std::string& str) {
    std::istringstream iss(str);
    double number;
    iss >> number;
    return !iss.fail() && iss.eof();
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr) {
            result += buffer.data();
        }
    }
    return result;
}



int binaryToDecimal(const std::string& binaryString) {
    int decimalNumber = 0;
    int base = 1;

    for (int i = binaryString.length() - 1; i >= 0; --i) {
        if (binaryString[i] == '1') {
            decimalNumber += base;
        }

        base *= 2;
    }

    return decimalNumber;
}


string to_binary(int n, int m) {
    string a;
    for (int i = 0; i < m; i++) {
        if (n % 2 == 0)
            a.push_back('0');
        else
            a.push_back('1');
        n = n / 2;
    }
    reverse(a.begin(), a.end());
    return a;
}

int compare(string a, string b) {
    int n = a.length();
    int c = 0, d = 0, k;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            c++;
            k = i;
        } else if (a[i] == b[i]) {
            d++;
        }
    }
    if (c == 1)
        return k;
    else if (d == n)
        return -2;
    else
        return -1;
}

string change(string a, int l) {
    a[l] = '_';
    return a;
}

void check_like(string a, vector<string>& b) {
    int flag = 0, n = b.size();
    for (int i = 0; i < n; i++) {
        if (compare(a, b[i]) == -2)
            return;
        else
            flag++;
    }
    if (flag == n) {
        b.push_back(a);
    }
    return;
}

string minimize(int variableNum , int minTermNumber , vector<int> minterms) {
    int n,m,i,j,k,l,row,col,count;
    vector<string>terms;
    vector<string>vect;
    vector<string>prime;
    vector<string>temp1;
    vector<string>ep;
    vector<int>temp2;
    vector<pair<int,int> >temp3;
    string result ;
    m = variableNum ;
    n = minTermNumber ;
    int*a=new int[n];
    cout << n << endl << m << endl ;

    for(int i=0;i<n;i++) {
        a[i] = minterms[i] ;
        cout << minterms[i] << endl ;
    }

    for(int i=0;i<n;i++) {
        vect.push_back(to_binary(a[i],m));
    }

    for(i=0;i<vect.size();i++) {
        terms.push_back(vect[i]);
    }

    //Line 75 to 110 finds the prime implicants
    while(!vect.empty()) {
        for( i=0;i<vect.size()-1;i++) {
            int c=0;
            for( j=i+1;j<vect.size();j++) {
                l=compare(vect[i],vect[j]);
                if(l!=-1 && l!=-2) {
                    temp1.push_back(change(vect[i],l));
                    temp2.push_back(j);
                }
                else c++;
            }
            if(c==j-i-1) {
                int d=0;for(int k=0;k<temp2.size();k++) {
                    if(i==(temp2[k])) {
                        d=1;break;
                    }
                } if(d==0)
                    check_like(vect[i],prime);
            }
        }
        int d=0;
        for(int k=0;k<temp2.size();k++) {
            if(i==(temp2[k])) {
                d=1;break;
            }
        }
        if(d==0)
            check_like(vect[i],prime);
        vect.clear();
        for(i=0;i<temp1.size();i++) {
            vect.push_back(temp1[i]);
        }
        temp1.clear();
        temp2.clear();
    }
    vector<string>().swap(temp1);
    vector<int>().swap(temp2);
    vector<string>().swap(vect);
    //print the prime implicants
    cout<<"Prime Implicants are:"<<endl;
    for(int i=0;i<prime.size();i++) {
        cout<<prime[i]<<endl;
    }


    row=prime.size();
    col=n;
    /*declaring prime implicant table.
row+1 = no. of rows in table
col = no. of column in table
t stands for table*/

    int**t = new int*[row+1];
    for(i=0;i<row+1;i++) {
        t[i]=new int[col];
    }

    for(i=0;i<row+1;i++) {
        for(j=0;j<col;j++)
            t[i][j]=0;
    }
    //lines 137 to 180 find the essential prime implicants
    for(i=0;i<row;i++) {
        int c;
        int n1=terms.size();
        int m1=prime[i].length();
        for( j=0;j<n1;j++) {
            c=1;
            for( k=0;k<m1;k++) {
                if(prime[i][k]!='_') {
                    if(prime[i][k]!=terms[j][k]) {
                        c=0;break;
                    }
                }
            }
            if(c==1)
                t[i][j]=1;
        }
    }
    for(j=0;j<col;j++) {
        count=0;
        for(i=0;i<row;i++) {
            if(t[i][j]==1) {
                count++;k=i;
            }
        }
        if(count==1){
            temp3.push_back(make_pair(j,k));
        }
    }

    for(i=0;i<temp3.size();i++) {
        if(t[row][temp3[i].first]!=1) {
            ep.push_back(prime[temp3[i].second]);
            t[temp3[i].second][temp3[i].first]=-1;
            t[row][temp3[i].first]=1;
            for(j=0;j<col;j++) {
                if(t[temp3[i].second][j]==1) {
                    for(k=0;k<row;k++) {
                        if(t[k][j]==1)
                            t[k][j]=-1;
                    }
                    t[row][j]=1;
                }
            }
        }
    }
    temp3.clear();

    for(i=0;i<row;i++) {
        count=0;
        for(j=0;j<col;j++) {
            if(t[i][j]==1)
                count++;
        }
        if(count>0){
            temp3.push_back(make_pair(count,i));
        }
    }
    //lines 181 to 223 find the remaining minterms of minimized function which get stored in ep vector
    sort(temp3.begin(),temp3.end());
    if(!temp3.empty()) {
        i=temp3.size()-1;
        { ep.push_back(prime[temp3[i].second]);
            for(j=0;j<col;j++) {
                if(t[temp3[i].second][j]==1) {
                    for(k=0;k<row;k++) {
                        if(t[k][j]==1) {
                            t[k][j]=-1;
                        }
                    }
                }
            }
        }

        while(1) {
            k=1;
            for(i=0;(i<temp3.size()-k && i>=0);i++) {
                count=0;
                for(j=0;j<col;j++) {
                    if(t[temp3[i].second][j]==1)
                        count++;
                }
                if(count>0) {
                    temp3[i].first=count;
                } else temp3[i].first=0;
            }
            sort(temp3.begin(),temp3.end()-k);
            i=temp3.size()-1-k;
            if(temp3[i].first>0) {
                ep.push_back(prime[temp3[i].second]);
                for(j=0;j<col;j++) {
                    if(t[temp3[i].second][j]==1) {
                        for(k=0;k<row;k++) {
                            if(t[k][j]==1) {
                                t[k][j]=-1;
                            }
                        }
                    }
                }
            } else
                break;
            k++;
        }
        //Printing minimized terms.

        cout<<"Minimized terms are"<<endl;
        for(i=0;i<ep.size();i++) {
            cout<< i << ep[i]<<endl;
            string temp ;
            if (variableNum == 5){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
                if (ep[i][2] == '0'){
                    temp +=  C0 ;
                } if (ep[i][2] == '1'){
                    temp += C1 ;
                }
                if (ep[i][3] == '0'){
                    temp +=  D0 ;
                } if (ep[i][3] == '1'){
                    temp += D1 ;
                }
                if (ep[i][4] == '0'){
                    temp +=  E0 ;
                } if (ep[i][4] == '1'){
                    temp += E1 ;
                }
            } else if (variableNum == 4){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
                if (ep[i][2] == '0'){
                    temp +=  C0 ;
                } if (ep[i][2] == '1'){
                    temp += C1 ;
                }
                if (ep[i][3] == '0'){
                    temp +=  D0 ;
                } if (ep[i][3] == '1'){
                    temp += D1 ;
                }
            } else if (variableNum == 3){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
                if (ep[i][2] == '0'){
                    temp +=  C0 ;
                } if (ep[i][2] == '1'){
                    temp += C1 ;
                }
            } else if (variableNum == 2){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
            }
            result += temp ;
            if (i != ep.size()-1 ){
                result += "+" ;
            }
        }
    } else {
        cout<<"Minimized terms are:"<<endl;
        for(i=0;i<prime.size();i++) {
            ep.push_back(prime[i]);
        }
        for(int i=0;i<ep.size();i++) {
            cout<< i << ep[i]<<endl;
            string temp ;
            if (variableNum == 5){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
                if (ep[i][2] == '0'){
                    temp +=  C0 ;
                } if (ep[i][2] == '1'){
                    temp += C1 ;
                }
                if (ep[i][3] == '0'){
                    temp +=  D0 ;
                } if (ep[i][3] == '1'){
                    temp += D1 ;
                }
                if (ep[i][4] == '0'){
                    temp +=  E0 ;
                } if (ep[i][4] == '1'){
                    temp += E1 ;
                }
            } else if (variableNum == 4){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
                if (ep[i][2] == '0'){
                    temp +=  C0 ;
                } if (ep[i][2] == '1'){
                    temp += C1 ;
                }
                if (ep[i][3] == '0'){
                    temp +=  D0 ;
                } if (ep[i][3] == '1'){
                    temp += D1 ;
                }
            } else if (variableNum == 3){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
                if (ep[i][2] == '0'){
                    temp +=  C0 ;
                } if (ep[i][2] == '1'){
                    temp += C1 ;
                }
            } else if (variableNum == 2){
                if (ep[i][0] == '0'){
                    temp +=  A0 ;
                } if (ep[i][0] == '1'){
                    temp += A1 ;
                }
                if (ep[i][1] == '0'){
                    temp +=  B0 ;
                } if (ep[i][1] == '1'){
                    temp += B1 ;
                }
            }
            result += temp ;
            if (i != ep.size()-1 ){
                result += "+" ;
            }
        }
    }
    return result ;

}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("کمینه ساز");
    QIcon icon("icon.png");
    setWindowIcon(icon);
    setFixedSize(1044,600); // resizable false
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_minButton_clicked()
{
    ui->resultField->setToolTip("");
    nv = 5 ;
    if (ui->dial->value() == 4){
        nv = 4 ;
    } else if (ui->dial->value() == 3){
        nv = 3 ;
    } else if (ui->dial->value() == 2){
        nv = 2 ;
    }

    ui->sopposButton->setText("POS");
    ui->sopposButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
    isSave = false ;
    result = "" ;
    resultPy = "" ;
    mintermNumber.clear();



    int no = nv ;

    vector<string> minterms;



    if (ui->abcde->isChecked())  {
        minterms.push_back(pad(decToBin(0)));
        mintermNumber.push_back(0);
    }
    if (ui->abcdE->isChecked())  {
        minterms.push_back(pad(decToBin(1)));
        mintermNumber.push_back(1);
    }
    if (ui->abcDe->isChecked())  {
        minterms.push_back(pad(decToBin(2)));
        mintermNumber.push_back(2);
    }
    if (ui->abcDE->isChecked())  {
        minterms.push_back(pad(decToBin(3)));
        mintermNumber.push_back(3);
    }
    if (ui->abCde->isChecked())  {
        minterms.push_back(pad(decToBin(4)));
        mintermNumber.push_back(4);
    }
    if (ui->abCdE->isChecked())  {
        minterms.push_back(pad(decToBin(5)));
        mintermNumber.push_back(5);
    }
    if (ui->abCDe->isChecked())  {
        minterms.push_back(pad(decToBin(6)));
        mintermNumber.push_back(6);
    }
    if (ui->abCDE->isChecked())  {
        minterms.push_back(pad(decToBin(7)));
        mintermNumber.push_back(7);
    }
    if (ui->aBcde->isChecked())  {
        minterms.push_back(pad(decToBin(8)));
        mintermNumber.push_back(8);
    }
    if (ui->aBcdE->isChecked())  {
        minterms.push_back(pad(decToBin(9)));
        mintermNumber.push_back(9);
    }
    if (ui->aBcDe->isChecked())  {
        minterms.push_back(pad(decToBin(10)));
        mintermNumber.push_back(10);
    }
    if (ui->aBcDE->isChecked())  {
        minterms.push_back(pad(decToBin(11)));
        mintermNumber.push_back(11);
    }
    if (ui->aBCde->isChecked())  {
        minterms.push_back(pad(decToBin(12)));
        mintermNumber.push_back(12);
    }
    if (ui->aBCdE->isChecked())  {
        minterms.push_back(pad(decToBin(13)));
        mintermNumber.push_back(13);
    }
    if (ui->aBCDe->isChecked())  {
        minterms.push_back(pad(decToBin(14)));
        mintermNumber.push_back(14);
    }
    if (ui->aBCDE->isChecked())  {
        minterms.push_back(pad(decToBin(15)));
        mintermNumber.push_back(15);
    }



    if (ui->Abcde->isChecked())  {
        minterms.push_back(pad(decToBin(16)));
        mintermNumber.push_back(16);
    }
    if (ui->AbcdE->isChecked())  {
        minterms.push_back(pad(decToBin(17)));
        mintermNumber.push_back(17);
    }
    if (ui->AbcDe->isChecked())  {
        minterms.push_back(pad(decToBin(18)));
        mintermNumber.push_back(18);
    }
    if (ui->AbcDE->isChecked())  {
        minterms.push_back(pad(decToBin(19)));
        mintermNumber.push_back(19);
    }
    if (ui->AbCde->isChecked())  {
        minterms.push_back(pad(decToBin(20)));
        mintermNumber.push_back(20);
    }
    if (ui->AbCdE->isChecked())  {
        minterms.push_back(pad(decToBin(21)));
        mintermNumber.push_back(21);
    }
    if (ui->AbCDe->isChecked())  {
        minterms.push_back(pad(decToBin(22)));
        mintermNumber.push_back(22);
    }
    if (ui->AbCDE->isChecked())  {
        minterms.push_back(pad(decToBin(23)));
        mintermNumber.push_back(23);
    }
    if (ui->ABcde->isChecked())  {
        minterms.push_back(pad(decToBin(24)));
        mintermNumber.push_back(24);
    }
    if (ui->ABcdE->isChecked())  {
        minterms.push_back(pad(decToBin(25)));
        mintermNumber.push_back(25);
    }
    if (ui->ABcDe->isChecked())  {
        minterms.push_back(pad(decToBin(26)));
        mintermNumber.push_back(26);
    }
    if (ui->ABcDE->isChecked())  {
        minterms.push_back(pad(decToBin(27)));
        mintermNumber.push_back(27);
    }
    if (ui->ABCde->isChecked())  {
        minterms.push_back(pad(decToBin(28)));
        mintermNumber.push_back(28);
    }
    if (ui->ABCdE->isChecked())  {
        minterms.push_back(pad(decToBin(29)));
        mintermNumber.push_back(29);
    }
    if (ui->ABCDe->isChecked())  {
        minterms.push_back(pad(decToBin(30)));
        mintermNumber.push_back(30);
    }
    if (ui->ABCDE->isChecked())  {
        minterms.push_back(pad(decToBin(31)));
        mintermNumber.push_back(31);
    }

    if (minterms.size() != 0 && minterms.size() != pow(2,nv)){

        ui->resultField->setPlainText("");

        cout << endl ;
        std::ofstream outputFile(mintermsTxt);
        if (outputFile.is_open()) {
            for (int number : mintermNumber) {
                outputFile << number << " ";
            }
            outputFile.close();
            std::cout << "Values have been written to the file." << std::endl;
        } else {
            std::cout << "Unable to open the file." << std::endl;
        }

        QString command = "python " + QString::fromStdString(pythonScript);

        FILE* pipe = _popen(command.toStdString().c_str(), "r");
        if (!pipe) {
            std::cerr << "Error opening pipe!" << std::endl;
        }
        resultPy = "" ;
        char buffer[128];
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != nullptr)
                resultPy += buffer;
        }

        _pclose(pipe);

        std::cout << resultPy.toStdString() << std::endl;

        SOPphrase = QString::fromStdString(toValidResult(minimize(no,mintermNumber.size(),mintermNumber))) ;
        ui->resultField->setText(SOPphrase);



        drawCircle = true;
    } else if(minterms.size() == 0){
        ui->resultField->setPlainText("");
        ui->resultField->setText("0");
    } else { // all minterms
        ui->resultField->setPlainText("");
        ui->resultField->setText("1");
        drawComplete = true ;

    }

    update();
    int termNumber = 1 ;
    int literalNumber = 0 ;


    string inputString = ui->resultField->toPlainText().toStdString();
    ui->resultField->setPlainText(QString::fromStdString(toValidResult(inputString)));
    for (char c : toValidResult(inputString)) {
        if (c == '+') {
            termNumber++;
        } else if (c == A1[0] || c == B1[0] || c == C1[0] || c == D1[0] || c == E1[0]) {
            literalNumber++;
        }
    }
    ui->lcdLiteralNumber->display(literalNumber);
    if (ui->resultField->toPlainText() == "0" || ui->resultField->toPlainText() == "1"){
        ui->lcdLiteralNumber->display(1);
    }
    ui->lcdTermNumber->display(termNumber);

    isMinButtonPushed = true ;

}



void MainWindow::on_groupButton_clicked()
{

    if (isMinButtonPushed){
        //MainWindow::on_minButton_clicked();
        if (resultPy.size() ==  0){
            QMessageBox msgBox;
            QFont font("B Kamran" , 13);
            msgBox.setFont(font);
            msgBox.setWindowTitle("There is no minterm-group");

            if (allSelect){
                msgBox.setText("All of the chosen minterms in one group!");
            } else {
                msgBox.setText("There is no minterm chosen!");
            }

            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();

        } else {
            QStringList parts = resultPy.split("] [", QString::SkipEmptyParts);

            int rowCount = parts.size();
            int columnCount = 1;

            QTableWidget* tableWidget = new QTableWidget(rowCount, columnCount); 
            QString columnName = "minterms-group"  ;
            int column = 0;
            QTableWidgetItem* headerItem = new QTableWidgetItem(columnName);
            tableWidget->setHorizontalHeaderItem(column, headerItem);

            for (int row = 0; row < rowCount; ++row) {
                QString part = parts[row].remove(QRegExp("[\\[\\]']"));

                QTableWidgetItem* item = new QTableWidgetItem(part);
                tableWidget->setItem(row, 0, item);
            }

            QDialog dialog;
            dialog.setWindowTitle("minterms-group");

            QVBoxLayout* layout = new QVBoxLayout(&dialog);

            layout->addWidget(tableWidget);

            dialog.setLayout(layout);

            int columnWidth = 400;
            for (int col = 0; col < columnCount; ++col) {
                tableWidget->setColumnWidth(col, columnWidth);
            }


            //          int rowHeight = 200; // ارتفاع مورد نظر برای ردیف (به صورت پیکسل)
  //        for (int row = 0; row < rowCount; ++row) {
      //        tableWidget->setRowHeight(row, rowHeight);
    //      }

            dialog.resize(400 ,600 ); //م اندازه پنجره
            tableWidget->setFont(QFont("B Kamran", 13));

            dialog.exec();
        }
    } else {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Erroe!");
        msgBox.setText("At first minimize the function");
        msgBox.setIcon(QMessageBox::Critical);

        QFont font;
        font.setFamily("B Kamran");
        font.setPointSize(13);

        msgBox.setFont(font);

        msgBox.setTextFormat(Qt::RichText);
        msgBox.exec();
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    if (drawCircle) {

        int red ;
        int green ;
        int blue ;
        QColor tempColor ;

        for (int i = 0 ; i < resultPy.size() ; i++) {
            QString c = QString(resultPy[i]);
            if ( c == "," || c == "'" || c == " ") continue ;
            if (c == "[") {
                red = QRandomGenerator::global()->bounded(256);
                green = QRandomGenerator::global()->bounded(256);
                blue = QRandomGenerator::global()->bounded(256);
                tempColor = QColor(red, green, blue);
                continue;
            }
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing, true);
            QPen pen(tempColor);
            pen.setWidth(3);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            if (c.toInt() == 0 && ui->abcde->isChecked()) { // == 0
                painter.drawEllipse(col1, row1, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->abcdE->isChecked()) { // == 1
                painter.drawEllipse(col2, row1, circleX, circleY);
            }
            if (c.toInt() == 3 && ui->abcDE->isChecked()) { // == 3
                painter.drawEllipse(col3, row1, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->abcDe->isChecked()) { // == 2
                painter.drawEllipse(col4, row1, circleX, circleY);
            }
            if (c.toInt() == 4 && ui->abCde->isChecked()) { // == 4
                painter.drawEllipse(col1, row2, circleX, circleY);
            }
            if (c.toInt() == 5 && ui->abCdE->isChecked()) { // == 5
                painter.drawEllipse(col2, row2, circleX, circleY);
            }
            if (c.toInt() == 7 && ui->abCDE->isChecked()) { // == 7
                painter.drawEllipse(col3, row2, circleX, circleY);
            }
            if (c.toInt() == 6 && ui->abCDe->isChecked()) { // == 6
                painter.drawEllipse(col4, row2, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->aBCde->isChecked()) { // == 12
                painter.drawEllipse(col1, row3, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->aBCdE->isChecked()) { // == 13
                painter.drawEllipse(col2, row3, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->aBCDE->isChecked()) { // == 15
                painter.drawEllipse(col3, row3, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->aBCDe->isChecked()) { // == 14
                painter.drawEllipse(col4, row3, circleX, circleY);
            }
            if (c.toInt() == 8 && ui->aBcde->isChecked()) { // == 8
                painter.drawEllipse(col1, row4, circleX, circleY);
            }
            if (c.toInt() == 9 && ui->aBcdE->isChecked()) { // == 9
                painter.drawEllipse(col2, row4, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->aBcDE->isChecked()) { // == 11
                painter.drawEllipse(col3, row4, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->aBcDe->isChecked()) { // == 10
                painter.drawEllipse(col4, row4, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->Abcde->isChecked()) { // == 16
                painter.drawEllipse(col5, row1, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->AbcdE->isChecked()) { // == 17
                painter.drawEllipse(col6, row1, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->AbcDE->isChecked()) { // == 19
                painter.drawEllipse(col7, row1, circleX, circleY);
            }
            if (c.toInt() == 1 && ui->AbcDe->isChecked()) { // == 18
                painter.drawEllipse(col8, row1, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->AbCde->isChecked()) { // == 20
                painter.drawEllipse(col5, row2, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->AbCdE->isChecked()) { // == 21
                painter.drawEllipse(col6, row2, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->AbCDE->isChecked()) { // == 23
                painter.drawEllipse(col7, row2, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->AbCDe->isChecked()) { // == 22
                painter.drawEllipse(col8, row2, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->ABCde->isChecked()) { // == 28
                painter.drawEllipse(col5, row3, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->ABCdE->isChecked()) { // == 29
                painter.drawEllipse(col6, row3, circleX, circleY);
            }
            if (c.toInt() == 3 && ui->ABCDE->isChecked()) { // == 31
                painter.drawEllipse(col7, row3, circleX, circleY);
            }
            if (c.toInt() == 3 && ui->ABCDe->isChecked()) { // == 30
                painter.drawEllipse(col8, row3, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->ABcde->isChecked()) { // == 24
                painter.drawEllipse(col5, row4, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->ABcdE->isChecked()) { // == 25
                painter.drawEllipse(col6, row4, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->ABcDE->isChecked()) { // == 27
                painter.drawEllipse(col7, row4, circleX, circleY);
            }
            if (c.toInt() == 2 && ui->ABcDe->isChecked()) { // == 26
                painter.drawEllipse(col8, row4, circleX, circleY);
            }
        }
        drawCircle = false;
    }
    if (drawComplete){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::red));
        painter.setBrush(Qt::NoBrush);

        QPainterPath path;
        if (nv == 5){
            path.addRoundedRect(totalX5_1, totalY5, totalWidth5, totalHeight5, totalCornerRadius, totalCornerRadius); // left tabel

            painter.drawPath(path);

            path.addRoundedRect(totalX5_2, totalY5, totalWidth5, totalHeight5, totalCornerRadius, totalCornerRadius); // right table

            painter.drawPath(path);

            QWidget::paintEvent(event);

        } else if (nv == 4){     
            path.addRoundedRect(totalX4, totalY4, totalWidth4, totalHeight4, totalCornerRadius, totalCornerRadius); // left tabel

            painter.drawPath(path);

        } else if (nv == 3){
            path.addRoundedRect(totalX3, totalY3, totalWidth3, totalHight3, totalCornerRadius, totalCornerRadius); // left tabel

            painter.drawPath(path);

        } else {    // nv == 2
            path.addRoundedRect(totalX2, totalY2, totalWidth2, totalHeight2, totalCornerRadius, totalCornerRadius); // left tabel

            painter.drawPath(path);
        }
    }
    drawComplete = false ;
}



void MainWindow::on_allSelectButton_clicked()
{
    isSave = false ;
    isMinButtonPushed = false ;

    if (allSelect) {

        ui->ABCDE->setChecked(false);
        ui->ABCDe->setChecked(false);
        ui->ABCdE->setChecked(false);
        ui->ABCde->setChecked(false);
        ui->ABcDE->setChecked(false);
        ui->ABcDe->setChecked(false);
        ui->ABcdE->setChecked(false);
        ui->ABcde->setChecked(false);
        ui->AbCDE->setChecked(false);
        ui->AbCDe->setChecked(false);
        ui->AbCdE->setChecked(false);
        ui->AbCde->setChecked(false);
        ui->AbcDE->setChecked(false);
        ui->AbcDe->setChecked(false);
        ui->AbcdE->setChecked(false);
        ui->Abcde->setChecked(false);
        ui->aBCDE->setChecked(false);
        ui->aBCDe->setChecked(false);
        ui->aBCdE->setChecked(false);
        ui->aBCde->setChecked(false);
        ui->aBcDE->setChecked(false);
        ui->aBcDe->setChecked(false);
        ui->aBcdE->setChecked(false);
        ui->aBcde->setChecked(false);
        ui->abCDE->setChecked(false);
        ui->abCDe->setChecked(false);
        ui->abCdE->setChecked(false);
        ui->abCde->setChecked(false);
        ui->abcDE->setChecked(false);
        ui->abcDe->setChecked(false);
        ui->abcdE->setChecked(false);
        ui->abcde->setChecked(false);


        allSelect = false ;
        ui->allSelectButton->setText("All");

    } else {
        if (ui->ABCDE->isEnabled())
            ui->ABCDE->setChecked(true);
        if (ui->ABCDe->isEnabled())
            ui->ABCDe->setChecked(true);
        if (ui->ABCdE->isEnabled())
            ui->ABCdE->setChecked(true);
        if (ui->ABCde->isEnabled())
            ui->ABCde->setChecked(true);
        if (ui->ABcDE->isEnabled())
            ui->ABcDE->setChecked(true);
        if (ui->ABcDe->isEnabled())
            ui->ABcDe->setChecked(true);
        if (ui->ABcdE->isEnabled())
            ui->ABcdE->setChecked(true);
        if (ui->ABcde->isEnabled())
            ui->ABcde->setChecked(true);
        if (ui->AbCDE->isEnabled())
            ui->AbCDE->setChecked(true);
        if (ui->AbCDe->isEnabled())
            ui->AbCDe->setChecked(true);
        if (ui->AbCdE->isEnabled())
            ui->AbCdE->setChecked(true);
        if (ui->AbCde->isEnabled())
            ui->AbCde->setChecked(true);
        if (ui->AbcDE->isEnabled())
            ui->AbcDE->setChecked(true);
        if (ui->AbcDe->isEnabled())
            ui->AbcDe->setChecked(true);
        if (ui->AbcdE->isEnabled())
            ui->AbcdE->setChecked(true);
        if (ui->Abcde->isEnabled())
            ui->Abcde->setChecked(true);
        if (ui->aBCDE->isEnabled())
            ui->aBCDE->setChecked(true);
        if (ui->aBCDe->isEnabled())
            ui->aBCDe->setChecked(true);
        if (ui->aBCdE->isEnabled())
            ui->aBCdE->setChecked(true);
        if (ui->aBCde->isEnabled())
            ui->aBCde->setChecked(true);
        if (ui->aBcDE->isEnabled())
            ui->aBcDE->setChecked(true);
        if (ui->aBcDe->isEnabled())
            ui->aBcDe->setChecked(true);
        if (ui->aBcdE->isEnabled())
            ui->aBcdE->setChecked(true);
        if (ui->aBcde->isEnabled())
            ui->aBcde->setChecked(true);
        if (ui->abCDE->isEnabled())
            ui->abCDE->setChecked(true);
        if (ui->abCDe->isEnabled())
            ui->abCDe->setChecked(true);
        if (ui->abCdE->isEnabled())
            ui->abCdE->setChecked(true);
        if (ui->abCde->isEnabled())
            ui->abCde->setChecked(true);
        if (ui->abcDE->isEnabled())
            ui->abcDE->setChecked(true);
        if (ui->abcDe->isEnabled())
            ui->abcDe->setChecked(true);
        if (ui->abcdE->isEnabled())
            ui->abcdE->setChecked(true);
        if (ui->abcde->isEnabled())
            ui->abcde->setChecked(true);


        allSelect = true ;
        ui->allSelectButton->setText("None");

    }
}



void MainWindow::on_saveButton_clicked()
{
    //    MainWindow::on_minButton_clicked();


    QString filePath = QFileDialog::getSaveFileName(this, "Choose the place to save", "", "Text files (*.txt)");

    if (!filePath.isEmpty())
    {
        QFile file(filePath);

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            if (resultPy.size() ==  0){
                if (allSelect){
                    QTextStream stream(&file);


                    stream << ui->fLabel->text() << "Minterms : " ;
                    for (int i = 0 ; i < 31 ; i++){
                        stream << i << " , ";
                    }
                    stream << 31 ;
                    stream << endl << "Minimized function : " << 1 << "   True";
                    stream << endl << endl << "merged minterms : " << endl ;
                    stream << "all minterms in one group" ;
                    stream << endl << "******************************************" << endl;

                    file.close();

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Message");
                    msgBox.setText("Save succesfully");
                    msgBox.setIcon(QMessageBox::Information);

                    QFont font;
                    font.setFamily("B Kamran");
                    font.setPointSize(13);
                    msgBox.setFont(font);

                    msgBox.exec();

                    isSave = true ;


                } else {
                    QTextStream stream(&file);


                    stream << ui->fLabel->text() << "Minterms : " ;
                    stream <<  " - ";
                    stream << endl << "Minimized function : " << 0 << "   False";
                    stream << endl << endl << "merged minterms : " << endl ;
                    stream << "-" ;
                    stream << endl << "******************************************" << endl;

                    file.close();

                    QMessageBox msgBox;
                    msgBox.setWindowTitle("Message");
                    msgBox.setText("Save succesfully");
                    msgBox.setIcon(QMessageBox::Information);

                    QFont font;
                    font.setFamily("B Kamran");
                    font.setPointSize(13);
                    msgBox.setFont(font);

                    msgBox.exec();

                    isSave = true ;

                }
            } else {
                QTextStream stream(&file);


                stream << ui->fLabel->text() << "Minterms : " ;
                for (int i = 0 ; i < mintermNumber.size() -1 ; i++){
                    stream << QString::number(mintermNumber[i]) << " , ";
                }
                stream << mintermNumber[mintermNumber.size()-1] ;
                stream << endl << "Minimized function (" << (ui->sopposButton->text() == "SOP" ? "POS) : " : "SOP ) : " )<< ui->resultField->toPlainText() ;
                stream << endl << endl << "merged minterms : " << endl ;
                for (int i = 0 ; i < resultPy.size() ; i++){
                    QString c = QString(resultPy[i]);
                    stream << c ;
                    if (c == "]") stream << endl ;
                }
                stream << endl << "******************************************" << endl;

                file.close();

                QMessageBox msgBox;
                msgBox.setWindowTitle("Message");
                msgBox.setText("Save succesfully.");
                msgBox.setIcon(QMessageBox::Information);

                QFont font;
                font.setFamily("B Kamran");
                font.setPointSize(13);
                msgBox.setFont(font);

                msgBox.exec();

                isSave = true ;

            }
        }
    }
}




void MainWindow::on_dcButton_clicked()
{
    isSave = false ;
    isMinButtonPushed = false ;


    QMessageBox messageBox(QMessageBox::Question, "dont care", "Choose the action:",
                           QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    messageBox.setButtonText(QMessageBox::Yes, "Show");
    messageBox.setButtonText(QMessageBox::No, "Edit");
    messageBox.setButtonText(QMessageBox::Cancel, "Clear");

    QFont font;
    font.setFamily("B Kamran");
    font.setPointSize(13);
    messageBox.setFont(font);

    int reply = messageBox.exec();

    if (reply == QMessageBox::Yes) {
        string text;
        std::ifstream inputFile(dontcaresTxt);
        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                text += line;
            }
            inputFile.close();
        } else {
            std::cerr << "Unable to open the file." << std::endl;
        }
        if (text != "") {
            QMessageBox msgBox;
            msgBox.setWindowTitle("dont care");
            msgBox.setText(QString::fromStdString(text));

            QFont font;
            font.setFamily("B Kamran");
            font.setPointSize(12);
            msgBox.setFont(font);

            msgBox.exec();

        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("dont care");
            msgBox.setText("You dont have DC");

            QFont font;
            font.setFamily("B Kamran");
            font.setPointSize(12);
            msgBox.setFont(font);

            msgBox.exec();

        }

    } else if (reply == QMessageBox::No) {
        bool ok;
        QFont font;
        font.setFamily("B Kamran");
        font.setPointSize(12);

        QString tempUserInput = QInputDialog::getText(this, "dont cares", "Input DC numbers with Space between them : ", QLineEdit::Normal, "", &ok);
        QInputDialog inputDialog;
        inputDialog.setFont(font);
        inputDialog.setInputMode(QInputDialog::TextInput);
        inputDialog.setWindowTitle("dont cares");
        inputDialog.setLabelText("Input DC numbers with Space between them : ");
        inputDialog.setFont(font);

        QString userInput = QString::fromStdString(extractNumbers(tempUserInput.toStdString()));
        if (ok && !userInput.isEmpty()) {

            std::ofstream outputFile(dontcaresTxt);
            if (outputFile.is_open()) {
                outputFile << userInput.toStdString();
                outputFile.close();
                std::cout << "Content has been written to the file." << std::endl;
            } else {
                std::cerr << "Unable to open the file." << std::endl;
            }



            istringstream iss(userInput.toStdString());
            vector<string> tokens;

            string token;
            set<string> dcSet;

            while (getline(iss, token, ' ')) {
                tokens.push_back(token);
                if (isNumber(token))
                    if (stoi(token) < 32 && stoi(token) > -1 )
                        dcSet.insert(token);
            }

            ui->lcdDontcareNumber->display(static_cast<int>(dcSet.size()));


            ui->abcde->setEnabled(true);
            ui->abcdE->setEnabled(true);
            ui->abcDe->setEnabled(true);
            ui->abcDE->setEnabled(true);

            if (ui->dial->value() == 4  || ui->dial->value() == 5 || ui->dial->value() == 3){
                ui->abCde->setEnabled(true);
                ui->abCdE->setEnabled(true);
                ui->abCDe->setEnabled(true);
                ui->abCDE->setEnabled(true);

                if (!(ui->dial->value() == 3)){
                    ui->aBcde->setEnabled(true);
                    ui->aBcdE->setEnabled(true);
                    ui->aBcDe->setEnabled(true);
                    ui->aBcDE->setEnabled(true);
                    ui->aBCde->setEnabled(true);
                    ui->aBCdE->setEnabled(true);
                    ui->aBCDe->setEnabled(true);
                    ui->aBCDE->setEnabled(true);
                }
            }

            if (ui->dial->value() == 5){
                ui->Abcde->setEnabled(true);
                ui->AbcdE->setEnabled(true);
                ui->AbcDe->setEnabled(true);
                ui->AbcDE->setEnabled(true);
                ui->AbCde->setEnabled(true);
                ui->AbCdE->setEnabled(true);
                ui->AbCDe->setEnabled(true);
                ui->AbCDE->setEnabled(true);
                ui->ABcde->setEnabled(true);
                ui->ABcdE->setEnabled(true);
                ui->ABcDe->setEnabled(true);
                ui->ABcDE->setEnabled(true);
                ui->ABCde->setEnabled(true);
                ui->ABCdE->setEnabled(true);
                ui->ABCDe->setEnabled(true);
                ui->ABCDE->setEnabled(true);
            }


            for ( auto& token : tokens) {
                if (token == "0")  {
                    ui->abcde->setChecked(false);
                    ui->abcde->setEnabled(false);
                    ui->abcde->setToolTip(ui->abcde->toolTip() + "\nDC");
                }
                if (token == "1")  {
                    ui->abcdE->setChecked(false);
                    ui->abcdE->setEnabled(false);
                    ui->abcdE->setToolTip(ui->abcdE->toolTip() + "\nDC");
                }
                if (token == "2")  {
                    ui->abcDe->setChecked(false);
                    ui->abcDe->setEnabled(false);
                    ui->abcDe->setToolTip(ui->abcDe->toolTip() + "\nDC");
                }
                if (token == "3")  {
                    ui->abcDE->setChecked(false);
                    ui->abcDE->setEnabled(false);
                    ui->abcDE->setToolTip(ui->abcDE->toolTip() + "\nDC");
                }
                if (token == "4")  {
                    ui->abCde->setChecked(false);
                    ui->abCde->setEnabled(false);
                    ui->abCde->setToolTip(ui->abCde->toolTip() + "\nDC");
                }
                if (token == "5")  {
                    ui->abCdE->setChecked(false);
                    ui->abCdE->setEnabled(false);
                    ui->abCdE->setToolTip(ui->abCdE->toolTip() + "\nDC");
                }
                if (token == "6")  {
                    ui->abCDe->setChecked(false);
                    ui->abCDe->setEnabled(false);
                    ui->abCDe->setToolTip(ui->abCDe->toolTip() + "\nDC");
                }
                if (token == "7")  {
                    ui->abCDE->setChecked(false);
                    ui->abCDE->setEnabled(false);
                    ui->abCDE->setToolTip(ui->abCDE->toolTip() + "\nDC");
                }
                if (token == "8")  {
                    ui->aBcde->setChecked(false);
                    ui->aBcde->setEnabled(false);
                    ui->aBcde->setToolTip(ui->aBcde->toolTip() + "\nDC");
                }
                if (token == "9")  {
                    ui->aBcdE->setChecked(false);
                    ui->aBcdE->setEnabled(false);
                    ui->aBcdE->setToolTip(ui->aBcdE->toolTip() + "\nDC");
                }
                if (token == "10")  {
                    ui->aBcDe->setChecked(false);
                    ui->aBcDe->setEnabled(false);
                    ui->aBcDe->setToolTip(ui->aBcDe->toolTip() + "\nDC");
                }
                if (token == "11")  {
                    ui->aBcDE->setChecked(false);
                    ui->aBcDE->setEnabled(false);
                    ui->aBcDE->setToolTip(ui->aBcDE->toolTip() + "\nDC");
                }
                if (token == "12")  {
                    ui->aBCde->setChecked(false);
                    ui->aBCde->setEnabled(false);
                    ui->aBCde->setToolTip(ui->aBCde->toolTip() + "\nDC");
                }
                if (token == "13")  {
                    ui->aBCdE->setChecked(false);
                    ui->aBCdE->setEnabled(false);
                    ui->aBCdE->setToolTip(ui->aBCdE->toolTip() + "\nDC");
                }
                if (token == "14")  {
                    ui->aBCDe->setChecked(false);
                    ui->aBCDe->setEnabled(false);
                    ui->aBCDe->setToolTip(ui->aBCDe->toolTip() + "\nDC");
                }
                if (token == "15")  {
                    ui->aBCDE->setChecked(false);
                    ui->aBCDE->setEnabled(false);
                    ui->aBCDE->setToolTip(ui->aBCDE->toolTip() + "\nDC");
                }



                if (token == "16")  {
                    ui->Abcde->setChecked(false);
                    ui->Abcde->setEnabled(false);
                    ui->Abcde->setToolTip(ui->Abcde->toolTip() + "\nDC");
                }
                if (token == "17")  {
                    ui->AbcdE->setChecked(false);
                    ui->AbcdE->setEnabled(false);
                    ui->AbcdE->setToolTip(ui->AbcdE->toolTip() + "\nDC");
                }
                if (token == "18")  {
                    ui->AbcDe->setChecked(false);
                    ui->AbcDe->setEnabled(false);
                    ui->AbcDe->setToolTip(ui->AbcDe->toolTip() + "\nDC");
                }
                if (token == "19")  {
                    ui->AbcDE->setChecked(false);
                    ui->AbcDE->setEnabled(false);
                    ui->AbcDE->setToolTip(ui->AbcDE->toolTip() + "\nDC");
                }
                if (token == "20")  {
                    ui->AbCde->setChecked(false);
                    ui->AbCde->setEnabled(false);
                    ui->AbCde->setToolTip(ui->AbCde->toolTip() + "\nDC");
                }
                if (token == "21")  {
                    ui->AbCdE->setChecked(false);
                    ui->AbCdE->setEnabled(false);
                    ui->AbCdE->setToolTip(ui->AbCdE->toolTip() + "\nDC");
                }
                if (token == "22")  {
                    ui->AbCDe->setChecked(false);
                    ui->AbCDe->setEnabled(false);
                    ui->AbCDe->setToolTip(ui->AbCDe->toolTip() + "\nDC");
                }
                if (token == "23")  {
                    ui->AbCDE->setChecked(false);
                    ui->AbCDE->setEnabled(false);
                    ui->AbCDE->setToolTip(ui->AbCDE->toolTip() + "\nDC");
                }
                if (token == "24")  {
                    ui->ABcde->setChecked(false);
                    ui->ABcde->setEnabled(false);
                    ui->ABcde->setToolTip(ui->ABcde->toolTip() + "\nDC");
                }
                if (token == "25")  {
                    ui->ABcdE->setChecked(false);
                    ui->ABcdE->setEnabled(false);
                    ui->ABcdE->setToolTip(ui->ABcdE->toolTip() + "\nDC");
                }
                if (token == "26")  {
                    ui->ABcDe->setChecked(false);
                    ui->ABcDe->setEnabled(false);
                    ui->ABcDe->setToolTip(ui->ABcDe->toolTip() + "\nDC");
                }
                if (token == "27")  {
                    ui->ABcDE->setChecked(false);
                    ui->ABcDE->setEnabled(false);
                    ui->ABcDE->setToolTip(ui->ABcDE->toolTip() + "\nDC");
                }
                if (token == "28")  {
                    ui->ABCde->setChecked(false);
                    ui->ABCde->setEnabled(false);
                    ui->ABCde->setToolTip(ui->ABCde->toolTip() + "\nDC");
                }
                if (token == "29")  {
                    ui->ABCdE->setChecked(false);
                    ui->ABCdE->setEnabled(false);
                    ui->ABCdE->setToolTip(ui->ABCdE->toolTip() + "\nDC");
                }
                if (token == "30")  {
                    ui->ABCDe->setChecked(false);
                    ui->ABCDe->setEnabled(false);
                    ui->ABCDe->setToolTip(ui->ABCDe->toolTip() + "\nDC");
                }
                if (token == "31")  {
                    ui->ABCDE->setChecked(false);
                    ui->ABCDE->setEnabled(false);
                    ui->ABCDE->setToolTip(ui->ABCDE->toolTip() + "\nDC");
                }

            }


            QMessageBox::information(this, "dont care",  userInput + "\n The checkBox that contain DC deactivate!");
        } else {
            QMessageBox::critical(this, "Error", "You dont enter the correct input!");
        }

    } else { // clear dont care's

        std::ofstream file(dontcaresTxt);
        file.close();

        ui->abcde->setEnabled(true);
        ui->abcdE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abcDE->setEnabled(true);

        if (ui->dial->value() == 5 || ui->dial->value() == 4 || ui->dial->value() == 3){
            ui->abCde->setEnabled(true);
            ui->abCdE->setEnabled(true);
            ui->abCDe->setEnabled(true);
            ui->abCDE->setEnabled(true);

            MainWindow::on_dial_sliderMoved(2);

            if (!(ui->dial->value() == 3)) {
                ui->aBcde->setEnabled(true);
                ui->aBcdE->setEnabled(true);
                ui->aBcDe->setEnabled(true);
                ui->aBcDE->setEnabled(true);
                ui->aBCde->setEnabled(true);
                ui->aBCdE->setEnabled(true);
                ui->aBCDe->setEnabled(true);
                ui->aBCDE->setEnabled(true);

                MainWindow::on_dial_sliderMoved(3);

            }
        }

        if (ui->dial->value() == 5){
            ui->Abcde->setEnabled(true);
            ui->AbcdE->setEnabled(true);
            ui->AbcDe->setEnabled(true);
            ui->AbcDE->setEnabled(true);
            ui->AbCde->setEnabled(true);
            ui->AbCdE->setEnabled(true);
            ui->AbCDe->setEnabled(true);
            ui->AbCDE->setEnabled(true);
            ui->ABcde->setEnabled(true);
            ui->ABcdE->setEnabled(true);
            ui->ABcDe->setEnabled(true);
            ui->ABcDE->setEnabled(true);
            ui->ABCde->setEnabled(true);
            ui->ABCdE->setEnabled(true);
            ui->ABCDe->setEnabled(true);
            ui->ABCDE->setEnabled(true);

            MainWindow::on_dial_sliderMoved(5);

        }

        ui->lcdDontcareNumber->display(0);


        QMessageBox msgBox;
        msgBox.setWindowTitle("Succesfully");
        msgBox.setText("dont care cleared");

        QFont font;
        font.setFamily("B Kamran");
        font.setPointSize(13);
        msgBox.setFont(font);

        msgBox.exec();

    }

}



void MainWindow::on_sopposButton_clicked()
{
    isSave = false;

    if (ui->resultField->toPlainText() == "0") {
        if (ui->sopposButton->text() == "POS") {
            ui->resultField->setPlainText("1");
            ui->resultField->setToolTip("True");
            ui->sopposButton->setText("SOP");
        } else {
            ui->resultField->setPlainText("1");
            ui->resultField->setToolTip("True");
            ui->sopposButton->setText("POS");
        }
    } else if (ui->resultField->toPlainText() == "1") {
        if (ui->sopposButton->text() == "POS") {
            ui->resultField->setPlainText("0");
            ui->resultField->setToolTip("False");
            ui->sopposButton->setText("SOP");
        } else {
            ui->resultField->setPlainText("0");
            ui->resultField->setToolTip("False");
            ui->sopposButton->setText("POS");
        }
    } else {
        if (ui->sopposButton->text() == "POS") {
            QString sop = ui->resultField->toPlainText();
            QString pos = "(";

            for (int i = 0; i < sop.size(); i++) {
                if (sop[i] == '+')
                    pos += ")(";
                else if (sop[i] == A1[0]) {
                    if (sop[i + 1] == '\'')
                        if (sop[i + 2] != '+')
                            pos += QString(A1[0]) + "+";
                        else
                            pos += QString(A1[0]) ;
                    else
                        if (sop[i + 1] != '+')
                            pos += QString(A0[0]) + "'+";
                        else
                            pos += QString(A0[0]) + "'";
                } else if (sop[i] == B1[0]) {
                    if (sop[i + 1] == '\'')
                        if (sop[i + 2] != '+')
                            pos += QString(B1[0]) + "+";
                        else
                            pos += QString(B1[0]) ;
                    else
                        if (sop[i + 1] != '+')
                            pos += QString(B0[0]) + "'+";
                        else
                            pos += QString(B0[0]) + "'";
                } else if (sop[i] == C1[0]) {
                    if (sop[i + 1] == '\'')
                        if (sop[i + 2] != '+')
                            pos += QString(C1[0]) + "+";
                        else
                            pos += QString(C1[0]) ;
                    else
                        if (sop[i + 1] != '+')
                            pos += QString(C0[0]) + "'+";
                        else
                            pos += QString(C0[0]) + "'";
                } else if (sop[i] == D1[0]) {
                    if (sop[i + 1] == '\'')
                        if (sop[i + 2] != '+')
                            pos += QString(D1[0]) + "+";
                        else
                            pos += QString(D1[0]) ;
                    else
                        if (sop[i + 1] != '+')
                            pos += QString(D0[0]) + "'+";
                        else
                            pos += QString(D0[0]) + "'";
                } else if (sop[i] == E1[0]) {
                    if (sop[i + 1] == '\'')
                        if (sop[i + 2] != '+')
                            pos += QString(E1[0]) + "+";
                        else
                            pos += QString(E1[0]) ;
                    else
                        if (sop[i + 1] != '+')
                            pos += QString(E0[0]) + "'+";
                        else
                            pos += QString(E0[0]) + "'";
                }
            }

            if (pos[pos.size() - 1] == '+') {
                pos.chop(1);
            }

            pos += ")";
            ui->resultField->setToolTip(sop);
            ui->resultField->setPlainText(pos);
            ui->sopposButton->setText("SOP");
        } else { // button is SOP
            QString pos = ui->resultField->toPlainText();
            QString sop;

            for (int i = 0; i < pos.size(); i++) {
                if (pos[i] == ')') {
                    if (i != pos.size() - 1)
                        sop += "+";
                }
                if (pos[i] == A1[0]) {
                    if (pos[i + 1] == '\'')
                        sop += QString(A1[0]);
                    else
                        sop += QString(A0[0]) + "'";
                }
                if (pos[i] == B1[0]) {
                    if (pos[i + 1] == '\'')
                        sop += QString(B1[0]);
                    else
                        sop += QString(B0[0]) + "'";
                }
                if (pos[i] == C1[0]) {
                    if (pos[i + 1] == '\'')
                        sop += QString(C1[0]);
                    else
                        sop += QString(C0[0]) + "'";
                }
                if (pos[i] == D1[0]) {
                    if (pos[i + 1] == '\'')
                        sop += QString(D1[0]);
                    else
                        sop += QString(D0[0]) + "'";
                }
                if (pos[i] == E1[0]) {
                    if (pos[i + 1] == '\'')
                        sop += QString(E1[0]);
                    else
                        sop += QString(E0[0]) + "'";
                }
            }

            ui->resultField->setToolTip(pos);
            ui->resultField->setPlainText(sop);
            ui->sopposButton->setText("POS");
        }
    }
}





void MainWindow::on_truetableButton_clicked()
{
    // ایجاد پنجره
    QMainWindow *window = new QMainWindow();
    QTableView *tableView;
    QStandardItemModel *model;
    if (ui->dial->value() == 5) {
        window->setFixedHeight(795);
        window->setFixedWidth(330);
        window->setWindowTitle("True Table");

        tableView = new QTableView(window);

        model = new QStandardItemModel(32, 6, window);

        QStringList columnHeaders;
        string temp = "f(" + A1 + "," + B1 + "," + C1 + "," + D1 + "," + E1 + ")" ;
        columnHeaders << QString::fromStdString(A1) << QString::fromStdString(B1) << QString::fromStdString(C1)
                      << QString::fromStdString(D1) << QString::fromStdString(E1) << QString::fromStdString(temp) ;
        model->setHorizontalHeaderLabels(columnHeaders);

        // ساخت اعداد باینری 0-31 پنج بیتی
        for (int row = 0; row < 32; ++row) {
            unsigned int number = row;
            std::bitset<5> binary(number);
            int i = 4;
            for (int col = 0; col < 5; ++col) {
                QModelIndex index = model->index(row, col);
                bool bit = binary[i];
                if (bit)
                    model->setData(index, "1");
                else
                    model->setData(index, "0");
                --i;
            }
        }

        QPalette palette = tableView->palette();
        palette.setColor(QPalette::Base, QColor(0, 250, 154));
        tableView->setPalette(palette);
    } else if (ui->dial->value() == 4) {
        window->setFixedHeight(420);
        window->setFixedWidth(280);
        window->setWindowTitle("True Table");

        tableView = new QTableView(window);

        model = new QStandardItemModel(16, 5, window);

        QStringList columnHeaders;
        string temp = "f(" + A1 + "," + B1 + "," + C1 + "," + D1 + ")" ;
        columnHeaders << QString::fromStdString(A1) << QString::fromStdString(B1) << QString::fromStdString(C1)
                      << QString::fromStdString(D1) << QString::fromStdString(temp) ;
        model->setHorizontalHeaderLabels(columnHeaders);

        // ساخت اعداد باینری 0-15 پنج بیتی
        for (int row = 0; row < 16; ++row) {
            unsigned int number = row;
            std::bitset<4> binary(number);
            int i = 3;
            for (int col = 0; col < 4; ++col) {
                QModelIndex index = model->index(row, col);
                bool bit = binary[i];
                if (bit)
                    model->setData(index, "1");
                else
                    model->setData(index, "0");
                --i;
            }
        }
        QPalette palette = tableView->palette();
        palette.setColor(QPalette::Base, QColor(135, 206, 235));
        tableView->setPalette(palette);
    } else if (ui->dial->value() == 3) {
        window->setFixedHeight(230);
        window->setFixedWidth(220);
        window->setWindowTitle("True Table");

        tableView = new QTableView(window);

        model = new QStandardItemModel(8, 4, window);

        QStringList columnHeaders;
        string temp = "f(" + A1 + "," + B1 + "," + C1 + ")" ;
        columnHeaders << QString::fromStdString(A1) << QString::fromStdString(B1) << QString::fromStdString(C1)
                      << QString::fromStdString(temp) ;
        model->setHorizontalHeaderLabels(columnHeaders);

        // ساخت اعداد باینری 0-7 پنج بیتی
        for (int row = 0; row < 8; ++row) {
            unsigned int number = row;
            std::bitset<3> binary(number);
            int i = 2;
            for (int col = 0; col < 3; ++col) {
                QModelIndex index = model->index(row, col);
                bool bit = binary[i];
                if (bit)
                    model->setData(index, "1");
                else
                    model->setData(index, "0");
                --i;
            }
        }
        QPalette palette = tableView->palette();
        palette.setColor(QPalette::Base, QColor(79, 209, 204));
        tableView->setPalette(palette);
    } else if (ui->dial->value() == 2) {
        window->setFixedHeight(130);
        window->setFixedWidth(160);
        window->setWindowTitle("True Table");

        tableView = new QTableView(window);

        model = new QStandardItemModel(4, 3, window);

        QStringList columnHeaders;
        string temp = "f(" + A1 + "," + B1 + ")" ;
        columnHeaders << QString::fromStdString(A1) << QString::fromStdString(B1) << QString::fromStdString(temp) ;
        model->setHorizontalHeaderLabels(columnHeaders);

        // ساخت اعداد باینری 0-3 پنج بیتی
        for (int row = 0; row < 4; ++row) {
            unsigned int number = row;
            std::bitset<2> binary(number);
            int i = 1;
            for (int col = 0; col < 2; ++col) {
                QModelIndex index = model->index(row, col);
                bool bit = binary[i];
                if (bit)
                    model->setData(index, "1");
                else
                    model->setData(index, "0");
                --i;
            }
        }
        QPalette palette = tableView->palette();
        palette.setColor(QPalette::Base, QColor(0, 255, 127));
        tableView->setPalette(palette);
    }



    QModelIndex cellIndex = model->index(0, model->columnCount() - 1);
    if (ui->abcde->isEnabled()) {
        if (ui->abcde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(1, model->columnCount() - 1);
    if (ui->abcdE->isEnabled()) {
        if (ui->abcdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(2, model->columnCount() - 1);
    if (ui->abcDe->isEnabled()) {
        if (ui->abcDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(3, model->columnCount() - 1);
    if (ui->abcDE->isEnabled()) {
        if (ui->abcDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(4, model->columnCount() - 1);
    if (ui->abCde->isEnabled()) {
        if (ui->abCde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(5, model->columnCount() - 1);
    if (ui->abCdE->isEnabled()) {
        if (ui->abCdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(6, model->columnCount() - 1);
    if (ui->abCDe->isEnabled()) {
        if (ui->abCDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(7, model->columnCount() - 1);
    if (ui->abCDE->isEnabled()) {
        if (ui->abCDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(8, model->columnCount() - 1);
    if (ui->aBcde->isEnabled()) {
        if (ui->aBcde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(9, model->columnCount() - 1);
    if (ui->aBcdE->isEnabled()) {
        if (ui->aBcdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(10, model->columnCount() - 1);
    if (ui->aBcDe->isEnabled()) {
        if (ui->aBcDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(11, model->columnCount() - 1);
    if (ui->aBcDE->isEnabled()) {
        if (ui->aBcDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(12, model->columnCount() - 1);
    if (ui->aBCde->isEnabled()) {
        if (ui->aBCde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(13, model->columnCount() - 1);
    if (ui->aBCdE->isEnabled()) {
        if (ui->aBCdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(14, model->columnCount() - 1);
    if (ui->aBCDe->isEnabled()) {
        if (ui->aBCDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(15, model->columnCount() - 1);
    if (ui->aBCDE->isEnabled()) {
        if (ui->aBCDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(16, model->columnCount() - 1);
    if (ui->Abcde->isEnabled()) {
        if (ui->Abcde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(17, model->columnCount() - 1);
    if (ui->AbcdE->isEnabled()) {
        if (ui->AbcdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(18, model->columnCount() - 1);
    if (ui->AbcDe->isEnabled()) {
        if (ui->AbcDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(19, model->columnCount() - 1);
    if (ui->AbcDE->isEnabled()) {
        if (ui->AbcDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(20, model->columnCount() - 1);
    if (ui->AbCde->isEnabled()) {
        if (ui->AbCde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(21, model->columnCount() - 1);
    if (ui->AbCdE->isEnabled()) {
        if (ui->AbCdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(22, model->columnCount() - 1);
    if (ui->AbCDe->isEnabled()) {
        if (ui->AbCDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(23, model->columnCount() - 1);
    if (ui->AbCDE->isEnabled()) {
        if (ui->AbCDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");


    cellIndex = model->index(24, model->columnCount() - 1);
    if (ui->ABcde->isEnabled()) {
        if (ui->ABcde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(25, model->columnCount() - 1);
    if (ui->ABcdE->isEnabled()) {
        if (ui->ABcdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(26, model->columnCount() - 1);
    if (ui->ABcDe->isEnabled()) {
        if (ui->ABcDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(27, model->columnCount() - 1);
    if (ui->ABcDE->isEnabled()) {
        if (ui->ABcDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(28, model->columnCount() - 1);
    if (ui->ABCde->isEnabled()) {
        if (ui->ABCde->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(29, model->columnCount() - 1);
    if (ui->ABCdE->isEnabled()) {
        if (ui->ABCdE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(30, model->columnCount() - 1);
    if (ui->ABCDe->isEnabled()) {
        if (ui->ABCDe->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");

    cellIndex = model->index(31, model->columnCount() - 1);
    if (ui->ABCDE->isEnabled()) {
        if (ui->ABCDE->isChecked()) {
            model->setData(cellIndex, 1);
        } else {
            model->setData(cellIndex, 0);
        }
    } else  model->setData(cellIndex, "DC");



    tableView->setModel(model);

    tableView->resizeColumnsToContents();
    tableView->resizeRowsToContents();

    window->setCentralWidget(tableView);
    window->show();
}






void MainWindow::on_abcde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;


    int value = ui->lcdMintermNumber->value();
    if (ui->abcde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);

}


void MainWindow::on_Abcde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->Abcde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abcdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abcdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abcDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abcDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abcDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abcDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abCde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abCde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abCdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abCdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abCDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abCDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_abCDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->abCDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBCde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBCde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBCdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBCdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBCDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBCDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBCDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBCDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBcde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBcde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBcdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBcdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}



void MainWindow::on_aBcDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBcDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_aBcDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->aBcDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbcdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbcdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbcDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbcDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbcDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbcDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbCde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbCde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbCdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbCdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbCDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbCDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_AbCDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->AbCDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABCde_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABCde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABCdE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;


    int value = ui->lcdMintermNumber->value();
    if (ui->ABCdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABCDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABCDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABCDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABCDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABcde_stateChanged(int arg1)
{

    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABcde->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABcdE_stateChanged(int arg1)
{

    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABcdE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABcDE_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABcDE->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}


void MainWindow::on_ABcDe_stateChanged(int arg1)
{
    isSave = false ;
    isMinButtonPushed = false ;

    int value = ui->lcdMintermNumber->value();
    if (ui->ABcDe->isChecked())
        value++;
    else
        value--;
    ui->lcdMintermNumber->display(value);
}






void MainWindow::on_changeVariableButton_clicked()
{
    if (ui->dial->value() == 5) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Change the variables");
        messageBox.setText("Choose your own variables");

        QVBoxLayout layout;
        QWidget *widget = new QWidget(&messageBox);
        widget->setLayout(&layout);

        QComboBox comboBoxA;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxA.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxA);
        comboBoxA.setCurrentText(QString::fromStdString(A1));

        QComboBox comboBoxB;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxB.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxB);
        comboBoxB.setCurrentText(QString::fromStdString(B1));

        QComboBox comboBoxC;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxC.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxC);
        comboBoxC.setCurrentText(QString::fromStdString(C1));

        QComboBox comboBoxD;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxD.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxD);
        comboBoxD.setCurrentText(QString::fromStdString(D1));

        QComboBox comboBoxE;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxE.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxE);
        comboBoxE.setCurrentText(QString::fromStdString(E1));

        messageBox.layout()->addWidget(widget);

        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();

        // نمایش مقادیر انتخاب شده در کامبو باکس‌ها
        QString selectedValues = "The changed varibles for  :\n";
        selectedValues += "fifth bit  : " + comboBoxA.currentText() + "\n";
        selectedValues += "forth bit  : " + comboBoxB.currentText() + "\n";
        selectedValues += "third bit  : " + comboBoxC.currentText() + "\n";
        selectedValues += "second bit : " + comboBoxD.currentText() + "\n";
        selectedValues += "first bit  : " + comboBoxE.currentText() + "\n";
        A1 = comboBoxA.currentText().toStdString() + "";
        A0 = comboBoxA.currentText().toStdString()  + "\'" ;
        B1 = comboBoxB.currentText().toStdString()  ;
        B0 = comboBoxB.currentText().toStdString()  + "\'" ;
        C1 = comboBoxC.currentText().toStdString()  ;
        C0 = comboBoxC.currentText().toStdString()  + "\'" ;
        D1 = comboBoxD.currentText().toStdString()  ;
        D0 = comboBoxD.currentText().toStdString()  + "\'" ;
        E1 = comboBoxE.currentText().toStdString()  ;
        E0 = comboBoxE.currentText().toStdString()  + "\'" ;

        QMessageBox::information(this, "متغیر ها", selectedValues);
        MainWindow::on_dial_sliderMoved(5);


    } else if (ui->dial->value() == 4) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Change variables");
        messageBox.setText("Choose your own variables");

        QVBoxLayout layout;
        QWidget *widget = new QWidget(&messageBox);
        widget->setLayout(&layout);

        QComboBox comboBoxA;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxA.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxA);
        comboBoxA.setCurrentText(QString::fromStdString(A1));

        QComboBox comboBoxB;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxB.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxB);
        comboBoxB.setCurrentText(QString::fromStdString(B1));


        QComboBox comboBoxC;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxC.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxC);
        comboBoxC.setCurrentText(QString::fromStdString(C1));


        QComboBox comboBoxD;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxD.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxD);
        comboBoxD.setCurrentText(QString::fromStdString(D1));



        messageBox.layout()->addWidget(widget);

        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();

        // نمایش مقادیر انتخاب شده در کامبو باکس‌ها
        QString selectedValues = "The changed variables for :\n";
        selectedValues += "forth bit  : " + comboBoxA.currentText() + "\n";
        selectedValues += "third bit  : " + comboBoxB.currentText() + "\n";
        selectedValues += "second bit : " + comboBoxC.currentText() + "\n";
        selectedValues += "first bit  : " + comboBoxD.currentText() + "\n";
        A1 = comboBoxA.currentText().toStdString() + "";
        A0 = comboBoxA.currentText().toStdString()  + "\'" ;
        B1 = comboBoxB.currentText().toStdString()  ;
        B0 = comboBoxB.currentText().toStdString()  + "\'" ;
        C1 = comboBoxC.currentText().toStdString()  ;
        C0 = comboBoxC.currentText().toStdString()  + "\'" ;
        D1 = comboBoxD.currentText().toStdString()  ;
        D0 = comboBoxD.currentText().toStdString()  + "\'" ;


        QMessageBox::information(this, "Variables", selectedValues);
        MainWindow::on_dial_sliderMoved(4);

    } else if (ui->dial->value() == 3){
        QMessageBox messageBox;
        messageBox.setWindowTitle("Change variables");
        messageBox.setText("Choose your own variables");

        QVBoxLayout layout;
        QWidget *widget = new QWidget(&messageBox);
        widget->setLayout(&layout);

        QComboBox comboBoxA;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxA.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxA);
        comboBoxA.setCurrentText(QString::fromStdString(A1));


        QComboBox comboBoxB;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxB.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxB);
        comboBoxB.setCurrentText(QString::fromStdString(B1));


        QComboBox comboBoxC;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxC.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxC);
        comboBoxC.setCurrentText(QString::fromStdString(C1));



        messageBox.layout()->addWidget(widget);

        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();

        // نمایش مقادیر انتخاب شده در کامبو باکس‌ها
        QString selectedValues = "The chosen variables for :\n";
        selectedValues += "third bit   : " + comboBoxA.currentText() + "\n";
        selectedValues += "second bit  : " + comboBoxB.currentText() + "\n";
        selectedValues += "first bit   : " + comboBoxC.currentText() + "\n";
        A1 = comboBoxA.currentText().toStdString() + "";
        A0 = comboBoxA.currentText().toStdString()  + "\'" ;
        B1 = comboBoxB.currentText().toStdString()  ;
        B0 = comboBoxB.currentText().toStdString()  + "\'" ;
        C1 = comboBoxC.currentText().toStdString()  ;
        C0 = comboBoxC.currentText().toStdString()  + "\'" ;



        QMessageBox::information(this, "Variables", selectedValues);
        MainWindow::on_dial_sliderMoved(3);

    } else if (ui->dial->value() == 2) {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Change variables");
        messageBox.setText("Choose your own variables");

        QVBoxLayout layout;
        QWidget *widget = new QWidget(&messageBox);
        widget->setLayout(&layout);

        QComboBox comboBoxA;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxA.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxA);
        comboBoxA.setCurrentText(QString::fromStdString(A1));


        QComboBox comboBoxB;
        for (char letter = 'A'; letter <= 'Z'; letter++) {
            comboBoxB.addItem(QString(letter));
        }
        layout.addWidget(&comboBoxB);
        comboBoxB.setCurrentText(QString::fromStdString(B1));



        messageBox.layout()->addWidget(widget);

        messageBox.addButton(QMessageBox::Ok);
        messageBox.exec();

        // نمایش مقادیر انتخاب شده در کامبو باکس‌ها
        QString selectedValues = "The choosen variables for :\n";
        selectedValues += "second bit  : " + comboBoxA.currentText() + "\n";
        selectedValues += "first bit   : " + comboBoxB.currentText() + "\n";
        A1 = comboBoxA.currentText().toStdString() + "";
        A0 = comboBoxA.currentText().toStdString()  + "\'" ;
        B1 = comboBoxB.currentText().toStdString()  ;
        B0 = comboBoxB.currentText().toStdString()  + "\'" ;





        QMessageBox::information(this, "Variables", selectedValues);
        MainWindow::on_dial_sliderMoved(2);


    }
}



void MainWindow::on_indexButton_clicked()
{
    if (ui->indexButton->text() == "Alphabet"){
        ui->indexButton->setText("Bit");

    } else {
        ui->indexButton->setText("Alphabet");

    }

    if (ui->dial->value() == 2){
        MainWindow::on_dial_sliderMoved(2);
    } else if (ui->dial->value() == 3){
        MainWindow::on_dial_sliderMoved(3);
    } else if (ui->dial->value() == 4){
        MainWindow::on_dial_sliderMoved(4);
    } else {
        MainWindow::on_dial_sliderMoved(5);
    }

}



void MainWindow::on_dial_sliderMoved(int position)
{
    if (position == 2){
        isSave = false ;
        isMinButtonPushed = false ;


        std::ofstream file(dontcaresTxt);
        file.close();

        ui->abcde->setEnabled(true);
        ui->abcdE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abcDE->setEnabled(true);

        if (ui->dial->value() == 5 || ui->dial->value() == 4 || ui->dial->value() == 3){
            ui->abCde->setEnabled(true);
            ui->abCdE->setEnabled(true);
            ui->abCDe->setEnabled(true);
            ui->abCDE->setEnabled(true);


            if (!(ui->dial->value() == 3)) {
                ui->aBcde->setEnabled(true);
                ui->aBcdE->setEnabled(true);
                ui->aBcDe->setEnabled(true);
                ui->aBcDE->setEnabled(true);
                ui->aBCde->setEnabled(true);
                ui->aBCdE->setEnabled(true);
                ui->aBCDe->setEnabled(true);
                ui->aBCDE->setEnabled(true);
            }
        }

        if (ui->dial->value() == 5){
            ui->Abcde->setEnabled(true);
            ui->AbcdE->setEnabled(true);
            ui->AbcDe->setEnabled(true);
            ui->AbcDE->setEnabled(true);
            ui->AbCde->setEnabled(true);
            ui->AbCdE->setEnabled(true);
            ui->AbCDe->setEnabled(true);
            ui->AbCDE->setEnabled(true);
            ui->ABcde->setEnabled(true);
            ui->ABcdE->setEnabled(true);
            ui->ABcDe->setEnabled(true);
            ui->ABcDE->setEnabled(true);
            ui->ABCde->setEnabled(true);
            ui->ABCdE->setEnabled(true);
            ui->ABCDe->setEnabled(true);
            ui->ABCDE->setEnabled(true);
        }

        ui->lcdDontcareNumber->display(0);


        ui->fLabel->setText(QString::fromStdString("f(" + A1 + "," + B1 + ")="));


        ui->abCDE->setEnabled(false);   // LEFT TABLE ROW 2 & 3 & 4
        ui->abCDe->setEnabled(false);
        ui->aBCde->setEnabled(false);
        ui->aBCdE->setEnabled(false);
        ui->aBCDE->setEnabled(false);
        ui->aBCDe->setEnabled(false);
        ui->aBcde->setEnabled(false);
        ui->aBcdE->setEnabled(false);
        ui->aBcDE->setEnabled(false);
        ui->aBcDe->setEnabled(false);
        ui->abCdE->setEnabled(false);
        ui->abCde->setEnabled(false);

        ui->abCDE->setChecked(false);   // LEFT TABLE ROW 2 & 3 & 4
        ui->abCDe->setChecked(false);
        ui->aBCde->setChecked(false);
        ui->aBCdE->setChecked(false);
        ui->aBCDE->setChecked(false);
        ui->aBCDe->setChecked(false);
        ui->aBcde->setChecked(false);
        ui->aBcdE->setChecked(false);
        ui->aBcDE->setChecked(false);
        ui->aBcDe->setChecked(false);
        ui->abCde->setChecked(false);
        ui->abCdE->setChecked(false);

        ui->Abcde->setEnabled(false);   // RIGHT TABLE
        ui->AbcdE->setEnabled(false);
        ui->AbcDE->setEnabled(false);
        ui->AbcDe->setEnabled(false);
        ui->AbCde->setEnabled(false);
        ui->AbCdE->setEnabled(false);
        ui->AbCDE->setEnabled(false);
        ui->AbCDe->setEnabled(false);
        ui->ABCde->setEnabled(false);
        ui->ABCdE->setEnabled(false);
        ui->ABCDE->setEnabled(false);
        ui->ABCDe->setEnabled(false);
        ui->ABcde->setEnabled(false);
        ui->ABcdE->setEnabled(false);
        ui->ABcDE->setEnabled(false);
        ui->ABcDe->setEnabled(false);

        ui->Abcde->setChecked(false); // RIGHT TABLE
        ui->AbcdE->setChecked(false);
        ui->AbcDE->setChecked(false);
        ui->AbcDe->setChecked(false);
        ui->AbCde->setChecked(false);
        ui->AbCdE->setChecked(false);
        ui->AbCDE->setChecked(false);
        ui->AbCDe->setChecked(false);
        ui->ABCde->setChecked(false);
        ui->ABCdE->setChecked(false);
        ui->ABCDE->setChecked(false);
        ui->ABCDe->setChecked(false);
        ui->ABcde->setChecked(false);
        ui->ABcdE->setChecked(false);
        ui->ABcDE->setChecked(false);
        ui->ABcDe->setChecked(false);


        ui->abcde->setToolTip(QString::fromStdString(A0 + B0 + "\n00\n" + "0"));
        ui->abcdE->setToolTip(QString::fromStdString(A0 + B1 + "\n01\n" + "1"));
        ui->abcDe->setToolTip(QString::fromStdString(A1 + B0 + "\n10\n" + "2"));
        ui->abcDE->setToolTip(QString::fromStdString(A1 + B1 + "\n11\n" + "3"));

        ui->abCde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->abCdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->abCDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->abCDE->setToolTip(QString::fromStdString("not existed in 2-variables"));

        ui->aBcde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBcdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBcDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBcDE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBCde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBCdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBCDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->aBCDE->setToolTip(QString::fromStdString("not existed in 2-variables"));

        ui->Abcde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbcdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbcDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbcDE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbCde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbCdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbCDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->AbCDE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABcde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABcdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABcDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABcDE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABCde->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABCdE->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABCDe->setToolTip(QString::fromStdString("not existed in 2-variables"));
        ui->ABCDE->setToolTip(QString::fromStdString("not existed in 2-variables"));

        ui->aGroupBox->setToolTip(QString::fromStdString(A1 + "X\n0X\nn < 4"));
        ui->AGroupBox->setToolTip(QString::fromStdString("not existed in 2-variables"));


        if (ui->indexButton->text() != "Bit" ){ // is bit model
            ui->aBClabel->setText("");
            ui->aDElabel->setText(QString::fromStdString(A1 + "    " + B1));
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText("");
            ui->abCindex->setText("");
            ui->aBCindex->setText("");
            ui->aBcindex->setText("");

            ui->adeindex->setText("0    0");
            ui->adEindex->setText("0    1");
            ui->aDEindex->setText("1    1");
            ui->aDeindex->setText("1    0");

            ui->Abcindex->setText("");
            ui->AbCindex->setText("");
            ui->ABCindex->setText("");
            ui->ABcindex->setText("");

            ui->Adeindex->setText("");
            ui->AdEindex->setText("");
            ui->ADEindex->setText("");
            ui->ADeindex->setText("");

        } else { // is phrase
            ui->aBClabel->setText("");
            ui->aDElabel->setText("");
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText("");
            ui->abCindex->setText("");
            ui->aBCindex->setText("");
            ui->aBcindex->setText("");

            ui->adeindex->setText(QString::fromStdString(A0 + "  " + B0));
            ui->adEindex->setText(QString::fromStdString(A0 + "   " + B1));
            ui->aDEindex->setText(QString::fromStdString(A1 + "    " + B1));
            ui->aDeindex->setText(QString::fromStdString(A1 + "   " + B0));

            ui->Abcindex->setText("");
            ui->AbCindex->setText("");
            ui->ABCindex->setText("");
            ui->ABcindex->setText("");

            ui->Adeindex->setText("");
            ui->AdEindex->setText("");
            ui->ADEindex->setText("");
            ui->ADeindex->setText("");
        }



        update();

    } else if (position == 3){
        isSave = false ;
        isMinButtonPushed = false ;


        std::ofstream file(dontcaresTxt);
        file.close();

        ui->abcde->setEnabled(true);
        ui->abcdE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abcDE->setEnabled(true);

        if (ui->dial->value() == 3   || ui->dial->value() == 3 || ui->dial->value() == 3){
            ui->abCde->setEnabled(true);
            ui->abCdE->setEnabled(true);
            ui->abCDe->setEnabled(true);
            ui->abCDE->setEnabled(true);

            if (!(ui->dial->value() == 3)) {
                ui->aBcde->setEnabled(true);
                ui->aBcdE->setEnabled(true);
                ui->aBcDe->setEnabled(true);
                ui->aBcDE->setEnabled(true);
                ui->aBCde->setEnabled(true);
                ui->aBCdE->setEnabled(true);
                ui->aBCDe->setEnabled(true);
                ui->aBCDE->setEnabled(true);
            }
        }

        if (ui->dial->value() == 5){
            ui->Abcde->setEnabled(true);
            ui->AbcdE->setEnabled(true);
            ui->AbcDe->setEnabled(true);
            ui->AbcDE->setEnabled(true);
            ui->AbCde->setEnabled(true);
            ui->AbCdE->setEnabled(true);
            ui->AbCDe->setEnabled(true);
            ui->AbCDE->setEnabled(true);
            ui->ABcde->setEnabled(true);
            ui->ABcdE->setEnabled(true);
            ui->ABcDe->setEnabled(true);
            ui->ABcDE->setEnabled(true);
            ui->ABCde->setEnabled(true);
            ui->ABCdE->setEnabled(true);
            ui->ABCDe->setEnabled(true);
            ui->ABCDE->setEnabled(true);
        }

        ui->lcdDontcareNumber->display(0);


        ui->fLabel->setText(QString::fromStdString("f(" + A1 + "," + B1 + "," + C1 + ")="));


        ui->abcde->setEnabled(true); // LEFT TABLE
        ui->abcdE->setEnabled(true);
        ui->abcDE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abCde->setEnabled(true);
        ui->abCdE->setEnabled(true);
        ui->abCDE->setEnabled(true);
        ui->abCDe->setEnabled(true);
        ui->aBCde->setEnabled(true);
        ui->aBCdE->setEnabled(true);
        ui->aBCDE->setEnabled(true);
        ui->aBCDe->setEnabled(true);
        ui->aBcde->setEnabled(true);
        ui->aBcdE->setEnabled(true);
        ui->aBcDE->setEnabled(true);
        ui->aBcDe->setEnabled(true);

        ui->abcDE->setEnabled(true); // LEFT TABLE
        ui->abcDe->setEnabled(true);
        ui->abCDE->setEnabled(true);
        ui->abCDe->setEnabled(true);

        ui->Abcde->setChecked(false); // RIGHT TABLE
        ui->AbcdE->setChecked(false);
        ui->AbcDE->setChecked(false);
        ui->AbcDe->setChecked(false);
        ui->AbCde->setChecked(false);
        ui->AbCdE->setChecked(false);
        ui->AbCDE->setChecked(false);
        ui->AbCDe->setChecked(false);
        ui->ABCde->setChecked(false);
        ui->ABCdE->setChecked(false);
        ui->ABCDE->setChecked(false);
        ui->ABCDe->setChecked(false);
        ui->ABcde->setChecked(false);
        ui->ABcdE->setChecked(false);
        ui->ABcDE->setChecked(false);
        ui->ABcDe->setChecked(false);

        ui->aBCde->setChecked(false);   // LEFT TABLE
        ui->aBCdE->setChecked(false);
        ui->aBCDE->setChecked(false);
        ui->aBCDe->setChecked(false);
        ui->aBcde->setChecked(false);
        ui->aBcdE->setChecked(false);
        ui->aBcDE->setChecked(false);
        ui->aBcDe->setChecked(false);

        ui->ABCDE->setEnabled(false);   // RIGHT
        ui->ABCDe->setEnabled(false);
        ui->ABCdE->setEnabled(false);
        ui->ABCde->setEnabled(false);
        ui->ABcDE->setEnabled(false);
        ui->ABcDe->setEnabled(false);
        ui->ABcdE->setEnabled(false);
        ui->ABcde->setEnabled(false);
        ui->AbCDE->setEnabled(false);
        ui->AbCDe->setEnabled(false);
        ui->AbCdE->setEnabled(false);
        ui->AbcDE->setEnabled(false);
        ui->AbCde->setEnabled(false);
        ui->AbcDe->setEnabled(false);
        ui->AbcdE->setEnabled(false);
        ui->Abcde->setEnabled(false);

        ui->aBCde->setEnabled(false);
        ui->aBCdE->setEnabled(false);
        ui->aBCDE->setEnabled(false);
        ui->aBCDe->setEnabled(false);
        ui->aBcde->setEnabled(false);
        ui->aBcdE->setEnabled(false);
        ui->aBcDE->setEnabled(false);
        ui->aBcDe->setEnabled(false);

        ui->abcde->setToolTip(QString::fromStdString(A0 + B0 + C0 + "\n000\n" + "0"));
        ui->abcdE->setToolTip(QString::fromStdString(A0 + B0 + C1 + "\n001\n" + "1"));
        ui->abcDe->setToolTip(QString::fromStdString(A0 + B1 + C0 + "\n010\n" + "2"));
        ui->abcDE->setToolTip(QString::fromStdString(A0 + B1 + C1 + "\n011\n" + "3"));
        ui->abCde->setToolTip(QString::fromStdString(A1 + B0 + C0 + "\n100\n" + "4"));
        ui->abCdE->setToolTip(QString::fromStdString(A1 + B0 + C1 + "\n101\n" + "5"));
        ui->abCDe->setToolTip(QString::fromStdString(A1 + B1 + C0 + "\n110\n" + "6"));
        ui->abCDE->setToolTip(QString::fromStdString(A1 + B1 + C1 + "\n111\n" + "7"));

        ui->aBcde->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBcdE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBcDe->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBcDE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBCde->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBCdE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBCDe->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->aBCDE->setToolTip(QString::fromStdString("not existed in 3-variables"));

        ui->Abcde->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbcdE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbcDe->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbcDE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbCde->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbCdE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbCDe->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->AbCDE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABcde->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABcdE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABcDe->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABcDE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABCde->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABCdE->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABCDe->setToolTip(QString::fromStdString("not existed in 3-variables"));
        ui->ABCDE->setToolTip(QString::fromStdString("not existed in 3-variables"));

        ui->aGroupBox->setToolTip(QString::fromStdString(A1 + "XX\n0XX\nn < 8"));
        ui->AGroupBox->setToolTip(QString::fromStdString("not existed in 3-variables"));


        if (ui->indexButton->text() != "Bit" ){ // is bit model
            ui->aBClabel->setText(QString::fromStdString(A1));
            ui->aDElabel->setText(QString::fromStdString(B1 + "    " + C1));
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText("0");
            ui->abCindex->setText("1");
            ui->aBCindex->setText("");
            ui->aBcindex->setText("");

            ui->adeindex->setText("0    0");
            ui->adEindex->setText("0    1");
            ui->aDEindex->setText("1    1");
            ui->aDeindex->setText("1    0");

            ui->Abcindex->setText("");
            ui->AbCindex->setText("");
            ui->ABCindex->setText("");
            ui->ABcindex->setText("");

            ui->Adeindex->setText("");
            ui->AdEindex->setText("");
            ui->ADEindex->setText("");
            ui->ADeindex->setText("");

        } else { // is phrase
            ui->aBClabel->setText("");
            ui->aDElabel->setText("");
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText(QString::fromStdString(A0));
            ui->abCindex->setText(QString::fromStdString(A1));
            ui->aBCindex->setText("");
            ui->aBcindex->setText("");

            ui->adeindex->setText(QString::fromStdString(B0 + "  " + C0));
            ui->adEindex->setText(QString::fromStdString(B0 + "   " + C1));
            ui->aDEindex->setText(QString::fromStdString(B1 + "    " + C1));
            ui->aDeindex->setText(QString::fromStdString(B1 + "   " + C0));

            ui->Abcindex->setText("");
            ui->AbCindex->setText("");
            ui->ABCindex->setText("");
            ui->ABcindex->setText("");

            ui->Adeindex->setText("");
            ui->AdEindex->setText("");
            ui->ADEindex->setText("");
            ui->ADeindex->setText("");
        }


        update();

    } else if (position == 4){
        isSave = false ;
        isMinButtonPushed = false ;

        std::ofstream file(dontcaresTxt);
        file.close();

        ui->abcde->setEnabled(true);
        ui->abcdE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abcDE->setEnabled(true);

        if (ui->dial->value() == 5 || ui->dial->value() == 4 || ui->dial->value() == 3){
            ui->abCde->setEnabled(true);
            ui->abCdE->setEnabled(true);
            ui->abCDe->setEnabled(true);
            ui->abCDE->setEnabled(true);

            if (!(ui->dial->value() == 3)) {
                ui->aBcde->setEnabled(true);
                ui->aBcdE->setEnabled(true);
                ui->aBcDe->setEnabled(true);
                ui->aBcDE->setEnabled(true);
                ui->aBCde->setEnabled(true);
                ui->aBCdE->setEnabled(true);
                ui->aBCDe->setEnabled(true);
                ui->aBCDE->setEnabled(true);
            }
        }

        if (ui->dial->value() == 5){
            ui->Abcde->setEnabled(true);
            ui->AbcdE->setEnabled(true);
            ui->AbcDe->setEnabled(true);
            ui->AbcDE->setEnabled(true);
            ui->AbCde->setEnabled(true);
            ui->AbCdE->setEnabled(true);
            ui->AbCDe->setEnabled(true);
            ui->AbCDE->setEnabled(true);
            ui->ABcde->setEnabled(true);
            ui->ABcdE->setEnabled(true);
            ui->ABcDe->setEnabled(true);
            ui->ABcDE->setEnabled(true);
            ui->ABCde->setEnabled(true);
            ui->ABCdE->setEnabled(true);
            ui->ABCDe->setEnabled(true);
            ui->ABCDE->setEnabled(true);
        }

        ui->lcdDontcareNumber->display(0);


        ui->fLabel->setText(QString::fromStdString("f(" + A1 + "," + B1 + "," + C1 + "," + D1 + ")="));

        ui->abcde->setEnabled(true); // LEFT TABLE
        ui->abcdE->setEnabled(true);
        ui->abcDE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abCde->setEnabled(true);
        ui->abCdE->setEnabled(true);
        ui->abCDE->setEnabled(true);
        ui->abCDe->setEnabled(true);
        ui->aBCde->setEnabled(true);
        ui->aBCdE->setEnabled(true);
        ui->aBCDE->setEnabled(true);
        ui->aBCDe->setEnabled(true);
        ui->aBcde->setEnabled(true);
        ui->aBcdE->setEnabled(true);
        ui->aBcDE->setEnabled(true);
        ui->aBcDe->setEnabled(true);

        ui->Abcde->setChecked(false); // RIGHT TABLE
        ui->AbcdE->setChecked(false);
        ui->AbcDE->setChecked(false);
        ui->AbcDe->setChecked(false);
        ui->AbCde->setChecked(false);
        ui->AbCdE->setChecked(false);
        ui->AbCDE->setChecked(false);
        ui->AbCDe->setChecked(false);
        ui->ABCde->setChecked(false);
        ui->ABCdE->setChecked(false);
        ui->ABCDE->setChecked(false);
        ui->ABCDe->setChecked(false);
        ui->ABcde->setChecked(false);
        ui->ABcdE->setChecked(false);
        ui->ABcDE->setChecked(false);
        ui->ABcDe->setChecked(false);

        ui->Abcde->setEnabled(false); // RIGHT TABLE
        ui->AbcdE->setEnabled(false);
        ui->AbcDE->setEnabled(false);
        ui->AbcDe->setEnabled(false);
        ui->AbCde->setEnabled(false);
        ui->AbCdE->setEnabled(false);
        ui->AbCDE->setEnabled(false);
        ui->AbCDe->setEnabled(false);
        ui->ABCde->setEnabled(false);
        ui->ABCdE->setEnabled(false);
        ui->ABCDE->setEnabled(false);
        ui->ABCDe->setEnabled(false);
        ui->ABcde->setEnabled(false);
        ui->ABcdE->setEnabled(false);
        ui->ABcDE->setEnabled(false);
        ui->ABcDe->setEnabled(false);

        ui->abcde->setToolTip(QString::fromStdString(A0 + B0 + C0 + D0 + "\n0000\n" + "0"));
        ui->abcdE->setToolTip(QString::fromStdString(A0 + B0 + C0 + D1 + "\n0001\n" + "1"));
        ui->abcDe->setToolTip(QString::fromStdString(A0 + B0 + C1 + D0 + "\n0010\n" + "2"));
        ui->abcDE->setToolTip(QString::fromStdString(A0 + B0 + C1 + D1 + "\n0011\n" + "3"));
        ui->abCde->setToolTip(QString::fromStdString(A0 + B1 + C0 + D0 + "\n0100\n" + "4"));
        ui->abCdE->setToolTip(QString::fromStdString(A0 + B1 + C0 + D1 + "\n0101\n" + "5"));
        ui->abCDe->setToolTip(QString::fromStdString(A0 + B1 + C1 + D0 + "\n0110\n" + "6"));
        ui->abCDE->setToolTip(QString::fromStdString(A0 + B1 + C1 + D1 + "\n0111\n" + "7"));
        ui->aBcde->setToolTip(QString::fromStdString(A1 + B0 + C0 + D0 + "\n1000\n" + "8"));
        ui->aBcdE->setToolTip(QString::fromStdString(A1 + B0 + C0 + D1 + "\n1001\n" + "9"));
        ui->aBcDe->setToolTip(QString::fromStdString(A1 + B0 + C1 + D0 + "\n1010\n" + "10"));
        ui->aBcDE->setToolTip(QString::fromStdString(A1 + B0 + C1 + D1 + "\n1011\n" + "11"));
        ui->aBCde->setToolTip(QString::fromStdString(A1 + B1 + C0 + D0 + "\n1100\n" + "12"));
        ui->aBCdE->setToolTip(QString::fromStdString(A1 + B1 + C0 + D1 + "\n1101\n" + "13"));
        ui->aBCDe->setToolTip(QString::fromStdString(A1 + B1 + C1 + D0 + "\n1110\n" + "14"));
        ui->aBCDE->setToolTip(QString::fromStdString(A1 + B1 + C1 + D1 + "\n1111\n" + "15"));

        ui->Abcde->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbcdE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbcDe->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbcDE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbCde->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbCdE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbCDe->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->AbCDE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABcde->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABcdE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABcDe->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABcDE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABCde->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABCdE->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABCDe->setToolTip(QString::fromStdString("not existed in 4-variables"));
        ui->ABCDE->setToolTip(QString::fromStdString("not existed in 4-variables"));

        ui->aGroupBox->setToolTip(QString::fromStdString(A1 + "XXX\n0XXX\nn < 16"));
        ui->AGroupBox->setToolTip(QString::fromStdString("not existed in 4-variables"));


        if (ui->indexButton->text() != "بیت" ){ // is bit model
            ui->aBClabel->setText(QString::fromStdString(A1 + "    " + B1 ));
            ui->aDElabel->setText(QString::fromStdString(C1 + "    " + D1));
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText("0    0");
            ui->abCindex->setText("0    1");
            ui->aBCindex->setText("1    1");
            ui->aBcindex->setText("1    0");

            ui->adeindex->setText("0    0");
            ui->adEindex->setText("0    1");
            ui->aDEindex->setText("1    1");
            ui->aDeindex->setText("1    0");

            ui->Abcindex->setText("");
            ui->AbCindex->setText("");
            ui->ABCindex->setText("");
            ui->ABcindex->setText("");

            ui->Adeindex->setText("");
            ui->AdEindex->setText("");
            ui->ADEindex->setText("");
            ui->ADeindex->setText("");

        } else { // is phrase
            ui->aBClabel->setText("");
            ui->aDElabel->setText("");
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText(QString::fromStdString(A0 + "  " +   B0));
            ui->abCindex->setText(QString::fromStdString(A0 + "   " +  B1));
            ui->aBCindex->setText(QString::fromStdString(A1 + "    " + B1));
            ui->aBcindex->setText(QString::fromStdString(A1 + "   " +  B0));

            ui->adeindex->setText(QString::fromStdString(C0 + "  " + D0));
            ui->adEindex->setText(QString::fromStdString(C0 + "   " + D1));
            ui->aDEindex->setText(QString::fromStdString(C1 + "    " + D1));
            ui->aDeindex->setText(QString::fromStdString(C1 + "   " + D0));

            ui->Abcindex->setText("");
            ui->AbCindex->setText("");
            ui->ABCindex->setText("");
            ui->ABcindex->setText("");

            ui->Adeindex->setText("");
            ui->AdEindex->setText("");
            ui->ADEindex->setText("");
            ui->ADeindex->setText("");
        }


        update();

    } else if (position == 5){
        isSave = false ;
        isMinButtonPushed = false ;

        std::ofstream file(dontcaresTxt);
        file.close();

        ui->abcde->setEnabled(true);
        ui->abcdE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abcDE->setEnabled(true);

        if (ui->dial->value() == 5 || ui->dial->value() == 4 || ui->dial->value() == 3){
            ui->abCde->setEnabled(true);
            ui->abCdE->setEnabled(true);
            ui->abCDe->setEnabled(true);
            ui->abCDE->setEnabled(true);

            if (!(ui->dial->value() == 3)) {
                ui->aBcde->setEnabled(true);
                ui->aBcdE->setEnabled(true);
                ui->aBcDe->setEnabled(true);
                ui->aBcDE->setEnabled(true);
                ui->aBCde->setEnabled(true);
                ui->aBCdE->setEnabled(true);
                ui->aBCDe->setEnabled(true);
                ui->aBCDE->setEnabled(true);
            }
        }

        if (ui->dial->value() == 5){
            ui->Abcde->setEnabled(true);
            ui->AbcdE->setEnabled(true);
            ui->AbcDe->setEnabled(true);
            ui->AbcDE->setEnabled(true);
            ui->AbCde->setEnabled(true);
            ui->AbCdE->setEnabled(true);
            ui->AbCDe->setEnabled(true);
            ui->AbCDE->setEnabled(true);
            ui->ABcde->setEnabled(true);
            ui->ABcdE->setEnabled(true);
            ui->ABcDe->setEnabled(true);
            ui->ABcDE->setEnabled(true);
            ui->ABCde->setEnabled(true);
            ui->ABCdE->setEnabled(true);
            ui->ABCDe->setEnabled(true);
            ui->ABCDE->setEnabled(true);
        }

        ui->lcdDontcareNumber->display(0);


        ui->fLabel->setText(QString::fromStdString("f(" + A1 + "," + B1 + "," + C1 + "," + D1 + "," + E1 + ")="));

        ui->abcde->setEnabled(true); // LEFT TABLE
        ui->abcdE->setEnabled(true);
        ui->abcDE->setEnabled(true);
        ui->abcDe->setEnabled(true);
        ui->abCde->setEnabled(true);
        ui->abCdE->setEnabled(true);
        ui->abCDE->setEnabled(true);
        ui->abCDe->setEnabled(true);
        ui->aBCde->setEnabled(true);
        ui->aBCdE->setEnabled(true);
        ui->aBCDE->setEnabled(true);
        ui->aBCDe->setEnabled(true);
        ui->aBcde->setEnabled(true);
        ui->aBcdE->setEnabled(true);
        ui->aBcDE->setEnabled(true);
        ui->aBcDe->setEnabled(true);

        ui->Abcde->setEnabled(true); // RIGHT TABLE
        ui->AbcdE->setEnabled(true);
        ui->AbcDE->setEnabled(true);
        ui->AbcDe->setEnabled(true);
        ui->AbCde->setEnabled(true);
        ui->AbCdE->setEnabled(true);
        ui->AbCDE->setEnabled(true);
        ui->AbCDe->setEnabled(true);
        ui->ABCde->setEnabled(true);
        ui->ABCdE->setEnabled(true);
        ui->ABCDE->setEnabled(true);
        ui->ABCDe->setEnabled(true);
        ui->ABcde->setEnabled(true);
        ui->ABcdE->setEnabled(true);
        ui->ABcDE->setEnabled(true);
        ui->ABcDe->setEnabled(true);


        ui->abcde->setToolTip(QString::fromStdString(A0 + B0 + C0 + D0 + E0 + "\n00000\n" + "0"));
        ui->abcdE->setToolTip(QString::fromStdString(A0 + B0 + C0 + D0 + E1 + "\n00001\n" + "1"));
        ui->abcDe->setToolTip(QString::fromStdString(A0 + B0 + C0 + D1 + E0 + "\n00010\n" + "2"));
        ui->abcDE->setToolTip(QString::fromStdString(A0 + B0 + C0 + D1 + E1 + "\n00011\n" + "3"));
        ui->abCde->setToolTip(QString::fromStdString(A0 + B0 + C1 + D0 + E0 + "\n00100\n" + "4"));
        ui->abCdE->setToolTip(QString::fromStdString(A0 + B0 + C1 + D0 + E1 + "\n00101\n" + "5"));
        ui->abCDe->setToolTip(QString::fromStdString(A0 + B0 + C1 + D1 + E0 + "\n00110\n" + "6"));
        ui->abCDE->setToolTip(QString::fromStdString(A0 + B0 + C1 + D1 + E1 + "\n00111\n" + "7"));
        ui->aBcde->setToolTip(QString::fromStdString(A0 + B1 + C0 + D0 + E0 + "\n01000\n" + "8"));
        ui->aBcdE->setToolTip(QString::fromStdString(A0 + B1 + C0 + D0 + E1 + "\n01001\n" + "9"));
        ui->aBcDe->setToolTip(QString::fromStdString(A0 + B1 + C0 + D1 + E0 + "\n01010\n" + "10"));
        ui->aBcDE->setToolTip(QString::fromStdString(A0 + B1 + C0 + D1 + E1 + "\n01011\n" + "11"));
        ui->aBCde->setToolTip(QString::fromStdString(A0 + B1 + C1 + D0 + E0 + "\n01100\n" + "12"));
        ui->aBCdE->setToolTip(QString::fromStdString(A0 + B1 + C1 + D0 + E1 + "\n01101\n" + "13"));
        ui->aBCDe->setToolTip(QString::fromStdString(A0 + B1 + C1 + D1 + E0 + "\n01110\n" + "14"));
        ui->aBCDE->setToolTip(QString::fromStdString(A0 + B1 + C1 + D1 + E1 + "\n01111\n" + "15"));
        ui->Abcde->setToolTip(QString::fromStdString(A1 + B0 + C0 + D0 + E0 + "\n10000\n" + "16"));
        ui->AbcdE->setToolTip(QString::fromStdString(A1 + B0 + C0 + D0 + E1 + "\n10001\n" + "17"));
        ui->AbcDe->setToolTip(QString::fromStdString(A1 + B0 + C0 + D1 + E0 + "\n10010\n" + "18"));
        ui->AbcDE->setToolTip(QString::fromStdString(A1 + B0 + C0 + D1 + E1 + "\n10011\n" + "19"));
        ui->AbCde->setToolTip(QString::fromStdString(A1 + B0 + C1 + D0 + E0 + "\n10100\n" + "20"));
        ui->AbCdE->setToolTip(QString::fromStdString(A1 + B0 + C1 + D0 + E1 + "\n10101\n" + "21"));
        ui->AbCDe->setToolTip(QString::fromStdString(A1 + B0 + C1 + D1 + E0 + "\n10110\n" + "22"));
        ui->AbCDE->setToolTip(QString::fromStdString(A1 + B0 + C1 + D1 + E1 + "\n10111\n" + "23"));
        ui->ABcde->setToolTip(QString::fromStdString(A1 + B1 + C0 + D0 + E0 + "\n11000\n" + "24"));
        ui->ABcdE->setToolTip(QString::fromStdString(A1 + B1 + C0 + D0 + E1 + "\n11001\n" + "25"));
        ui->ABcDe->setToolTip(QString::fromStdString(A1 + B1 + C0 + D1 + E0 + "\n11010\n" + "26"));
        ui->ABcDE->setToolTip(QString::fromStdString(A1 + B1 + C0 + D1 + E1 + "\n11011\n" + "27"));
        ui->ABCde->setToolTip(QString::fromStdString(A1 + B1 + C1 + D0 + E0 + "\n11100\n" + "28"));
        ui->ABCdE->setToolTip(QString::fromStdString(A1 + B1 + C1 + D0 + E1 + "\n11101\n" + "29"));
        ui->ABCDe->setToolTip(QString::fromStdString(A1 + B1 + C1 + D1 + E0 + "\n11110\n" + "30"));
        ui->ABCDE->setToolTip(QString::fromStdString(A1 + B1 + C1 + D1 + E1 + "\n11111\n" + "31"));

        ui->aGroupBox->setToolTip(QString::fromStdString(A1 + "XXXX\n0XXXX\nn < 16"));
        ui->AGroupBox->setToolTip(QString::fromStdString(A1 + "XXXX\n1XXXX\n16 <= n > 32"));



        if (ui->indexButton->text() != "بیت" ){ // is bit model
            ui->aBClabel->setText(QString::fromStdString(A1 + "    " + B1 ));
            ui->aDElabel->setText(QString::fromStdString(C1 + "    " + D1));
            ui->ABClabel->setText(QString::fromStdString(A1 + "    " + B1));
            ui->ADElabel->setText(QString::fromStdString(C1 + "    " + D1));
            ui->Alabel->setText(QString::fromStdString(A1 + "=1"));
            ui->alabel->setText(QString::fromStdString(A1 + "=0"));

            ui->abcindex->setText("0    0");
            ui->abCindex->setText("0    1");
            ui->aBCindex->setText("1    1");
            ui->aBcindex->setText("1    0");

            ui->adeindex->setText("0    0");
            ui->adEindex->setText("0    1");
            ui->aDEindex->setText("1    1");
            ui->aDeindex->setText("1    0");

            ui->Abcindex->setText("0    0");
            ui->AbCindex->setText("0    1");
            ui->ABCindex->setText("1    1");
            ui->ABcindex->setText("1    0");

            ui->Adeindex->setText("0    0");
            ui->AdEindex->setText("0    1");
            ui->ADEindex->setText("1    1");
            ui->ADeindex->setText("1    0");

        } else { // is phrase
            ui->aBClabel->setText("");
            ui->aDElabel->setText("");
            ui->ABClabel->setText("");
            ui->ADElabel->setText("");
            ui->Alabel->setText("");
            ui->alabel->setText("");

            ui->abcindex->setText(QString::fromStdString(A0 + B0 + C0));
            ui->abCindex->setText(QString::fromStdString(A0 + B0 + C1));
            ui->aBCindex->setText(QString::fromStdString(A0 + B1 + C1));
            ui->aBcindex->setText(QString::fromStdString(A0 + B1 + C0));

            ui->adeindex->setText(QString::fromStdString(A0 + D0 + E0));
            ui->adEindex->setText(QString::fromStdString(A0 + D0 + E1));
            ui->aDEindex->setText(QString::fromStdString(A0 + D1 + E1));
            ui->aDeindex->setText(QString::fromStdString(A0 + D1 + E0));

            ui->Abcindex->setText(QString::fromStdString(A1 + B0 + C0));
            ui->AbCindex->setText(QString::fromStdString(A1 + B0 + C1));
            ui->ABCindex->setText(QString::fromStdString(A1 + B1 + C1));
            ui->ABcindex->setText(QString::fromStdString(A1 + B1 + C0));

            ui->Adeindex->setText(QString::fromStdString(A1 + D0 + E0));
            ui->AdEindex->setText(QString::fromStdString(A1 + D0 + E1));
            ui->ADEindex->setText(QString::fromStdString(A1 + D1 + E1));
            ui->ADeindex->setText(QString::fromStdString(A1 + D1 + E0));
        }

        update();
    }

}




/*
    Reza Asadi

    Inspired by (Quine Mc) :  https:/github.com/int-main/Quine-McCluskey
                              https://github.com/mansiag/Quine-McClusky-Method/blob/master/tab-final.cpp
*/


