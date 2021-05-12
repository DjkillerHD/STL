/// Sebastian Arnauer 24.03.2021
///Aufgabenstellung: Einfach verkettete Listen; Datenstruktur mit Name Zulassung und Feldern Nachname, Marke, Type, Farbe, CO(float), Hubraum(int) /// !mittels STL!
/// Unterprogramme mit
/// 1. Einfügen am Anfang
/// 2. Anhängen am Ende
/// 3. Ausgabe am Bildschirm
/// 4. Einlesen von einer Datei
/// 5. Asugabe in eine Datei
/// 6. Suchen nach Type (alle auflisten)
/// 7. Suchen nach CO (alle auflisten)
/// 8. Loeschen nach Nachname (alle)
/// 9. Loeschen nach Farbe (alle)


#include <windows.h>
#include <iostream>
#include "display.h"
#include "Zulassungen.h"

using namespace std;



void Zulassungen :: eingebenAnfang(Zulassung &newElement)
{
    elemente.push_front(newElement);
}

void Zulassungen :: eingebenEnde(Zulassung &newElement)
{
    elemente.push_back(newElement);
}

void Zulassungen :: ausgeben()
{
    list <Zulassung> :: iterator iter;
    short pos=0;

    cout << endl << endl;

    for(iter=elemente.begin(); iter!=elemente.end(); ++iter)
    {
        ++pos;
        cout << "Element " << pos << ":" << endl;
        cout << "Nachname: " << iter->getNachname() << endl;
        cout << "Marke: " << iter->getMarke() << endl;
        cout << "Type: " << iter->getType() << endl;
        cout << "Farbe: " << iter->getFarbe() << endl;
        cout << "CO: " << iter->getCO() << endl;
        cout << "Hubraum: " << iter->getHubraum() << endl << endl;
    }
}

void Zulassungen :: einlesenDatei()
{
    string filename;
    cout << "Name der Datei (mit.txt): ";
    getline(cin, filename);

    char einfuegen;

    do
    {
        cout << endl << "'A'nfang oder 'E'nde angängen: ";
        cin >> einfuegen;
        cout << endl;
    }while(einfuegen!='A' && einfuegen!='a' && einfuegen!='E' && einfuegen !='e');


    ifstream fileRead(filename);

    if(!fileRead)
    {
        textcolor(RED);
        cout << endl << endl << "Fehler beim öffnen der Datei!" << endl << endl;
        textcolor(WHITE);
    }
    else
    {
        string buf;
        Zulassung elm;
        int counter=0;  // keeps track of the element currently being read

        while(getline(fileRead, buf))   // solange etwas eingelesen werden kann
        {

            int posNeedForRead=buf.find(':')+2; /// es ist erst alles nach dem ':' wichtig zum einlesen!! + 2 liest erst ab dem Ersten Buchstaben ein. (Siehe Formatierung)

            char bufToRead[buf.length()-posNeedForRead+10]; /// Erstellen eines Char-Arrays mit der benötigten Länge

            memset(bufToRead, 0x00, sizeof(bufToRead));    /// Clearen des Char-Arrays, da am Ende immer Müll-Characters stehen

            buf.copy(bufToRead, (2+buf.length()-posNeedForRead), posNeedForRead);   /// Kopieren des wichtigen Teil vom String auf das Char Array

            string toRead;

            toRead.clear();
            toRead+=bufToRead;   /// Kopieren des Char-Arrays auf einen String


            switch(counter%6)   // Switch da, um zu wissen, welche Eigenschaft gerade eingelesen wird
            {
            case 0: /// Nachname
                {
                    elm.setNachname(toRead);   // Alle Elemente einlesen (Laut MusterFile vorgegeben)
                }
                break;

            case 1: /// Marke
                {

                    elm.setMarke(toRead);
                }
                break;

            case 2: /// Type
                {
                    elm.setType(toRead);
                }
                break;

            case 3: /// Farbe
                {
                    elm.setFarbe(toRead);
                }
                break;

            case 4: /// CO-Wert
                {
                    for(int buf=0; buf<=2; ++buf)   /// Da laut Vorgabe, am Ende des CO-Werts "g/cm^3" steht, wird dies gelöscht.
                    {
                        toRead.pop_back();
                    }

                    float f=stof(toRead);   /// Umwandlung String --> Float
                    elm.setCO(f);
                }
                break;

            case 5: /// Hubraum
                {
                    for(int buf=0; buf<=2; ++buf)   /// Da laut Vorgabe, am Ende des CO-Werts "ccm" steht, wird dies gelöscht.
                    {
                        toRead.pop_back();
                    }

                    int i=stoi(toRead); /// String --> Int
                    elm.setHubraum(i);

                    /// Das Element wird erst in Fall 5 eingefügt, da dieser immer eintritt und ab Fall 5 die Letzte
                    /// Eigenschaft eingelesen wurde.

                    if(einfuegen=='A' || einfuegen=='a')
                    {
                        eingebenAnfang(elm);    /// Am Anfang einfügen
                    }
                    else if(einfuegen=='E' || einfuegen=='e')
                    {
                        eingebenEnde(elm);      /// Am Ende anhängen
                    }

                    getline(fileRead, buf);  /// Da laut Format eine Leerzeile nach jedem Datensatz ist --> Leerzeile überspringen
                }
                break;
            }

            counter++;
        }

        textcolor(RED); cout << endl << "Fertig eingelesen!" << endl << endl; textcolor(WHITE);
    }
}

void Zulassungen :: ausgebenDatei()
{
    string filename;
    cout << endl << endl << "Name der Datei: ";
    getline(cin, filename);

    ofstream fileWrite(filename);

    list <Zulassung> :: iterator iter;

    for(iter=elemente.begin(); iter!=elemente.end(); ++iter)
    {
        fileWrite << "Nachname: " << iter->getNachname() << endl;   // Eigenschaften des jetztigen Elements aufs File schreiben (laut MusterFile)
        fileWrite << "Marke: " << iter->getMarke() << endl;
        fileWrite << "Type: " << iter->getType() << endl;
        fileWrite << "Farbe: " << iter->getFarbe() << endl;
        fileWrite << "CO: " << iter->getFarbe() << "g/cm^3" << endl;
        fileWrite << "Hubraum: " << iter->getHubraum() << "ccm" << endl;
        fileWrite << endl;  /// Da laut Formatierungsvorlage (selbst gewählt) ein Leerzeichen nach jedem Datensatz kommt, muss eine Leerzeile eingefügt werden.
    }

    textcolor(RED); cout << endl << "Fertig geschrieben!" << endl << endl; textcolor(WHITE);
}

void Zulassungen :: sucheType(string &elementToSearch)
{
    list <Zulassung> :: iterator iter;
    short pos=0;

    for(iter=elemente.begin(); iter!=elemente.end(); ++iter)
    {
        ++pos;
        if(iter->getType()==elementToSearch)
        {
            cout << "Element " << pos << ":" << endl;
            cout << "Nachname: " << iter->getNachname() << endl;
            cout << "Marke: " << iter->getMarke() << endl;
            cout << "Type: " << iter->getType() << endl;
            cout << "Farbe: " << iter->getFarbe() << endl;
            cout << "CO: " << iter->getCO() << endl;
            cout << "Hubraum: " << iter->getHubraum() << endl << endl;
        }
    }
}

void Zulassungen :: sucheCO(float elementToSearch)
{
    list <Zulassung> :: iterator iter;
    short pos=0;

    for(iter=elemente.begin(); iter!=elemente.end(); ++iter)
    {
        ++pos;
        if(iter->getCO()==elementToSearch)
        {
            cout << "Element " << pos << ":" << endl;
            cout << "Nachname: " << iter->getNachname() << endl;
            cout << "Marke: " << iter->getMarke() << endl;
            cout << "Type: " << iter->getType() << endl;
            cout << "Farbe: " << iter->getFarbe() << endl;
            cout << "CO: " << iter->getCO() << endl;
            cout << "Hubraum: " << iter->getHubraum() << endl << endl;
        }
    }
}

void Zulassungen :: deleteNachname(string &elementToSearch)
{
    list <Zulassung> :: iterator iter; // iterator
    short pos=0;
    bool gefunden=false;

    try
    {
        for(iter=elemente.begin(); iter!=elemente.end(); ++iter)    /// iter ist zuerst das 1. Element, solange iter nicht das letzte Element ist, wird iter zum nächsten Element !
        {
            ++pos;
            if(iter->getNachname()==elementToSearch)    // iter->getNachname, greift auf die Methode getNachname zu, um von dem derzeitigen Element den Nachnamen herauszufinden
            {                                           // falls gleich, soll es gelöscht werden
                char buf;

                gefunden=true;

                cout << "Element " << pos << ":" << endl;
                cout << "Nachname: " << iter->getNachname() << endl;
                cout << "Marke: " << iter->getMarke() << endl;
                cout << "Type: " << iter->getType() << endl;
                cout << "Farbe: " << iter->getFarbe() << endl;
                cout << "CO: " << iter->getCO() << endl;
                cout << "Hubraum: " << iter->getHubraum();

                cout << endl << endl << "Soll dieses Element gelöscht werden? J/N: ";
                cin >> buf;
                if(buf=='J' || buf =='j')
                {
                    try // Versuchung des try/catch befehls
                    {
                        iter=elemente.erase(iter);
                        cout << endl << endl << "Element wurde gelöscht!" << endl << endl;
                    }
                    catch(exception &e)
                    {
                        textcolor(RED); cerr << "ERROR" << endl; textbackground(WHITE);
                    }

                }
            }
        }
        if(!gefunden)
        {
            textcolor(RED);
            cerr << endl << "Keine Elemente gefunden!!" << endl << endl;
            textcolor(WHITE);
        }
    }
    catch(exception& e)
    {
        textcolor(RED); cerr << "ERROR" << endl; textbackground(WHITE);
    }
}

void Zulassungen :: deleteFarbe(string &elementToSearch)
{
    list <Zulassung> :: iterator iter; // iterator
    short pos=0;
    bool gefunden=false;

    try
    {
        for(iter=elemente.begin(); iter!=elemente.end(); ++iter)    /// iter ist zuerst das 1. Element, solange iter nicht das letzte Element ist, wird iter zum nächsten Element !
        {
            ++pos;
            if(iter->getFarbe()==elementToSearch)    // iter->getNachname, greift auf die Methode getNachname zu, um von dem derzeitigen Element den Nachnamen herauszufinden
            {                                           // falls gleich, soll es gelöscht werden
                char buf;

                gefunden=true;

                cout << "Element " << pos << ":" << endl;
                cout << "Nachname: " << iter->getNachname() << endl;
                cout << "Marke: " << iter->getMarke() << endl;
                cout << "Type: " << iter->getType() << endl;
                cout << "Farbe: " << iter->getFarbe() << endl;
                cout << "CO: " << iter->getCO() << endl;
                cout << "Hubraum: " << iter->getHubraum();

                cout << endl << endl << "Soll dieses Element gelöscht werden? J/N: ";
                cin >> buf;
                if(buf=='J' || buf =='j')
                {
                    try
                    {
                        iter=elemente.erase(iter);
                        cout << endl << endl << "Element wurde gelöscht!" << endl << endl;
                    }
                    catch(exception &e)
                    {
                        textcolor(RED); cerr << "ERROR" << endl; textbackground(WHITE);
                    }

                }
            }
        }
        if(!gefunden)
        {
            textcolor(RED);
            cerr << endl << "Keine Elemente gefunden!!" << endl << endl;
            textcolor(WHITE);
        }
    }
    catch(exception& e)
    {
        textcolor(RED); cerr << "ERROR" << endl; textbackground(WHITE);
    }

}



void menuausgabe();
void menuausgabe()
{
    textcolor(LIGHTMAGENTA); printf("0"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Beenden\n");
    textcolor(LIGHTMAGENTA); printf("1"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Einfügen am Anfang\n");
    textcolor(LIGHTMAGENTA); printf("2"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Anhängen am Ende\n");
    textcolor(LIGHTMAGENTA); printf("3"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Ausgabe am Bildschirm\n");
    textcolor(LIGHTMAGENTA); printf("4"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Einlesen von einer Datei\n");
    textcolor(LIGHTMAGENTA); printf("5"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Ausgabe in eine Datei\n");
    textcolor(LIGHTMAGENTA); printf("6"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Suchen nach Type (alle Elemente werden aufgelistet)\n");
    textcolor(LIGHTMAGENTA); printf("7"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Suchen nach CO-Ausstoß (alle Elemente werden aufgelistet)\n");
    textcolor(LIGHTMAGENTA); printf("8"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Loeschen nach Nachname (alle Elemente werden gelöscht)\n");
    textcolor(LIGHTMAGENTA); printf("9"); textcolor(DARKGRAY); printf(")"); textcolor(WHITE); printf(" Loeschen nach Farbe (alle Elemente werden gelöscht)\n");

    textcolor(LIGHTBLUE); printf("Eingabe: ");
    fflush(stdin);
}


int main()
{
    console_init();
    setfenstertitle("Verkettete Liste mittels STL - by Sebastian Arnauer");

    bool wh=true;
    short ausw;
    Zulassungen element;
    Zulassung buf;

    while(wh)
    {
         menuausgabe();
         fflush(stdin); cin >> ausw; fflush(stdin);     // Eingabe der Auswahl, was man tun möchte

         switch(ausw)
         {
         case 0:    // beenden
            {
                wh=false;
            }
            break;

         case 1:    // Eingeben am Anfang
            {
                textcolor(RED); cout << endl << "Eingeben am Anfang" << endl << endl; textcolor(WHITE);

                string eingabeString;
                float eingabeNumber;

                cout << endl << "Nachname: "; getline(cin, eingabeString);          buf.setNachname(eingabeString);    // Eingabe und setzen von einer Eigenschaft
                cout << "Marke: "; getline(cin, eingabeString);                     buf.setMarke(eingabeString);
                cout << "Type: "; getline(cin, eingabeString);                      buf.setType(eingabeString);
                cout << "Farbe: "; getline(cin, eingabeString);                     buf.setFarbe(eingabeString);
                cout << "CO: ";  cin >> eingabeNumber;                              buf.setCO(eingabeNumber);
                cout << "Hubraum: "; cin >> eingabeNumber;                          buf.setHubraum(eingabeNumber);     // Da ein Float auch als int übergeben werden kann (ohne Nachkommastellen natürlich), wurde keine neue Variable erstellt
                cout << endl << endl << endl << endl;

                element.eingebenAnfang(buf);
            }
            break;

         case 2:    // Eingeben am Ende
            {
                textcolor(RED); cout << endl << "Eingeben am Anfang" << endl << endl; textcolor(WHITE);

                string eingabeString;
                float eingabeNumber;

                cout << endl << "Nachname: "; getline(cin, eingabeString);          buf.setNachname(eingabeString);    // Eingabe und setzen von einer Eigenschaft
                cout << "Marke: "; getline(cin, eingabeString);                     buf.setMarke(eingabeString);
                cout << "Type: "; getline(cin, eingabeString);                      buf.setType(eingabeString);
                cout << "Farbe: "; getline(cin, eingabeString);                     buf.setFarbe(eingabeString);
                cout << "CO: ";  cin >> eingabeNumber;                              buf.setCO(eingabeNumber);
                cout << "Hubraum: "; cin >> eingabeNumber;                          buf.setHubraum(eingabeNumber);     // Da ein Float auch als int übergeben werden kann (ohne Nachkommastellen natürlich), wurde keine neue Variable erstellt
                cout << endl << endl << endl << endl;

                element.eingebenEnde(buf);
            }
            break;

         case 3:    // Ausgabe an der Konsole
            {
                textcolor(RED); cout << endl << "Ausgabe in die Konsole" << endl << endl; textcolor(WHITE);

                element.ausgeben();
            }
            break;

         case 4:    //  Daten einer Datei einlesen
            {
               textcolor(RED); cout << endl << "Einlesen einer Datei" << endl << endl; textcolor(WHITE);

               element.einlesenDatei();
            }
            break;

         case 5:    // Daten in eine Datei ausgeben
             {
                 textcolor(RED); cout << endl << "Ausgabe in eine Datei" << endl << endl; textcolor(WHITE);

                 element.ausgebenDatei();
             }
            break;

         case 6:    // Elemente nach Type durchsuchen
            {
                textcolor(RED); cout << endl << "Suchen nach Type" << endl << endl; textcolor(WHITE);

                string elmToSearch;
                cout << "Type: "; getline(cin, elmToSearch); cout << endl;
                element.sucheType(elmToSearch);
            }
            break;

         case 7:    // Elemente nach CO durchsuchen
            {
                textcolor(RED); cout << endl << "Suchen nach CO" << endl << endl; textcolor(WHITE);

                float elmToSearch;
                cout << "CO: "; cin >> elmToSearch; cout << endl;
                element.sucheCO(elmToSearch);
            }
            break;

         case 8:    // Elemente nach Nachname löschen
            {
                textcolor(RED); cout << endl << "Nachname löschen" << endl << endl; textcolor(WHITE);

                string elmToSearch;
                cout << "Nachname: "; getline(cin, elmToSearch); cout << endl;
                element.deleteNachname(elmToSearch);
            }
            break;

         case 9:    // Elemente nach Farbe löschen
            {
                textcolor(RED); cout << endl << "Farbe löschen" << endl << endl; textcolor(WHITE);

                string elmToSearch;
                cout << "Farbe: "; getline(cin, elmToSearch); cout << endl;
                element.deleteFarbe(elmToSearch);
            }
            break;

         default:   // Sollte nicht eintreffen
            {
                textcolor(RED);
                cout << endl << "Diesen Modus gibt es nicht! " << endl << endl;
            }
            break;
         }
    }

    textcolor(RED);
    cout << endl << "Thanks for Using this Program -- Shutdown" << endl;

    return 0;
}
