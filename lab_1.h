#ifndef LAB_1_H
#define LAB_1_H

#include "Commands/arrCommands.h"
#include "Commands/stackCommands.h"
#include "Commands/queueCommands.h"
#include "Commands/listCommands.h"
#include "Commands/hashCommands.h"
#include "Commands/treeCommands.h"
#include "Structures/Pair.h"
#include "Structures/arr.h"

#include <iostream>
#include <string>

using namespace std;



structures getType(const string& fName);


string delFirstLetter(const string &input);

structures structRequest(const char& input);
commands commandRequest(const string& request);
request getRequest(int argc, char *argv[]);

#endif