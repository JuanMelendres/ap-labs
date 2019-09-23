// Juan Antonio Melendres Villa A00369017
/*
    References:
        -> Tanks to Flavio Copes that help me to understand how to use the walk function, I look the information on this         web site: https://flaviocopes.com/go-list-files/
        -> Tanks to Go Documentation where I search for functions that help me to develop this. (Is the reference that the     professor give us).
            Web site: https://golang.org/pkg/path/filepath/#Walk && https://golang.org/pkg/os/#Lstat
        -> Thanks to ddebroy, because his question help me to understand want was for the Sockets, because on the OS documentation in go-land I didn't understand. Web site: https://github.com/golang/go/issues/33357
        -> Thanks to zosmac, because his question help me to understand want was for the Devices, because on the OS documentation in go-land I didn't understand. Web site: https://github.com/golang/go/issues/23123
*/

package main

import (
	"fmt"
	"os"
	"path/filepath"
)

// Variables
var directories int = 0;
var symboLink int = 0;
var devices int = 0;
var sockets int = 0;
var otherFiles int = 0;

// scanDir stands for the directory scanning implementation
func scanDir(dir string) error {
	dirData := filepath.Walk(dir, visit);
	return dirData;
}

func visit(dir string, file os.FileInfo, err error) error {
	if file.IsDir() {
		directories++;
		return nil;
	}
	if file.Mode()&os.ModeSymlink != 0 {
		symboLink++;
		return nil;
	}
	if file.Mode().IsRegular() {
		otherFiles++;
		return nil;
	}
	if file.Mode()&os.ModeSocket != 0 {
		sockets++;
		return nil;
	}
	if file.Mode()&os.ModeDevice != 0 {
		devices++;
		return nil;
	}
	return nil;
}

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: ./dir-scan <directory>");
		os.Exit(1);
	}
	directory := os.Args[1];
	scanDir(directory);
	fmt.Printf(
			"Directory Scanner Tool\n"+
			"+-----------------------+---------------+\n" +
			"| Path\t\t\t|\t%s\t|\n" +
			"+-----------------------+---------------+\n" +
			"| Directories:\t\t|\t%d\t|\n" +
			"| Symbolic Links:\t|\t%d\t|\n" +
			"| Devices:\t\t|\t%d\t|\n" +
			"| Sockets:\t\t|\t%d\t|\n" +
			"| Symbolic Links:\t|\t%d\t|\n" +
			"| Other files:\t\t|\t%d\t|\n" +
			"+-----------------------+---------------+\n",
			directory, directories, symboLink, devices, sockets, symboLink, otherFiles);
}
