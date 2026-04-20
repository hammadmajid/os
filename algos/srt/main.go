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
}

func mustInt(s string) int {
	n, err := strconv.Atoi(s)
	if err != nil {
		fmt.Fprintf(os.Stderr, "invalid number %q: %v\n", s, err)
		os.Exit(1)
	}
	return n
}

func load(path string) []*Process {
	f, err := os.Open(path)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	defer f.Close()

	rows, err := csv.NewReader(f).ReadAll()
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}

	procs := make([]*Process, 0, len(rows)-1)
	for _, r := range rows[1:] {
		b := mustInt(r[1])
		procs = append(procs, &Process{
			Name:      r[0],
			Burst:     b,
			Arrival:   mustInt(r[2]),
			Remaining: b,
		})
	}
	return procs
}

func simulate(procs []*Process) {
	t, done := 0, 0
	n := len(procs)

	for done < n {
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
		cur.Remaining--
		t++
		if cur.Remaining == 0 {
			cur.Finish = t
			done++
		}
	}
}

func printTable(procs []*Process) {
	// sort by arrival for display
	sorted := make([]*Process, len(procs))
	copy(sorted, procs)
	sort.Slice(sorted, func(i, j int) bool {
		return sorted[i].Arrival < sorted[j].Arrival
	})

	// header
	fmt.Printf("%-10s %8s %10s %10s %12s %10s\n",
		"Process", "Burst", "Arrival", "Finish", "Turnaround", "Waiting")
	fmt.Println(repeat("-", 64))

	var totalTA, totalWT int
	for _, p := range sorted {
		ta := p.Finish - p.Arrival
		wt := ta - p.Burst
		totalTA += ta
		totalWT += wt
		fmt.Printf("%-10s %8d %10d %10d %12d %10d\n",
			p.Name, p.Burst, p.Arrival, p.Finish, ta, wt)
	}

	n := len(sorted)
	fmt.Println(repeat("-", 64))
	fmt.Printf("%-10s %8s %10s %10s %12.2f %10.2f\n",
		"Average", "", "", "",
		float64(totalTA)/float64(n),
		float64(totalWT)/float64(n))
}

func repeat(s string, n int) string {
	out := ""
	for i := 0; i < n; i++ {
		out += s
	}
	return out
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "usage: srtf <file.csv>")
		os.Exit(1)
	}
	procs := load(os.Args[1])
	simulate(procs)
	printTable(procs)
}
