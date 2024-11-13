/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

class TaskManager
{
private:
  int id = 0;
  //This function is used to add the task in a taskfile
  void TaskAdder (vector < pair < int, pair < string, string >>> &store)
  {
	fstream files;
	//ios::app mode will add the task at the end 
	files.open ("taskfile.txt", ios::app);
	if (files.is_open ())
	  {

		for (int i = 0; i < store.size (); i++)
		  {
			files << store[i].first << " " << store[i].second.
			  first << " " << store[i].second.second << "\n";
		  }
	  }
	files.close ();
  }

  //This function helps in fetching the last id that exists
  int fetchId ()
  {
	fstream files;
	files.open ("taskfile.txt", ios::in);
	int count = 0;
	if (files.is_open ())
	  {
		string ch;
		while (getline (files, ch))
		  {
			count = ch[0] - '0';
		  }
	  }
	files.close ();
	return count;
  }

  //This function is used to delete the task provided by the user from the file 
  bool TaskDeleter (vector < int >&store)
  {
	fstream files;
	vector < string > copy;
	//file is open for read only ios::in
	files.open ("taskfile.txt", ios::in);
	if (files.is_open ())
	  {
		string val;
		while (getline (files, val))
		  {
			copy.push_back (val);
		  }
	  }
	files.close ();
	bool flag = false;
	//file is open for write ios::out
	files.open ("taskfile.txt", ios::out);
	int count = 1;
	int j = 0;
	if (files.is_open ())
	  {
		for (int i = 0; i < copy.size (); i++)
		  {
			if (j < store.size () && i + 1 == store[j])
			  {
				j++;
				flag = true;
			  }
			else
			  {
				copy[i][0] = count + '0';
				files << copy[i] << "\n";
				count++;
			  }
		  }
	  }
	id = count;
	files.close ();
	if (j < store.size ())
	  {
		for (int i = j; i < store.size (); i++)
		  {
			cout << "Id= " << store[i] << " is not present...\n";
		  }
	  }
	return flag;
  }

public:

  //This function helps you to view your tasks
  void TaskView ()
  {
    //Creates a fstream object
	fstream files;
	bool flag = false;
	//Open the file whom you want to read
	files.open ("taskfile.txt", ios::in);
	//Check if file is open
	if (files.is_open ())
	  {
		string data;
		//Read the data from the file
		while (getline (files, data))
		  {
			cout << data << endl;
			flag = true;
		  }
	  }
	//close the file
	files.close ();
	
	if (flag == false)
	  {
		cout << "There is no task exist for view..\n";
	  }
  }

  //This function helps you to add task 
  void TaskAdd ()
  {
	id = fetchId ();
	int t;
	vector < pair < int, pair < string, string >>> store;
	cout << "Number of tasks you want to assign:" << endl;
	cin >> t;
	cin.ignore ();
	while (t--)
	  {
		string name;
		string task_desc;
		cout << "Enter the name of person whom you want to assign a task:" <<
		  endl;
		getline (cin, name);
		cout << "Enter the task Description:" << endl;
		getline (cin, task_desc);
		id = id + 1;
		store.push_back ({id,{name, task_desc}});
		cout << endl;
	  }
	TaskAdder(store);
	cout << "Tasks Added Successfully" << endl;
  }


  //This function will delete the tasks you want to delete
  void TaskDelete ()
  {
	int t;
	set < int >s;
	cout << "Enter the number of tasks you want to delete:" << endl;
	cin >> t;
	cout << "Enter the Id's of the tasks:" << endl;
	while (t--)
	  {
		int input;
		cin >> input;
		s.insert (input);
	  }
	vector < int >store (s.begin (), s.end ());
	bool flag = TaskDeleter(store);

	if (flag)
	  cout << "Task deleted Successfully..." << endl;
  }


  void AllTaskDelete ()
  {
	fstream files;
	files.open ("taskfile.txt", ios::out | ios::trunc);
	if (files.is_open ())
	  {
		files.close ();
	  }
	cout << "All Tasks are deleted Successfully...\n";
  }

};


int main ()
{
  TaskManager tm;
  cout << "**********WELCOME TO TASK MANAGEMENT SYSTEM**********" << endl;
  cout << endl;
  int choice;
  do
	{
	  cout << "Enter Your choice" << endl;
	  cout << "1: View All Tasks" << endl;
	  cout << "2: Add New Task" << endl;
	  cout << "3: Delete a Task" << endl;
	  cout << "4: Delete all Tasks" << endl;
	  cout << "5: Exit" << endl;
	  cin >> choice;
	  switch (choice)
		{
		case 1:
		  tm.TaskView ();
		  cout << endl;
		  break;
		case 2:
		  tm.TaskAdd ();
		  cout << endl;
		  break;
		case 3:
		  tm.TaskDelete ();
		  cout << endl;
		  break;
		case 4:
		  tm.AllTaskDelete ();
		  cout << endl;
		  break;
		case 5:
		  break;
		default:
		  cout <<
			"You Have Entered a Wrong Choice ,Please Enter a Correct Choice.."
			<< endl;
		  break;
		}
	  cout << endl;
	}
  while (choice != 5);
  return 0;
}
