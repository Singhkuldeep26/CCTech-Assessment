#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

struct Point {
    int id;
    double x;
    double y;
};

struct Connection {
    int p1;
    int p2;
};

class DataFileReader {
public:
    DataFileReader(const std::string& filename) : filename(filename) {}

    std::vector<Point> readPTS() {
        std::vector<Point> points;
        std::ifstream file(filename);
        std::string line;
        bool inPTS = false;

        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (line == "PTS") {
                    inPTS = true;
                    continue;
                } else if (line == "CON") {
                    inPTS = false;
                    break;
                }

                if (inPTS) {
                    std::istringstream iss(line);
                    Point point;
                    if (iss >> point.id >> point.x >> point.y) {
                        points.push_back(point);
                    } else {
                        std::cerr << "Skipping invalid line in PTS section: " << line << std::endl;
                    }
                }
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }

        return points;
    }

    std::vector<Connection> readCON() {
        std::vector<Connection> connections;
        std::ifstream file(filename);
        std::string line;
        bool inCON = false;

        if (file.is_open()) {
            while (std::getline(file, line)) {
                if (line == "CON") {
                    inCON = true;
                    continue;
                } else if (line.empty()) {
                    inCON = false;
                    continue;
                }

                if (inCON) {
                    std::istringstream iss(line);
                    Connection connection;
                    if (iss >> connection.p1 >> connection.p2) {
                        connections.push_back(connection);
                    } else {
                        std::cerr << "Skipping invalid line in CON section: " << line << std::endl;
                    }
                }
            }
            file.close();
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
        }

        return connections;
    }

private:
    std::string filename;
};

int main() {
    DataFileReader reader("data.txt");
    
    std::vector<Point> ptsData = reader.readPTS();
    std::cout << "PTS data:" << std::endl;
    for (const auto& point : ptsData) {
        std::cout << "ID: " << point.id << ", X: " << point.x << ", Y: " << point.y << std::endl;
    }

    std::vector<Connection> conData = reader.readCON();
    std::cout << "CON data:" << std::endl;
    for (const auto& connection : conData) {
        std::cout << "P1: " << connection.p1 << ", P2: " << connection.p2 << std::endl;
    }

    return 0;
}
