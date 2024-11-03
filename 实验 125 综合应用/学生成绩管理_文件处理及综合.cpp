#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;
char filename[30];
ofstream outstuf;

class course
{
public:
    course();
    int ttpp();
    virtual void print(int loc)  = 0;
    int idLoc(int);
    vector <vector<int>>idIndex;
    stringstream convIntString;
protected:
    int lineNo;
    string cstringDataCache;
    int cintDataCache;
    struct stuInfoStruct {
        int idNo;
        char name[20];
        char gender;
        string status;
        int score;
    };
};

class students :public course
{
public:
    int ScoreRq=55;
    void newStu();
    void mark();
    void graduate(int);
    virtual void print(int loc)
    {
        if (loc)//函数有时会得到0数值，意味用户输入不存在id，当时当刻便可跳过输出步骤
        {
            fstream file(filename);
            int currLoc = 0;
            loc = (loc - 1) * 5 + 1;//确定文件指针目的地
            for (; currLoc < loc; currLoc++)//前往目的地的首
                getline(file, cstringDataCache);
            for (; currLoc < loc + 5; currLoc++)//此for用于输出一学生的数据
            {
                cstringDataCache.clear();
                getline(file, cstringDataCache);
                cout << cstringDataCache << endl;
            }
            convIntString.clear();
            convIntString << cstringDataCache.substr(11);//获取学生exam mark，判断在当前情况下学生能否毕业
            convIntString >> cintDataCache;//<-转换为可以计算的数字
            (cintDataCache > ScoreRq) ? cout << "Student passing" : cout << "Student failing";
            file.close();
        }
        else
            cout << "ID not found." << endl;
    }
};

class graduate:public course
{
public:
virtual void print(int loc) {//一样是输出数据，但是为毕业学生打造，原理无异
    cout << "We value students’ personal privacy and thoroughly delete all their personal data when they graduate.\nType \"exit\" to exit :)  :";
    cin >> cstringDataCache;
    if (cstringDataCache=="admin")
    {
        cout << "pass:";
        cin >> cstringDataCache;
        if (cstringDataCache == "5hT9$8mN")
        {
            cout << "loc:" << loc << endl;
            if (loc - 1)
            {
                fstream file(filename);
                int currLoc = 0;
                loc = (loc - 1) * 5 + 1;
                for (; currLoc < loc; currLoc++)
                    getline(file, cstringDataCache);
                for (; currLoc < loc + 5; currLoc++)
                {
                    cstringDataCache.clear();
                    getline(file, cstringDataCache);
                    cout << cstringDataCache << endl;
                }
                file.close();
            }
            else
                cout << "ID not found." << endl;
        }
        else cout << "Easter egg found! :)\n";
    }
}
};


course::course()//course的构造函数，凡打开程序时都会执行，用于确定文件名与环境初始化
{
    if (filename[0] == '\0')//student和graduate时都会执行course构造函数，但只需要一次，第二次filename将不会是空
    {
        cout << "Data file name:";
        cin >> filename;
        strcat_s(filename, sizeof(filename), ".txt");//加上.txt，让文件成为文字档
        outstuf.open(filename, ios::_Nocreate);
        if (!outstuf)       //如果文件不存在，就加上这行文字，因为_Nocreate只能开启已有文件。
        {
            outstuf.open(filename);
            outstuf << "Student score data file:0";
        }
        outstuf.close();
        fstream readFile(filename);
        int currPointer = 1;
        for (int i = 0; i < ttpp(); i++)//输入id和是否毕业入vector
        {
            for (; currPointer != (i * 5 + 3); currPointer++)//移文件指针至id
            {
                getline(readFile, cstringDataCache);
                //cout << "Test Data:" << cstringDataCache << endl;
            }
            //cout <<"Data:" << cstringDataCache.substr(10) << endl;
            convIntString << cstringDataCache.substr(10);//转换string成int，因为vector被声明int
            convIntString >> cintDataCache;
            convIntString.clear();
            idIndex.push_back({ cintDataCache, 1 });//预设为所有学生未毕业，是否毕业后面决定
            //cout << i << " :" << idIndex[i][0] << endl;
            for (; currPointer != (i * 5 + 6); currPointer++)//移文件指针至status
            {
                getline(readFile, cstringDataCache);
                //cout << "Test Data:" << cstringDataCache << endl;
            }
            //cout <<"Data:" << cstringDataCache << endl;
            if (cstringDataCache == "Status:Graduate")//如果是毕业生就写1
                idIndex[i][1] = 0;
            //for (int i = 0; i < idIndex.size(); i++)
            //{
            //    for (int j = 0; j <= 1; j++)
            //        cout << idIndex[i][j] << " ";
            //    cout << endl;
            //}
        }
        readFile.close();//手尾
    }
}

int course::ttpp()        //total people，旨在获取总人数
{
    fstream readFile(filename);
    getline(readFile, cstringDataCache);
    cstringDataCache = cstringDataCache.substr(24);//获取第24字之后的文字，即总学生数 ，以string形式
    convIntString << cstringDataCache;//转换成int，方便输出后运算
    convIntString >> cintDataCache;
    convIntString.clear();//清除转换的缓存，因为否则同一程序开启两次，即使cstringDataCache有变，convIntString自身也保持上一次的数据不变
    return cintDataCache;
}

int course::idLoc(int id)
{
    int loc=0;
    for (int i = 0; i < idIndex.size(); i++)
        if (idIndex[i][0] == id)
            loc = i+1;//loc为id的位置/顺序，如果没有找到便不会赋值，便会返回0
    return loc;
}

void students::newStu()//新学生
{
    course::stuInfoStruct stuStc;
IDinput:
    cout << "Student ID: ";
    cin >> stuStc.idNo;
    if (idLoc(stuStc.idNo)!=0)
    {
        cout << "ID: " << stuStc.idNo << " had been assigned to another student, it need to be UNIQUE.\nPlease re-enter.\n";
        goto IDinput;
    }
    cout << "Name: ";
    cin.ignore();
    cin.get(stuStc.name, 20);
    cin.ignore();
    do
    {
        cout << "Gender (Input [ M / F ] only.) : ";
        cin >> stuStc.gender;
    } 
    while (!(stuStc.gender == 'M' || stuStc.gender == 'F'));
    outstuf.open(filename, ios::app);//储存数据在文件最后
    outstuf << "\nStudentID:" << stuStc.idNo << "\nName:" << stuStc.name << "\nGender:" << stuStc.gender << "\nStatus: Student\nExam Score:000";
    outstuf.close();
    //更改Student score data file:后的数字，使其+1
    outstuf.open(filename, 1);
    outstuf << "Student score data file:" << ttpp() + 1;//复写成Student score data file:x+1
    outstuf.close();
    idIndex.push_back({ stuStc.idNo,1 });
}

void students::mark()
{
    string temp,temp2,cstringDataCache;
    fstream file(filename);
    int currentLine=1,targetLine,pos=0;
    string data2write;
    for (int i = 0; i < ttpp(); i++)
    {
        targetLine = i * 5 + 3;//移动文件指针至name行，获取人的名字，用于告知用户输入对象
        file.seekg(pos, ios::beg);
        for (currentLine; currentLine != targetLine; currentLine++)
        {
            getline(file, temp);
            pos += temp.size() + 2;
            //cout <<"pos:"<< pos << endl;
        }
        getline(file, cstringDataCache);//在此获取name
        getline(file, temp);//temp和temp2.size()用于输入pos
        getline(file, temp2);
        currentLine += 3;
        //cout << temp2;
        if (true)
        {
            cout << "Input mark of " << cstringDataCache << " :";
            cin >> cintDataCache;
            pos = pos + cstringDataCache.size() + temp.size() + temp2.size()+6+11;
            file.seekg(pos, ios::beg);
            file << setw(3) << setfill('0') <<cintDataCache<<endl;
        }
    }
    file.close();
}

void students::graduate(int scoreRqLocal)
{
    //cout << "Size:" << idIndex.size();
    int scoreRq,pos=0;
    string dump;
    fstream rFile(filename),wFile(filename);
    //cin >> scoreRq;
    for (int i = 0,j=1; i < ttpp(); i++)
    {
            for (; j != i * 3 + 5; j++)//移动文件读指针至state，并同步写指针的函数pos
            {
                getline(rFile, dump);
                pos = pos + dump.size() + 2;
                //cout << "pos:" << pos <<"dump size:" <<dump<< endl;
                dump.clear();
            }
            getline(rFile, cstringDataCache);
            //cout << "Cstring:" << cstringDataCache<<endl;
            if (cstringDataCache == "Status: Student"|| cstringDataCache == "Status:Re-Study")//如果是学生或重读生，才进入核心程序
            {
                getline(rFile, cstringDataCache);
                convIntString << cstringDataCache.substr(12);
                convIntString >> cintDataCache;
                convIntString.clear();
                wFile.seekg(pos);
                //cout <<"Cstring:"<< cstringDataCache.substr(12)<< "Cint:" << cintDataCache<<endl;
                if (cintDataCache >= scoreRqLocal)//如果分数>=所需分数则状态定为毕业
                {
                    wFile.write( "Status:Graduate",15);
                    idIndex[i][1] = 0;
                    //cout << "pos:" << pos << endl;
                }
                else wFile.write( "Status:Re-Study",15);//不足分数就状态定为重修
            }
            pos += 33;
        //cout << "i:" << i << "j:" << j << ":" << 5cstringDataCache << endl;
        cstringDataCache.clear();
    }
    rFile.close();
    wFile.close();
}

int main()
{
    students stu;
    graduate grd;
    int id;
    char opno;
    while (true)
    {
        cout << "Op.No.\tOperation\n[1]\tNew Student\n[2]\tExam held (give mark)\n[3]\tPrint Student information\n[4]\tCourse End\nOperation No.:";
        cin >> opno;
        switch (opno) 
        {
        case '1':
            stu.newStu();
            break;
        case '2':
            stu.mark();
            break;
        case '3':
            cout << "ID:";
            cin >> id;
            if(stu.idLoc(id))
                if (stu.idIndex[stu.idLoc(id)-1][1]==0)//
                    grd.print(stu.idLoc(id));
                else
                    stu.print(stu.idLoc(id));
            break;
        case '4':
        Enter:
            cout << "Comfirm course end?\nAll student(s) score over " << stu.ScoreRq << " would be graduate from course.\nOp.No.\t\tOperation\n[Y]\t\tComfirm course end\n[1]\t\tEdit passing score.\n[Any key]\tBack to manu.\nOperation No: ";
            cin >> opno;
            if(opno=='Y')
                stu.graduate(stu.ScoreRq);
            else if (opno == '1')
            {
                cout << "Set pass require score (equal or above): ";
                cin >> stu.ScoreRq;
                stu.ScoreRq;
                goto Enter;
            }
            break;
        default:
            cout << "Invalid Operation No..";
            break;
        }
    }
}
