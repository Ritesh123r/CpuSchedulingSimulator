#include<bits/stdc++.h>
//#include<iostream>
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
using namespace std;
struct Process{
   int pid, arrival, burst, remaining, priority;
    int completion , waiting , turnaround,start ;
	
};

bool cmpArrival(Process a, Process b) {
    return a.arrival < b.arrival;
}

void printtable(vector<Process>& v){
	 cout << "\n Table (Vertical Table Format):\n";
	 
	 cout << "\nPID\tArrival\tBurst\tPriority\tCT\tTAT\tWT\n";
	 
	 for(auto &ele : v){
	 	cout << ele.pid << "\t" << ele.arrival << "\t" << ele.burst << "\t" << ele.priority
             << "\t\t" << ele.completion << "\t" << ele.turnaround << "\t" << ele.waiting << "\n";
	 }
}

void ganttchart(vector<pair<string,int>>& gantt){
	 cout << "\nGantt Chart (Vertical Table Format):\n";
    cout << "+---------+------------+----------------+\n";
    cout << "| Process | Start Time | Completion Time|\n";
    cout << "+---------+------------+----------------+\n";
    
    int pretime=0;
    for(auto &ele : gantt){
    	int comtime=ele.second;
    	string proc=ele.first;
    	cout << "| " << setw(7) << proc<<"| "<<setw(10)<<pretime<<"| "<<setw(14)<<comtime<<" |\n";
    	pretime=comtime;
	}
	
	cout << "+---------+------------+----------------+\n";
}

void FCFS(vector<Process> v){
	sort(v.begin(),v.end(),cmpArrival);
	int time=0;
	vector<pair<string,int>> gantt;
	for(auto &ele : v){
		if(ele.arrival>time){
			gantt.push_back({"IDLE",ele.arrival});
			time=ele.arrival;
		}
		
		ele.start=time;
		time+=ele.burst;
		ele.completion=time;
		ele.turnaround=ele.completion-ele.arrival;
		ele.waiting=ele.turnaround-ele.burst;
		gantt.push_back({"P"+to_string(ele.pid),ele.completion});

	}
	
	cout<<endl;
	cout << CYAN << "================FCFS Scheduling ============================\n";
    cout << "=============================================" << RESET << "\n";
    ganttchart(gantt);
    printtable(v);
	
}

void sjf(vector<Process> v){
	int n=v.size();
	sort(v.begin(),v.end(),cmpArrival);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
	
	vector<pair<string,int>> gantt;
	int time=0;
	int completed=0;
	int i=0;
	
	while(completed!=n){
		while(i<n&&v[i].arrival<=time){
			pq.push({v[i].burst,i});
			i++;
			
		}
		
		if(pq.size()==0){  //no process is ready for execute
		   time++;
		   if(gantt.size()==0||gantt[gantt.size()-1].first!="IDLE"){ //it the cpu is not idle at time--
		   	      gantt.push_back({"IDLE",time});
		   }
		   
		   else{  // if the cpu is idle at time-- and also at current time so we have only update the time
		   	gantt[gantt.size()-1].second=time;
		   	
		   }
			
		}
		
		else{
			//pop the process with shortest time
			auto [brust,idx]=pq.top();
			pq.pop();
			
			if(gantt.size()==0||gantt[gantt.size()-1].first!="P"+to_string(v[idx].pid)){ //if the size of the gantt chart is 0 or the pid the current process and the pid of the last procees added in the gantt chart is not same 
				gantt.push_back({"P"+to_string(v[idx].pid),time+v[idx].burst});
			}
			
			else{
				gantt[gantt.size()-1].second+=v[idx].burst;  //if the current process id and the gantt last process id is same it means that the process is running is the same
			}
			v[idx].start=time;
			time+=v[idx].burst;
			v[idx].completion=time;
			v[idx].turnaround=v[idx].completion - v[idx].arrival;
			v[idx].waiting=v[idx].turnaround-v[idx].burst;
			completed++;
			
		}
	
		
		
	}
		
	cout<<endl;
	cout << CYAN << "================FCFS Scheduling ============================\n";
    cout << "=============================================" << RESET << "\n";
    ganttchart(gantt);
    printtable(v);
	
	
}

void SJF(vector<Process> v){
	
	int n=v.size();
	sort(v.begin(),v.end(),cmpArrival);
	int completed=0,time=0,i=0;
	vector<pair<string, int>> gantt;
	
	for (auto &ele : v){
		ele.remaining=ele.burst;
		 ele.start = -1;
	}
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> p;
	
	while(completed<n){
		
		while(i<n&& v[i].arrival<=time) {
			p.push({v[i].remaining,i});
			i++;
		}
		
		if(p.size()==0){ //there is no process is ready to run on cpu
			time++;
			if(gantt.size()==0||gantt.back().first!="IDLE")  
			{
				 gantt.push_back({"IDLE", time});
			}
			
			else{
				gantt.back().second=time;
			}
		}
		
		else{
				auto [a,b]=p.top();
			p.pop();
//			int a=ele.first;
//			int b=ele.second;
			if(v[b].start==-1) v[b].start=time;
			
			if(gantt.size()==0||gantt.back().first!="P"+to_string(v[b].pid)){
				gantt.push_back({"P"+to_string(v[b].pid),time+1});
			}
			
			else gantt.back().second++;
			
			v[b].remaining--;
			time++;
			
			if(v[b].remaining>0){
				p.push({v[b].remaining,b});
			}
			
			else{
				completed++;
				v[b].completion=time;
				v[b].turnaround=time-v[b].arrival;
				v[b].waiting=v[b].turnaround-v[b].burst;
			}
			
		
		}
		
		
	}
	
	cout<<endl;
	cout << CYAN << "================SJF Preemptive Scheduling ============================\n";
    cout << "=============================================" << RESET << "\n";
    ganttchart(gantt);
    printtable(v);
	
	
	
}

void SRTF(vector<Process> v){
		int n=v.size();
	sort(v.begin(),v.end(),cmpArrival);
	int completed=0,time=0,i=0;
	vector<pair<string, int>> gantt;
	
	for (auto &ele : v){
		ele.remaining=ele.burst;
		 ele.start = -1;
	}
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> p;
	
	while(completed<n){
		
		while(i<n&& v[i].arrival<=time) {
			p.push({v[i].remaining,i});
			i++;
		}
		
		if(p.size()==0){ //there is no process is ready to run on cpu
			time++;
			if(gantt.size()==0||gantt.back().first!="IDLE")  
			{
				 gantt.push_back({"IDLE", time});
			}
			
			else{
				gantt.back().second=time;
			}
		}
		
		else{
				auto [a,b]=p.top();
			p.pop();
//			int a=ele.first;
//			int b=ele.second;
			if(v[b].start==-1) v[b].start=time;
			
			if(gantt.size()==0||gantt.back().first!="P"+to_string(v[b].pid)){
				gantt.push_back({"P"+to_string(v[b].pid),time+1});
			}
			
			else gantt.back().second++;
			
			v[b].remaining--;
			time++;
			
			if(v[b].remaining>0){
				p.push({v[b].remaining,b});
			}
			
			else{
				completed++;
				v[b].completion=time;
				v[b].turnaround=time-v[b].arrival;
				v[b].waiting=v[b].turnaround-v[b].burst;
			}
			
		
		}
		
		
	}
	
	cout<<endl;
	cout << CYAN << "================SRTF Scheduling ============================\n";
    cout << "=============================================" << RESET << "\n";
    ganttchart(gantt);
    printtable(v);
	
	
	
}


void PriorityNonPreemtive(vector<Process> v){
	
	int n=v.size();
	sort(v.begin(),v.end(),cmpArrival);
	  int time = 0, i = 0, completed = 0;
		vector<pair<string, int>> gantt;
	
	priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<>> p; // priority , arrival ,index
	
	while(completed<n){
		while(i<n&&v[i].arrival<=time){
			p.push({v[i].priority,v[i].arrival,i});
			i++;
		}
		
		if(p.size()==0) {//NO process is ready to run
			time++;
			if(gantt.size()==0||gantt.back().first!="IDLE") gantt.push_back({"IDLE",time});
			
			else gantt.back().second=time;
			
			
		}
		else{
			auto [prio,arrive,idx]=p.top();
			p.pop();
			v[idx].start=time;
			time+=v[idx].burst;
			v[idx].completion=time;
			v[idx].turnaround=v[idx].completion-v[idx].arrival;
			v[idx].waiting=v[idx].turnaround-v[idx].burst;
			gantt.push_back({"P"+to_string(v[idx].pid),time});
			completed++;
		}
	}
	cout<<endl;
	cout << CYAN << "================SRTF Scheduling ============================\n";
    cout << "=============================================" << RESET << "\n";
    ganttchart(gantt);
    printtable(v);
	
	
	
	
}

void PriorityPreemptive(vector<Process> v) {
    int n = v.size();
    sort(v.begin(), v.end(), cmpArrival);

    int time = 0, i = 0, completed = 0;
    vector<pair<string, int>> gantt;
    vector<int> remaining(n);
    for (int j = 0; j < n; j++) remaining[j] = v[j].burst;

    // priority, arrival, index
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;

    int lastIdx = -1;
    while (completed < n) {
        while (i < n && v[i].arrival <= time) {
            pq.push({v[i].priority, v[i].arrival, i});
            i++;
        }

        if (pq.empty()) {
            time++;
            if (gantt.empty() || gantt.back().first != "IDLE")
                gantt.push_back({"IDLE", time});
            else
                gantt.back().second = time;
        } else {
            auto [prio, arrive, idx] = pq.top();
            pq.pop();

            if (remaining[idx] == v[idx].burst)
                v[idx].start = time;

            remaining[idx]--;
            time++;

            if (gantt.empty() || gantt.back().first != "P" + to_string(v[idx].pid))
                gantt.push_back({"P" + to_string(v[idx].pid), time});
            else
                gantt.back().second = time;

            if (remaining[idx] == 0) {
                v[idx].completion = time;
                v[idx].turnaround = v[idx].completion - v[idx].arrival;
                v[idx].waiting = v[idx].turnaround - v[idx].burst;
                completed++;
            } else {
                pq.push({v[idx].priority, v[idx].arrival, idx}); // Push again if not completed
            }
        }
    }

    cout << endl;
    cout << CYAN << "================ Priority Preemptive Scheduling ==================\n";
    cout << "=====================================================" << RESET << "\n";
    ganttchart(gantt);
    printtable(v);
}



void RR(vector<Process>& v, int quantum) {
	
	int n=v.size();
	sort(v.begin(),v.end(),cmpArrival);
	
	int time=0,completed=0,i=0;
	vector<pair<string, int>> gantt;
	
	//making an vector for storing the remaining time for a process to run on the cpu
	vector<int> reamain(n);
	
	for (int j = 0; j < n; j++) reamain[j] = v[j].burst;

	//making a vector that check a process is alredy present in the queue or not
	vector<bool> present(n,false);
	
	//making a queue that maintain round robin order of the process
	queue<int> q;
	
	while(i<n&&v[i].arrival<=time) {
		present[i]=true;
		q.push(i);
		i++;
	}
	
	// if the q.size()==0 --> cpu is idle time t=0;
	
	if(q.size()==0){
		gantt.push_back({"IDLE",time});
	}
	
	while(completed<n){
		if(q.size()==0){
			time++;
				
				// add new arriving process during IDLE
				while(i<n&&v[i].arrival<=time){
					q.push(i);
					present[i]=true;
					i++;
				}
				
				//marking the idle in the gantt chart
				if(gantt.size()==0||gantt.back().first!="IDLE") gantt.push_back({"IDLE",time});//if cpu is not idle at its previous time
				else gantt.back().second=time;
				continue;
			
		}
		
		//if q.size()!=0
		int idx=q.front();
		q.pop();
		
		// marking the time for the first execution process
		if(reamain[idx]==v[idx].burst) v[idx].start=time;
		
		// calculate the actual time to run
		int exectime=min(quantum,reamain[idx]);
	//	int start_time = time;
        time += exectime;
         reamain[idx] -= exectime;


    gantt.push_back({"P" + to_string(v[idx].pid), time});

       //gantt.back().second = time;
		
		
		
		
		// add new arrive process in the queue during this time
		while(i<n&&v[i].arrival<=time){
			if(present[i]!=true){
				q.push(i);
				present[i]=true;
			}
			i++;
		}
		
		if(reamain[idx]>0){
			q.push(idx);
			
		}
		//else process will complete
		else{
			v[idx].completion=time;
			v[idx].turnaround=v[idx].completion-v[idx].arrival;
			v[idx].waiting=v[idx].turnaround-v[idx].burst;
			completed++;
		}

		
	}


    

    // Output section
    cout << endl;
    cout << CYAN << "================ Round Robin Scheduling =========================\n";
    cout << "=====================================================" << RESET << "\n";

    // Print Gantt Chart and Process Table
    ganttchart(gantt);
     printtable(v);
}


	
	
	
	




int main(){
    cout << CYAN << "=============================================\n";
    cout << "         CPU Scheduling Simulator (C++)      \n";
    cout << "=============================================" << RESET << "\n";

    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    vector<Process> original(n);

    for(int i = 0; i < n; i++){
        original[i].pid = i + 1;
        cout << "Enter the Arrival time of P" << i + 1 << ": ";
        cin >> original[i].arrival;
        cout << "Enter the Burst time of P" << i + 1 << ": ";
        cin >> original[i].burst;
        cout << "Enter the Priority (if not given, enter 0): ";
        cin >> original[i].priority;
    }

    while (true) {
        cout << CYAN << "\nChoose Scheduling Algorithm (Enter 8 to Exit):\n";
        cout << "1. First Come First Serve (FCFS)\n";
        cout << "2. Shortest Job First (Non-preemptive)\n";
        cout << "3. Shortest Job First (Preemptive)\n";
        cout << "4. Shortest Remaining Time First (SRTF)\n";
        cout << "5. Priority Scheduling (Non-preemptive)\n";
        cout << "6. Priority Scheduling (Preemptive)\n";
        cout << "7. Round Robin\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: " << RESET;

        int choice;
        cin >> choice;

        if (choice == 8) {
            cout << "Exiting...\n";
            break;
        }

        vector<Process> v = original; // Reset copy for each algorithm

        switch(choice){
            case 1:
                FCFS(v);
                break;
            case 2:
                sjf(v);
                break;
            case 3:
                SJF(v);
                break;
            case 4:
                SRTF(v);
                break;
            case 5:
                PriorityNonPreemtive(v);
                break;
            case 6:
                PriorityPreemptive(v);
                break;
            case 7:
                int quantum;
                cout << "Enter the quantum time: ";
                cin >> quantum;
                RR(v, quantum);
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;

	
	
}
