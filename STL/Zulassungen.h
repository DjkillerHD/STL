#ifndef ZULASSUNGEN_H_INCLUDED
#define ZULASSUNGEN_H_INCLUDED

/// Sebastian Arnauer 11.05.2021
/// Diese Klasse ist da, um den Container zu benutzen

#include <list>
#include "Zulassung.h"
#include <fstream>
#include <string>
#include <sstream>
#include <exception>

class Zulassungen
{
private:

    std::list <Zulassung> elemente; // Dies ist der STL-Container list, womit man nun aus der Klasse "Zulassung" eine verkettete Liste erstellen kann

public:

    Zulassungen() {}    // Default-Konstruktor

    /// Prototypen für alle Methoden
    void eingebenAnfang(Zulassung &newElement);
    void eingebenEnde(Zulassung &newElement);
    void ausgeben();
    void einlesenDatei();
    void ausgebenDatei();
    void sucheType(std::string &elementToSearch);
    void sucheCO(float elementToSearch);
    void deleteNachname(std::string &elementToSearch);
    void deleteFarbe(std::string &elementToSearch);

};


#endif // ZULASSUNGEN_H_INCLUDED
