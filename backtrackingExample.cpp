#include <iostream>
#include <list>
#include <unordered_set>
using namespace std;

list<int> SolveMazeBackTrackIter(list<int> maze[], int start, int finish)
{
    unordered_set<int> visited;
    
    //current path we are exploring
    list<int> path;

    //start of path is just the start
    path.push_back(start);
    int currentPoint = start;

    //currentlt visiting this spot
    visited.insert(currentPoint);

    //while we have move spots to explore, keep looking for finish
    while (path.back() != finish && path.empty() == false)
    {
        list<int>::iterator iter = maze[currentPoint].begin();
        bool foundNextMove = false;

        //look for next move
        while ((iter != maze[currentPoint].end()) && (!foundNextMove))
        {
            //found somewhere to move to
            if (visited.count(*iter) == 0)
            {
                foundNextMove = true;
            }
            else
            {
                iter++;
            }
        }

        //found somewhere to move to
        if (foundNextMove)
        {
            //add spot to path
            path.push_back(*iter);
            visited.insert(*iter);
        }
        else
        {
            //no where to go from this spot. BACKTRACK
            path.pop_back();
        }

        currentPoint = path.back();
    }
    return path;
}

bool solveMazeRecursion(list<int> maze[], int start, int finish, unordered_set<int>& visited, list<int>& path)
{
    //we found the exit return
    if (start == finish)
    {
        path.push_front(start);
        return true;
    }

    //add the current spot to the visited list
    visited.insert(start);

    //look at the spots we can reach from this one
    list<int>::iterator iter = maze[start].begin();
    while (iter != maze[start].end())
    {
        //if we haven't already visited 
        if (visited.count(*iter) == 0)
        {
            //visited the spot we can reach
            if (solveMazeRecursion(maze, *iter, finish, visited, path))
            {
                //found the end
                path.push_front(start);
                return true;
            }
        }
        iter++;
    }
    
    //no where to go from this spot. BACKTRACK
    return false;
}

int main()
{
    list<int> maze[9];

    //Another way to represent a maze/map, marking where each spot can reach

    // 0 can reach 1 and 3
    maze[0].push_back(1);
    maze[0].push_back(3);

    // 1 can reach 0 and 2
    maze[1].push_back(0);
    maze[1].push_back(2);

    maze[2].push_back(1);

    maze[3].push_back(0);
    maze[3].push_back(4);
    maze[3].push_back(6);

    maze[4].push_back(3);
    maze[4].push_back(5);
    maze[4].push_back(7);

    maze[5].push_back(4);

    maze[6].push_back(3);

    maze[7].push_back(4);
    maze[7].push_back(8);

    maze[8].push_back(7);

     /*
        __________
         0  1  2 |
        |   _____|
        |3  4  5 |
        |6 |7  8 
        ----------
     */

    //running backtrack without recursion 
    list<int> solutionPath = SolveMazeBackTrackIter(maze, 0, 8);

    //iterator is just like a "pointer" that allows you to access
    //the values in the list, you CANNOT access element in a list with '[]' 
    //so an iterator can be used like a pointer to access elements.
    list<int>::iterator iter;

    cout << "Path for non-recursive solution: \n";
    for (iter = solutionPath.begin(); iter != solutionPath.end(); iter++)
    {
        cout << *iter << endl;
    }

    //running backtrack with recursion
    unordered_set<int> visited;
    list<int> solutionPathRec;
    solveMazeRecursion(maze, 0, 8, visited, solutionPathRec);

    cout << "Path for recursive solution: \n";
    for (iter = solutionPathRec.begin(); iter != solutionPathRec.end(); iter++)
    {
        cout << *iter << endl;
    }
}