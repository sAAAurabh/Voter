#pragma once
#include <string>

struct Candidate
{
    std::string nid;
    std::string first;
    std::string last;
    std::string party;
    std::string salt;
    std::string hash;
    int votes;
    std::string dob;
    std::string gender;
    std::string photo_path;
<<<<<<< HEAD
    std::string manifesto;   // NEW
=======
    std::string party_symbol_path;
>>>>>>> 5094e62d2a962719f5a89bdc0c8262471357a2d8

    bool is_locked = false;
    int attempts_left = 5;
};