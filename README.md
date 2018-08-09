# Amazoom

For this course project, you will design and implement a real-time simulation of the system
software that runs an automated warehouse. You are responsible for producing a design
document that describes the system architecture and information 􀃓ow for your automated
warehouse design, as well as a multi-process, multi-threaded simulation of the software to prove to
Amazoom that your design is safe, e􀃕cient, and will satisfy all their needs.

Introduction

Amazoom is the largest internet-based retailer in the world, selling and shipping everything from
bananas to laptops to engagement rings. They’re currently looking to cut costs by automating all of
their warehouses, but they do not have the in-house expertise to design such a thing. They just put
out an open call for proposals.

Warehouse Function

Layout
Amazoom’s warehouses are laid out on a grid, with long aisles of shelving. Their products are
randomly distributed on the shelves (e.g. pickles can be next to perfume) to allow for faster
collection of items when putting together an order. The warehouse grid and shelves are labelled so
that products can be easily located. For example, a box of Kleenex might be stored at (A, 3, right, 6),
which corresponds to column A, row 3, on the right-hand side, and the 6th shelf from the bottom.
Each shelving space – corresponding to a single coordinate – has a limited weight capacity for
storing items.

Central Computer
The warehouse has a central computer system that is used to keep track of:
* a database of products and inventory 
* the locations of inventory within the warehouse
* a list of orders received, orders ready for delivery, and orders out for delivery
* the arrival/departure of delivery and restocking trucks

When orders are placed, the computer plans the routes to take to collect items. When restocking,
the computer plans the route and locations for new items to be placed. This makes the process
ideal for automation.

Orders come in from a single remote webserver. If the warehouse has all the items requested, it
fulfils the order by:
* updating the inventory list to re􀃓ect the sale
* inserting the order into a queue to be collected for delivery

All items in the order are collected and brought to the next waiting delivery truck. Once on the
truck, the central warehouse computer is noti􀃒ed that the order is ready for delivery.
The computer also provides a user-interface where the warehouse manager can
* query the status of an order
* check the number in stock of an item
* get alerts about low-stock items

Automation
Amazoom wants to automate the collecting and loading of orders for delivery, and the restocking of
items onto warehouse shelves.
Your engineering 􀃒rm has already designed the perfect robots for the job. They can be wirelessly
controlled, have advanced object recognition, automated navigation, and collision avoidance
capabilities. They are both extremely strong and dexterous, capable of picking up any item that
Amazoom sells. The robots do have a certain carrying capacity by weight, however, limiting the
number of items they can transport at a time.

Your job, as the new system software engineer, is to design and implement the software that runs
the entire warehouse operation. This includes software processes for:
* The central warehouse computer
* The user-interface for the computer
* The automation robots
* The remote webserver that places orders
* Delivery and restocking trucks




