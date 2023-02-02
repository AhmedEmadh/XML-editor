# Project Description

## Introduction
XML (Extensible Markup Language) is one of the most famous formats for storing and sharing
information among different devices. Some text editors such as Sublime Text are able to parse
such files and do some basic operations. In this project, you will work on developing a GUI
(Graphical User Interface) based program to parse and visualize an XML file.

In our system the XML file will represent users in a social network <br>
Each user has id (unique), name, list of posts, list of followers. <br>
Each post has text and list of topics.

Here you can find a sample of input file: [https://drive.google.com/file/d/1_GeHIjYQZEAZNu6ZxdXEotPnHhiKnaWn/view](https://drive.google.com/file/d/1_GeHIjYQZEAZNu6ZxdXEotPnHhiKnaWn/view)

## Why this project?
In this project, you will learn how to understand and parse XML and json files. Additionally, you
will work on designing a GUI (Graphical User Interface) to visualize XML and json files. You
should also work on designing the program such that it makes use of optimal data structures
for the implemented features.

## Requirements

- Building a GUI in which the user can specify the location of an input XML file.

- Checking the XML consistency: The input XML may have inconsistencies like missing any
of the closing and opening tags or not matching tags.The program should be able to detect
and visually show any errors in consistency. Optimally, the program will also be able to
automatically solve the errors.
- Formatting (Prettifying) the XML: the XML file should be well formatted by keeping the indentation for each level.
- Converting XML to JSON: JSON (Javascript Object Notation) is another format that is used to represent data. It’s helpful to convert the XML into JSON, especially when using javascript as there’s tons of libraries and tools that use json notation.
- Minifying the XML file: Since spaces and newlines (\n) are actually characters that can increase the size of an XML document. This feature should aim at decreasing the size of an XML file (compressing it) by deleting the whitespaces and indentations.
- Compressing the data in the XML/JSON file: You should come-up with a way to reduce the size of the file using a data compression technique. You can invent your own ad-hoc method for such compression. On the other hand, you can check how JSONH works and try to distill ideas from it. Finally, you can use a data compression technique such as byte pair encoding (https://en.wikipedia.org/wiki/Byte_pair_encoding). The smaller the output file is, the more efficient your algorithm is.
- Representing the users data using the graph data structure: the XML file will represent the users data in a social network (their posts, followers, ...etc). The user data is his id (unique across the network), name, list of his posts and followers. So you should represent the relation between the followers using the graph data structure as it will be very helpful for the network analysis. If the input file was like this (the dots mean that there are additional tags inside the user tag) : Then you should build a graph relation between the user that looks like the graph beneath.
- Network analysis: by representing the network using the graph data structure, we can extract some important data: <br>
&emsp;  - who is the most influencer user (has the most followers) <br>
&emsp;  - who is the most active user (connected to lots of users) <br>
&emsp;  - the mutual followers between 2 users <br>
&emsp;  - for each user, suggest a list of users to follow (the followers of his followers) <br>

- Post search: given a specific word or topic, get the posts where this word or topic was mentioned.

## Bonus Requirements
- Graph visualization: you’re free to use any tool or 3rd party library to help you visualize the graph of the network showing how the user is connected to each other.<br>

- Additional operations: you’re free to implement additional operations to help you analyze the network better.
