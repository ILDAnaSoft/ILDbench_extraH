#pragma once
#ifndef FUNCTION_CALC_H
#define FUNCTION_CALC_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

#include "Lib/MessageFormat.h" 

float Get_Significance(float sig, float bkg);

float Get_Efficiency(float current, float origin);

#endif
