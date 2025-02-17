#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Task{
	string description;
	bool completed;
};


void saveTasks(vector<Task> &tasks){
	ofstream fout("tasks.txt");
	if (!fout){
		cout<<"There was an error saving your tasks.\n";
		return;
	}
	
	for (auto& task : tasks){
		fout<<task.description<<";"<<task.completed<<"\n";
	}
	
	fout.close();
}


void loadTasks(vector<Task> &tasks){
	ifstream fin("tasks.txt");
	if (!fin){
		cout<<"No tasks found. \n";
		return;
	}
	
	string desc;
	bool completed;
	while(getline(fin, desc, ';') && fin>>completed){
		fin.ignore();
		Task t;
		t.description = desc;
		t.completed = completed;
		tasks.push_back(t);
	}
	
	fin.close();
}


int main(){
	vector<Task> tasks;
	int choice;
	
	
	loadTasks(tasks);
	
	do{

		cout<<"To-Do list @kalloniatis"<<endl;
		cout<<"\nSelect an action,\n";
		cout<<"1. Add task.\n";
		cout<<"2. View tasks. \n";
		cout<<"3. Mark a task as completed. \n";
		cout<<"4. Delete a task.\n";
		cout<<"5. Exit.\n";
		cout<<"Enter action's number: ";
		cin>>choice;
		
		if (choice == 1){			// ADD TASK			
			cin.ignore(); // ignore leftover newline character
			cout<<"\nEnter task description: ";
			string desc;
			getline(cin, desc);
			Task t;
			t.description = desc;
			t.completed = false;
			tasks.push_back(t);
			saveTasks(tasks);
			cout<<"Task added! \n";			
		}else if (choice == 2){		// VIEW TASKS
			if (tasks.empty()) {
				cout<<"\nTo-Do list is empty.\n";
			}else{
				cout<<"\nTo-Do list:\n";
				for(int i=0; i<tasks.size(); i++){
					cout<< i + 1 <<". ["<<(tasks[i].completed ? "✔" : " ")<<"] "<<tasks[i].description<<endl; // boolCase ? true : false
				}
			}			
		}else if (choice == 3){		// MARK COMPLETED TASK
			if (tasks.empty()){
				cout<<"\nNo tasks available. \n";
			}else{
				cout<<"\nEnter the task's number you wish to mark as completed: ";
				int taskNumber;
				cin>>taskNumber;
				if (taskNumber < 1 || taskNumber > tasks.size()){
					cout<<"Invalid task number.\n";
				}else{
					tasks[taskNumber-1].completed = true;
					saveTasks(tasks);
					cout<<"Task marked as completed.\n";
				}
			}
		}else if (choice == 4){		// DELETE TASK
			if (tasks.empty()){
				cout<<"\nNo tasks available.\n";
			}else{
				cout<<"\nEnter the task's number you wish to delete: ";
				int taskNumber;
				cin>>taskNumber;
				if (taskNumber < 1 || taskNumber > tasks.size()){
					cout<<"Invalid task number.\n";
				}else{
					tasks.erase(tasks.begin() + (taskNumber-1)); // delete the tasknumber-th - 1 task after the beggining of the vector
					saveTasks(tasks);
					cout<<"Task deleted.\n";
				}
			}
		}else if (choice == 5){
			cout<<"\nExiting... \n";
		}else{
			cout<<"\nInvalid input please try again. \n";
		}
		
		
	} while (choice != 5);
	
	
	return 0;
}
