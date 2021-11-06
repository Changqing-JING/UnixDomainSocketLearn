cmake_minimum_required(VERSION 3.5)

project(UnixDomainSocketLearn)

aux_source_directory(client clientSources)
aux_source_directory(server serverSources)

add_executable(client ${clientSources})
add_executable(server ${serverSources})