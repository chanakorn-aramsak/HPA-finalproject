# HPA-finalproject
## terasort
to update terasort into docker image
```sh
docker login
docker build -t clickads/terasort:latest .
docker push clickads/terasort:latest
```

To run the command:

1. Change directory to the folder that contains the input file `sort-rand-199999999.txt`:
`cd /path/to/folder`
2. Optionally, replace `sort-rand-199999999.txt` with another input file. Make sure that the file is located in the current directory.
3. Run the command:
`time docker run -v $PWD:/input -v $PWD:/output clickads/terasort:latest ./prog /input/sort-rand-199999999.txt /output/out.txt`

This command runs a Docker container that uses the `clickads/terasort` image and sorts the specified input file from the `/input` directory to the `/output/out.txt` file. The `time` command is used to measure the execution time of the command.

Replace `/path/to/folder` with the absolute path of the folder that contains the input file. Replace `sort-rand-199999999.txt` with the filename of the input file you want to use.

Note that the `clickads/terasort` image is not provided in this snippet and needs to be downloaded separately.


## powergrid
to update powergrid into docker image

```sh
docker login
docker build -t clickads/powergrid:latest .
docker push clickads/powergrid:latest
```

To run the command:

1. Change directory to the folder that contains the input file `grid-6-7.txt`:
`cd /path/to/folder`
2. Optionally, replace `grid-6-7.txt` with another input file. Make sure that the file is located in the current directory.
3. Run the command:
`time docker run -v $PWD:/input -v $PWD:/output clickads/powergrid:latest ./prog /input/grid-6-7 /output/out.txt`

This command runs a Docker container that uses the `clickads/powergrid` image and sorts the specified input file from the `/input` directory to the `/output/out.txt` file. The `time` command is used to measure the execution time of the command.

Replace `/path/to/folder` with the absolute path of the folder that contains the input file. Replace `grid-6-7.txt` with the filename of the input file you want to use.

Note that the `clickads/powergrid` image is not provided in this snippet and needs to be downloaded separately.