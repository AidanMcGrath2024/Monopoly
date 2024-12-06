#!/bin/sh
export current_directory=`pwd`
project_root_dir=$current_directory

echo "Hello Friend! Let's try and build this application together :D"


# compile the rest of the application
cd ${project_root_dir}

# remove the build directory that has the current code in it
echo "deleting the BUILD directory"
rm -rf ${project_root_dir}/build
rm -rf ${project_root_dir}/install

echo "make a new BUILD directory to start the compiling process"
mkdir -p ${project_root_dir}/build
cd ${project_root_dir}/build

echo "cmake engage!"
cmake ..

echo "convert this to an executable application -- let's go!!"
cmake --build . -j 4
cmake --install .
cd ${project_root_dir}
echo "declare success -- hooray!"

echo "running the executable with some default parameters"
echo "./build/main -c config.inp > results.txt 2>&1"
echo "  the 2>&1 redirects the stderr to a 1 so we don't see the gnuplot problems"
mkdir -p ${project_root_dir}/results
./build/main -c config.inp > results/results.txt 2>&1
