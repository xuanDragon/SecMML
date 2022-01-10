/*
 * @Author: Xinyu Tu
 * @Date: 2021-12-07 10:04:24
 * @LastEditors: Xinyu Tu
 * @LastEditTime: 2021-12-28 16:41:22
 */

#include <cstdio>
#include <fstream>
#include "json/json.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include "../util/SocketManager.h"
#include "../core/Player.h"
#include "../util/IOManager.h"
#include "../machine_learning/BPGraph.h"
#include <typeinfo>
// #include "../machine_learning/LSTMGraph.h"
using namespace std;

int main(int argc, char **argv)
{
    cout << "begin" << endl;
    Config::config = Config::init("../config/parameter/constant.json");
    cout << Config::config->B << endl;
    cout << Config::config->SQRTINV << endl;
    cout << Config::config->INV2 << endl;
    cout << Config::config->LOCAL_TEST << endl;
    DBGtest = 0;
    if (argc < 2)
    {
        DBGprint("Please enter party index:\n");
        scanf("%d", &node_type);
    }
    else
    {
        node_type = argv[1][0] - '0';
    }
    DBGprint("party index: %d\n", node_type);

    Player::init();

    SocketManager::SMMLF tel;
    if (Config::config->LOCAL_TEST)
    {
        tel.init(Config::config->IP, Config::config->PORT);
    }
    else
    {
        tel.init();
    }

    IOManager::init();
    // IOManager::train_data.print_part();
    // IOManager::test_data.print_part();
    // IOManager::train_label.print_part();
    // IOManager::test_label.print_part();
    BPGraph::LR *bp = new BPGraph::LR(&IOManager::train_data, &IOManager::train_label, &IOManager::test_data, &IOManager::test_label);

    if (Config::config->LOGISTIC == 1)
    {
        bp->logistic_graph();
    }
    else if (Config::config->LINEAR == 1)
    {
        bp->linear_graph();
    }
    bp->train();
    return 0;
}