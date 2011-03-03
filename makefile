EXE=
LIBSRC=utils/obj


bin : bin/WebCrawl

memTest : bin/TestDriver
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=test/config/string.supp  bin/TestDriver

test : bin/TestDriver
	bin/TestDriver

clean :
	@- rm -f obj/*.o > /dev/null 2>&1
	@- rm -f lib/*.a > /dev/null 2>&1
	@- rm -f utils/obj/*.o > /dev/null 2>&1
	@- rm -f bin/* > /dev/null 2>&1

bin/WebCrawl : obj/MainDriver.o lib/libutils.a obj/StopWords.o obj/Url.o
	g++ -o bin/WebCrawl obj/*.o lib/libutils.a

bin/TestDriver : obj/TestDriver.o lib/libutils.a obj/StopWords.o obj/Url.o obj/PageDownloader.o obj/HTMLParser.o
	g++ -o bin/TestDriver obj/*.o lib/libutils.a

obj/MainDriver.o : src/MainDriver.cpp
	g++ -c -Wall -o obj/MainDriver.o -I inc/ -I utils/inc src/MainDriver.cpp

obj/TestDriver.o : src/TestDriver.cpp
	g++ -c -Wall -o obj/TestDriver.o -I inc/ -I utils/inc src/TestDriver.cpp

obj/WebCrawler.o : src/WebCrawler.cpp inc/WebCrawler.h
	g++ -c -o obj/WebCrawler.o -I inc/ -I utils/inc src/WebCrawler.cpp

obj/StopWords.o : src/StopWords.cpp inc/StopWords.h
	g++ -c -o obj/StopWords.o -I inc/ -I utils/inc src/StopWords.cpp

obj/Url.o : src/Url.cpp inc/Url.h
	g++ -c -o obj/Url.o -I inc/ -I utils/inc src/Url.cpp

obj/PageDownloader.o : src/PageDownloader.cpp inc/PageDownloader.h
	g++ -c -o obj/PageDownloader.o -I inc/ -I utils/inc src/PageDownloader.cpp

obj/HTMLParser.o : src/HTMLParser.cpp inc/HTMLParser.h
	g++ -c -o obj/HTMLParser.o -I inc/ -I utils/inc src/HTMLParser.cpp

# library
#

lib : lib/libutils.a

lib/libutils.a : utils/obj/CommandRunner.o  utils/obj/FileInputStream.o  utils/obj/FileSystem.o utils/obj/HTMLToken.o utils/obj/HTMLTokenizer.o utils/obj/HTTPInputStream.o  utils/obj/StringUtil.o utils/obj/URLInputStream.o
	ar r lib/libutils.a utils/obj/*.o

utils/obj/CommandRunner.o: utils/src/CommandRunner.cpp utils/inc/CS240Exception.h utils/inc/StringUtil.h utils/inc/CommandRunner.h
	g++ -c -o utils/obj/CommandRunner.o -I utils/inc -I inc/ utils/src/CommandRunner.cpp

utils/obj/FileInputStream.o: utils/src/FileInputStream.cpp utils/inc/FileInputStream.h utils/inc/InputStream.h utils/inc/CS240Exception.h
	g++ -o utils/obj/FileInputStream.o -c -I utils/inc -I inc/ utils/src/FileInputStream.cpp

utils/obj/FileSystem.o: utils/src/FileSystem.cpp utils/inc/FileSystem.h utils/inc/CS240Exception.h utils/inc/UnitTest.h
	g++ -o utils/obj/FileSystem.o -c -I utils/inc -I inc/ utils/src/FileSystem.cpp

utils/obj/HTMLToken.o: utils/src/HTMLToken.cpp utils/inc/HTMLToken.h
	g++ -o utils/obj/HTMLToken.o -c -I utils/inc -I inc/ utils/src/HTMLToken.cpp

utils/obj/HTMLTokenizer.o: utils/src/HTMLTokenizer.cpp utils/inc/HTMLTokenizer.h utils/inc/URLInputStream.h utils/inc/InputStream.h utils/inc/HTMLToken.h
	g++ -o utils/obj/HTMLTokenizer.o -c -I utils/inc -I inc/ utils/src/HTMLTokenizer.cpp

utils/obj/HTTPInputStream.o: utils/src/HTTPInputStream.cpp utils/inc/CS240Exception.h utils/inc/StringUtil.h utils/inc/HTTPInputStream.h utils/inc/InputStream.h
	g++ -o utils/obj/HTTPInputStream.o -c -I utils/inc -I inc/ utils/src/HTTPInputStream.cpp

utils/obj/StringUtil.o: utils/src/StringUtil.cpp utils/inc/StringUtil.h
	g++ -o utils/obj/StringUtil.o -c -I utils/inc -I inc/ utils/src/StringUtil.cpp

utils/obj/URLInputStream.o: utils/src/URLInputStream.cpp utils/inc/StringUtil.h utils/inc/CS240Exception.h \
 utils/inc/HTTPInputStream.h utils/inc/InputStream.h utils/inc/FileInputStream.h utils/inc/URLInputStream.h utils/inc/InputStream.h
	g++ -o utils/obj/URLInputStream.o -c -I utils/inc -I inc/ utils/src/URLInputStream.cpp
