# http-server

Lightweight, simple static file serving http server written in C++.  
Created as a way to learn low-level socket programming in C++ and more about the HTTP protocol.

## Features

- Handles HTTP requests and responses.
- Supports multiple concurrent connections.
- Lightweight and fast.
- Serves static files with proper MIME type detection.
- Demonstrates foundational concepts of socket programming and multithreading in C++.

## Requirements

- C++17 or later
- **Only tested on Linux, may require some changes to work on windows**

## Installation

1. Clone the repository

2. Build the project:

3. Create a directory named "htdocs"

4. Populate the directory with web files, example: 
```bash
htdocs/
>index.html
>style.css
>index.js
```

5. Run main and connect, localhost:8080