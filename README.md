# Movies Application


## A movies management application written in C++ that lets the user to create it's own watch list using the available movies

This project was build as a homework for my last assignment in the second semester of my faculty. It's main objective was to simulate a local database of movies having both admin and user GUI

## Features:
* Choose what type of file you want the user's watch list to be saved as (CSV or HTML)
* All movies read from a txt file
* Unlimited undos redos
  
## Mode Menu:
* Select as what you want to connect (admin or user)
## Admin Interface:
* Button "Back": returns you to the menu where you have to select the mode
* Button "Add": adds to the list the movie with the information from the line edits
* Button "Delete": deletes from the list the movie with the title and year from the line edits
* Button "Update": updates the movie from the list with the same title and year with the information from the line edits
* Button "Undo": undos the previous action
* Button "Redo": redos the previous action
* List item clicked: fills the line edits with the information of the movie clicked
## User Interface:
* Button "Back": returns you to the menu where you have to select the mode
* Button "Play": plays the trailer of the movie selected from the respective list
* Button "Delete": deletes from the watch list the movie selected
* Button "Save": saves the watch list as a file(CSV or HTML)
* Button "Display": opens the watch list file saved
* Button "Add": adds to the watch list the movie selected
* Line edit text changed: updates the search list with the movies that match the genre written
  
## Implementation:
* Object Oriented Programming
* MVC design pattern
* Layered architecture
*  Custom errors handling
*  Qt framework GUI
* Undo and redo actions saved in unique pointers


## Preview

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/f37de7bd-7e42-4cfa-b6eb-766181919c27)

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/3cec59c3-52ad-4cfa-94f7-708fefa7f092)

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/cfe8bf40-bd40-43d7-95d4-4b81c9b9326c)

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/00002fe5-8972-4038-896a-9ae5b9f68560)

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/256f86d8-9982-448d-8d0a-23a5c45c6b8f)

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/0254817b-5159-43c4-beca-a38e07a9a459)

![image](https://github.com/Stefan2114/Movies--Application/assets/147135917/3bb45785-66a5-4b85-bf2f-554633181d96)
