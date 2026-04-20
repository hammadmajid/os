package main

import (
	"encoding/csv"
	"fmt"
	"os"
	"sort"
	"strconv"
)

type Process struct {
	Name      string
	Burst     int
	Arrival   int
	Remaining int
	Finish    int
	Started   bool
}

type Execution struct {
	Process string
	Start   int
	End     int
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "usage: srtf <file.csv>")
		os.Exit(1)
	}

	f, err := os.Open(os.Args[1])
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	defer f.Close()

	records, err := csv.NewReader(f).ReadAll()
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	procs := make([]*Process, 0, len(records)-1)
	for _, row := range records[1:] {
		burst, _ := strconv.Atoi(row[1])
		arrival, _ := strconv.Atoi(row[2])
		procs = append(procs, &Process{
			Name:      row[0],
			Burst:     burst,
			Arrival:   arrival,
			Remaining: burst,
		})
	}

	// run SRTF
	t := 0
	done := 0
	n := len(procs)
	var executions []Execution

	for done < n {
		// pick arrived, unfinished process with shortest remaining time
		var cur *Process
		for _, p := range procs {
			if p.Arrival <= t && p.Remaining > 0 {
				if cur == nil || p.Remaining < cur.Remaining {
					cur = p
				}
			}
		}

		if cur == nil {
			t++
			continue
		}

		// track execution for Gantt chart
		if !cur.Started {
			cur.Started = true
		}
		execStart := t
		cur.Remaining--
		t++
		executions = append(executions, Execution{
			Process: cur.Name,
			Start:   execStart,
			End:     t,
		})

		if cur.Remaining == 0 {
			cur.Finish = t
			done++
		}
	}

	// sort output by arrival for clean display
	sort.Slice(procs, func(i, j int) bool {
		return procs[i].Arrival < procs[j].Arrival
	})

	// column widths
	colW := []int{9, 11, 13, 12, 12, 13}
	headers := []string{"Process", "Burst", "Arrival", "Finish", "Turnaround", "Waiting"}

	sep := func() {
		fmt.Print("+")
		for _, w := range colW {
			for i := 0; i < w+2; i++ {
				fmt.Print("-")
			}
			fmt.Print("+")
		}
		fmt.Println()
	}

	row := func(cols []string) {
		fmt.Print("|")
		for i, c := range cols {
			pad := colW[i] - len(c)
			fmt.Printf(" %s%*s |", c, pad, "")
		}
		fmt.Println()
	}

	var totalTA, totalWT int
	for _, p := range procs {
		totalTA += p.Finish - p.Arrival
		totalWT += p.Finish - p.Arrival - p.Burst
	}
	avgTA := float64(totalTA) / float64(n)
	avgWT := float64(totalWT) / float64(n)

	sep()
	row(headers)
	sep()
	for _, p := range procs {
		ta := p.Finish - p.Arrival
		wt := ta - p.Burst
		row([]string{
			p.Name,
			strconv.Itoa(p.Burst),
			strconv.Itoa(p.Arrival),
			strconv.Itoa(p.Finish),
			strconv.Itoa(ta),
			strconv.Itoa(wt),
		})
	}
	sep()
	row([]string{
		"Average", "", "", "",
		fmt.Sprintf("%.2f", avgTA),
		fmt.Sprintf("%.2f", avgWT),
	})
	sep()

	// render Gantt chart
	fmt.Println()
	fmt.Println("GANTT CHART")
	fmt.Println()

	// get unique process names and find max time
	processMap := make(map[string]bool)
	maxTime := 0
	for _, exec := range executions {
		processMap[exec.Process] = true
		if exec.End > maxTime {
			maxTime = exec.End
		}
	}

	// sort process names
	var processNames []string
	for name := range processMap {
		processNames = append(processNames, name)
	}
	sort.Strings(processNames)

	// render time scale
	fmt.Print("      |")
	for i := 0; i < maxTime; i++ {
		fmt.Printf("%d", i%10)
	}
	fmt.Println()

	// render time markers
	fmt.Print("      |")
	for i := 0; i < maxTime; i++ {
		if i%10 == 0 && i > 0 {
			fmt.Print("^")
		} else {
			fmt.Print(" ")
		}
	}
	fmt.Println()

	// render each process
	for _, procName := range processNames {
		fmt.Printf("%6s|", procName)
		lastEnd := 0

		// collect executions for this process
		var procExecs []Execution
		for _, exec := range executions {
			if exec.Process == procName {
				procExecs = append(procExecs, exec)
			}
		}

		for _, exec := range procExecs {
			// fill gaps
			for i := lastEnd; i < exec.Start; i++ {
				fmt.Print(" ")
			}
			// fill execution block
			blockLen := exec.End - exec.Start
			for i := 0; i < blockLen; i++ {
				fmt.Print("█")
			}
			lastEnd = exec.End
		}
		fmt.Println()
	}

	// render bottom scale
	fmt.Print("      |")
	for i := 0; i <= maxTime; i++ {
		if i%10 == 0 {
			fmt.Print("0")
		} else {
			fmt.Print(" ")
		}
	}
	fmt.Println()

	fmt.Print("      |")
	for i := 0; i < maxTime; i++ {
		fmt.Print("-")
	}
	fmt.Println()

	fmt.Print("      0")
	spacing := ""
	for i := 0; i < maxTime-1; i++ {
		spacing += " "
	}
	fmt.Printf("%s%d\n", spacing, maxTime)
}
