//
// Created by Duong Ngan Ha on 25/07/2020.
//
#include <iostream>
#define IL_STD
#include <ilcplex/ilocplex.h>
#include <algorithm>
#include<fstream>
#include<vector>
#include <map>
using namespace std;
ILOSTLBEGIN

ifstream input("../input.txt");
ofstream output("../output.txt");


const int sizeOfMatrix = 10;

struct pos {
    int row;
    int col;
    pos (){

    }
    pos (int _r, int _c){
        row = _r;
        col = _c;
    }
};

enum typeOfSudoku {
    Classical = 1,
    Xsudoku,
    Windoku,
    Jigsaw,
    Killer,
};



void dfs(int i, int j, int** color, vector<pos>& sameBlock, bool** checkHide){
    for (int k = 1; k < 5; k++){
        if (k == 1) //east
        {
            if ((j + 1) < sizeOfMatrix && !checkHide[i][j + 1] && color[i][j] == color[i][j + 1]) {
                pos newPos(i, j + 1);
                sameBlock.push_back(newPos);
                checkHide[i][j + 1] = 1;
                dfs(i, j + 1, color, sameBlock, checkHide);
            }
        }
        else if (k == 2) //west
        {
            if ((j - 1) > 0 && !checkHide[i][j - 1] && color[i][j] == color[i][j - 1]) {
                pos newPos(i, j - 1);
                sameBlock.push_back(newPos);
                checkHide[i][j - 1] = 1;
                dfs(i, j - 1, color, sameBlock, checkHide);
            }
        }
        else if (k == 3) //South
        {
            if ((i + 1) < sizeOfMatrix && !checkHide[i + 1][j] && color[i][j] == color[i + 1][j]) {
                pos newPos(i + 1, j);
                sameBlock.push_back(newPos);
                checkHide[i + 1][j] = 1;
                dfs(i + 1, j, color, sameBlock, checkHide);
            }
        }
        else if (k == 4) //Nouth
        {
            if ((i - 1) > 0 && !checkHide[i - 1][j] && color[i][j] == color[i - 1][j]) {
                pos newPos(i - 1, j);
                sameBlock.push_back(newPos);
                checkHide[i - 1][j] = 1;
                dfs(i - 1, j, color, sameBlock, checkHide);
            }
        }
    }
}

int main(int argc, char** argv) {
    if (argc == 3) {
        input = ifstream(argv[1]);
        output = ofstream(argv[2]);
    }
    int type;
    input >> type;

    IloEnv env;
    IloModel model(env);
    //Variable
    IloArray <IloArray<IloNumVarArray>> x(env);
    for (int i1 = 0; i1 < sizeOfMatrix; i1++) {
        IloArray <IloNumVarArray> x1(env);
        for (int i2 = 0; i2 < sizeOfMatrix; i2++) {
            IloNumVarArray x2(env);
            for (int i3 = 0; i3 < sizeOfMatrix; i3++) {
                x2.add(IloNumVar(env, 0, 1, ILOINT));
            }
            x1.add(x2);
        }
        x.add(x1);
    }

    switch (type) {
        case Classical: {

            int inputNum[sizeOfMatrix][sizeOfMatrix];
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> inputNum[i][j];
                }
            }

            vector<pos> block;
            for (int i = 1; i < sizeOfMatrix; i += 3) {
                for (int j = 1; j < sizeOfMatrix; j += 3) {
                    pos tmp(i, j);
                    block.push_back(tmp);
                }
            }

            //(2)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    if (inputNum[i][j] != 0) {
                        model.add(x[i][j][inputNum[i][j]] == 1);
                    }
                }
            }

            //(3)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int k = 1; k < sizeOfMatrix; k++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(4)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int i = 1; i < sizeOfMatrix; i++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(5)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int i = 1; i < sizeOfMatrix; i++) {
                    IloExpr tmp(env);
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(6)
            //cout << block.size() << endl;
            for (int y = 0; y < block.size(); y++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int i = block[y].row; i < block[y].row + 3; i++) {
                        for (int j = block[y].col; j < block[y].col + 3; j++) {
                            tmp += x[i][j][k];
                        }
                    }
                    model.add(tmp == 1);
                }
            }

            break;
        }

        case Xsudoku :
        {

            int inputNum[sizeOfMatrix][sizeOfMatrix];
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> inputNum[i][j];
                }
            }

            vector<pos> block;
            for (int i = 1; i < sizeOfMatrix; i += 3) {
                for (int j = 1; j < sizeOfMatrix; j += 3) {
                    pos tmp(i, j);
                    block.push_back(tmp);
                }
            }

            //(2)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    if (inputNum[i][j] != 0) {
                        model.add(x[i][j][inputNum[i][j]] == 1);
                    }
                }
            }

            //(3)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int k = 1; k < sizeOfMatrix; k++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(4)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int i = 1; i < sizeOfMatrix; i++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(5)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int i = 1; i < sizeOfMatrix; i++) {
                    IloExpr tmp(env);
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(6)
            for (int y = 0; y < block.size(); y++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int i = block[y].row; i < block[y].row + 3; i++) {
                        for (int j = block[y].col; j < block[y].col + 3; j++) {
                            tmp += x[i][j][k];
                        }
                    }
                    model.add(tmp == 1);
                }
            }

            //main diagonal
            for (int k = 1; k < sizeOfMatrix; k++) {
                IloExpr tmp(env);
                for (int i = 1; i < sizeOfMatrix; i++) {
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        if (i == j) tmp += x[i][j][k];

                    }
                }
                model.add(tmp == 1);
            }

            //secondary diagonal
            for (int k = 1; k < sizeOfMatrix; k++) {
                IloExpr tmp(env);
                for (int i = 1; i < sizeOfMatrix; i++) {
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        if (i + j == sizeOfMatrix) tmp += x[i][j][k];

                    }
                }
                model.add(tmp == 1);
            }

            break;
        }

        case Windoku :
        {

            int inputNum[sizeOfMatrix][sizeOfMatrix];
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> inputNum[i][j];
                }
            }

            vector<pos> block;
            for (int i = 1; i < sizeOfMatrix; i += 3) {
                for (int j = 1; j < sizeOfMatrix; j += 3) {
                    pos tmp(i, j);
                    block.push_back(tmp);
                }
            }
            pos tmp1(2,2);
            pos tmp2(2,6);
            pos tmp3(6,2);
            pos tmp4(6,6);
            block.push_back(tmp1);
            block.push_back(tmp2);
            block.push_back(tmp3);
            block.push_back(tmp4);

            //(2)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    if (inputNum[i][j] != 0) {
                        model.add(x[i][j][inputNum[i][j]] == 1);
                    }
                }
            }

            //(3)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int k = 1; k < sizeOfMatrix; k++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(4)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int i = 1; i < sizeOfMatrix; i++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(5)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int i = 1; i < sizeOfMatrix; i++) {
                    IloExpr tmp(env);
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(6)
            for (int y = 0; y < block.size(); y++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int i = block[y].row; i < block[y].row + 3; i++) {
                        for (int j = block[y].col; j < block[y].col + 3; j++) {
                            tmp += x[i][j][k];
                        }
                    }
                    model.add(tmp == 1);
                }
            }

            break;
        }

        case Jigsaw : {

            int inputNum[sizeOfMatrix][sizeOfMatrix];
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> inputNum[i][j];
                }
            }

            //(2)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    if (inputNum[i][j] != 0) {
                        model.add(x[i][j][inputNum[i][j]] == 1);
                    }
                }
            }

            //(3)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int k = 1; k < sizeOfMatrix; k++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(4)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int i = 1; i < sizeOfMatrix; i++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(5)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int i = 1; i < sizeOfMatrix; i++) {
                    IloExpr tmp(env);
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //color block

            int color[sizeOfMatrix][sizeOfMatrix];
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> color[i][j];
                }
            }

            vector<vector<pos>> block;
            for (int m = 1; m < sizeOfMatrix; m++) {
                vector<pos> tmp;
                block.push_back(tmp);
            }

            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    pos tmp(i, j);
                    block[color[i][j]].push_back(tmp);
                    //cout << "block " << color[i][j] << " : " << i << " " << j << endl;
                }
            }

            for (int i = 0; i < block.size(); i++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int j = 0; j < block[i].size(); j++) {
                        tmp += x[block[i][j].row][block[i][j].col][k];
                    }
                    model.add(tmp == 1);
                }
            }
            break;
        }

        case Killer :
        {

            int inputNum[sizeOfMatrix][sizeOfMatrix];
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> inputNum[i][j];
                }
            }

            vector<pos> block;
            for (int i = 1; i < sizeOfMatrix; i += 3) {
                for (int j = 1; j < sizeOfMatrix; j += 3) {
                    pos tmp(i, j);
                    block.push_back(tmp);
                }
            }

            //(3)
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int k = 1; k < sizeOfMatrix; k++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(4)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    IloExpr tmp(env);
                    for (int i = 1; i < sizeOfMatrix; i++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(5)
            for (int k = 1; k < sizeOfMatrix; k++) {
                for (int i = 1; i < sizeOfMatrix; i++) {
                    IloExpr tmp(env);
                    for (int j = 1; j < sizeOfMatrix; j++) {
                        tmp += x[i][j][k];

                    }
                    model.add(tmp == 1);
                }
            }

            //(6)
            for (int y = 0; y < block.size(); y++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int i = block[y].row; i < block[y].row + 3; i++) {
                        for (int j = block[y].col; j < block[y].col + 3; j++) {
                            tmp += x[i][j][k];
                        }
                    }
                    model.add(tmp == 1);
                }
            }


            //color block
            int** color = new int*[sizeOfMatrix];
            for (int i = 0; i < sizeOfMatrix; i++){
                color[i] = new int[sizeOfMatrix];
            }
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    input >> color[i][j];
                }
            }

            bool** checkHide = new bool*[sizeOfMatrix];
            for (int i = 0; i < sizeOfMatrix; i++){
                checkHide[i] = new bool[sizeOfMatrix];
            }
            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    if (i*j == 0) checkHide[i][j] = 1;
                    else checkHide[i][j] = 0;
                }
            }

            for (int i = 1; i < sizeOfMatrix; i++){
                for (int j = 1; j < sizeOfMatrix; j++){
                    if (checkHide[i][j] == 0){
                        vector<pos> sameBlock;
                        pos now(i,j);
                        sameBlock.push_back(now);
                        checkHide[i][j] = 1;
                        dfs(i, j, color, sameBlock, checkHide);

                        IloExpr tmpSum(env);

                        for (int k = 1; k < sizeOfMatrix; k++) {
                            IloExpr tmp(env);
                            for (int y = 0; y < sameBlock.size(); y++){
                                tmp += x[sameBlock[y].row][sameBlock[y].col][k];
                            }
                            tmpSum += k*tmp;
                        }
                        model.add(tmpSum == inputNum[i][j]);
                    }
                }
            }
            break;
        }
    }

    for (int i = 0; i < sizeOfMatrix; i++) {
        for (int j = 0; j < sizeOfMatrix; j++) {
            for (int k = 0; k < sizeOfMatrix; k++) {
                if (i * j * k == 0) model.add(x[i][j][k] == 0);
            }
        }
    }

    IloExpr sum(env);
    for (int i = 1; i < sizeOfMatrix; i++) {
        for (int j = 1; j < sizeOfMatrix; j++) {
            for (int k = 1; k < sizeOfMatrix; k++) {
                sum += 0 * x[i][j][k];
            }
        }
    }

    model.add(IloMinimize(env, sum));
    IloCplex cplex(model);
    //cplex.exportModel("/Users/hatnho0708/Library/Preferences/CLion2019.3/scratches/model.lp");
    IloNum tol = cplex.getParam(IloCplex::EpInt);

    IloNum start;
    start = cplex.getTime();

    output <<  ((cplex.getTime() - start < 0.001) ? 0.001 : (cplex.getTime() - start)) << endl;
    if (cplex.solve()){
        IloArray <IloArray<IloNumArray>> sol(env, sizeOfMatrix);
        for (int i = 0; i < sizeOfMatrix; i++) {
            sol[i] = IloArray<IloNumArray>(env, sizeOfMatrix);
            for (int j = 0; j < sizeOfMatrix; j++) {
                sol[i][j] = IloNumArray(env);
                cplex.getValues(sol[i][j], x[i][j]);
            }
        }

        for (int i = 1; i < sizeOfMatrix; i++) {
            for (int j = 1; j < sizeOfMatrix; j++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    if (sol[i][j][k] >= 1 - tol) output << k << " ";
                }
            }
            output << endl;
        }
    }
    else output << "-1";





    env.end();
    return 0;
}

