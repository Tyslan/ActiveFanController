if [ ! -d "build" ]; then
  echo "build folder doesn't exists. Creating one."
  mkdir build
fi

cd build
cmake ../src
cmake --build .

echo "ActiveFanControl is available in the build folder."