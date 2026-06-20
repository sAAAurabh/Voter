#pragma once
#include <string>
#include "voting_page.h"

struct Voter
{
    std::string nid;
    std::string first;
    std::string last;
    std::string salt;
    std::string hash;
    std::string dob;
    std::string gender;
    std::string photo_path;

    bool has_voted = false;
    bool is_locked = false;
    int attempts_left = 5;



};