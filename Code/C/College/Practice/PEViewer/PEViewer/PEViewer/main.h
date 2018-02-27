#pragma once

 
// Sleep time for abnormal exit


void __init(PE&, int, char const *[]);
void __run(PE&);
int Menu();
void flush();


void flush();



void __init(PE &pe, int argc, char const *argv[]){
    if (argc == 1){
        char    path[MAX_PATH], ch;
        int     i = 0;
        cout << "The Absolute location of the PE file to be opened(100 char limited): " << endl;
        while((ch = getchar()) != '\n' && i < 100) {
            *(path+(i++)) = ch;
        }
        *(path+i) = '\0';
    #ifdef debug
        pe.OpenPE("test/kernel32.dll");
    #else
        pe.OpenPE(path);
    #endif
    } else if (argc == 2){
    #ifdef debug
        pe.OpenPE("test/notepad.exe");
    #else
        pe.OpenPE(argv[1]);
    #endif
    } else {
        cout << "Wrong Argument!" << endl;
        Sleep(SleepTime);
        exit(1);
    }
}


void __run(PE& pe){
    if (!pe.Is32PE()){
        cout << "This is not a 32-bits PE file" << endl;
        Sleep(SleepTime);
        exit(1);
    }
    else {
        char    ch;
        while (1) {
            ch = Menu();
        #ifndef debug_cls
            system("cls");
        #endif
            switch (ch){
                case    7: exit(0);  // Exit
                case    0: pe.ShowDosHeader();      break;
                case    1:
                case    2: 
                case    3: pe.ShowNTHeader(ch-1);   break;
                case    4: pe.ShowSectionHeader();  break;
                case    5: pe.ShowINT();            break;
                case    6: pe.ShowEAT();            break;
            }
            cout << endl << endl << endl << endl;
            system("pause");
        }
    }
}


int Menu(){
#ifndef debug_cls
    system("cls");
#endif
    char   ch;
    cout << "--------------Menu-------------------" << endl;
    cout << "---------a.Show Dos Header-----------" << endl;
    cout << "---------b.Show NT Header------------" << endl;
    cout << "---------c.Show File Header----------" << endl;
    cout << "---------d.Show Optional Header------" << endl;
    cout << "---------e.Show Section Header-------" << endl;
    cout << "---------f.Show INT------------------" << endl;
    cout << "---------g.Show EAT------------------" << endl;
    cout << "---------h.Exit----------------------" << endl;
    cout << "Input your choise: ";
    while ((ch=getchar()) == 0x20);
    flush();
    ch = tolower(ch);
    while (ch < 'a' || ch > 'h'){
        cout << endl << "Wrong option, again: ";
        while ((ch=getchar()) == 0x20);
        flush();
        ch = tolower(ch); 
    }
    return ch - 'a';
}
