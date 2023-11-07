# Intelligent Room Access Using Computer Vision
The Intelligent Room Access Using Computer Vision is an innovative solution that combines Python OpenCV, MySQL database, HTML/CSS, PHP and Arduino IDE(C++, Iot)to create a seamless and efficient system. Face recognition algorithms are used in this project to reliably identify persons and record their attendance in real-time. The system offers easy interaction and navigation for users by employing a user-friendly interface designed using Python Tkinter. The MySQL database serves as a dependable repository for securely preserving attendance records and user information. Furthermore, the Arduino IDE connection enables control of the door lock system, providing access to authorized personnel upon successful attendance recognition. This project leverages these technologies to provide a complete, secure, and dependable solution for attendance management and door access control.


To effectively launch the project on your machine, you must follow a few simple steps. First, make sure you've installed all of the dependencies listed in the requirements.txt file. Next, ensure that you have a MySQL server installed and have a basic understanding of its functions. With these prerequisites in place, proceed with the project requirements to establish the necessary database, tables, and declare default data. This includes creating the database, specifying the table architecture, and populating it with default data as needed. You will be able to successfully launch the project on your machine if you follow these procedures.


## execution

- Python 3.11

### for windows user

Before beginning the installation process in Windows, you must complete the following extra steps:
- Follow the instructions described in this video https://www.youtube.com/watch?v=xaDJ5xnc8dc, from the minute 4:39 to 6:07
- Install the packages in requirements.txt Note: If not requirements is not properly installed errors may occur.

### For more info you can directly visit the documentation link: https://github.com/ageitgey/face_recognition

# "face recog.rar" file is the Python Code for Face Recognition
# "public_html.zip" file is the Code for web system
# "database-to-nodeMCU.ino" file is for the door lock. It sends and recieve signals from the PHP-API. Note this file is fot http only if your web uses https implement the "webhost with ssl.txt" instead

## 1. Create a database with this name, "iraucv_db"

create database iraucv_db;

## 2. Now create a table ("employee_details") under that database.

This table is intended for the information of the employees who registered on the system.

CREATE TABLE `employee_details` (
  `employee_number` varchar(50) NOT NULL,
  `employee_name` varchar(100) NOT NULL,
  `gender` varchar(10) NOT NULL,
  `email` varchar(100) NOT NULL,
  `birthdate` date NOT NULL,
  `address1` varchar(100) NOT NULL,
  `address2` varchar(100) NOT NULL,
  `address3` varchar(100) NOT NULL,
  `zipcode` int(4) NOT NULL,
  `date_created` date NOT NULL,
  `time_created` time NOT NULL,
  `account_status` varchar(10) NOT NULL,
  `date_time_updated` datetime(6) NOT NULL DEFAULT current_timestamp(6) ON UPDATE current_timestamp(6),
  PRIMARY KEY (`employee_number`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

## 3. Create another table ("room_1") there

This table is intended to show the status of the room. You can name the tables based on what room they are in (e.g., room_2, room_3, room_4, etc.). The status of the door lock will depend on this table.

CREATE TABLE `room_1` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `status` tinyint(1) DEFAULT 0,
  `accessed_by` varchar(5) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

Insert this to the table "room_1" assuming it will be on initial state:

INSERT INTO `room_1` (`id`, `status`, `accessed_by`) VALUES
(1, 0, 'admin');

## 4. Create another table ("room_1_attendance")

This table is intended for storing data on who logged in or out of a specific room.
Note: Since there's only one room that was deployed, it was named room_1_attendance. Rename it with a better name that will describe the table..

CREATE TABLE `room_1_attendance` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `room_number` varchar(100) NOT NULL,
  `employee_number` varchar(100) NOT NULL,
  `employee_name` varchar(100) NOT NULL,
  `date` date NOT NULL,
  `time_in` time NOT NULL,
  `logged_in_pic` longblob NOT NULL,
  `time_out` time NOT NULL,
  `logged_out_pic` longblob NOT NULL,
  `logged_out_by` varchar(5) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

## 5. Create another table ("user_form")

This table is intended for the web part of the system, which is exclusive to UCU-CEA staff and administrators.

CREATE TABLE `user_form` (
  `id` int(100) NOT NULL AUTO_INCREMENT,
  `name` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(100) NOT NULL,
  `user_type` varchar(25) NOT NULL DEFAULT 'user',
  `status` varchar(50) NOT NULL DEFAULT 'Active',
  PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

INSERT INTO `user_form` (`id`, `name`, `email`, `password`, `user_type`, `status`) VALUES
(1, 'Admin CEA', 'admin@cea.com', 'e85de916711a78e8c58867dceee792d1', 'admin', 'Active');

password = admincea

## 6. Hardware Circuit Design and Development

This sit the simplified instructions for connecting the components in the circuit.
### LM2596 Buck Converter:
   - Connect the positive terminal of the 12V DC adapter to the LM2596's VIN pin.
   - Connect the negative terminal of the 12V DC adapter to the LM2596's GND pin.
   - Use a small screwdriver to adjust the LM2596's output voltage to 5V using the potentiometer. Measure the output voltage with a multimeter at the VOUT and GND pins.

### NodeMCU ESP8266 (U2):
   - Connect the 5V output from the LM2596 to the ESP8266's VIN pin.
   - Connect the GND from the LM2596 to the ESP8266's GND pin.
   - Connect the VCC pin from the relay module to the ESP8266's 3.3V output pin.
   - Connect the GND from the relay module to the ESP8266's GND pin.

### 5V Relay Module:
   - Connect the 3.3V output from the ESP8266 to the relay module's VCC pin.
   - Connect the GND from the ESP8266 to the relay module's GND pin.
   - Connect a digital output pin (e.g., D1 GPIO5) from the ESP8266 to the relay module's IN pin.

### Solenoid Door Lock:
   - Connect the positive terminal of the solenoid door lock to either the NC (Normally Closed) or NO (Normally Open) pin on the relay module, depending on the desired behavior. 
   - Connect the negative terminal of the solenoid door lock to the negative terminal of the 12V DC adapter.
   - Connect the positive terminal of the 12V DC adapter to the COM (Common) pin on the relay module.
   - Connect the negative terminal of the 12V DC adapter to the other terminal of the solenoid's negative terminal.

Now, you can control the solenoid door lock by setting the digital output pin (D1 GPIO5 in this case) on the ESP8266 to HIGH or LOW. To open the door lock (energize the solenoid), set the pin to HIGH if using the NC configuration or to LOW if using the NO configuration.


## 7. To make the system auto start
### Create a bat file containing this code:
@echo off
cd (Directory of the python file)
start "" osk.exe
python main.py
pause

### Create a shortcut of the bat file
### Press windows + R then type "shell:startup" and paste the shortcut of the bat file.

## 8. Note: No Copyright Infringement Intended

This system was created solely for academic purposes, ensuring complete conformity with copyright regulations. The developer would like to thank and recognize the various web resources that served as the foundation for this system. It is critical to note that this implementation, which functions as an face recognition, attendance, and door lock system, has been specifically customized for its intended purpose. While drawing on existing publicly available systems for inspiration, this implementation stands apart from any previously disclosed system. The developer's vision, purpose, and purposeful changes have all played a role in building this system. This system was initially developed using a variety of web resources, and it was later improved by Vener C. Servito, a Computer Engineering student at Urdaneta City University.

## 9. CPEnois TEAM:

Labrador, Hilbert R. - Research Encoder

Mandapat, Jesus G. - Circuit Assembler

Porras, Karlo L. - Survey Conductee

Servito, Vener C. - System Developer

Vallinan, John Lloyd S. - Leader
