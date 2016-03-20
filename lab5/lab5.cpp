#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stdlib.h>

using namespace std;
void start(int pid, int size, vector<vector<int>> & page_table,bool *page_table_references, int*processes, bool *page_in_use, unsigned int PIDMAX);
void reference();
void terminate();

int main(int argc, char *argv[]) {
	unsigned int PIDMAX = 6;
	string line;
	if (argc != 2) { //check if input file given
		cerr << "No input file given\n";
		exit(1);
	}

	ifstream infile(argv[1]);
	int pid_reference = 0,
		virtual_page_reference = 0,
		pid_start =0,
		addr_space_size = 0,
		pid_terminate = 0;
	int *processes;
	processes = new int[PIDMAX]; //index is id of process
	bool * page_table_references;
	page_table_references = new bool[PIDMAX]; //marks if page has been referenced
	bool *page_in_use;
	page_in_use = new bool[PIDMAX];
	vector<vector<int>> page_table(PIDMAX); //list of pages assigned to a process
	for (unsigned int i =0; i < PIDMAX; i++) {
		page_table_references[i] = 0;
		page_in_use[i] = 0;
		processes[i] = 0;
	}
	for (unsigned int i =0; i < PIDMAX; i++) {
		vector<int> v;
		page_table[i] = v;
	}
	while(getline(infile, line)) {
		stringstream s(line);
		string type_of_command;
		s >> type_of_command;
		cout << "command type: " << type_of_command << endl;

		if ("REFERENCE"== type_of_command) {
			s >> pid_reference >> virtual_page_reference;
			/*TODO mark which page has been referenced
				check if page replacement needed
				check if in memory for page replacement
			*/
	 	} else if ("START"== type_of_command) {
			s >> pid_start >> addr_space_size;
			start(pid_start, addr_space_size, page_table, page_table_references, processes, page_in_use, PIDMAX);
		} else { //TERMINATE
			s >> pid_terminate;
			processes[pid_terminate] = 0; //set process to stopped running
			/*TODO free pages
				mark pages as free
				write page to memory
			*/
		}
	}
	cout << "pages assigned: " << endl;

	for (unsigned int i =0; i < PIDMAX; i++) {
		if (page_in_use[i]) cout << " " << i;
	}
	cout << endl;
	for (unsigned int i =0; i < PIDMAX; i++) {
		if (processes[i] == 0)continue;
		cout << "process " << i << ", with pages:";
		for (unsigned int j =0; j < page_table[i].size(); j++)
			cout << " " << page_table[i][j];
		cout << endl;
	}
	delete[] processes;
	delete[] page_in_use;
	delete[] page_table_references;
}

void start(int pid, int size, vector<vector<int>> & page_table,bool *page_table_references, int*processes, bool *page_in_use, unsigned int PIDMAX){
	//set process as running
	processes[pid] = 1;
	bool pages_allocated = false; //flag to check if we need to replace page

	for (unsigned int i =0; i < PIDMAX; i++) {
		if (!size) { //finished allocating pages
			pages_allocated = true;
			break;
		}
		if (!page_in_use[i]){
			/* map page to process
			set the reference to 0
			mark page as allocated*/
			page_table[pid].push_back(i);
			page_table_references[i] = 0;
			page_in_use[i]= 1;
			size--;
		}

	}
	if (pages_allocated) return;
	cout << "not all pages allocated\n";
	//TODO swap pages to allocate pages
}
