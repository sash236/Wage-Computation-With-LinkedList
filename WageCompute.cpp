/***********************
/*
/* Compiler Visual Studio 6, EE
/* Wage Computation.
/* CEmployee : A class for the employee linked list. One node represents an employee and the employee's particulars.
/*
/***********************/

#include <iostream>
#include <fstream>
#include <string> 
#include <iomanip>

#define LINE_SIZE 80  
using namespace std; 
  
void (*_new_handler) ();    // pointer to handler 
void outOfMemory();    // Function Prototype 

//////////////////////////////////////////////////////////////////////////////
// class definition to store employee information 
class CEmployee { 
    public: 
        void Create(ifstream &inFile); 
        void GetEmpData(CEmployee *pFreshNode, ifstream &inFile); 
		void ReadEmpData(CEmployee *pFreshNode); 
        void ComputeWage(); 
        void Remove(); 
        void ListAllEmps();

    private: 
        char m_aName[30]; 
        unsigned int m_nAge; 
        unsigned int m_nSalary; 
        CEmployee *m_pLink; 
}; 
   
//////////////////////////////////////////////////////////////////////////////
// Function: CEmployee::Remove

// Purpose: Delete each node

// Parameters: 
//		File object inFile reference  is passed on
//		LINE_SIZE defined to be 80

// Local Variables:
//		CEmployee *pCurr - local Employee node pointer

////////////////////////////////////////////////////////////////
void CEmployee::Remove() 
{ 
    CEmployee *pCurr, *pDeleteThisNode;			// local Employee node pointer

	pCurr = m_pLink ;				// local Employee node pointer is initiated

//    pCurr = pHeadNode; 
    while (pCurr != 0)				// deltes each node systamatically
    { 
        pDeleteThisNode = pCurr; 
        pCurr = pCurr->m_pLink;		// calculates the next pointer in the Linked List
        delete pDeleteThisNode;		// then deletes the node
    } 
} 
   
//////////////////////////////////////////////////////////////////////////////
// Function: CEmployee::GetEmpData

// Purpose: Collects Employee data

// Parameters: 
//		File object inFile reference  is passed on
//		LINE_SIZE defined to be 80

// Local Variables:
//		int i			- local int 
//		CEmployee *pFreshNode, *pHeadNode,*pCurNode - local Employee node pointers

////////////////////////////////////////////////////////////////
void CEmployee::GetEmpData(CEmployee *pFreshNode, ifstream &inFile) 
{
    char str[LINE_SIZE];    // Line to be read from file
	inFile.getline(str, LINE_SIZE);							// Reads file
  	strcpy(pFreshNode->m_aName,strdup(strtok(str, ";")));	// Copies Employees name excluding ";"
	pFreshNode->m_nAge    = atoi(strtok(NULL, ";"));		// Copies Employees Age excluding ";"
	pFreshNode->m_nSalary = atoi(strtok(NULL, ";"));		// Copies Employees Salary excluding ";"
} 

  
//////////////////////////////////////////////////////////////////////////////
// Function: CEmployee::Create

// Purpose: Creates a node for each candidate

// Parameters: 
//		File object inFile reference  is passed on

// Local Variables:
//		int i			- local int 
//		CEmployee *pFreshNode, *pHeadNode,*pCurNode - local Employee node pointers


////////////////////////////////////////////////////////////////
void CEmployee::Create(ifstream &inFile) 
{ 
    CEmployee *pFreshNode, *pHeadNode, *pCurNode;	// local Employee node pointers

    for (int i=0; !inFile.eof(); i++) 
    { 
        pFreshNode = new CEmployee;					// Creates node for Employees
        GetEmpData(pFreshNode, inFile);				// Colletcs Employee data
        pFreshNode->m_pLink = 0;					// Set the m_pLink to Null
        if (i == 0) { 
            pHeadNode = pFreshNode;					// Initializes the local pointers for the first node
            pCurNode = pFreshNode; 					// Initializes the local pointersfor the first node
        } 
        else { 
            pCurNode->m_pLink = pFreshNode; 		// Initializes the local pointers for the subsequent nodes
            pCurNode = pFreshNode;				// Initializes the local pointersfor the subsequent nodes
        } 
    } // end for loop 

	m_pLink = pHeadNode ;						// Assigns the head node to m_pLink for other functions use

} 
   
//////////////////////////////////////////////////////////////////////////////
// Function: CEmployee::ComputeWage

// Purpose: Calculates wages for the week

// Parameters: 
//		Alley name is being passed on

// Local Variables:
//		int nNumHours			- local int 
//		float fWeekPay			- local float variable
//		char caSearchName[30]	- local candicate search name
//		CEmployee *pCurNode - local Employee node pointer


////////////////////////////////////////////////////////////////
void CEmployee::ComputeWage() 
{ 
    int nNumHours; 
    float fWeekPay; 
    char caSearchName[30];
	memset(caSearchName,'\0',30);

    CEmployee *pCurNode;						// local Employee node pointer 
	pCurNode = m_pLink ;						// local Employee node pointer is initiated

    cout << "\nEnter employee's Name to compute pay: "; // colleting employee's name
    cin.getline(caSearchName,30);						// collects the colleting employee's name
    while (pCurNode != 0) 
    { 
        if (strcmpi(caSearchName,pCurNode->m_aName) == 0) {  // searches the Employee in the database
            cout << "How many hours did ";				// Prompts for employee's hours
            cout << pCurNode->m_aName << " work this week? "; // Prompts for employee's hours
            cin >> nNumHours;					// colleting employee's hours
            fWeekPay = (pCurNode->m_nSalary / 2080) * nNumHours; 
            cout << "Annual salary is: ";					// Prints the salary
            cout << pCurNode->m_nSalary << "\n";			// Prints the salary
            cout << pCurNode->m_aName << "'s ";				// Prints the Employee's name
            cout << " pay this week is: " << fWeekPay << "\n"; // Prints the Employee's pay
            break; 
        } // end if 
        else 
            pCurNode = pCurNode->m_pLink;			 // Moves to the next Employee in the search
    }  // end while 
} 

//////////////////////////////////////////////////////////////////////////////

// Function: CEmployee::ListAllEmps

// Purpose: Lists all the employees details 

// Parameters: 

// Local Variables:
//		int nCount		- local int 
//		const m			- local const 
//		CEmployee *pCurNode - local Employee node pointer


////////////////////////////////////////////////////////////////

void CEmployee::ListAllEmps()
{
	int nCount = 0;
	const m = 1000;								// To format the Salary with a ","

    CEmployee *pCurNode;						// local Employee node pointer 
	pCurNode = m_pLink ;						// local Employee node pointer is initiated

	cout.setf(ios::left, ios::adjustfield);
	cout<< "#   "
		<< " Employee Name                 "
		<< "Age       "
		<< "Salary" << endl
		<< "====================================================" << endl;


	while(pCurNode)
	{

		if (nCount < 9)				// Formating for single digit cases
		{
		cout<< setw(1)  << setfill(' ') << setiosflags(ios::left) << ++nCount << ". " << "  "
			<< setw(30) << setiosflags(ios::left) << pCurNode->m_aName	// Prints the Employee name
		    << setw(10) << setiosflags(ios::left) << pCurNode->m_nAge 	// Prints the Employee's age
			<< setiosflags(ios::left) << pCurNode->m_nSalary/m << ","  // Prints the digits before prior to the comma
			<< setw(3) << setfill('0') << setiosflags(ios::left) << pCurNode->m_nSalary%m << endl; // Prints the remaining digits 

		pCurNode = pCurNode->m_pLink;									// calculates the next employee's node
		}

		if (nCount >= 9) 			// Formating for double digit cases
		{
		cout<< setw(2) << setfill(' ')  << setiosflags(ios::left) << ++nCount << "." << "  "
			<< setw(30) << setiosflags(ios::left) << pCurNode->m_aName	// Prints the Employee name
		    << setw(10) << setiosflags(ios::left) << pCurNode->m_nAge	// Prints the Employee's age
			<< setiosflags(ios::left) << pCurNode->m_nSalary/m << "," // Prints the digits prior to the comma
			<< setw(3) << setfill('0') << setiosflags(ios::left) << pCurNode->m_nSalary%m << endl; // Prints the remaining digits

		pCurNode = pCurNode->m_pLink;									// calculates the next employee's node
		}


	}
}


//////////////////////////////////////////////////////////////////////////////

// Function: OutofMemory

// Purpose: Reports error before exiting

// Parameters: 

// Local Variables:

////////////////////////////////////////////////////////////////

void OutOfMemory() 
{ 
    cerr << "Dynamic Memory Allocation Failure\n"; 
    cerr << "Exiting ...\n"; 
    exit(1); 
} 
   
//////////////////////////////////////////////////////////////////////////////

// Function: main

// Purpose: Process the Wage Computation

// Parameters: 
//		Built in file name for the data

// Local Variables:

////////////////////////////////////////////////////////////////

void main()
{ 
    ifstream   inFile("assignment3.data");

	if (!inFile)
	{
	    cout << "Cannot open 'assignment3.data' input file.\n";
		exit(1);
    }


    _new_handler = &OutOfMemory;    // memory handler 


    CEmployee Worker;				// creates the object Worker of CEmployee 
    Worker.Create(inFile);			// calls Create() function and passes the object for the file
	Worker.ListAllEmps();			// calls ListAllEmps() function 
	Worker.ComputeWage(); 			// calls ComputeWage() function
    Worker.Remove(); 				// calls Remove() function to delete the nodes

} 
