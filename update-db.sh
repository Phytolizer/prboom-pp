rm -rf db && rm -rf build && codeql database create db -l cpp -c "cmake -Wno-dev -Bbuild prboom2" -c "cmake --build build" -j 9

