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
    std::string manifesto;   // NEW

    bool is_locked = false;
    int attempts_left = 5;
};