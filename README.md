# Spotify Replica Project

## Overview

This project is a replica of Spotify, implementing basic functionalities such as user authentication, music library management, and search capabilities.

## Features

- **User Authentication:** Users can sign up with a username and a strong password. Password strength criteria include at least 8 characters, including one symbol, one digit, one uppercase, and one lowercase letter.
  
- **Music Library Management:** The application manages a collection of songs stored in a text file (`songs_file.txt`). It supports functionalities such as displaying available songs, showing lyrics, and searching songs by various criteria (artist, name, rating, genre).
  
- **Search Functionality:** Users can search for songs based on artist name, song name, rating, or genre.

## Project Structure

The project is structured as follows:

- **`main.cpp`:** Contains the main function and integrates all components of the Spotify replica.
  
- **`User`, `Song`, `FileHandler`, `MusicLibrary`, `MusicManager` classes:** Implements the core functionalities of user management, song representation, file handling, music library operations, and user interaction management.
  
- **`songs_file.txt`:** Text file containing details of songs used by the application.

## Conclusion

This Spotify replica project demonstrates the application of Object-Oriented Programming (OOP) principles in building a music player application. By utilizing concepts such as inheritance, encapsulation, and polymorphism, we have created a modular and extensible system. The project features user authentication, comprehensive music library management, and robust search capabilities, providing users with a seamless music listening experience.
