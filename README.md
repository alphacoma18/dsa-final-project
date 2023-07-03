# Machine Problem: Video Rental Store

## Text Files

### Video Format

Line 1: id
Line 2: Movie Title
Line 3: Genre
Line 4: Production
Line 5: Number of Copies

### Customer Format

Line 1: id
Line 2: Name
Line 3: Address

### Rental Format

Line 1: id
Line 2: Customer_ID
Line 3: Video_ID (of all rented videos of a customer)

### Persist Format

Line 1: Last Video ID
Line 2: Last Customer ID
Line 3: Last Rental ID

## How to Run (VS Code)

1. Open the project folder in VS Code
2. Install the Code Runner extension
3. Modify cpp map executor to `cd $dir && g++ *.cpp -o $fileNameWithoutExt && $dir$fileNameWithoutExt`
4. Run the program from `main.cpp`

## Database Implementation

### Explanation

Video, Customer, and Rental are the three tables used in the database. Customers and Rentals are in a one-to-many relationship. Video and Rental are in a many-to-many relationship. The Rental table is the bridge table between Video and Customer.

### Codes

#### Video

```sql
CREATE TABLE Video (
    id INT NOT NULL AUTO_INCREMENT,
    title VARCHAR(255) NOT NULL,
    genre VARCHAR(255) NOT NULL,
    production VARCHAR(255) NOT NULL,
    copies INT NOT NULL,
)
```

#### Rental

```sql
CREATE TABLE Rental (
    id INT NOT NULL AUTO_INCREMENT,
    customer_id INT NOT NULL,
    video_id INT NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (customer_id) REFERENCES customer(id),
    FOREIGN KEY (video_id) REFERENCES video(id)
)
```

#### Customer

```sql
CREATE TABLE Customer (
    id INT NOT NULL AUTO_INCREMENT,
    name VARCHAR(255) NOT NULL,
    address VARCHAR(255) NOT NULL,
    PRIMARY KEY (id)
)
```

## Members

- Enrico Casas, Documentation
- Justine Mae Celestial, QA
- Rab Karl Colasino, Programmer 1
- Alpha Romer Coma, Lead Programmer
- Raphael Andre Mercado, Programmer 2
