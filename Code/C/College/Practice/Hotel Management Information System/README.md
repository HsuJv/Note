<!-- MarkdownTOC -->

- [Software Requirements Specification](#software-requirements-specification)
    - [Introduction](#introduction)
        - [Target](#target)
    - [Cases](#cases)
    - [Overall description](#overall-description)
        - [User class and user characteristics](#user-class-and-user-characteristics)
        - [Runtime Environment](#runtime-environment)
        - [Design and implementation constraints](#design-and-implementation-constraints)
        - [User Documentation](#user-documentation)
    - [Other non-functional requirements](#other-non-functional-requirements)
        - [Security](#security)
        - [Integrity](#integrity)
    - [Data Dictionary](#data-dictionary)

<!-- /MarkdownTOC -->

## Software Requirements Specification

### Introduction

##### Target
+ *Hotel Management Information System(HMIS)* is a software system responsible for the overall management of room booking and customer records.

### Cases
<table>
    <caption>Major players and user cases</caption>
    <thead>
        <tr>
            <th>Major Players</th>
            <th>User Cases</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td rowspan="5">Manager</td>
            <td>Set/amend classes for each room and the price per class. Each room should have a single price. </td>
        </tr>
        <tr>
            <td>Provide a fixed discount on the regular price of rooms for special circumstances, e.g. group bookings. </td>
        </tr>
        <tr>
            <td>Manage a customer database (add/edit/remove customers) </td>
        </tr>
        <tr>
            <td>Manage a cashier database (add/remove cashier) </td>
        </tr>
        <tr>
            <td>View hotel business statistics. </td>
        </tr>
        <tr>
            <td rowspan="3">Guest</td>
            <td> Register a booking (by recording a customer’s name, address, telephone number and hotel member card no.). Customers without a hotel membership card, cannot book a VIP room. </td>
        </tr>
        <tr>
            <td>A search facility should be provided for room availability and dates.</td>
        </tr>
        <tr>
            <td>Additionally, the operator can book one or more rooms to a registered customer and at a regular or discounted price.</td>
        </tr>
        <tr>
            <td rowspan="3">Cashier</td>
            <td>Record the arrival of a customer in the system.</td>
        </tr>
        <tr>
            <td>Edit booking details e.g. period of stay or room. </td>
        </tr>
        <tr>
            <td>Check-out customers by calculating charges or even change the payment from the regular to the discounted price if the customer was dissatisfied. </td>
        </tr>
    </tbody>
</table>


### Overall description

##### User class and user characteristics
<table>
    <caption>Manager</caption>
    <thead>
        <tr>
            <th>Type</th>
            <th>Var Name</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>char*</td>
            <td>password</td>
        </tr>
    </tbody>
</table>
<table>
    <caption>VIP Guest</caption>
    <thead>
        <tr>
            <th>Type</th>
            <th>Var Name</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>char*</td>
            <td>name</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>address</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>telephone</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>membership card</td>
        </tr>
    </tbody>
</table>
<table>
    <caption>Cashier</caption>
    <thead>
        <tr>
            <th>Type</th>
            <th>Var Name</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>char*</td>
            <td>account</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>password</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>stuff number</td>
        </tr>
    </tbody>
</table>
<table>
    <caption>Room</caption>
    <thead>
        <tr>
            <th>Type</th>
            <th>Var Name</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>unsigned int</td>
            <td>room number</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>class</td>
        </tr> 
        <tr>
            <td>int</td>
            <td>occupied</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>occupied period</td>
        </tr>
    </tbody>
</table>
<table>
    <caption>Bill</caption>
    <thead>
        <tr>
            <th>Type</th>
            <th>Var Name</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <td>unsigned int</td>
            <td>bill number</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>name</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>membership card</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>tel</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>room number</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>room class</td>
        </tr>
        <tr>
            <td>unsigned int</td>
            <td>stuff number</td>
        </tr>
        <tr>
            <td>double</td>
            <td>account payable</td>
        </tr>
        <tr>
            <td>double</td>
            <td>account paid</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>period</td>
        </tr>
        <tr>
            <td>char*</td>
            <td>date</td>
        </tr>
    </tbody>
</table>

##### Runtime Environment
+ Vcruntime140.dll (which is included in vc++2015 redistributable) needed.

##### Design and implementation constraints
+ All the designs, codings follow the standards of C11 (ISO/IEC 9899:2011 - Information technology -- Programming languages -- C).
+ All source files will be compiled by Microsoft Visual Studio Community 2015.

##### User Documentation
+ The default administrator's account is created, you must change the password as soon as achieving this production.
+ If you are a new user to this production and are not an administrator, you must call the administrator to create a new account for you.

### Other non-functional requirements

##### Security
+ All the data are ex-Vigenère encrypted.
+ The passwords are md5 encrypted especially.

##### Integrity
+ The system should have the functionality to prevent unauthorized access to the system to prevent data loss or tampering. 
+ To ensure the integrity of the data correlation. User access to records, data and access must be fully protected by a specific method to establish appropriate protection.

### Data Dictionary
+ Guest Information = name + address + telephone + membership card
+ Manager Information = password
+ Cashier Information = account + password + staff number
+ Room Information = room number + room class + occupied + occupied period
+ Bill Information = Guest Information->name + Guest Information->tel + Guest Information->membership card + Room->room number + Room->room class + Cashier Information->staff number + account payable + account paid + period + date
