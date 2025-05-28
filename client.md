# This file is a design sketch for Client

* Title: Fortune Teller Client

* Program requirements:
    - The client must accept excatly one command line argument, which is host name or IP address of the server.
    - It should establish a TCP connection with the server using the predefined server port.
    - Once connected, the client sends a single question to the server.It should ensure only one question is sent before proceeding.
    - After sending the question, the client must wait for a reply from the server, upon receiving the response, the client should display the received string in the terminal.
    - The client must terminate after displaying the server's reply.
    - Errors should be handled gracefully and display meaningful error messages in case of failure.
 
* Program inputs:
    - One string argument is provided when the program is launched.It will represent the server's hostname or IP address.
    - A single yes/no style string type question with a maximum length of 256 bytes(including the terminating null character) user input is taken from the terminal.

* Program outputs:
    - Data received(answer to client's question) from the server over the TCP connection, is printed(as String) directly to the terminal.
    - If there were errors running the program, they were displayed to the terminal.

* Test plan:
    - Case1:
        Ensure that the client can connect to the server sucessfully.
    
    - Input:        
        ./server
        ./client localhost
        Enter your (yes/no) question: Will I get full marks in this assignment

     - Expected output:
        Q: "Will I get full marks in this assignment"
        R: "Signs point to yes"

    - Case2:
        Ensure that the server provides random responses.
    
    - Input:
        ./client localhost
        Enter your (yes/no) question: Will I get a raise this year

    - Expected output:
        Q: "Will I get a raise this year"
        R: "It is certain"

        
    - Input:
        ./client localhost
        Enter your (yes/no) question: Will I get a raise this year

    - Expected output:
        Q: "Will I get a raise this year"
        R: "You may rely on it"


    - Input:
        ./client localhost
        Enter your (yes/no) question: Will I get a raise this year

    - Expected output:
        Q: "Will I get a raise this year"
        R: "Outlook not so good"


    - Input:
        ./client localhost
        Enter your (yes/no) question: Will I get a raise this year

    - Expected output:
        Q: "Will I get a raise this year"
        R: "Cannot predict now"

    - Case 3:
        Check if the client handles invalid inputs properly.

    - Input:
        ./client localhost
        Enter your (yes/no) question:

    - Expected output:
        Error: Please enter a valid input, try again.
        
        Enter your (yes/no) question: Will it rain tommorow

        Q: "Will it rain tommorow"
        R: "Very doubtful"

* Design overview:
    - Introduction:
        The client sends a yes/no question to the server.
        The server responds with a randomly selected fortune form a predefined set of 20 responses.
        The communication follows the TCP protocol for reliable message exchange.
        The server runs continuously and handles multiple client requests one at a time.
        The client terminates after receiving a response.


    - Flow chart:
    
+-------------+                 +---------------+
| Client      |                 |    Server     |
+-------------+                 +---------------+
        |                               |
        |                               |
        |   Connect to server           |
        |------------------------------>|
        |                               |
        |   Send question               |
        |------------------------------>|
        |                               |
        |   Receive response            |
        |<------------------------------|
        |                               |
        |   Display reponse             |
        |                               |
        |   Close connection            |
        |------------------------------>|
        |                               |
    [Client Terminates]         [Server keeps running]


    - Client Pseudocode:
        START CLIENT
            CHECK if hostname is provided
            RESOLVE hostname to IP address
            CREATE socket
            CONNECT to server

            PROMPT user for a question
            SEND question to server
            RECEIVE fortune response from server
            DISPLAY response

            CLOSE connection
        STOP CLIENT







