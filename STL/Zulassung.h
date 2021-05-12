#ifndef ZULASSUNG_H_INCLUDED
#define ZULASSUNG_H_INCLUDED

/// Sebastian Arnauer 24.03.2021
/// Diese Klasse ist dazu da, um alle Eigenschaften herzustellen

class Zulassung
{
private:

    /// Alle Eigenschaften der Verkettete-Liste Aufgabe
    std::string nachname;
    std::string marke;
    std::string type;
    std::string farbe;
    float co;
    int hubraum;

public:

    Zulassung() // Default-Konstruktor
    {
        nachname="test";
        marke="test";
        type="test";
        farbe="test";
        co=69420;
        hubraum=69420;
    }
    Zulassung(std::string &nachname, std::string &marke, std::string &type, std::string &farbe, float co, int hubraum)
    {
        this->nachname=nachname;
        this->marke=marke;
        this->type=type;
        this->farbe=farbe;
        this->co=co;
        this->hubraum=hubraum;
    }

    /// Set-Methoden /////////////////
    void setNachname(std::string &nachname)
    {
        this->nachname=nachname;
    }
    void setMarke(std::string &marke)
    {
        this->marke=marke;
    }
    void setType(std::string &type)
    {
        this->type=type;
    }
    void setFarbe(std::string &farbe)
    {
        this->farbe=farbe;
    }
    void setCO(float co)
    {
        this->co=co;
    }
    void setHubraum(int hubraum)
    {
        this->hubraum=hubraum;
    }

    /// Get-Methoden ////////////
    std::string getNachname()
    {
        return nachname;
    }
    std::string getMarke()
    {
        return marke;
    }
    std::string getType()
    {
        return type;
    }
    std::string getFarbe()
    {
        return farbe;
    }
    float getCO()
    {
        return co;
    }
    int getHubraum()
    {
        return hubraum;
    }
};

#endif // ZULASSUNG_H_INCLUDED
