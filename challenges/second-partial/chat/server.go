// Copyright © 2016 Alan A. A. Donovan & Brian W. Kernighan.
// License: https://creativecommons.org/licenses/by-nc-sa/4.0/

// See page 254.
//!+

// Chat is a server that lets clients chat with each other.
package main

import (
	"bufio"
	"flag"
	"fmt"
	"log"
	"net"
	"regexp"
	"strings"
	"time"
)

//!+broadcaster
type client chan<- string // an outgoing message channel

var (
	entering = make(chan client)
	leaving  = make(chan client)
	messages = make(chan string) // all incoming client messages
	usersChan = make(map[string]net.Conn) // Here is the connection for the user
)

type clientData struct {
  user string
  admin bool
}

var listClients []clientData
var ConUsers int = 0

func broadcaster() {
	clients := make(map[client]bool) // all connected clients
	for {
		select {
		case msg := <-messages:
			// Broadcast incoming message to all
			// clients' outgoing message channels.
			for cli := range clients {
				cli <- msg
			}
		case cli := <-entering:
			clients[cli] = true
		case cli := <-leaving:
			delete(clients, cli)
			close(cli)
		}
	}
}

//!-broadcaster

//!+handleConn
func handleConn(conn net.Conn) {
	ch := make(chan string) // outgoing client messages
	who := ""
	isAdmin := ConUsers == 0;
	go clientWriter(conn, ch)
	input := bufio.NewScanner(conn)
	for input.Scan() {
		mssg := input.Text()
		if match, _ := regexp.MatchString("<user>.+", mssg); match {
			newClient := clientData{user: mssg, admin: isAdmin}
			listClients = append(listClients, newClient)
			ConUsers++
			// check if the user is already select
			separatedString := strings.Split(mssg, ">")
			who = separatedString[1]
			fmt.Printf("irc-server > New connected user [%s] \n", who)
			ch <- "irc-server > Welcome to the simple IRC server"
			ch <- "irc-server > Your user [" + who + "] is succesfuly logged"
			if isAdmin {
				ch <- "irc-server > Congrats, you were the first user."
				ch <- "irc-server > You're the new IRC Server ADMIN"
				fmt.Printf("irc-server > [%s] was promoted as the channel ADMIN\n", who)
			}
			messages <- "irc-server > New connected user [" + who + "]"
			entering <- ch
			usersChan[who] = conn
		} else if mssg == "/users" { // User list
			fmt.Fprintf(conn, "irc-server > ")
			for key := range usersChan {
				fmt.Fprintf(conn, "%s, ", key)
			}
			fmt.Fprintf(conn, "\n")
		} else if match, _ := regexp.MatchString("^/msg .+ .+", mssg); match { // message to another user
			strimString := strings.Split(mssg, " ")
			lenSlice := len(strimString)
			if user, check := usersChan[strimString[1]]; check {
				fmt.Fprintf(user, "%s [privateMSG] > ", who)
				for i := 2; i < lenSlice; i++ {
					fmt.Fprintf(user, " %s ", strimString[i])
				}
				fmt.Fprintf(user, "\n")
			} else {
				fmt.Fprintf(conn, "irc-server > No user [%s] found, use /users to see connected users. \n", strimString[1])
			}
		} else if mssg == "/time" { // local time
			// Time Idea from: https://www.golangprograms.com/how-to-get-the-current-date-and-time-with-timestamp-in-local-and-other-timezones.html
			loc, _ := time.LoadLocation("America/Mexico_city")
			// Time format from: https://gobyexample.com/time-formatting-parsing
    	tme := time.Now().In(loc).Format("15:04")
    	fmt.Fprintf(conn, "irc-server > Local Time: %s %s\n", loc, tme)
		} else if match, _ := regexp.MatchString("^/user .+$", mssg); match { // More info of the user
			strimString := strings.Split(mssg, " ")
			if user, check := usersChan[strimString[1]]; check {
				fmt.Fprintf(conn, "irc-server > username: %s, IP: %s \n", strimString[1], user.RemoteAddr().String())
			} else {
				fmt.Fprintf(conn, "irc-server > No user (%s) found, use /users to see connected users. \n", strimString[1])
			}
		} else if match, _ := regexp.MatchString("^/kick .+$", mssg); match { // Kick a user (Only the admin)
			strimString := strings.Split(mssg, " ")
			user := who
			kickUser := strimString[1]
			if listClients[0].user == user {
				if listClients[0].admin {
					fmt.Fprintf(conn, "irc-server > You kicked user [%s]\n", kickUser)
					fmt.Printf("irc-server > [%s] was kicked\n", kickUser)
				} else {
					fmt.Fprintf(conn, "irc-server > You're kicked from this channel\n")
					fmt.Fprintf(conn, "irc-server > Bad language is not allowed on this channel\n")
					usersChan[strimString[1]].Close()
					delete(usersChan, kickUser)
				}
				messages <- "irc-server > [" + kickUser + "] was kicked from channel for bad language policy violation"
			} else {
					ch <- "irc-server > only channel ADMIN can do this"
			}
		} else {
			messages <- who + "> " + input.Text()
		}
	}
	// NOTE: ignoring potential errors from input.Err()
	leaving <- ch
	messages <- "irc-server > [" + who + "] has left"
	fmt.Printf("irc-server > [%s] left \n", who)
	conn.Close()
}

func clientWriter(conn net.Conn, ch <-chan string) {
	for msg := range ch {
		fmt.Fprintln(conn, msg) // NOTE: ignoring network errors
	}
}

//!-handleConn

//!+main
func main() {
	host := flag.String("host", "localhost", "host string")
	port := flag.String("port", "9000", "port string")
	flag.Parse()
	fmt.Printf("irc-server > Simple IRC Server startd at %s:%s \n", *host, *port)
	fmt.Printf("irc-server > Ready for receiving new clients \n")
	listener, err := net.Listen("tcp", *host+":"+*port)
	if err != nil {
		log.Fatal(err)
	}
	go broadcaster()
	for {
		conn, err := listener.Accept()
		if err != nil {
			log.Print(err)
			continue
		}
		go handleConn(conn)
	}
}

//!-main
