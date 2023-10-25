# Use an official Ubuntu runtime as a base image
FROM ubuntu:latest

# Install g++ and make
RUN apt-get update && apt-get install -y g++ make

# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the program
RUN make

# Run the program
CMD ["./threads-assignment"]