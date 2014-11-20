cmake_minimum_required(VERSION 2.8)

# Look for boost
include(../depends/cmake/boost_install.txt)
BoostInstall()
list(APPEND paths -DBOOST_ROOT:PATH=${BOOST_ROOT} -DBoost_Version:STRING=${Boost_Version})

# Look for loki
include(../depends/cmake/loki_install.txt)
LokiInstall()
list(APPEND paths -DLOKI_ROOT:PATH=${LOKI_ROOT} -DLOKI_Revno:STRING=${LOKI_Revno})

# Look for expat
include(../depends/cmake/expat_install.txt)
EXPATInstall()
list(APPEND paths -DEXPAT_ROOT:PATH=${EXPAT_ROOT} -DEXPAT_Version:STRING=${EXPAT_Version})

# Look for xml_parser
include(../depends/cmake/_install.txt)
set(XML_PARSER_LIBRARIES "xml_parser")
_Install(xml_parser "${paths}")
list(APPEND paths -Dxml_parser_DIR:PATH=${xml_parser_DIR} -Dxml_parser_Version:STRING=${xml_parser_Version})

# For precompiled headers
include(../depends/cmake/use_precompiled_header2.cmake)

# Add sub-directories
add_subdirectory(architecture)
add_subdirectory(comunication)
add_subdirectory(config)
add_subdirectory(draw)
add_subdirectory(factory)
add_subdirectory(graph)
add_subdirectory(pattern)
add_subdirectory(status_track)
add_subdirectory(utils)
add_subdirectory(settings)