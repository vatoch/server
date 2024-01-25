# Use a base image with a full Linux distribution
FROM gcc:latest

# Set the working directory inside the container
WORKDIR /app

# Copy the source code into the container
COPY . /app

# Compile the C application
RUN gcc -o myapp server.c

# Optionally, you can remove the source code to reduce the image size
# RUN rm -rf /app

# Expose the port your application will run on (if applicable)
EXPOSE 8081

# Command to run your application
CMD ["./myapp"]

