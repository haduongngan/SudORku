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
            for (int m = 0; m < sizeOfMatrix - 1; m++) {
                vector<pos> tmp;
                block.push_back(tmp);
            }

            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    pos tmp(i, j);
                    block[color[i][j]].push_back(tmp);
                }
            }

            for (int m = 0; m < sizeOfMatrix - 1; m++) {
                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int y = 0; y < block[m].size(); y++) {
                        tmp += x[block[m][y].row][block[m][y].col][k];
                    }
                    model.add(tmp == 1);
                }
            }
            break;
        }

        case Killer :
        {

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
            int numOfBlock;
            input >> numOfBlock;
            for (int num = 1; num <= numOfBlock; num++){
                int sumOfBlock;
                input >> sumOfBlock;
                int sizeOfBlock;
                input >> sizeOfBlock;
                vector<pos> block;
                for (int i = 1; i <= sizeOfBlock; i++) {
                    int r,c;
                    input >> r >> c;
                    pos tmp(r, c);
                    block.push_back(tmp);
                }

                IloExpr tmpSum(env);

                for (int k = 1; k < sizeOfMatrix; k++) {
                    IloExpr tmp(env);
                    for (int y = 0; y < block.size(); y++){
                        tmp += x[block[y].row][block[y].col][k];
                    }
                    tmpSum += k*tmp;
                }
                model.add(tmpSum == sumOfBlock);
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
    IloNum tol = cplex.getParam(IloCplex::EpInt);
    cplex.setParam(IloCplex::Param::MIP::Pool::AbsGap, tol);
    cplex.setParam(IloCplex::Param::MIP::Pool::Intensity, 4);
    cplex.setParam(IloCplex::Param::MIP::Limits::Populate, 5);

    //cplex.exportModel("/Users/hatnho0708/Library/Preferences/CLion2019.3/scratches/model.lp");

    IloNum start;
    start = cplex.getTime();

    cplex.populate();
    output <<  ((cplex.getTime() - start < 0.001) ? 0.001 : (cplex.getTime() - start)) << endl;

        int numSol = cplex.getSolnPoolNsolns();
        output << numSol << endl << endl;

        for (int g = 0; g < numSol; g++){
            IloArray <IloArray<IloNumArray>> sol(env, sizeOfMatrix);
            for (int i = 0; i < sizeOfMatrix; i++) {
                sol[i] = IloArray<IloNumArray>(env, sizeOfMatrix);
                for (int j = 0; j < sizeOfMatrix; j++) {
                    sol[i][j] = IloNumArray(env);
                    cplex.getValues(sol[i][j], x[i][j], g);
                }
            }

            for (int i = 1; i < sizeOfMatrix; i++) {
                for (int j = 1; j < sizeOfMatrix; j++) {
                    for (int k = 1 ; k < sizeOfMatrix; k++) {
                        if (sol[i][j][k] >= 1 - tol) output << k << " ";
                    }
                }
                output << endl;
            }
            output << endl;
        }


    env.end();
    return 0;
}
