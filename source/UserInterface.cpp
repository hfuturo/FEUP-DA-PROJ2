#include <iostream>
#include <string>

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
        std::cout << "(4) Compare efficiency\n\n";

        std::cout << "Select an option (you must Read and Parse a dataset first): ";
        std::cin >> userchoice;
        std::cout << std::endl;
        std::cin.ignore();

        switch (userchoice) {
            case 'q':
            case 'Q': run = false; break;

            case '0': {
                char userchoice2;
                std::string file;
                std::cout << "Select the type of graph you want to use\n\n";
                std::cout << "(1) Toy-Graphs\n";
                std::cout << "(2) Extra_Fully_Connected_Graphs\n";
                std::cout << "(3) Real_world Graphs\n\n";

                std::cout << "Insert the option number you want to select.\n";
                std::cin >> userchoice2;
                std::cout << std::endl;

                graph.getVertexSet().clear();

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

                    //TODO: adicionar metodo para ler real graphs
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

                        break;
                    }
                }
                std::cout << "Done.\n";
                break;
            }

            case '1': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n\n";
                    break;
                }

                std::cout << "*** Backtracking Algorithm ***\n\n";
                graph.tspBF();
                break;
            }

            case '2': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n\n";
                    break;
                }

                std::cout << "*** Approximation Algorithm ***\n\n";
                graph.approximation();
                break;
            }

            //TODO: IMPLEMENT
            case '3': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n\n";
                    break;
                }

                break;
            }

            case '4': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n\n";
                    break;
                }

                std::cout << "*** Compare efficiency ***\n\n";
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