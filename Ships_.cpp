
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <deque>

using namespace std;

int main()
{
	string str, ship_name;
	int N, action, dock_number;
	bool there_is_free_dock;

	ifstream input("SHIPS.IN");
	ofstream output("SHIPS.OUT");

	if (!input) {
		output << "File SHIPS.IN does not exist!";
		return 0;
	}

	if (!getline(input, str)) {
		output << "File SHIPS.IN is empty!";
		return 0;
	}
	
	N = stoi(str);
	vector<string> ships_in_docks(N);
	deque<string> ship_queue;

	while (getline(input, str)) {
		action = str[0];

		switch (action) {
		case '1':
			ship_name = str.substr(2);

			there_is_free_dock = false;
			for (int i = 0; i < ships_in_docks.size(); i++) {
				if (ships_in_docks[i] == "") {
					there_is_free_dock = true;
					ships_in_docks[i] = ship_name;

					break;
				}
			}

			if (!there_is_free_dock) {
				ship_queue.push_back(ship_name);
			}

			break;

		case '2':
			dock_number = stoi(str.substr(2));
			ships_in_docks[dock_number] = "";

			if (!ship_queue.empty()) {
				ship_name = ship_queue.front();
				ship_queue.pop_front();

				for (int i = 0; i < ships_in_docks.size(); i++) {
					if (ships_in_docks[i] == "") {
						ships_in_docks[i] = ship_name;
						break;
					}
				}
			}

			break;

		case '3':
			output << "There are " << ship_queue.size() << " ship(s) in queue. ";
			for (int i = 0; i < ship_queue.size(); i++) {
				output << "'" << ship_queue[i] << "' ";
			}
			output << endl;

			break;

		case '4':
			for (int i = 0; i < ships_in_docks.size(); i++) {
				if (ships_in_docks[i] != "") {
					output << "Dock number " << i << " contains ship '" << ships_in_docks[i] << "'; ";
				}
			}
			output << endl;

			break;
		}
	}
	input.close();
	output.close();
	
	return 0;
}