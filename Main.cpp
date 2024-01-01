#include<iostream>
#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
	class MLQ
{
	private:
	int pid[20];
	int burst_t[20];
	int arrival_t;
	int su[20], wt[20],tat[20],i, k, n, temp;
	float wtavg, tatavg;
	public:
	void datacollect()
	{
	cout<<"Enter the number of processes:";
	cin>>n;
	for(i=0;i<n;i++)
	{
		pid[i] = i;
		cout<<"Enter the Burst Time of Process "<<i<<":";
		cin>>burst_t[i];
		cout<<"System/User Process (0/1) ? ";
		cin>>su[i];
	}	
		}
	void avgtimez()
	{
		for(i=0;i<n;i++)
		for(k=i+1;k<n;k++)
			if(su[i] > su[k])
			{
			temp=pid[i];
			pid[i]=pid[k];
			pid[k]=temp;
			temp=burst_t[i];
			burst_t[i]=burst_t[k];
			burst_t[k]=temp;
			temp=su[i];
			su[i]=su[k];
			su[k]=temp;
			}
	wtavg = wt[0] = 0;
	tatavg = tat[0] = burst_t[0];
	for(i=1;i<n;i++)
	{
		wt[i] = wt[i-1] + burst_t[i-1];
		tat[i] = tat[i-1] + burst_t[i];
		wtavg = wtavg + wt[i];
		tatavg = tatavg + tat[i];
	}
	cout<<"\nPROCESS\t\t SYSTEM/USER PROCESS \tBURST TIME\tWAITING TIME\tTURNAROUND TIME";
	for(i=0;i<n;i++)
		cout<<"\n"<<pid[i]<< "\t\t\t"<<su[i]<<"  \t\t\t"<<burst_t[i]<<"  \t\t"<<wt[i]<<" \t\t "<<tat[i];
	cout<<"\nAverage Waiting Time is --- "<<wtavg<<endl;
	cout<<"\nAverage Turnaround Time is --- "<<tatavg<<endl;
		}	
};

	class HRR
{
	private:
		int pid[20];
		int burst_t[20];
		int arrival_t[20];
		int wait_t[20];
		int tat[20];
		int completed[20];
		int sum_bt;
		float nortt[20];
		int n;
	public:
		void datacollect()
		{
			int noP;
			cout<<"Enter number of processes : ";
			cin>>noP;
			for(int i=1; i<=noP;i++)
			{
				pid[i]=i;
				cout<<"Enter Burst Time of "<<i<<" Process : ";
				cin>>burst_t[i];
				cout<<"Enter Arrival Time of "<<i<<" Process : ";
				cin>>arrival_t[i];
			}
		}
		void arrivalsort()
		{
			int temp;
			for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {

			// Check for lesser arrival time
			if (arrival_t[i] > arrival_t[j]) {

				// Swap earlier process to front
				temp = pid[i];
				pid[i] = pid[j];
				pid[j] = temp;
			}
		}
	}
		}
		void intialization()
		{
			int i,j;
			sum_bt=0;
		
			for (i = 0; i < n; i++) {
		pid[i] = i;
		arrival_t[i] = arrival_t[i];
		arrival_t[i] = burst_t[i];

		// Variable for Completion status
		// Pending = 0
		// Completed = 1
		completed[i] = 0;

		// Variable for sum of all Burst Times
		sum_bt += burst_t[i];
	}
		}
	void time()
	{
		float t, avgwt = 0, avgtt = 0;
		n = 5;
		arrivalsort();
	cout << "PN\tAT\tBT\tWT\tTAT\tNTT";
	for (t = arrival_t[0]; t < sum_bt;) {
		float hrr = -99;
		float temp;
		int loc;
		for (int i = 0; i < n; i++) {
			if (arrival_t[i] <= t && completed[i] != 1) {
				temp = (burst_t[i] + (t - arrival_t[i])) /burst_t[i];
				if (hrr < temp) {
					hrr = temp;
				loc = i;
				}
			}
		}
		t += burst_t[loc];
		wait_t[loc] = t - arrival_t[loc] - burst_t[loc];
		tat[loc] = t - arrival_t[loc];	
		avgtt += tat[loc];//tat+acvgt
		
		nortt[loc] = ((float)tat[loc] / burst_t[loc]);		
		completed[loc] = 1;
		avgwt += wait_t[loc];
		cout << "\n" << pid[loc] << "\t" << arrival_t[loc];
		cout << "\t" << burst_t[loc] << "\t" << wait_t[loc];
		cout << "\t" << tat[loc] << "\t" << nortt[loc];
	}
	cout << "\nAverage waiting time: " << avgwt / n << endl;
	cout << "Average Turn Around time:" << avgtt / n;
	}
};
class SRTF
{	
	private:
		int pid[20];
		int burst_t[20];
		int arrival_t[20];
		int n;
	public:
	void datacollect()
	{
		int noP;
		cout<<"Enter number of Processes\n";
		cin>>noP;
		for(int i=1;i<noP;i++)
		{
			pid[i]=i;
			cout<<"Enter Burst Time of Process"<<i<<" : ";
			cin>>burst_t[i];
			cout<<"Enter Arrival Time of Process"<<i<<" i ";
			cin>>arrival_t[i];
		}
		n = sizeof(pid[20]+burst_t[20]+arrival_t[20])/ sizeof(pid[0]+burst_t[0]+arrival_t[0]);
		
	}
	void waitingtime (int n, int wt[20])
{
    int rt[n];
    for (int i = 0; i < n; i++)
        rt[i] = burst_t[i];
    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((arrival_t[j] <= t) &&
            (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false) {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wt[shortest] = finish_time - burst_t[shortest] - arrival_t[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}
void findTurnAroundTime(int n, int  wt[20], int tat[20])
{
    for (int i = 0; i < n; i++)
        tat[i] = burst_t[i] + wt[i];
}
void findavgTime()
{
    int wt[n], tat[n], total_wt = 0,
                    total_tat = 0;
    waitingtime(n,wt);
    findTurnAroundTime(n,wt, tat);
    cout << " P\t\t"
        << "BT\t\t"
        << "WT\t\t"
        << "TAT\t\t\n";
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
        cout << " " << pid << "\t\t"
            << burst_t << "\t\t " << wt[i]
            << "\t\t " << tat[i] << endl;
    }
    cout << "\nAverage waiting time = "
        << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)n;
}
};
int main()
{
	class MLQ M;
	class SRTF S;
    class HRR H;
    int opt;
    cout<<"\n\n\n\t\t\t\t\tWELCOME CPU SCHDULER ALGORITHM CHECKER\n\n\n";
    cout<<"\t\tKINDLY SELECT FROM THE FOLLOWING ALGORITHMS\n";
    cout<<"\t1)Shortest Remaining Time\n\t2)Highest Response Time\n\t3)MultiLevel Queue\n";
    cout<<"\t0)To Exit\n\t";
    cin>>opt;
	do 
	{
	switch (opt)
    {
    	case 1: 
    	system("CLS");
		cout<<"\n\n\t\tSHORTEST REMAINING TIME ALGORITHM\n\n\t"; 	
    	S.datacollect();
    	S.findavgTime();
    	break;
    	case 2:
    	system("CLS");
		cout<<"\n\n\t\tHIGHEST RESPONSE RATIO ALGORITHM\n\n\t"; 
    	H.datacollect();
    	H.intialization();
    	H.time();
    	break;
    	case 3:
    	system("CLS");
		cout<<"\n\n\t\tMULTI LEVEL QUEUE ALGORTIMH\n\n\t";
    	M.datacollect();
    	M.avgtimez();
		case 0:
			exit(0);
			break;
		default:
    		cout<<"Select a Valid Option";
    		break;
	}
}
	while((opt > 0 && opt < 4));
	system("PAUSE");
	return 0;
}





