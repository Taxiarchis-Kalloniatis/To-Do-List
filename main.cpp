// kalloniatis
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Task{
	string description;
	bool completed;
	int priority; 
	/*
		1 - low priority
		2 - medium priority
		3 - high priority
		4 - critical priority
	*/
};


void saveTasks(vector<Task> &tasks){
	ofstream fout("tasks.txt");
	if (!fout){
		cout<<"There was an error saving your tasks.\n";
		return;
	}
	
	for (auto& task : tasks){
		fout<<task.description<<";"<<task.completed<<";"<<task.priority<<"\n";
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
	int prior;
	while(fin.peek() != EOF){
		getline(fin, desc, ';');
		fin >> completed;
		fin.ignore();
		fin>> prior;
		fin.ignore();

		Task t;
		t.description = desc;
		t.completed = completed;
		t.priority = prior;
		tasks.push_back(t);
	}
	
	fin.close();
}


int main(){
	vector<Task> tasks;
	int choice;
	
	
	loadTasks(tasks);
	
	do{

		cout<<"\nTo-Do list @kalloniatis"<<endl;
		cout<<"Select an action,\n";
		cout<<"1. Add task.\n";
		cout<<"2. View tasks.\n";
		cout<<"3. Mark a task as completed.\n";
		cout<<"4. Delete a task.\n";
		cout<<"5. Update a task's description.\n";
		cout<<"6. Update a task's priority.\n";
		cout<<"7. Exit.\n";
		cout<<"Enter action's number: ";
		cin>>choice;
		
		if (choice == 1){			// ADD TASK			
			cin.ignore(); // ignore leftover newline character
			cout<<"\nEnter task description: ";
			string desc;
			getline(cin, desc);
			
			cout<<"Enter priority (1=Low, 2=Medium, 3=High, 4=Critical): ";
			int priority;
			cin>>priority;

			while (priority < 1 || priority > 4){
				cout<<"Invalid priority please re-enter: ";
				cin>>priority;
			}

			Task t;
			t.description = desc;
			t.completed = false;
			t.priority = priority;
			tasks.push_back(t);

			saveTasks(tasks);
			cout<<"Task added! \n";			
		}else if (choice == 2){		// VIEW TASKS
			if (tasks.empty()) {
				cout<<"\nTo-Do list is empty.\n";
			}else{
				cout<<"\nTo-Do list:\n";
				for(int i=0; i<tasks.size(); i++){
					string priority;
					switch (tasks[i].priority){
						case 1:
							priority = "Low Priority "; break;
						case 2:
							priority = "Medium Priority "; break;
						case 3:
							priority = "High Priority "; break;
						case 4:
							priority = "Critical Priority "; break;
					}
					cout<< i + 1 <<". ["<<(tasks[i].completed ? "DONE" : " ")<<"] "<<tasks[i].description<<"	// "<<priority<<"\n"; // boolCase ? true : false
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
				cout<<"\nThere are no available tasks.\n";
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
			if (tasks.size() == 0){
				cout<<"\nThere are no available tasks.\n";
			}else{
				cout<<"\nEnter the task's number which you wish to change the description: ";
				int taskNumber;
				cin>>taskNumber;
				if (taskNumber < 1 || taskNumber > tasks.size()){
					cout<<"Invalid task number, please retry.\n";
				}else{
					cin.ignore();
					cout<<"Please type the new description: ";
					string desc;
					getline(cin, desc);
					tasks[taskNumber-1].description = desc;
					saveTasks(tasks);
					cout<<"Successfuly changed the task's description.\n";
				}
			}
		}else if (choice == 6){
			if (tasks.size() == 0){
				cout<<"\nThere are no available tasks.\n";
			}else{
				cout<<"\nPlease enter the task's whose priority you wish to change: ";
				int taskNumber;
				cin>>taskNumber;
				if (taskNumber < 1 || taskNumber > tasks.size()){
					cout<<"Invalid task.\n";
				}else{
					cout<<"Please enter the new priority (1=Low, 2=Medium, 3=High, 4=Critical): ";
					int priority;
					cin>>priority;
					while (priority < 1 || priority > 4){
						cout<<"Invalid priority please re-enter: ";
						cin>>priority;
					}
					tasks[taskNumber-1].priority = priority;
					saveTasks(tasks);
					cout<<"Successfuly updated task's priority.\n";
				}
			}
		}else if (choice == 7){
			cout<<"\nExiting... \n";
		}else{
			cout<<"\nInvalid input please try again. \n";
		}
		
		
	} while (choice != 7);
	
	
	return 0;
}
