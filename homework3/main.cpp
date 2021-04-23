#include "pugixml.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <algorithm>
#include <cstring>
#include <set>
#include <cmath>

const double M_PI = 3.14159;

using namespace std;

class Transports {
private:
    int number_trans;
    std::string type_of_vehicle_trans;
    std::string object_type_trans;
    std::string name_stopping_trans;
    std::string the_official_name_trans;
    std::vector<std::string> location_trans;
    std::vector<std::string> routes_trans;
    double x_coordinates_trans;
    double y_coordinates_trans;
public:
    Transports(int number = 0, std::string type_of_vehicle = "", std::string name_stopping = "",
               std::string the_official_name = "", std::vector<std::string> location = {},
               std::vector<std::string> routes = {}, double x_coordinates = 0, double y_coordinates = 0)
            : number_trans(number), type_of_vehicle_trans(type_of_vehicle), name_stopping_trans(name_stopping),
              the_official_name_trans(the_official_name), location_trans(location), routes_trans(routes),
              x_coordinates_trans(x_coordinates), y_coordinates_trans(y_coordinates) {}

    std::vector<std::string> get_location() {
        return location_trans;
    }

    std::vector<std::string> get_routes() {
        return routes_trans;
    }

    std::string get_routesX(int x) {
        return routes_trans[x];
    }

    std::string get_type_of_vehicle() const {
        return type_of_vehicle_trans;
    }

    std::string get_location_i(int x) {
        return location_trans[x];
    }

    double getX() const {
        return x_coordinates_trans;
    }

    double getY() const {
        return y_coordinates_trans;
    }
};

struct Type_vehicle_routes {
    std::string name_route;
    std::vector<Transports> buses;
    std::vector<Transports> trams;
    std::vector<Transports> trolleybuses;

};

double length(Transports &first, Transports &second) {
    double x1_rad = first.getX() * M_PI / 180;
    double y1_rad = first.getY() * M_PI / 180;
    double x2_rad = second.getX() * M_PI / 180;
    double y2_rad = second.getY() * M_PI / 180;
    double len = 2 * 6371 * asin(sqrt(
            pow(sin((x2_rad - x1_rad) / 2), 2) + cos(x1_rad) * cos(x2_rad) * pow(sin((y2_rad - y1_rad) / 2), 2)));
    return len;
}


int main() {
//    setlocale(LC_ALL, "Rus");
    system("chcp 65001");

    pugi::xml_document data;
    data.load_file("table.xml");

    std::map<std::string, int> map_location;
    std::vector<Transports> all_station;

    std::map<std::string, Type_vehicle_routes> routes_with_street;

    std::map<std::string, int> count_bus_routes;
    std::map<std::string, int> count_tram_routes;
    std::map<std::string, int> count_trolleybus_routes;
    std::set<std::string> all_routes_name;


    for (pugi::xml_node i = data.child("dataset").child("transport_station"); i; i = i.next_sibling(
            "transport_station")) {
        std::string coordinate = i.child_value("coordinates");
        unsigned int size_1coordinate = coordinate.find(',');
        unsigned int size_2coordinate = coordinate.size() - size_1coordinate;
        double x = std::stod(coordinate.substr(0, size_1coordinate));
        double y = std::stod(coordinate.substr(size_1coordinate + 1, size_2coordinate));

        std::string route = i.child_value("routes");
        std::vector<std::string> all_routes;
        unsigned int start = 0;
        int j = count(route.begin(), route.end(), ',') + count(route.begin(), route.end(), '.');
        unsigned int size_coordinate;
        size_coordinate = route.find(',', start + 1);


        for (int k = j; k > 0; k--) {
            if (route.find(',', start + 1) != std::string::npos) {
                size_coordinate = route.find(',', start + 1);

            } else if (route.find('.', start + 1) != std::string::npos) {
                size_coordinate = route.find('.', start + 1);
            }
            all_routes.push_back(route.substr(start, size_coordinate - start));
            all_routes_name.insert(route.substr(start, size_coordinate));
            start = size_coordinate + 1;
        }
        if (route.size() > start) {
            size_coordinate = route.size() - start;
            all_routes.push_back(route.substr(start, size_coordinate));
            all_routes_name.insert(route.substr(start, size_coordinate));
        }


        std::string data_location = i.child_value("location");


        std::vector<std::string> all_location;
        unsigned int start_data = 0;
        int c = count(data_location.begin(), data_location.end(), ',');
        unsigned int size_location;


        std::vector<std::string> remove_titles = {" pr.", " УЛ.", " улица", " УЛИЦА", "улица", "ул.", " ул.", " шоссе",
                                                  " ШОССЕ", " ш.", " Ш.", "ш.", " проспект", "проспект", " ПРОСПЕКТ",
                                                  " пр.",
                                                  " ПР.", " пр", " ПР", " бульвар", " БУЛЬВАР", " бул.",
                                                  " переулок", " ПЕРЕУЛОК", " ПЕР.", " пер."};
        unsigned int start_erase;
        unsigned int size_erase;


        for (int k = c; k > 0; k--) {
            if (start_data < data_location.size()) {
                if (data_location.find(',', start_data + 1) != std::string::npos) {
                    size_location = data_location.find(',', start_data + 1);
                }
                std::string str_changes = data_location.substr(start_data, size_location - start_data);
                for (auto &m: remove_titles) {
                    if (str_changes.find(m) != std::string::npos) {
                        start_erase = str_changes.find(m);
                        size_erase = m.size() + start_erase;
                        str_changes.erase(start_erase, size_erase);
                    }
                }
                if (str_changes[str_changes.size() - 1] == ' ') {
                    str_changes.erase(str_changes.end() - 1);
                }
                if (str_changes[0] == ' ') {
                    str_changes.erase(str_changes.begin());
                }
                all_location.push_back(str_changes);
                start_data = size_location + 1;
                map_location[str_changes]++;
            }
        }
        if (start_data < data_location.size()) {

            size_location = data_location.size() - start_data;

            std::string str_changes = data_location.substr(start_data, size_location);

            for (auto &m: remove_titles) {
                if (str_changes.find(m) != std::string::npos) {
                    start_erase = str_changes.find(m);
                    size_erase = m.size() + start_erase;
                    str_changes.erase(start_erase, size_erase);
                }
            }
            if (!str_changes.empty()) {
                if (str_changes[str_changes.size() - 1] == ' ') {
                    str_changes.erase(str_changes.end() - 1);
                }
            }
            if (str_changes[0] == ' ') {
                str_changes.erase(str_changes.begin());
            }
            all_location.push_back(str_changes);
            map_location[str_changes]++;
        }
        Transports new_station(std::stoi(i.child_value("number")), i.child_value("type_of_vehicle"),
                               i.child_value("name_stopping"), i.child_value("the_official_name"), all_location,
                               all_routes, x, y);
        all_station.push_back(new_station);
        if (strcmp("Автобус", i.child_value("type_of_vehicle")) == 0) {
            for (auto &k: all_routes) {
                count_bus_routes[k]++;  //in route 23- 5 station for bus
            }

        }
        if (strcmp("Трамвай", i.child_value("type_of_vehicle")) == 0) {
            for (auto &k: all_routes) {
                count_tram_routes[k]++;  //in route 23- 5 station for tram
            }
        }
        if (strcmp("Троллейбус", i.child_value("type_of_vehicle")) == 0) {
            for (auto &k: all_routes) {
                count_trolleybus_routes[k]++;  //in route 23- 5 station for trolleybus
            }
        }

    }

    int max_bus_routes = 0;
    int max_tram_routes = 0;
    int max_trolleybus_routes = 0;
    std::string number_max_routes_bus;
    std::string number_max_routes_tram;
    std::string number_max_routes_trolleybus;
    for (auto &k: count_bus_routes) {
        if (max_bus_routes < k.second) {
            max_bus_routes = k.second;
            number_max_routes_bus = k.first;
        }
    }
    for (auto &k: count_tram_routes) {
        if (max_tram_routes < k.second) {
            max_tram_routes = k.second;
            number_max_routes_tram = k.first;
        }
    }
    for (auto &k: count_trolleybus_routes) {
        if (max_trolleybus_routes < k.second) {
            max_trolleybus_routes = k.second;
            number_max_routes_trolleybus = k.first;
        }
    }
    std::cout << "_________________________TASK1__________________________" << '\n';
    std::cout << "Автобусы: маршрут № " << number_max_routes_bus << " имеет больше всего остановок = " << max_bus_routes
              << '\n';
    std::cout << "Трамваи: маршрут № " << number_max_routes_tram << " имеет больше всего остановок = "
              << max_tram_routes << '\n';
    std::cout << "Троллейбусы: маршрут № " << number_max_routes_trolleybus << " имеет больше всего остановок = "
              << max_trolleybus_routes << '\n';



    std::map<std::string, double> length_route_bus;
    std::map<std::string, double> length_route_tram;
    std::map<std::string, double> length_route_trolleybus;

    for (auto &k:all_station) {
        if (k.get_type_of_vehicle() == "Автобус") {
            for (auto &j:k.get_routes()) {
                routes_with_street[j].name_route = j;
                routes_with_street[j].buses.push_back(k);
            }
        } else if (k.get_type_of_vehicle() == "Трамвай") {
            for (auto &j:k.get_routes()) {
                routes_with_street[j].name_route = j;
                routes_with_street[j].trams.push_back(k);
            }
        } else if (k.get_type_of_vehicle() == "Троллейбус") {
            for (auto &j:k.get_routes()) {
                routes_with_street[j].name_route = j;
                routes_with_street[j].trolleybuses.push_back(k);
            }
        }
    }
    for (auto &k:all_routes_name) {
        if (!routes_with_street[k].buses.empty()) {
            for (int j = 0; j < routes_with_street[k].buses.size() - 1; j++) {
                length_route_bus[k] = length_route_bus[k] +
                                      length(routes_with_street[k].buses[j], routes_with_street[k].buses[j + 1]);
            }
        }
        if (!routes_with_street[k].trams.empty()) {
            for (int j = 0; j < routes_with_street[k].trams.size() - 1; j++) {
                length_route_tram[k] = length_route_tram[k] +
                                       length(routes_with_street[k].trams[j], routes_with_street[k].trams[j + 1]);
            }
        }
        if (!routes_with_street[k].trolleybuses.empty()) {
            for (int j = 0; j < routes_with_street[k].trolleybuses.size() - 1; j++) {
                length_route_trolleybus[k] = length_route_trolleybus[k] + length(routes_with_street[k].trolleybuses[j],
                                                                                 routes_with_street[k].trolleybuses[j +
                                                                                                                    1]);
            }
        }
    }
    max_bus_routes = 0;
    max_tram_routes = 0;
    max_trolleybus_routes = 0;
    number_max_routes_bus = ' ';


    for (auto &k:length_route_bus)
        if (max_bus_routes < k.second) {
            max_bus_routes = k.second;
            number_max_routes_bus = k.first;
        }
    for (auto &k:length_route_tram)
        if (max_tram_routes < k.second) {
            max_tram_routes = k.second;
            number_max_routes_tram = k.first;
        }
    for (auto &k:length_route_trolleybus)
        if (max_trolleybus_routes < k.second) {
            max_trolleybus_routes = k.second;
            number_max_routes_trolleybus = k.first;
        }


    std::cout << "_________________________TASK2__________________________" << '\n';
    std::cout << "Автобусы: маршрут № " << number_max_routes_bus << " имеет самый длинный путь " << '\n';
    std::cout << "Трамваи: маршрут № " << number_max_routes_tram << " имеет самый длинный путь " << '\n';
    std::cout << "Троллейбусы: маршрут № " << number_max_routes_trolleybus << " имеет самый длинный путь " << '\n';


    int max_station_street = 0;
    std::string name_max_station_street;
    for (auto &k: map_location) {
        if (max_station_street < k.second) {
            max_station_street = k.second;
            name_max_station_street = k.first;
        }
    }

    if (name_max_station_street.find("ое") != std::string::npos &&
        name_max_station_street.find("ое") == name_max_station_street.size() - 4) {
        name_max_station_street = name_max_station_street + " шоссе";
    }
    std::cout << "_________________________TASK3__________________________" << '\n';
    std::cout << "Улица " << name_max_station_street << " имеет больше всего остановок = " << max_station_street
              << '\n';


    return 0;


}
