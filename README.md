# TCP Fortune Client-Server

This is a multi-threaded TCP client-server application written in C. The server sends randomized "fortune" messages to connected clients over a custom TCP protocol.

## Features

- Developed in C using POSIX sockets and threading
- Handles multiple clients concurrently using `pthread`
- Custom message protocol with structured responses
- Clean separation of client and server logic

## How It Works

1. Server listens on a specified port and spawns a new thread for each client.
2. Clients connect via TCP and receive a random "fortune" message from a predefined set.
3. Server uses synchronization to manage concurrent access to shared resources.

## Tech Stack

- C
- TCP/IP Sockets
- POSIX Threads
- Linux

## Usage

### Build

```bash
make all
