#include "gameUtil.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <limits>
using namespace std;
int GameUtil::compute(Square* square, Player* player){
  // TODO: Part 1 debug
  double chi = player->getChi();
  double weight = player->getWeight();
  double teleporterEnergy = square->getTeleporterEnergy();
  double cannonPowder = square->getCannonPowder();

  double teleporterCompute = 0.;//add ., maybe not necessary
  for(double i = 1.0; i <=chi; i=i+1.0){ //i start from 1, because when i=0, the value inside sqrt will be 0
    teleporterCompute += sqrt(chi * i * teleporterEnergy);
  }
  teleporterCompute *= 1.0/(1.0 + chi);

  double cannonCompute = pow(pow(cannonPowder,1.7)/pow(weight,1.5) ,2)/9.8;

  return floor(std::max(cannonCompute >= teleporterCompute ? cannonCompute : teleporterCompute, 1.0)); //not sure whether should I use floor or not, but in my opinion, I should use it
}

bool GameUtil::isValidPath(std::vector<int>& path, Player* player, Game* game){
  // TODO: Part 2

  std::vector<Square*> gameboard;
  gameboard=game->getBoard();
  int num_board = gameboard.size();
  int num_path = path.size();  

  //First Check start point
  if (path[0]!=0)
     return false;

  //Then check the end point
  if (path[num_path-1] != (num_board-1)) //pay attention to -1
     return false;

  //Check each step
  //std::vector<Square*>::iterator itr = gameboard.begin();//It is not necessary to use iterator
  int max_distance;
  for (int i=0; i<num_path-1; i++){    //It is not necessary to check the last element in path, as it has already been checked
     //Before computing max_distance, you should make sure that path[i] is a valid ID -->Here is why I have the issue
     if (path[i] >= num_board || path[i]<0)
        return false;

     max_distance=compute(gameboard.at(path[i]), player);
     if (path[i+1]-path[i]>max_distance)
        return false;;
  }

  return true;
}

void RecursiveSearchShortest(int *numofsquares, std::vector<int>* maxstep, 
                                     int i, int* dist, int* shortdist){ //The purpose of using pointer is to avoid reallocating of memory for the same value in recursion
  // if (i > *numofsquares)//Maybe this is not necessary, can be removed to improve effenciency
  //    cout << "error, i is larger than numofsquares! " << endl;
  // else if (i == *numofsquares)//return if reach the last square
   if (i == *numofsquares)//return if reach the last square
   {
     if (*dist<*shortdist)
        *shortdist = *dist;
     *dist = *dist-1; //I made mistake here
     return;
   }
   else
   {
     for (int j=maxstep->at(i); j > 0; j--)//go through all possible valid step----fuck, I made a mistake here, in the wrong code, it is j>=0, stupid...
     {
        int k = i + j;
        if (k<=*numofsquares)
        {
           *dist= *dist + 1; //take a step, dist plus one
           if (*dist < *shortdist) //it is not necessary to continue searching if dist is already larger than or equal to shortdist
              RecursiveSearchShortest(numofsquares, maxstep, k, dist, shortdist); //recursively call
           else
           {
              *dist = *dist - 2; //Why -2, first -1 to keep *dist unchanged, then -1 to return to the direct up recursion
              return;
           }
           //return; //I made a mistake here
        }//end of if

     }//end of for loop
     *dist = *dist - 1; //Go to the direct up level of recursion
     return;
   }//end of else
}
int GameUtil::shortestPathDistance(Game* game, Player* player){
  // TODO: Part 3
  std::vector<Square*> gameboard;
  gameboard=game->getBoard();
  int numofsquares = gameboard.size()-1; //sorry, the name is misleading....haha!

  //compute maxstep, the purpose of computing maxstep is to avoid repeat computing, any way to improve efficiency
  int i;
  int temp_max;
  std::vector<int> maxstep;
  for (i=0; i<=numofsquares; i++) //pay attention to the exact meaning of numofsquares
  {
      temp_max=compute(gameboard[i], player);
      maxstep.push_back(temp_max);
  }
  
  //search for the shortest distance
  int shortest = std::numeric_limits<int>::max(); //Hope fully this is large enough
  int dist = 0; //should be intialized
  i = 0; //start from first square
  RecursiveSearchShortest(&numofsquares, &maxstep, //I need double check to make sure whether vector name is reference or pointer
                                     i, &dist, &shortest);
 
  return shortest;
}
