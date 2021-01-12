cmake_minimum_required(VERSION 3.7)
project(ts)

function(my_ts_add_executable targetname srcs depends libs)
    add_executable(${targetname} ${srcs})
    add_dependencies(${targetname} ${depends})
    #force_redefine_file_macro_for_source(${targetname})
    target_link_libraries(${targetname} ${libs})
endfunction()

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -march=native -D__STDC_FORMAT_MACROS -rdynamic -O0 -ggdb -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

include_directories("."
                    "./ts")

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

set(LIBS ${PROJECT_NAME}
        pthread
        dl
        pcre
        tcl
        hwloc
        cap
        m
        rt
        ${OPENSSL_LIBRARIES}
        )

set(LIB_SRC
        ts/Allocator.h
        ts/apidefs.h
        ts/Arena.cc
        ts/Arena.h
        ts/BaseLogFile.cc
        ts/BaseLogFile.h
        ts/Bitops.cc
        ts/Bitops.h
        ts/CompileParseRules.cc
        ts/ConsistentHash.cc
        ts/ConsistentHash.h
        ts/ContFlags.cc
        ts/ContFlags.h
        ts/CryptoHash.h
        ts/defalloc.h
        ts/Diags.cc
        ts/Diags.h
        ts/DynArray.h
        ts/EventNotify.cc
        ts/EventNotify.h
        ts/fastlz.c
        ts/fastlz.h
        ts/Hash.cc
        ts/Hash.h
        ts/HashFNV.cc
        ts/HashFNV.h
        ts/HashMD5.cc
        ts/HashMD5.h
        ts/HashSip.cc
        ts/HashSip.h
        ts/HostLookup.cc
        #ts/HostLookup.h
        ts/hugepages.cc
        ts/hugepages.h
        ts/I_Layout.h
        ts/I_Version.h
        ts/ink_aiocb.h
        ts/ink_align.h
        ts/ink_apidefs.h
        ts/ink_args.cc
        ts/ink_args.h
        ts/ink_assert.cc
        ts/ink_assert.h
        ts/ink_atomic.h
        ts/ink_base64.cc
        ts/ink_base64.h
        ts/ink_cap.cc
        ts/ink_cap.h
        ts/ink_code.cc
        ts/ink_code.h
        ts/ink_config.h
        ts/ink_defs.cc
        ts/ink_defs.h
        ts/ink_error.cc
        ts/ink_error.h
        ts/ink_exception.h
        ts/ink_file.cc
        ts/ink_file.h
        ts/ink_hash_table.cc
        ts/ink_hash_table.h
        ts/ink_hrtime.cc
        ts/ink_hrtime.h
        ts/ink_inet.cc
        ts/ink_inet.h
        ts/ink_inout.h
        ts/ink_llqueue.h
        ts/ink_lockfile.h
        ts/INK_MD5.h
        ts/ink_memory.cc
        ts/ink_memory.h
        ts/ink_mutex.cc
        ts/ink_mutex.h
        ts/ink_platform.h
        ts/ink_queue.cc
        ts/ink_queue.h
        ts/ink_queue_utils.cc
        ts/ink_queue_ext.cc
        ts/ink_queue_ext.h
        ts/ink_rand.cc
        ts/ink_rand.h
        ts/ink_res_init.cc
        ts/ink_res_mkquery.cc
        ts/ink_resolver.h
        ts/ink_resource.cc
        ts/ink_resource.h
        ts/ink_rwlock.cc
        ts/ink_rwlock.h
        ts/ink_sock.cc
        ts/ink_sock.h
        ts/ink_sprintf.cc
        ts/ink_sprintf.h
        ts/ink_stack_trace.cc
        ts/ink_stack_trace.h
        ts/ink_string++.cc
        ts/ink_string++.h
        ts/ink_string.cc
        ts/ink_string.h
        ts/ink_sys_control.cc
        ts/ink_sys_control.h
        ts/ink_syslog.cc
        ts/ink_syslog.h
        ts/ink_thread.cc
        ts/ink_thread.h
        ts/ink_time.cc
        ts/ink_time.h
        ts/InkErrno.h
        ts/IntrusiveDList.h
        #ts/IntrusivePtrTest.cc
        ts/IpMap.cc
        ts/IpMap.h
        ts/IpMapConf.cc
        ts/IpMapConf.h
        #ts/IpMapTest.cc
        ts/Layout.cc
        ts/List.h
        ts/llqueue.cc
        #ts/load_http_hdr.cc
        ts/lockfile.cc
        ts/Map.h
        ts/MatcherUtils.cc
        ts/MatcherUtils.h
        #ts/mkdfa.c
        ts/MMH.cc
        ts/MMH.h
        ts/ParseRules.cc
        ts/ParseRules.h
        ts/PriorityQueue.h
        ts/Ptr.h
        ts/RawHashTable.cc
        ts/RawHashTable.h
        ts/RbTree.cc
        ts/RbTree.h
        ts/Regex.cc
        ts/Regex.h
        ts/Regression.cc
        ts/Regression.h
        ts/signals.cc
        ts/signals.h
        ts/SimpleTokenizer.h
        #ts/TestBox.h
        #ts/TestHttpHeader.cc
        ts/TextBuffer.cc
        ts/TextBuffer.h
        ts/Tokenizer.cc
        ts/Tokenizer.h
        ts/Trie.h
        ts/TsBuffer.h
        ts/Vec.cc
        ts/Vec.h
        ts/Version.cc #TODO
        ts/X509HostnameValidator.cc
        ts/X509HostnameValidator.h
        )

add_library(${PROJECT_NAME} SHARED ${LIB_SRC})
add_library(${PROJECT_NAME}_static STATIC ${LIB_SRC})

option(TEST "ON for complile test" ON)
if(TEST)
  my_ts_add_executable(diags_test test/diags_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(list_test test/list_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(arena_test test/arena_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(atomic_test test/atomic_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(freelist_test test/freelist_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(map_test test/map_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(pq_test test/pq_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(regex_test test/regex_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(vector_test test/vector_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(geometry_test test/geometry_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(x509_test test/x509_test.cc ${PROJECT_NAME} "${LIBS}")

  my_ts_add_executable(mem_test test/mem_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(ptr_test test/ptr_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(token_test test/token_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(event_notify_test test/event_notify_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(fastlz_test test/fastlz_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(dynarray_test test/dynarray_test.cc ${PROJECT_NAME} "${LIBS}")
  #my_ts_add_executable(hostlookup_test test/hostlookup_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(hugepage_test test/hugepage_test.cc ${PROJECT_NAME} "${LIBS}")
  my_ts_add_executable(args_test test/args_test.cc ${PROJECT_NAME} "${LIBS}")
endif()

#test_geometry.cc
#test_Regex.cc
#test_Vec.cc
#test_X509HostnameValidator.cc
