#include<iostream>
using namespace std;
bool check = false;  // false -> 1 set, true -> 2 sets
template<class T>
class Relation
{
    private:T *set1,*set2;
            int **rel;
            int size1,size2;
    public: 
    Relation()
    {
        size1 = 0;
        size2 = 0;
        set1 = set2 = new T[1];
        rel = new int*[1];
        rel[0] = new int[1];
    }
    // Constructor for 1 set 
    Relation(int s)
    {
        size1 = s;
        size2 = 0;
        set1 = new T[s];
        set2 = new T[1];
        rel = new int*[s];
        for(int i=0; i<s; i++)
        rel[i] = new int[s];
        inputset();
    }
    // Constructor for 2 sets
    Relation(int s1, int s2)
    {
        size1 = s1;
        size2 = s2;
        set1 = new T[s1];
        set2 = new T[s2];
        rel = new int*[s1];
        for(int i=0; i<s1; i++)
        rel[i] = new int[s2];
        inputset();
    }
    void inputset()
    {
        int i=0;
        cout<<"\nEnter set1 elements: ";
        for(i=0; i<size1; i++)
        cin>>set1[i];
        if(check)
        {
            cout<<"\nEnter set2 elements: ";
            for(i=0; i<size2; i++)
            cin>>set2[i];
        }
        duplicate();
        displayset();
        inputrel();
        displayrel(rel);
        conditions();
        displayClosure();
    }
    void inputrel()
    {
        int i=0,j=0,s1=size1,s2=size2;
        if(!check)      //  means 1 set
        {
            s2 = s1;
        }
        cout<<"\nEnter relation as follows: ";
        for(i=0; i<s1; i++)
        {
            for(j=0; j<s2;j++)
            {
                if(!check)
                cout<<"\nIs ( "<<set1[i]<<","<<set1[j]<<" ) in relation?(1 or 0): ";
                else
                cout<<"\nIs ( "<<set1[i]<<","<<set2[j]<<" ) in relation?(1 or 0): ";
                cin>>rel[i][j];
                switch(rel[i][j])
                {
                    case 1: break;
                    case 0: break;
                    default:cout<<"\n INVALID RELATION ENTRY (EXITING)";
                            exit(0);
                }
            }
        }
    }
    void duplicate()
    {
       int i,j,k;
       for(i=0; i<size1; i++)
       {
           for(j=i+1; j<size1; )
           {
               if(set1[i]==set1[j])
               {
                    for(k=j; k<size1-1; k++)
                    {
                        set1[k] = set1[k+1];
                    }
                    size1--;
               }
               else
               {
                   j++;
               }    
           }
       }
       if(check)
       {
        for(i=0; i<size2; i++)
        {
            for(j=i+1; j<size2; )
            {
                if(set2[i]==set2[j])
                {
                    for(k=j; k<size2-1; k++)
                    {
                        set2[k] = set2[k+1];
                    }
                    size2--;
                }
                else
                {
                    j++;
                }    
            }
        }
       }

    }
    void displayset()
    {
        int i;
        cout<<"\nSet A = ";
        if(size1>0)
        {
            cout<<"{ ";
            for(i=0; i<size1; i++)
            {
                cout<<set1[i];
                if(i==size1-1)
                cout<<" }";

                else
                cout<<" , ";
            }
        }
        else
        cout<<"{ }";

        if(check)
        {
            cout<<"\nSet B = ";
            if(size2>0)
            {
                cout<<"{ ";
                for(i=0; i<size2; i++)
                {
                    cout<<set2[i];
                    if(i==size2-1)
                    cout<<" }";

                    else
                    cout<<" , ";
                }
            }
            else
            cout<<"{ }";
        }
    }
    void displayrel(int **rel)
    {
        // Matrix format of 0 and 1
        cout<<"\nRelation in matrix form: \n";
        int i,j,s1=size1,s2=size2,count=0;
        if(!check)
        {
            s2=s1;
        }
        for(i=0; i<s1; i++)
        {
            for(j=0; j<s2; j++)
            {
                cout<<rel[i][j]<<" ";
            }
            cout<<endl;
        }
        // Relation in set format
        cout<<"Relation in set form = { ";
        for(i=0; i<s1; i++)
        {
            for(j=0; j<s2; j++)
            {
                if(rel[i][j]==1)
                {
                    if(count!=0)
                    cout<<" , ";

                    if(!check)
                    cout<<" ( "<<set1[i]<<","<<set1[j]<<" )";
                    else
                    cout<<" ( "<<set1[i]<<","<<set2[j]<<" )";
                    count++;  
                }
            }
        }
        cout<<" }"<<endl;
    }
    bool reflexivity()
    {
        int i;
        bool flag = true;
        for(i=0; i<size1; i++)
        {
            if(rel[i][i]!=1)
            {
                flag=false;
                break;
            }
        }
        return flag;
    }
    bool symmetricity()
    {
        int i=0,j;
        bool flag = true;
        while(i<size1-1 && flag)
        {
            for(j=i+1; j<size1; j++)
            {
                if(rel[i][j]!=rel[j][i])
                {
                    flag = false;
                    break;
                }
            }
            i++;
        }
        return flag;
    }
    bool antisymmetricity()
    {
        int i=0,j;
        bool flag = true;
        while(i<size1-1 && flag)
        {
            for(j=i+1; j<size1; j++)
            {
                if((rel[i][j]==1)&&(rel[j][i]==1))
                {
                    if(set1[i]!=set1[j])
                    {
                        flag=false;
                        break;
                    }
                }
            }
            i++;
        }
        return flag;
    }
    bool transitivity()
    {
        int i=0,j,k;
        bool flag = true;
        while(i<size1 && flag)
        {
            j=i;
            while(j<size1 && flag)
            {
                if(rel[i][j]==1)
                {
                    for(k=0; k<size1; k++)
                    {
                        if(rel[j][k]==1)
                        {
                            if(rel[i][k]!=1)
                            {
                                flag = false;
                                break;
                            }
                        }
                    }
                }
                j++;
            }
            i++;
        }
        return flag;
    }
    void conditions()
    {
        if(reflexivity())
        cout<<"\nRelation is Reflexive";
        else
        cout<<"\nRelation is NOT Reflexive";

        if(symmetricity())
        cout<<"\nRelation is Symmetric";
        else
        cout<<"\nRelation is NOT Symmetric";

        if(antisymmetricity())
        cout<<"\nRelation is Anti-Symmetric";
        else        
        cout<<"\nRelation is NOT Anti-Symmetric";

        if(transitivity())
        cout<<"\nRelation is Transitive";
        else
        cout<<"\nRelation is NOT Transitive";

        if(equivalence())
        cout<<"\nRelation is Equivalence Relation";
        else
        cout<<"\nRelation is NOT Equivalence Relation";
        
        if(partiallyOrdered())
        cout<<"\nRelation is Partially Ordered Relation";
        else
        cout<<"\nRelation is NOT Partially Ordered Relation";
    }
    bool equivalence()
    {
        return (reflexivity() && symmetricity() && transitivity()); 
    }
    bool partiallyOrdered()
    {
        return (reflexivity() && antisymmetricity() && transitivity());
    }
    int** reflexiveClosure()
    {
        int i,j;
        int **reldash;              // new relation for closure
        reldash = new int*[size1];
        for(i=0; i<size1; i++)
        reldash[i] = new int[size1];

        for(i=0; i<size1; i++)
        {
            for(j=0; j<size1; j++)
            {
                if(i==j)        // diagonal elements
                {
                    reldash[i][j] = 1;
                }
                else
                {
                    reldash[i][j] = rel[i][j];      // non-diagonal elements 
                }
            } 
        }
        return reldash;
    }
    int **symmetricClosure()
    {
        int i,j;
        int **reldash;
        reldash = new int*[size1];
        for(i=0; i<size1; i++)
        reldash[i] = new int[size1];
        
        for(i=0; i<size1; i++)                  // copy rel into reldash
        {
            for(j=0; j<size1; j++)
            {
                reldash[i][j]=rel[i][j];
            }
        }
        for(i=0; i<size1-1; i++)                // do closure
        {
            for(j=i+1; j<size1; j++)
            {
                if((reldash[i][j]==1)||(reldash[j][i]==1))  // if either is = 1  
                {                                           // then both should be = 1
                    reldash[i][j]=reldash[j][i]=1;
                }
            }
        }
        return reldash;

    }
    int **transitiveClosure()
    {
        int i=0,j,temp,k;
        int **reldash;
        bool flag = true;
        reldash = new int*[size1];
        for(i=0; i<size1; i++)
        reldash[i] = new int[size1];

        for(i=0; i<size1; i++)                  // copy rel into reldash
        {
            for(j=0; j<size1; j++)
            {
                reldash[i][j]=rel[i][j];
            }
        }

        do
        {
            i=0;
            while(i<size1)
            {
                j=i;
                flag = true;
                while(j<size1)
                {
                    if(reldash[i][j]==1)
                    {
                        for(k=0; k<size1; k++)
                        {
                            if(reldash[j][k]==1)
                            {
                                reldash[i][k] = 1;  // ex- (1,3)=1,(3,2)=1 then make 1,2 = 1
                            }
                        }
                    }
                    j++;
                }
                i++;
            }
        }while(!flag);
        return reldash;
    }
    void displayClosure()
    {
        cout<<"\n\nReflexive Closure";
        displayrel(reflexiveClosure());
        cout<<"\n\nSymmetric Closure";
        displayrel(symmetricClosure());
        cout<<"\n\nTransitive Closure";
        displayrel(transitiveClosure());
    }
}; 
int main()
{
    int ans,size1,size2;
    cout<<"\nHow many sets you want to enter(1 or 2): ";
    cin>>ans;
    switch(ans)
    {
        case 1: {
                cout<<"\nEnter size of set: ";
                cin>>size1;
                Relation<int> r1(size1);
                break;
                }
        case 2: {
                cout<<"\nEnter size of set 1: ";
                cin>>size1;
                cout<<"\nEnter size of set 2: ";
                cin>>size2;
                check = true;
                Relation<int> r2(size1,size2);
                break;
                }   
        default: cout<<"\nInvalid entry!";
    }
    return 0;
}