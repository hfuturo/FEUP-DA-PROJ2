#include <iostream>
#include <string>
#include <chrono>

#include "../include/UserInterface.h"
#include "../include/Graph.h"
#include "../include/constants.h"

//TODO: Preencher Read and Parse Dataset caso sejam real graphs
void UserInterface::showMenu() {
    Graph graph {};
    bool run = true;
    char userchoice;

    while (run) {
        std::cout << "\n\nMenu\n\n";
        std::cout << "(0) Read and Parse Dataset\n";
        std::cout << "(1) Backtracking Algorithm\n";
        std::cout << "(2) Approximation Algorithm\n";
        std::cout << "(3) Other Heuristics\n";
        std::cout << "(4) Compare efficiency\n";
        std::cout << "(Q) Quit\n\n";

        std::cout << "Select an option (you must Read and Parse a dataset first): ";
        std::cin >> userchoice;
        std::cout << std::endl;
        std::cin.ignore();

        switch (userchoice) {
            case 'q':
            case 'Q': run = false; break;

            case '0': {
                bool validInput = true;
                char userchoice2;
                std::string file;
                std::cout << "Select the type of graph you want to use\n\n";
                std::cout << "(1) Toy-Graphs\n";
                std::cout << "(2) Extra_Fully_Connected_Graphs\n";
                std::cout << "(3) Real_world Graphs\n\n";

                std::cout << "Insert the option number you want to select.\n";
                std::cin >> userchoice2;
                std::cout << std::endl;

                switch (userchoice2) {
                    case '1': {
                        std::cout << "Insert the name of the graph you want to use\n";
                        std::cout << "(shipping.csv | stadiums.csv | tourism.csv)\n\n";
                        std::cin.ignore();
                        while (true) {
                            std::cout << "Name: ";
                            std::getline(std::cin, file);
                            if (!file.empty() && (file == "shipping.csv" || file == "stadiums.csv" || file == "tourism.csv"))
                                break;
                            std::cout << "\nInvalid input.\n\n";
                        }
                        std::cout << "\nReading file...\n";
                        graph.fill(TOY_GRAPH + file, false);
                        break;
                    }

                    case '2': {
                        std::cout << "Insert the number of nodes you want to use\n";
                        std::cout << "(25 | 50 | 75 | 100 | 200 | 300 | 400 | 500 | 600 | 700 | 800 | 900)\n\n";
                        std::cin.ignore();
                        while (true) {
                            std::cout << "Number: ";
                            std::getline(std::cin, file);
                            if (!file.empty() && (file == "25" || file == "50" || file == "75" || file == "100" || file == "200" ||
                                file == "300" || file == "400" || file == "500" || file == "600" || file == "700" || file == "800"||
                                file == "900")) {
                                break;
                            }
                            std::cout << "\nInvalid input.\n\n";
                        }
                        std::cout << "\nReading file...\n";
                        graph.fill(EXTRA_FULLY_CONNECTED_GRAPHS + file + ".csv", false);
                        break;
                    }

                    case '3': {
                        std::cout << "Insert the graph you want to use\n";
                        std::cout << "(1 | 2 | 3)\n\n";
                        std::cin.ignore();
                        while (true) {
                            std::cout << "Graph: ";
                            std::getline(std::cin, file);
                            if (!file.empty() && (file == "1" || file == "2" || file == "3"))
                                break;
                            std::cout << "\nInvalid input.\n\n";
                        }
                        std::cout << "\nReading file...\n";
                        graph.fill(REAL_WORLD_GRAPHS + file, true);
                        break;
                    }

                    default: {
                        std::cout << "Invalid input.\n\n";
                        validInput = false;
                        break;
                    }
                }

                if (validInput) std::cout << "Done.\n";
                break;
            }

            case '1': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n";
                    break;
                }

                std::cout << "*** Backtracking Algorithm ***\n\n";

                std::vector<int> path;
                //double distance = graph.tspBF(path);
                graph.tspBT(path);

                bool first = true;
                for (auto& v : path) {
                    if (first) {
                        first = false;
                        std::cout << v;
                    }
                    else {
                        std::cout << " -> " << v;
                    }
                }
                std::cout << std::endl;
              //  std::cout << "Distance: " << distance << std::endl << std::endl;

                break;
            }

            case '2': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n";
                    break;
                }

                std::cout << "*** Approximation Algorithm ***\n\n";
                std::vector<Vertex*> path;
                double distance = graph.approximation(path);
                std::cout << "Path:\n\t";

                bool first = true;
                for (auto& v : path) {
                    if (first) {
                        first = false;
                        std::cout << v->getId();
                    }
                    else {
                        std::cout << " -> " << v->getId();
                    }
                }
                std::cout << std::endl;
                std::cout << "Distance: " << distance << std::endl << std::endl;
                break;
            }

            //TODO: IMPLEMENT
            case '3': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n";
                    break;
                }

                break;
            }

            case '4': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n";
                    break;
                }

                char userchoice2;
                std::cout << "*** Compare efficiency ***\n";
                std::cout << "Select which algorithms you want to compare\n\n";
                std::cout << "(1) All\n";
                std::cout << "(2) Backtracking && Approximation\n";
                std::cout << "(3) Backtracking && Other Heuristics\n";
                std::cout << "(4) Approximation && Other Heuristics\n";

                std::cin >> userchoice2;
                std::cout << std::endl;
                std::cin.ignore();

                std::vector<Vertex*> approximationPath;
                std::vector<int> backtrackingPath;

                switch (userchoice2) {
                    case '1': {
                        auto tStartB = std::chrono::high_resolution_clock::now();
                        graph.tspBF(backtrackingPath);
                        auto tEndBStartA = std::chrono::high_resolution_clock::now();
                        graph.approximation(approximationPath);
                        auto tEndA = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> time_b = tEndBStartA - tStartB;
                        std::chrono::duration<double, std::milli> time_a = tEndA - tEndBStartA;
                        std::cout << "Backtracking algorithm took " << time_b.count() << " milliseconds.\n";
                        std::cout << "Approximation algorithm took " << time_a.count() << " milliseconds.\n";
                        std::cout << "Approximation algorithm was " << time_b.count() - time_a.count() << " milliseconds faster, which is a "
                            << (time_b.count() - time_a.count()) * 100 / time_b.count() << "% improvement\n";
                        break;
                    }

                    case '2': {
                        auto tStartB = std::chrono::high_resolution_clock::now();
                        graph.tspBF(backtrackingPath);
                        auto tEndBStartA = std::chrono::high_resolution_clock::now();
                        graph.approximation(approximationPath);
                        auto tEndA = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> time_b = tEndBStartA - tStartB;
                        std::chrono::duration<double, std::milli> time_a = tEndA - tEndBStartA;
                        std::cout << "Backtracking algorithm took " << time_b.count() << " milliseconds.\n";
                        std::cout << "Approximation algorithm took " << time_a.count() << " milliseconds.\n";
                        std::cout << "Approximation algorithm was " << time_b.count() - time_a.count() << " milliseconds faster, which is a "
                                  << (time_b.count() - time_a.count()) * 100 / time_b.count() << "% improvement\n";
                        break;
                    }

                    //TODO: Implement time for other heuristics
                    case '3': {
                        auto tStartB = std::chrono::high_resolution_clock::now();
                        graph.tspBF(backtrackingPath);
                        auto tEndBStartOH = std::chrono::high_resolution_clock::now();
                        // TODO:: CHAMAR OTHER HEURISTICS FUNCTION
                        auto tEndOH = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> time_b = tEndBStartOH - tStartB;
                        std::chrono::duration<double, std::milli> time_oh = tEndOH - tEndBStartOH;
                        std::cout << "Backtracking algorithm took " << time_b.count() << " milliseconds.\n";
                        std::cout << "Other Heuristics algorithm took " << time_oh.count() << " milliseconds.\n";
                    }

                    //TODO: Implement time for other heuristics
                    case '4': {
                        auto tStartA = std::chrono::high_resolution_clock::now();
                        graph.approximation(approximationPath);
                        auto tEndAStartOH = std::chrono::high_resolution_clock::now();
                        //TODO: CHAMAR OTHER HEURISTICS FUNCTION
                        auto tEndOH = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> time_a = tEndAStartOH - tStartA;
                        std::chrono::duration<double, std::milli> time_oh = tEndOH - tEndAStartOH;
                        std::cout << "Approximation algorithm took " << time_a.count() << " milliseconds.\n";
                        std::cout << "Other Heuristics algorithm took " << time_oh.count() << " milliseconds.\n";
                    }
                }
                break;
            }

            default: {
                std::cout << "Invalid input\n\n";
            }

        }
        if (!run) break;
        std::cout << "\n\nPress a random key to continue\n";
        char filler;
        std::cin >> filler;
    }
}