#include "admin.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <string>
#include "picosh.h"
#include <QDebug>
#include "database.h"
#include <QDate>


using namespace std;

// generates salt
string Admin::gen_salt()
{
    string chars = "abcdefghijklmnopqrstuvwxyz0123456789";
    string salt;

    for(int i = 0; i < 6; i++)
        salt += chars[rand() % chars.size()];

    return salt;
}


// hashes salt + password
string Admin::hash_pass(const string& pass, const string& salt)
{
    return picosha2::hash256_hex_string(salt + pass);
}


// finds voter
bool Admin::find_voter(const string& nid, Voter& v)
{
    {
        QSqlQuery q;
        q.prepare("SELECT * FROM voters WHERE nid=?");
        q.addBindValue(QString::fromStdString(nid));

        if (!q.exec() || !q.next())
            return false;

        v.nid = q.value("nid").toString().toStdString();
        v.first = q.value("first").toString().toStdString();
        v.last = q.value("last").toString().toStdString();
        v.dob = q.value("dob").toString().toStdString();
        v.gender = q.value("gender").toString().toStdString();
        v.photo_path = q.value("photo_path").toString().toStdString();
        v.hash = q.value("password_hash").toString().toStdString();
        v.salt = q.value("salt").toString().toStdString();
        v.has_voted = q.value("has_voted").toInt();
        v.is_locked = q.value("is_locked").toInt();
        v.attempts_left = q.value("attempts_left").toInt();
    }
    return true;
}


// finds candidate
bool Admin::find_candidate(const std::string& nid, Candidate& c)
{   {
        QSqlQuery q(Database::db);

        q.prepare("SELECT * FROM candidates WHERE nid=?");
        q.addBindValue(QString::fromStdString(nid));

        if (!q.exec() || !q.next())
            return false;

        c.nid = q.value("nid").toString().toStdString();
        c.first = q.value("first").toString().toStdString();
        c.last = q.value("last").toString().toStdString();
        c.dob = q.value("dob").toString().toStdString();
        c.gender = q.value("gender").toString().toStdString();
        c.photo_path = q.value("photo_path").toString().toStdString();
        c.party_symbol_path = q.value("party_symbol_path").toString().toStdString();
        c.hash = q.value("password_hash").toString().toStdString();
        c.salt = q.value("salt").toString().toStdString();
        c.votes = q.value("votes").toInt();
        c.is_locked = q.value("is_locked").toInt();
        c.attempts_left = q.value("attempts_left").toInt();
        c.party = q.value("party").toString().toStdString();
        c.manifesto = q.value("manifesto").toString().toStdString();

    }

    return true;
}


// add voter
void Admin::add_voter(const Voter& v)
{   {
        QSqlQuery q;

        q.prepare(
            "INSERT INTO voters "
            "(nid, first, last, dob, gender, password_hash, salt, photo_path, has_voted, is_locked, attempts_left) "
            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
            );

        q.addBindValue(QString::fromStdString(v.nid));
        q.addBindValue(QString::fromStdString(v.first));
        q.addBindValue(QString::fromStdString(v.last));
        q.addBindValue(QString::fromStdString(v.dob));
        q.addBindValue(QString::fromStdString(v.gender));
        q.addBindValue(QString::fromStdString(v.hash));
        q.addBindValue(QString::fromStdString(v.salt));
        q.addBindValue(QString::fromStdString(v.photo_path));
        q.addBindValue(0);   // has_voted
        q.addBindValue(0);   // is_locked
        q.addBindValue(5);   // attempts_left

        if (!q.exec()) {
            qDebug() << "add_voter failed:" << q.lastError().text();
            return;
        }
    }
}


// add candidate
void Admin::add_candidate(const Candidate& c)
{

    {
    QSqlQuery q(Database::db);
    q.prepare(
        "INSERT INTO candidates "
        "(nid, first, last, party, dob, gender, password_hash, salt, photo_path, party_symbol_path, votes, is_locked, attempts_left) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
        );

    q.addBindValue(QString::fromStdString(c.nid));
    q.addBindValue(QString::fromStdString(c.first));
    q.addBindValue(QString::fromStdString(c.last));
    q.addBindValue(QString::fromStdString(c.party));
    q.addBindValue(QString::fromStdString(c.dob));
    q.addBindValue(QString::fromStdString(c.gender));
    q.addBindValue(QString::fromStdString(c.hash));
    q.addBindValue(QString::fromStdString(c.salt));
    q.addBindValue(QString::fromStdString(c.photo_path));
    q.addBindValue(QString::fromStdString(c.party_symbol_path));
    q.addBindValue(0); // votes
    q.addBindValue(0); // islocked
    q.addBindValue(5); // attempts_left


        if (!q.exec()) {
            qDebug() << "add_candidate failed:" << q.lastError().text();
            return;
        }
    }
}


// updates voter
void Admin::update_voter(const Voter& v)
{   {
        QSqlQuery q;

        q.prepare(
            "UPDATE voters SET "
            "first = ?, "
            "last = ?, "
            "salt = ?, "
            "password_hash = ?, "
            "dob = ?, "
            "gender = ?, "
            "photo_path = ?, "
            "has_voted = ?, "
            "is_locked = ?, "
            "attempts_left = ? "
            "WHERE nid = ?"
            );

        q.addBindValue(QString::fromStdString(v.first));
        q.addBindValue(QString::fromStdString(v.last));
        q.addBindValue(QString::fromStdString(v.salt));
        q.addBindValue(QString::fromStdString(v.hash));
        q.addBindValue(QString::fromStdString(v.dob));
        q.addBindValue(QString::fromStdString(v.gender));
        q.addBindValue(QString::fromStdString(v.photo_path));
        q.addBindValue(v.has_voted ? 1 : 0);
        q.addBindValue(v.is_locked ? 1 : 0);
        q.addBindValue(v.attempts_left);
        q.addBindValue(QString::fromStdString(v.nid));

        if (!q.exec()) {
            qDebug() << "update_voter failed:" << q.lastError().text();
        }
    }
}


// updates candidate
void Admin::update_candidate(const Candidate& c)
{   {
        QSqlQuery q;
        q.prepare(
            "UPDATE candidates SET "
            "first = ?, "
            "last = ?, "
            "salt = ?, "
            "password_hash = ?, "
            "dob = ?, "
            "gender = ?, "
            "photo_path = ?, "
            "party_symbol_path = ?, "
            "party = ?, "
            "votes = ?, "
            "is_locked = ?, "
            "attempts_left = ? "
            "manifesto = ?"
            "WHERE nid = ?"
            );

        q.addBindValue(QString::fromStdString(c.first));
        q.addBindValue(QString::fromStdString(c.last));
        q.addBindValue(QString::fromStdString(c.salt));
        q.addBindValue(QString::fromStdString(c.hash));
        q.addBindValue(QString::fromStdString(c.dob));
        q.addBindValue(QString::fromStdString(c.gender));
        q.addBindValue(QString::fromStdString(c.photo_path));
        q.addBindValue(QString::fromStdString(c.party_symbol_path));
        q.addBindValue(QString::fromStdString(c.party));
        q.addBindValue(c.votes);
        q.addBindValue(c.is_locked ? 1 : 0);
        q.addBindValue(c.attempts_left);
        q.addBindValue(QString::fromStdString(c.manifesto));


        if (!q.exec()) {
            qDebug() << "update_candidate failed:" << q.lastError().text();
        }
    }
}


// login voter
login_result Admin::login_voter(const std::string& nid, const std::string& pass)
{
    Voter v;

    if (!find_voter(nid, v))
        return not_found;

    if (v.is_locked)
        return acc_locked;

    std::string computed = hash_pass(pass, v.salt);

    if (computed == v.hash)
    {
        update_voter(v);
        return login_success;
    }

    if (v.attempts_left > 0)
        v.attempts_left--;

    if (v.attempts_left <= 0)
    {
        v.attempts_left = 0;
        v.is_locked = true;
        update_voter(v);
        return acc_locked;
    }

    update_voter(v);
    return wrong_pass;
}


// login candidate
login_result Admin::login_candidate(const std::string& nid, const std::string& pass)
{
    Candidate c;

    if (!find_candidate(nid, c))
        return not_found;

    if (c.is_locked)
        return acc_locked;

    if (hash_pass(pass, c.salt) == c.hash)
    {
        c.attempts_left = 5;
        update_candidate(c);
        return login_success;
    }

    c.attempts_left--;

    if (c.attempts_left <= 0)
    {
        c.is_locked = true;
        update_candidate(c);
        return acc_locked;
    }

    update_candidate(c);
    return wrong_pass;
}


// validates password
pass_val Admin::is_valid_pass(const string pass, string nm)
{
    {
        if (pass.length() < 7)
            return letter;

        int digits = 0;
        bool has_special = false;
        bool has_capital = false;

        for (unsigned char c : pass)
        {
            if (isdigit(c))
                digits++;
            else if (isupper(c))
                has_capital = true;
            else if (!isalnum(c))
                has_special = true;
        }

        if (pass == nm)
            return name;

        if (digits < 3)
            return number;

        if (!has_special)
            return special;

        if (!has_capital)
            return capital;

        return is_valid;
    }
}

// calculate age
string Admin::calculate_age(const std::string& dob)
{
    QString dob_string = QString::fromStdString(dob);

    QDate birth_date = QDate::fromString(dob_string, "dd/MM/yyyy");


    QDate today = QDate::currentDate();

    int age = today.year() - birth_date.year();


    if (today.month() < birth_date.month() ||
        (today.month() == birth_date.month() &&
         today.day() < birth_date.day()))
    {
        age--;
    }

    return to_string(age);
}



// calculate age



// get manifesto for a specific candidate
std::string Admin::get_manifesto(const std::string& nid)
{
    Candidate c;
    if (find_candidate(nid, c))
        return c.manifesto;
    return "";
}


// update manifesto for a candidate
void Admin::update_manifesto(const std::string& nid, const std::string& manifesto)
{
    QSqlQuery q;
    q.prepare("UPDATE candidates SET manifesto=? WHERE nid=?");
    q.addBindValue(QString::fromStdString(manifesto));
    q.addBindValue(QString::fromStdString(nid));
    q.exec();
}


// get all candidates from database
std::vector<Candidate> Admin::get_all_candidates()
{
    std::vector<Candidate> candidates;
    QSqlQuery q;
    if (!q.exec("SELECT * FROM candidates"))
        return candidates;

    while (q.next()) {
        Candidate c;
        c.nid           = q.value("nid").toString().toStdString();
        c.first         = q.value("first").toString().toStdString();
        c.last          = q.value("last").toString().toStdString();
        c.party         = q.value("party").toString().toStdString();
        c.dob           = q.value("dob").toString().toStdString();
        c.gender        = q.value("gender").toString().toStdString();
        c.photo_path    = q.value("photo_path").toString().toStdString();
        c.party_symbol_path = q.value("party_symbol_path").toString().toStdString();
        c.votes         = q.value("votes").toInt();
        c.is_locked     = q.value("is_locked").toInt();
        c.attempts_left = q.value("attempts_left").toInt();
        c.manifesto     = q.value("manifesto").toString().toStdString();
        candidates.push_back(c);
    }
    return candidates;
}