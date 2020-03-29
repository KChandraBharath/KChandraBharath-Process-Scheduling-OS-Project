#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
	int n;
	printf("enter the number of processes");
	scanf("%d",&n);
	int process[n];
	char process_name[n][2];
	int arrival_time[n];
	int burst_time[n];
	int completion_time[n];
	int turn_around_time[n];
	float normalized_tat[n];
	int waiting_time[n];
	int burst_copy[n];
	//int starting;
	//int start[10];
	int small,index;
	//int n;
	int ready_queue3[100];
	int ready_queue2[100];
	int time,temp;
	int no_elem_RQ;
	int time_quantum;
	
	int i=0,j=0,f=0,choice;
	while(i<n){
		printf("enter process name");
		scanf("%s",process_name[i]);
		printf("enter the id of process");
		scanf("%d",&process[i]);
		printf("enter the arrival time");
		scanf("%d",&arrival_time[i]);
		printf("enter the burst time");
		scanf("%d",&burst_time[i]);
		completion_time[i]=0;
		turn_around_time[i]=0;
		normalized_tat[i]=0.0;
		waiting_time[i]=0;
		i++;
	}
	i=0;
	for(i=0;i<100;i++) {
		ready_queue2[i]=-1;
		ready_queue3[i]=-1;
	}
	time=0;
	for(i=0;i<n;i++){
		burst_copy[i]=burst_time[i];
	}
	time=0;
	j=0;
	int k=0;
	int rQ2=0;
	int rQ3=0;
	int complete=0;
	int tq1=6,tq2=10;
	int e3=0,e2=0;
	/*while(complete==0){*/
	/*round robin*/
		for(i=0;i<n;i++){
			if(arrival_time[i]<=time){
				if(burst_copy[i]>tq1){
					//printf("\nprocessing %d",i);
					//printf("case1\n");
					//printf("%d %d",time,time+tq1);
					time+=tq1;
					burst_copy[i]-=tq1;
					ready_queue2[e2]=i;
					//printf("\n %d added to q2",i);
					int g;
					/*for(g=0;g<rQ2;g++){
						printf("\n%d %d",ready_queue2[g]);
					}*/
					rQ2++;e2++;
				}
				else{
					//printf("%d %d",time,time+burst_copy[i]);
					//printf("\nprocessing %d",i);
					time+=burst_copy[i];
					completion_time[i]=time;
					turn_around_time[i]=completion_time[i]-arrival_time[i];
					waiting_time[i]=turn_around_time[i]-burst_time[i];
					burst_copy[i]=0;
					//if(rQ2==0&&rQ3==0) complete=1;
					//printf("case2\n");
				}
			}
			else if(ready_queue2[j]>-1){
				int j1=ready_queue2[j];
				//printf("\nprocessing %d",j1);
				if(burst_copy[j1]>tq2){
					//printf("%d %d",time,time+tq2);
					time+=tq2;
					burst_copy[j1]-=tq2;
					ready_queue3[e3]=j1;
					//printf("\n %d removed from q2",j1);
					//printf("\n %d added to q3",j1);
					rQ3++;e3++;
					rQ2--;
					j++;
					i--;
					//printf("case3\n");
				}
				else{
					//printf("%d %d",time,time+burst_copy[j1]);
					//printf("\nprocessing %d",j1);
					time+=burst_copy[j1];
					completion_time[j1]=time;
					turn_around_time[j1]=completion_time[j1]-arrival_time[j1];
					waiting_time[j1]=turn_around_time[j1]-burst_time[j1];
					burst_copy[j1]=0;
					rQ2--;
					//printf("\n %d removed from q2",j1);
					j++;
					i--;
					//printf("case4\n");
				}
			}
			else if(ready_queue3[k]>-1){
				int j2=ready_queue3[k];
				//printf("\nprocessing %d",j2);
				//printf("%d %d",time,time+burst_copy[j2]);
				time+=burst_copy[j2];
				completion_time[j2]=time;
				turn_around_time[j2]=completion_time[j2]-arrival_time[j2];
				waiting_time[j2]=turn_around_time[j2]-burst_time[j2];
				burst_copy[j2]=0;
				rQ3--;
				k++;
				i--;
				if(rQ3==0) complete=1; 
				//printf("case5\n");
			}
			//else break;
		}
	//}
		//printf("%d\n",rQ2 );
		//printf("%d %d %d",ready_queue2[1],ready_queue2[2],ready_queue2[3]);
		while(rQ2>0){
			if(ready_queue2[j]>-1){
				int j1=ready_queue2[j];
				//printf("\nprocessing %d",j1);
				if(burst_copy[j1]>tq2){
					//printf("\n%d %d",time,time+tq2);
					time+=tq2;
					burst_copy[j1]-=tq2;
					ready_queue3[e3]=j1;
					//printf("\n %d removed from q2",j1);
					//printf("\n %d added to q3",j1);
					e3++;
					rQ3++;
					//rQ2--;
					j++;
					//i--;
					//printf("case3\n");
				}
				else{
					//printf("\n%d %d",time,time+burst_copy[j1]);
					time+=burst_copy[j1];
					completion_time[j1]=time;
					turn_around_time[j1]=completion_time[j1]-arrival_time[j1];
					waiting_time[j1]=turn_around_time[j1]-burst_time[j1];
					burst_copy[j1]=0;
					//printf("\n %d removed from q2",j1);
					//rQ2--;
					j++;
					//i--;
					//printf("case4\n");
				}
			}
			rQ2--;
		}
		/*round robin completed*/
		int buffer[rQ3];
		j=k;
		for(int i=0;i<rQ3;i++){
			buffer[i]=burst_copy[ready_queue3[j]];j++;
		}

		for (int i = k+rQ3-1; i >= k; i--)  
        for (int j = k+rQ3-1; j >= k+rQ3 - i; j--)  
            if (buffer[j] > buffer[j - 1]){
            	int u=buffer[j];
            	buffer[j]=buffer[j-1];
            	buffer[j-1]=u;
            	int u2=ready_queue3[j];
            	ready_queue3[j]=ready_queue3[j-1];
            	ready_queue3[j-1]=u2;
                //swap(a[j], a[j-1]); 
            }
        //for(i=0;i<rQ3;i++) printf("rQ3 ele %d %d",buffer[i],ready_queue3[i+k]);
		//printf("%d\n",rQ3);
		//printf("\n%d %d %d %d",ready_queue3[0],ready_queue3[1],ready_queue3[2],ready_queue3[3]);
        /*shortest job last*/
		while(rQ3>0){
				if(ready_queue3[k]>-1){

					int j2=ready_queue3[k];
					//printf("\nprocessing %d",j2);
					//printf("\n%d %d",time,time+burst_copy[j2]);
					time+=burst_copy[j2];
					completion_time[j2]=time;
					turn_around_time[j2]=completion_time[j2]-arrival_time[j2];
					waiting_time[j2]=turn_around_time[j2]-burst_time[j2];
					burst_copy[j2]=0;
					rQ3--;
					k++;
					//i--;
					if(rQ3==0) complete=1; 
					//printf("case5\n");
				}
		}
		
	printf("\npro\tat\tbt\tct\ttat\twt");
	for(i=0;i<n;i++){
		printf("\n%c%c\t%d\t%d\t%d\t%d\t%d",process_name[i][0],process_name[i][1],arrival_time[i],burst_time[i],completion_time[i],turn_around_time[i],waiting_time[i]);
	}
	float average_tat=0;
	float average_wt=0;
	for(i=0;i<n;i++){
		average_tat+=turn_around_time[i];
		average_wt+=waiting_time[i];
	}
	average_wt/=n;average_tat/=n;
	printf("\nAverage turn_around_time :%f",average_tat);
	printf("\nAverage waiting_time :%f",average_wt);
}
	









