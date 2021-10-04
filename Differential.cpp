#include <cryptominisat5/cryptominisat.h>
#include <assert.h>
#include <vector>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>

using std::vector;
using namespace CMSat;
using namespace std;

int BestWeightInteger = 11;
int BestWeightDecimal = 1;

int Constraint[55][12] = {
    {5, 5, 1, 5, 5, 1, 5, 5, 5, 5, 5, 1},
    {1, 5, 1, 1, 1, 0, 1, 0, 5, 5, 5, 5},
    {0, 1, 1, 5, 1, 1, 5, 1, 5, 5, 5, 5},
    {1, 5, 0, 1, 1, 1, 1, 0, 5, 5, 5, 5},
    {0, 1, 0, 1, 5, 0, 5, 1, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 1},
    {1, 5, 1, 1, 5, 1, 0, 1, 5, 5, 5, 5},
    {1, 5, 0, 5, 1, 0, 0, 1, 5, 5, 5, 5},
    {5, 1, 5, 5, 5, 0, 0, 0, 0, 5, 5, 5},
    {1, 1, 5, 1, 5, 5, 0, 0, 1, 5, 5, 5},
    {5, 5, 0, 5, 5, 0, 5, 5, 5, 5, 5, 1},
    {5, 0, 0, 5, 5, 5, 0, 1, 0, 5, 5, 5},
    {5, 1, 5, 1, 0, 5, 1, 1, 5, 5, 5, 5},
    {5, 0, 0, 0, 5, 5, 5, 5, 1, 5, 5, 5},
    {5, 0, 5, 0, 0, 5, 5, 5, 1, 5, 5, 5},
    {1, 0, 5, 5, 1, 5, 1, 1, 1, 5, 5, 5},
    {0, 1, 5, 1, 5, 5, 1, 1, 1, 5, 5, 5},
    {5, 5, 5, 0, 0, 5, 5, 0, 1, 5, 5, 5},
    {5, 1, 5, 5, 0, 5, 1, 1, 0, 5, 5, 0},
    {0, 1, 1, 0, 5, 5, 0, 5, 5, 5, 5, 5},
    {5, 0, 5, 5, 0, 0, 5, 0, 5, 5, 1, 5},
    {1, 5, 1, 5, 5, 5, 1, 1, 0, 5, 5, 5},
    {0, 5, 5, 0, 1, 5, 1, 1, 5, 5, 5, 5},
    {1, 1, 0, 5, 5, 5, 5, 1, 0, 5, 5, 5},
    {5, 5, 1, 0, 0, 0, 5, 5, 1, 5, 5, 5},
    {1, 5, 0, 0, 5, 5, 5, 1, 1, 5, 5, 5},
    {5, 5, 0, 0, 0, 1, 5, 5, 1, 5, 5, 5},
    {1, 5, 5, 5, 0, 1, 0, 1, 5, 5, 5, 5},
    {5, 5, 5, 5, 0, 5, 0, 0, 1, 5, 5, 5},
    {5, 0, 0, 5, 5, 5, 1, 0, 0, 5, 5, 5},
    {5, 1, 5, 5, 0, 1, 1, 0, 5, 5, 5, 5},
    {5, 5, 5, 5, 1, 5, 5, 0, 0, 5, 5, 5},
    {0, 1, 0, 0, 5, 5, 5, 0, 5, 5, 5, 5},
    {5, 0, 5, 0, 5, 5, 0, 0, 5, 5, 1, 5},
    {5, 5, 1, 5, 5, 5, 5, 0, 5, 0, 5, 5},
    {5, 5, 5, 5, 5, 1, 0, 5, 5, 0, 5, 5},
    {5, 5, 5, 1, 5, 0, 5, 0, 0, 5, 5, 5},
    {0, 1, 5, 5, 0, 1, 5, 0, 5, 5, 5, 5},
    {0, 5, 5, 5, 0, 0, 0, 1, 5, 5, 5, 5},
    {0, 0, 5, 5, 0, 5, 1, 1, 5, 5, 5, 5},
    {1, 5, 5, 5, 5, 5, 5, 5, 5, 0, 5, 5},
    {5, 0, 5, 1, 5, 5, 5, 5, 0, 5, 5, 5},
    {5, 5, 5, 5, 1, 5, 0, 5, 0, 5, 5, 5},
    {5, 5, 5, 1, 0, 5, 5, 1, 0, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 5, 5},
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 5, 1},
    {5, 5, 5, 5, 1, 5, 5, 5, 5, 0, 5, 5},
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 0, 5},
    {0, 1, 1, 1, 5, 1, 1, 5, 5, 5, 5, 5},
    {5, 0, 1, 1, 5, 0, 1, 0, 5, 5, 5, 5},
    {0, 0, 1, 1, 5, 0, 0, 1, 5, 5, 5, 5},
    {5, 0, 0, 5, 1, 1, 1, 0, 5, 5, 5, 5},
    {0, 0, 0, 5, 1, 1, 0, 1, 5, 5, 5, 5},
    {0, 1, 0, 5, 1, 0, 1, 5, 5, 5, 5, 5},
    {1, 1, 1, 0, 5, 5, 1, 5, 5, 5, 5, 5}
};

void GenerateLess(int * x, int ** u, int * vn, int * cn,
    SATSolver & solver, vector<Lit> & clause)
{
    int n=(*vn);
    int k=(*cn);

    if (k>0)
    {
        clause.clear();
        clause.push_back(Lit(x[0], true));
        clause.push_back(Lit(u[0][0],false));
        solver.add_clause(clause);

        for (int j=1;j<k;j++)
        {
            clause.clear();
            clause.push_back(Lit(u[0][j],true));
            solver.add_clause(clause);
        }
        for (int i=1;i<n-1;i++)
        {
            clause.clear();
            clause.push_back(Lit(x[i],true));
            clause.push_back(Lit(u[i][0],false));
            solver.add_clause(clause);

            clause.clear();
            clause.push_back(Lit(u[i-1][0],true));
            clause.push_back(Lit(u[i][0],false));
            solver.add_clause(clause);

            clause.clear();
            clause.push_back(Lit(x[i],true));
            clause.push_back(Lit(u[i-1][k-1],true));
            solver.add_clause(clause);
        }
        for (int j=1;j<k;j++)
        {
            for (int i=1;i<n-1;i++)
            {
                clause.clear();
                clause.push_back(Lit(x[i],true));
                clause.push_back(Lit(u[i-1][j-1],true));
                clause.push_back(Lit(u[i][j],false));
                solver.add_clause(clause);

                clause.clear();
                clause.push_back(Lit(u[i-1][j],true));
                clause.push_back(Lit(u[i][j],false));
                solver.add_clause(clause);
            }
        }

        clause.clear();
        clause.push_back(Lit(x[n-1],true));
        clause.push_back(Lit(u[n-2][k-1],true));
        solver.add_clause(clause);
    }
    if (k==0)
    {
        for (int i=0;i<n;i++)
        {
            clause.clear();
            clause.push_back(Lit(x[i], true));
            solver.add_clause(clause);
        }
    }
}

int main()
{
    int trailround = 4;
    int ** xin = new int * [trailround];
    int ** p = new int * [trailround];
    int ** q = new int * [trailround];
    int ** m = new int * [trailround];
    int ** w = new int * [trailround];
    int ** xout = new int * [trailround];
    
    for (int round = 0; round < trailround; round++)
    {
        xin[round] = new int [64];
        p[round] = new int [16];
        q[round] = new int [16];
        m[round] = new int [16];
        w[round] = new int [16];
        xout[round] = new int [64];
    }
    
    // Allocate variable
    int sx = 0;
    for (int round = 0; round < trailround; round++)
    {
        for (int i = 0; i < 64; i++)
        {
            xin[round][i] = sx++;
        }
        for (int i = 0; i < 16; i++)
        {
            p[round][i] = sx++;
        }
        for (int i = 0; i < 16; i++)
        {
            q[round][i] = sx++;
        }
        for (int i = 0; i < 16; i++)
        {
            m[round][i] = sx++;
        }
        for (int i = 0; i < 16; i++)
        {
            w[round][i] = sx++;
        }
    }
    
    for (int round = 0; round < trailround - 1; round++)
    {
        for (int i = 0; i < 64; i++)
        {
            xout[round][i] = xin[round + 1][i];
        }
    }
    for (int i = 0; i < 64; i++)
    {
        xout[trailround - 1][i] = sx++;
    }
    
    int TotalProb = 16 * trailround * 3;
    int Prob = BestWeightInteger;
    
    int DecimalTotalProb = 16 * trailround;
    int DecimalProb = BestWeightDecimal;
    
    int ** UP = new int * [TotalProb - 1];
    for (int i = 0; i < TotalProb - 1; i++)
    {
        UP[i] = new int [Prob];
    }
    for (int i = 0; i < TotalProb - 1; i++)
    {
        for (int j = 0; j < Prob; j++)
        {
            UP[i][j] = sx++;
        }
    }
    
    int ** DUP = new int * [DecimalTotalProb - 1];
    for (int i = 0; i < DecimalTotalProb - 1; i++)
    {
        DUP[i] = new int [DecimalProb];
    }
    for (int i = 0; i < DecimalTotalProb - 1; i++)
    {
        for (int j = 0; j < DecimalProb; j++)
        {
            DUP[i][j] = sx++;
        }
    }
    
    SATSolver solver;
    vector<Lit> clause;
    solver.set_num_threads(1);
    solver.new_vars(sx);
    
    // Nonzero Input Difference
    clause.clear();
    for (int i=0;i<64;i++)
    {
        clause.push_back(Lit(xin[0][i],false));
    }
    solver.add_clause(clause);
    
    for (int round = 0; round < trailround; round++)
    {
        int y[64];
        int P[64] = {48,1,18,35,32,49,2,19,16,33,50,3,0,17,34,51,
            52,5,22,39,36,53,6,23,20,37,54,7,4,21,38,55,
            56,9,26,43,40,57,10,27,24,41,58,11,8,25,42,59,
            60,13,30,47,44,61,14,31,28,45,62,15,12,29,46,63};
        for (int i = 0; i < 64; i++)
        {
            y[i] = xout[round][P[i]];
        }
        
        for (int sbox = 0; sbox < 16; sbox++)
        {
            int X[12];
            for (int i = 0; i < 4; i++)
            {
                X[i] = xin[round][4 * sbox + i];
                X[i + 4] = y[4 * sbox + i];
            }
            X[8] = p[round][sbox];
            X[9] = q[round][sbox];
            X[10] = m[round][sbox];
            X[11] = w[round][sbox];
            for (int restriction = 0; restriction < 55; restriction++)
            {
                clause.clear();
                for (int i = 0; i < 12; i++)
                {
                    if (Constraint[restriction][i] == 1)
                    {
                        clause.push_back(Lit(X[i], true));
                    }
                    if (Constraint[restriction][i] == 0)
                    {
                        clause.push_back(Lit(X[i], false));
                    }
                }
                solver.add_clause(clause);
            }
        }
    }
    
    int * AddProb = new int [TotalProb];
    for (int round = 0; round < trailround; round++)
    {
        for (int i = 0; i < 16; i++)
        {
            AddProb[48 * round + i] = p[round][i];
            AddProb[48 * round + i + 16] = q[round][i];
            AddProb[48 * round + i + 32] = m[round][i];
        }
    }
    
    int NumProb = TotalProb;
    int ConsProb = Prob;
    
    GenerateLess(AddProb, UP, &NumProb, &ConsProb, solver, clause);
    
    int * AddWeight = new int [DecimalTotalProb];
    for (int round = 0; round < trailround; round++)
    {
        for (int i = 0; i < 16; i++)
        {
            AddWeight[16 * round + i] = w[round][i];
        }
    }
    NumProb = DecimalTotalProb;
    ConsProb = DecimalProb;
    GenerateLess(AddWeight, DUP, &NumProb, &ConsProb, solver, clause);
    
    lbool ret = solver.solve();
    
    if (ret == l_True)
    {
        for (size_t round = 0; round < trailround; round++)
        {
            cout<<"Round: "<<(dec)<<round<<" ---------------------------- "<<"\n";
            int tem[64];
            cout<<"xin: "<<"\n";
            for (size_t i = 0; i < 64; i++)
            {
                if (solver.get_model()[xin[round][i]]!=l_Undef)
                {
                    if (solver.get_model()[xin[round][i]]==l_True)
                    {
                        tem[i]=1;
                    }
                    else
                    {
                        tem[i]=0;
                    }
                }
            }
            for (int sbox = 0; sbox < 16; sbox++)
            {
                int a = 0;
                for (int i = 0; i < 4; i++)
                {
                    a ^= (tem[4 * sbox + i] << (3 - i));
                }
                cout<<(hex)<<a<<",";
                if (((sbox + 1)%4) == 0)
                {
                    cout<<" ";
                }
            }
            cout<<"\n";
            
            cout<<"xout: "<<"\n";
            for (size_t i = 0; i < 64; i++)
            {
                if (solver.get_model()[xout[round][i]]!=l_Undef)
                {
                    if (solver.get_model()[xout[round][i]]==l_True)
                    {
                        tem[i]=1;
                    }
                    else
                    {
                        tem[i]=0;
                    }
                }
            }
            for (int sbox = 0; sbox < 16; sbox++)
            {
                int a = 0;
                for (int i = 0; i < 4; i++)
                {
                    a ^= (tem[4 * sbox + i] << (3 - i));
                }
                cout<<(hex)<<a<<",";
                if (((sbox + 1)%4) == 0)
                {
                    cout<<" ";
                }
            }
            cout<<"\n";
        }
    }
    
    for (int round = 0; round < trailround; round++)
    {
        delete [] xin[round];
        delete [] p[round];
        delete [] q[round];
        delete [] m[round];
        delete [] w[round];
        delete [] xout[round];
    }
    delete [] xin;
    delete [] p;
    delete [] q;
    delete [] m;
    delete [] w;
    delete [] xout;
    for (int i = 0; i < TotalProb - 1; i++)
    {
        delete [] UP[i];
    }
    delete [] UP;
    for (int i = 0; i < DecimalTotalProb - 1; i++)
    {
        delete [] DUP[i];
    }
    delete [] DUP;
    delete [] AddProb;
    delete [] AddWeight;
    return 0;
}
