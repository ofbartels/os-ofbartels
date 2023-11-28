# Use an official Ubuntu runtime as a base image
FROM ubuntu:latest

# Update packages and install g++ and make
RUN apt-get update && apt-get install -y g++ make

# Install additional libraries needed for the cryptographic operations
RUN apt-get install -y libc6-dev

# Install OpenSSL development libraries
RUN apt-get install -y libssl-dev

# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the program (assuming your Makefile is compatible with g++ and make on Linux)
RUN make

# Run the program (adjust the executable name as necessary)
CMD ["./encrypted-message"]