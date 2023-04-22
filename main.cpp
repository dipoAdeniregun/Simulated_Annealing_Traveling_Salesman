#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#define _USE_MATH_DEFINES
#include <math.h>


struct Coord_t{
    double x {};
    double y {};
};

double energyFunction(const std::vector<Coord_t> &states){
    /*
        calculate the energy of a state
    */
   int length = states.size();
   double energy = 0.0;

   for(int i = 0; i < length -1; i++){
        energy +=  sqrt(pow((states[i].x - states[i+1].x), 2.0) + pow((states[i].y - states[i+1].y), 2.0));
   }
   energy += sqrt(pow((states[length-1].x - states[0].x), 2.0) + pow((states[length -1].y - states[1].y), 2.0));
    return energy;
}

void neighbourFunction(const std::vector<Coord_t>& state, std::vector<Coord_t>& neighbour){
    /*
        Calculate a neighbour state by randomly flipping any two random
        entries in the state
    */
   int error = 0;
   int length = state.size();

   neighbour = state;

   int index1 = rand()% (length);
   int index2;

   if (length == 1)
   {
        return;
   }


   do
   {
    index2 = rand()% (length);
   } while (index2 == index1);

   Coord_t temp = neighbour[index1];
   neighbour[index1] = neighbour[index2];
   neighbour[index2] = temp;
}

void travelingSalesmanSA(const std::vector<Coord_t>& cities, double (*energyFunction)(const std::vector<Coord_t>&), void (*neighbourFunction)(const std::vector<Coord_t>&, std::vector<Coord_t>&), int maxiter, int innermaxiter){
    int currIter = 0;
    int cooling = 100;
    double deltaE;
    double probTransitionAcceptance;
    double chance;
    
    std::vector<Coord_t> state = cities;
    double stateE = energyFunction(cities);
    int length = cities.size();

    std::vector<Coord_t> neighbour = state;
    double neighbourE = stateE;

    std::vector<Coord_t> bestState = state;
    double bestStateE = stateE;

    std::vector<double> bestEHistory(maxiter);
    std::vector<double> EHistory(maxiter);

    while (currIter < maxiter)
    {
        currIter++;

        //inner iterations helps keep c constant for innermaxiter times
        //before cooling c
        for(int i = 0; i < innermaxiter; i++){
            neighbourFunction(state, neighbour);
            neighbourE = energyFunction(neighbour);

            if(neighbourE < stateE){
                state = neighbour;
                stateE = neighbourE;
            }

            else{
                deltaE = neighbourE - stateE;
                probTransitionAcceptance = pow(M_E, (-deltaE/cooling));
                chance = (double) (rand())/(double) (RAND_MAX);

                if(chance < probTransitionAcceptance){
                    state = neighbour;
                    stateE = neighbourE;
                }
            }

            if (stateE < bestStateE)
            {
                bestStateE = stateE;
                bestState = state;
            }
        }

        bestEHistory[currIter-1] = bestStateE;
        EHistory[currIter-1] = stateE;
        
        cooling = 0.9*cooling; //simple cooling function

        std::cout << "Outer Iteration: " << currIter << " Energy: " << stateE << std::endl;
    }
    
}

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Wrong Usage! Pass number of cities in problem as command line argument.\n";
        return 1;
    }

    srand (static_cast <unsigned> (time(0)));

    int n = atoi(argv[1]);
    std::cout << "Now using simulated annealing to solve the traveling salesman problem for " << n << " cities.\n";

    std::vector <Coord_t> cities(n);

    //initialize mock data for all our cities
    for(int i = 0; i < n; i++){
        cities[i].x = (double) (rand()) / (double) (RAND_MAX);
        cities[i].y = (double) (rand()) / (double) (RAND_MAX);
    }

    // double energy = energyFunction(cities);
    // std::vector<Coord_t> neighbour(n);
    // neighbourFunction(cities, neighbour);
    // double neighbourE = energyFunction(neighbour);

    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << "x: " << cities[i].x << " y: " << cities[i].y << std::endl;
    // }
    // std::cout << "State has an energy of: " << energy << std::endl;

    // std::cout << "\nFor the neighbour: \n";
    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << "x: " << neighbour[i].x << " y: " << neighbour[i].y << std::endl;
    // }
    // std::cout << "Neighbour has an energy of: " << neighbourE << std::endl;

    int maxiter = 300;
    int innermaxiter = 1000;

    travelingSalesmanSA(cities, energyFunction, neighbourFunction, maxiter, innermaxiter);

}