#!/bin/sh
export current_directory=`pwd`
project_root_dir=$current_directory

echo "Hello Friend! Let's try and build this application together :D"

# compile the rest of the application
cd ${project_root_dir}

mkdir -p ${project_root_dir}/third_party
cd ${project_root_dir}/third_party
if [ ! -d "sfml_lib" ]; then
    git clone https://github.com/SFML/SFML.git sfml_lib
    cd ${project_root_dir}/third_party/sfml_lib
    git fetch --tags --depth 1
    git checkout -b 2.6.2 tags/2.6.2
    
    rm -rf build install
    mkdir -p build && mkdir -p install && cd build
    cmake -DCMAKE_INSTALL_PREFIX="${project_root_dir}/third_party/sfml_lib/install" -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS:BOOL=ON ..
    cmake --build . --config Release -j 4
    cmake --install . --config Release

    mkdir -p "${project_root_dir}/third_party/sfml_lib/install/Frameworks/freetype.framework"
    cp -r "${project_root_dir}/third_party/sfml_lib/install/lib/freetype.framework" "${project_root_dir}/third_party/sfml_lib/install/Frameworks/"
fi

# remove the build directory that has the current code in it
echo "deleting the BUILD directory"
# rm -rf ${project_root_dir}/build
rm -rf ${project_root_dir}/install

echo "make a new BUILD directory to start the compiling process"
mkdir -p ${project_root_dir}/build
cd ${project_root_dir}/build

echo "cmake engage!"
cmake ..

echo "convert this to an executable application -- let's go!!"
cmake --build . -j 4
cmake --install .

echo "Copying Images folder to build directory"
cp -r ${project_root_dir}/Images ${project_root_dir}/build/Images

cd ${project_root_dir}
echo "declare success -- hooray!"

echo "running the executable ..."
cd ${project_root_dir}/build
./main
