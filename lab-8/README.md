# Lab 8: Implement Process scheduling algorithm; FIFO, SJF, RR, PPS

## task 1

you will implement the following scheduling algorithms: First Come First Serve (FIFO), Shortest Job First (SJF), Round Robin (RR) with a fixed time quantum, and Priority Preemptive Scheduling (PPS). Your program should simulate how processes are executed under each algorithm and display the order of execution.
You are also required to calculate and display the Waiting Time and Turnaround Time for each process in every scheduling method. Additionally, compare the performance of these algorithms based on criteria such as efficiency, fairness, and response time.
Finally, analyze your results and briefly explain which scheduling algorithm performs best under different scenarios and why.  Requirements
Input at least 4–5 processes
Clearly show execution order (Gantt Chart or sequence)
Calculate:
Waiting Time
Turnaround Time
Use any programming language (preferably C++) ⭐ Bonus (Optional)
Allow user input dynamically
Add average waiting & turnaround time comparison
Visualize scheduling (optional)

## task 2

  You are developing a scheduling system for a hospital emergency unit where patients arrive at different times with varying levels of urgency. Each patient is treated as a process with attributes such as arrival time, treatment time (burst time), and priority (critical, serious, normal). Implement Priority Preemptive Scheduling (PPS) to ensure critical patients are treated first. Additionally, simulate the same data using FIFO and SJF to compare system performance. Calculate waiting time and turnaround time, and analyze which algorithm is most suitable for emergency handling.

## Task 3 

An online food delivery platform processes multiple orders from customers. Each order requires a certain preparation time and arrives at different intervals. Implement and scheduling algorithms to simulate how orders are processed in the kitchen. Compare the results and discuss which algorithm minimizes customer waiting time and improves service efficiency.  

## task 4

In a university computer lab, multiple students run programs on a shared system. To ensure fairness, the CPU is allocated using scheduling with a fixed time quantum. Implement the RR algorithm and simulate process execution. Analyze how changing the time quantum affects system performance, waiting time, and response time.
