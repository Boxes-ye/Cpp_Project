#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <memory>
#include <fstream>
#include <sstream> //字符串流
#include <algorithm>
#include "staff.h"
#define FILENAME "comFile.txt"

class WorkManger
{
public:
        int m_Staffnum;
        std::vector<std::unique_ptr<Staff>> m_staff;
        bool isEmpty;

public:
        WorkManger();
        ~WorkManger();
        void Show_Menu();
        void Exit_Menu();
        // void test01();
        // void test02();
        void Add_Staff();
        void Load_Staff();
        void Del_Staff();
        void Mod_Staff();
        void Find_Staff();
        void Sort_Staff();
        void Clear_File();
};

int Randomint(int min, int max);