#include <iostream>
#include <string>
#include <chrono>

#include "../include/UserInterface.h"
#include "../include/Graph.h"
#include "../include/constants.h"

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

                if (validInput) std::cout << "Done.";
                break;
            }

            case '1': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n";
                    break;
                }

                std::cout << "*** Backtracking Algorithm ***\n\n";

                std::vector<int> path;

                auto start = std::chrono::high_resolution_clock::now();
                double distance = graph.tspBT(path);
                auto stop = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> time = stop - start;

                std::cout << "Path: ";

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
                std::cout << "Distance: " << distance << std::endl;
                std::cout << "Time: " << time.count() << " milliseconds";

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
                std::cout << "Path: ";

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
                std::cout << "Distance: " << distance;
                break;
            }

            case '3': {
                if (graph.getVertexSet().empty()) {
                    std::cout << "You need to read a graph in '(0) Read and Parse Dataset'\n";
                    break;
                }

                std::vector<int> path;
                double distance = graph.otherHeuristics(path);

                if (distance == -1) {
                    std::cout << "Unable to do approximation. Graph is not complete";
                    break;
                }

                std::cout << "Path: ";

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
                std::cout << "Distance: " << distance;
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

                double backTrackingDistance, approximationDistance, heuristicDistance;
                std::vector<Vertex*> approximationPath;
                std::vector<int> backtrackingPath;
                std::vector<int> heuristicPath;

                switch (userchoice2) {
                    case '1': {
                        auto tStartB = std::chrono::high_resolution_clock::now();
                        backTrackingDistance = graph.tspBT(backtrackingPath);
                        auto tEndBStartA = std::chrono::high_resolution_clock::now();
                        approximationDistance = graph.approximation(approximationPath);
                        auto tEndAStartOh = std::chrono::high_resolution_clock::now();
                        heuristicDistance = graph.otherHeuristics(heuristicPath);
                        auto tEndOh = std::chrono::high_resolution_clock::now();

                        if (heuristicDistance == -1) {
                            std::cout << "Unable to do approximation. Graph is not complete";
                            break;
                        }

                        std::chrono::duration<double, std::milli> time_b = tEndBStartA - tStartB;
                        std::chrono::duration<double, std::milli> time_a = tEndAStartOh - tEndBStartA;
                        std::chrono::duration<double, std::milli> time_oh = tEndOh - tEndAStartOh;
                        std::cout << "Backtracking algorithm\n\t Distance: " << backTrackingDistance << " meters in " << time_b.count() << " milliseconds.\n";
                        std::cout << "Approximation algorithm\n\t Distance: " << approximationDistance << " meters in " << time_a.count() << " milliseconds.\n";
                        std::cout << "Other Heuristics algorithm\n\t Distance: " << heuristicDistance << " meters in " << time_oh.count() << " milliseconds.\n\n";

                        std::pair<double, std::string> ap {time_a.count(), "Approximation"};
                        std::pair<double, std::string> bt {time_b.count(), "Backtracking"};
                        std::pair<double, std::string> oh {time_oh.count(), "Other Heuristics"};

                        std::vector<std::pair<double, std::string>> times;
                        times.push_back(ap);
                        times.push_back(bt);
                        times.push_back(oh);

                        std::sort(times.begin(), times.end(), [](std::pair<double, std::string>& p1, std::pair<double, std::string>& p2){
                            return p1.first < p2.first;
                        });

                        for (int i = 0; i < times.size(); i++) {
                            std::cout << times[i].second << " executed in " << times[i].first << " milliseconds";
                            if (i != 0) std::cout << " | " << times[i].first - times[0].first << " milliseconds slower (" << (times[i].first * 100 / times[0].first) - 100 << "%).";
                            std::cout << std::endl;
                        }

                        times.clear();

                        ap.first = approximationDistance;
                        bt.first = backTrackingDistance;
                        oh.first = heuristicDistance;

                        std::cout << ap.first << " " << ap.second << std::endl;

                        times.push_back(ap);
                        times.push_back(bt);
                        times.push_back(oh);

                        std::sort(times.begin(), times.end(), [](std::pair<double, std::string>& p1, std::pair<double, std::string>& p2){
                            return p1.first < p2.first;
                        });

                        std::cout << std::endl;

                        for (int i = 0; i < times.size(); i++) {
                            std::cout << times[i].second << " got a distance of " << times[i].first << " meters";
                            if (i != 0) std::cout << " | " << times[i].first - times[0].first << " meters longer (" << (times[i].first * 100 / times[0].first) - 100 << "%).";
                            std::cout << std::endl;
                        }

                        break;
                    }

                    case '2': {
                        auto tStartB = std::chrono::high_resolution_clock::now();
                        backTrackingDistance = graph.tspBT(backtrackingPath);
                        auto tEndBStartA = std::chrono::high_resolution_clock::now();
                        approximationDistance = graph.approximation(approximationPath);
                        auto tEndA = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> time_b = tEndBStartA - tStartB;
                        std::chrono::duration<double, std::milli> time_a = tEndA - tEndBStartA;
                        std::cout << "Backtracking algorithm\n\t Distance: " << backTrackingDistance << " meters in " << time_b.count() << " milliseconds.\n";
                        std::cout << "Approximation algorithm\n\t Distance: " << approximationDistance << "meters in "<< time_a.count() << " milliseconds.\n\n";
                        bool backTrackGreaterTime = time_b.count() >= time_a.count();
                        bool backTrackGreaterDistance = backTrackingDistance >= approximationDistance;

                        if (backTrackGreaterTime) {
                            std::cout << "Approximation algorithm was " << time_b.count() - time_a.count() << " milliseconds faster, which is a "
                                      << (time_b.count() - time_a.count()) * 100 / time_b.count() << "% improvement\n";
                        }
                        else {
                            std::cout << "Backtracking algorithm was " << time_a.count() - time_b.count() << " milliseconds faster, which is a "
                                      << (time_a.count() - time_b.count()) * 100 / time_a.count() << "% improvement\n";
                        }

                        if (backTrackGreaterDistance) {
                            std::cout << "Other Heuristics algorithm distance is " << backTrackingDistance - approximationDistance << " meters shorter, which is a "
                                      << (backTrackingDistance - approximationDistance) * 100 / backTrackingDistance << "% improvement\n";
                        }
                        else {
                            std::cout << "Backtracking algorithm distance is " << approximationDistance - backTrackingDistance << " meters shorter, which is a "
                                      << (approximationDistance - backTrackingDistance) * 100 / approximationDistance << "% improvement\n";
                        }

                        break;
                    }

                    case '3': {
                        auto tStartB = std::chrono::high_resolution_clock::now();
                        backTrackingDistance = graph.tspBT(backtrackingPath);
                        auto tEndBStartOH = std::chrono::high_resolution_clock::now();
                        heuristicDistance = graph.otherHeuristics(heuristicPath);
                        auto tEndOH = std::chrono::high_resolution_clock::now();

                        std::chrono::duration<double, std::milli> time_b = tEndBStartOH - tStartB;
                        std::chrono::duration<double, std::milli> time_oh = tEndOH - tEndBStartOH;
                        std::cout << "Backtracking algorithm\n\t Distance: " << backTrackingDistance << " meters in " << time_b.count() << " milliseconds.\n";
                        std::cout << "Other Heuristics algorithm\n\t Distance: " << heuristicDistance << " meters in " << time_oh.count() << " milliseconds.\n\n";
                        bool backTrackGreaterTime = time_b.count() >= time_oh.count();
                        bool backTrackGreaterDistance = backTrackingDistance >= heuristicDistance;

                        if (backTrackGreaterTime) {
                            std::cout << "Other Heuristics algorithm was " << time_b.count() - time_oh.count() << " milliseconds faster, which is a "
                                << (time_b.count() - time_oh.count()) * 100 / time_b.count() << "% improvement\n";
                        }
                        else {
                            std::cout << "Backtracking algorithm was " << time_oh.count() - time_b.count() << " milliseconds faster, which is a "
                                      << (time_oh.count() - time_b.count()) * 100 / time_oh.count() << "% improvement\n";
                        }

                        if (backTrackGreaterDistance) {
                            std::cout << "Other Heuristics algorithm distance is " << backTrackingDistance - heuristicDistance << " meters shorter, which is a "
                                << (backTrackingDistance - heuristicDistance) * 100 / backTrackingDistance << "% improvement\n";
                        }
                        else {
                            std::cout << "Backtracking algorithm distance is " << heuristicDistance - backTrackingDistance << " meters shorter, which is a "
                                      << (heuristicDistance - backTrackingDistance) * 100 / heuristicDistance << "% improvement\n";
                        }

                        break;
                    }

                    case '4': {
                        auto tStartA = std::chrono::high_resolution_clock::now();
                        approximationDistance = graph.approximation(approximationPath);
                        auto tEndAStartOH = std::chrono::high_resolution_clock::now();
                        heuristicDistance = graph.otherHeuristics(heuristicPath);
                        auto tEndOH = std::chrono::high_resolution_clock::now();

                        if (heuristicDistance == -1) {
                            std::cout << "Unable to do approximation. Graph is not complete";
                            break;
                        }

                        std::chrono::duration<double, std::milli> time_a = tEndAStartOH - tStartA;
                        std::chrono::duration<double, std::milli> time_oh = tEndOH - tEndAStartOH;
                        std::cout << "Approximation algorithm\n\t Distance: " << approximationDistance << " meters in " << time_a.count() << " milliseconds.\n";
                        std::cout << "Other Heuristics algorithm\n\t Distance: " << heuristicDistance << " meters in " << time_oh.count() << " milliseconds.\n\n";

                        bool approximationGreaterTime = time_a.count() >= time_oh.count();
                        bool approximationGreaterDistance = approximationDistance >= heuristicDistance;

                        if (approximationGreaterTime) {
                            std::cout << "Other Heuristics algorithm was " << time_a.count() - time_oh.count() << " milliseconds faster, which is a "
                                      << (time_a.count() - time_oh.count()) * 100 / time_a.count() << "% improvement\n";
                        }
                        else {
                            std::cout << "Approximation algorithm was " << time_oh.count() - time_a.count() << " milliseconds faster, which is a "
                                      << (time_oh.count() - time_a.count()) * 100 / time_oh.count() << "% improvement\n";
                        }

                        if (approximationGreaterDistance) {
                            std::cout << "Other Heuristics algorithm distance is " << approximationDistance - heuristicDistance << " meters shorter, which is a "
                                      << (approximationDistance - heuristicDistance) * 100 / approximationDistance << "% improvement\n";
                        }
                        else {
                            std::cout << "Approximation algorithm distance is " << heuristicDistance - approximationDistance << " meters shorter, which is a "
                                      << (heuristicDistance - approximationDistance) * 100 / heuristicDistance << "% improvement\n";
                        }

                        break;
                    }

                    default: {
                        std::cout << "Invalid input\n\n";
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