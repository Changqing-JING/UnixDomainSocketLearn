cmake_minimum_required(VERSION 3.5)

project(UnixDomainSocketLearn)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads)

aux_source_directory(client clientSources)
aux_source_directory(server serverSources)
aux_source_directory(boost_client boostClientSources)
aux_source_directory(boost_server boostServerSources)

add_executable(client ${clientSources})
add_executable(server ${serverSources})

add_executable(boost_client ${boostClientSources})
add_executable(boost_server ${boostServerSources})

target_link_libraries(boost_client ${Boost_LIBRARIES} Threads::Threads)
target_link_libraries(boost_server ${Boost_LIBRARIES} Threads::Threads)
