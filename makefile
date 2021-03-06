EXE=
LIBSRC=utils/obj

memBin : bin/crawler
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=test/config/string.supp  bin/crawler http://www.cksuperman.com/test.html test/output/output.txt ./test/input/stopword.txt


bin : bin/crawler

memTest : bin/TestDriver
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 --show-reachable=yes --suppressions=test/config/string.supp  bin/TestDriver

test : bin/TestDriver
	bin/TestDriver

clean :
	@- rm -f obj/*.o > /dev/null 2>&1
	@- rm -f lib/*.a > /dev/null 2>&1
	@- rm -f utils/obj/*.o > /dev/null 2>&1
	@- rm -f bin/* > /dev/null 2>&1

bin/crawler : obj/MainDriver.o lib/libutils.a obj/Url.o obj/WebCrawler.o obj/PageQueue.o obj/PageHistory.o obj/KeyWordIndex.o obj/PrintXml.o
	g++ -o bin/crawler obj/MainDriver.o obj/PrintXml.o obj/WebCrawler.o obj/StopWords.o obj/Url.o obj/HTMLParser.o obj/Page.o obj/OccurrenceSet.o obj/PageQueue.o obj/KeyWordIndex.o obj/PageHistory.o lib/libutils.a -lboost_regex

bin/TestDriver : obj/TestDriver.o lib/libutils.a obj/StopWords.o obj/Url.o obj/HTMLParser.o obj/Page.o obj/OccurrenceSet.o obj/PageQueue.o obj/KeyWordIndex.o obj/PageHistory.o
	g++ -g -o bin/TestDriver obj/TestDriver.o obj/StopWords.o obj/Url.o obj/HTMLParser.o obj/Page.o obj/OccurrenceSet.o obj/PageQueue.o obj/KeyWordIndex.o obj/PageHistory.o lib/libutils.a -lboost_regex

obj/MainDriver.o : src/MainDriver.cpp
	g++ -c -g -Wall -o obj/MainDriver.o -I inc/ -I utils/inc src/MainDriver.cpp

obj/TestDriver.o : src/TestDriver.cpp
	g++ -c -g -Wall -o obj/TestDriver.o -I inc/ -I utils/inc src/TestDriver.cpp

obj/WebCrawler.o : src/WebCrawler.cpp inc/WebCrawler.h obj/Url.o obj/StopWords.o
	g++ -c -g -Wall -o obj/WebCrawler.o -I inc/ -I utils/inc src/WebCrawler.cpp

obj/StopWords.o : src/StopWords.cpp inc/StopWords.h
	g++ -c -g -Wall -o obj/StopWords.o -I inc/ -I utils/inc src/StopWords.cpp

obj/Url.o : src/Url.cpp inc/Url.h
	g++ -c -g -Wall -o obj/Url.o -I inc/ -I utils/inc src/Url.cpp

obj/HTMLParser.o : src/HTMLParser.cpp inc/HTMLParser.h
	g++ -c -g -Wall -o obj/HTMLParser.o -I inc/ -I utils/inc src/HTMLParser.cpp

obj/Page.o : src/Page.cpp inc/Page.h obj/HTMLParser.o obj/Url.o
	g++ -c -g -Wall -o obj/Page.o -I inc/ -I utils/inc src/Page.cpp

obj/OccurrenceSet.o : src/OccurrenceSet.cpp inc/OccurrenceSet.h
	g++ -c -g -Wall -o obj/OccurrenceSet.o -I inc/ -I utils/inc src/OccurrenceSet.cpp

obj/PageQueue.o : src/PageQueue.cpp inc/PageQueue.h obj/Page.o
	g++ -c -g -Wall -o obj/PageQueue.o -I inc/ -I utils/inc src/PageQueue.cpp

obj/KeyWordIndex.o : src/KeyWordIndex.cpp inc/KeyWordIndex.h obj/OccurrenceSet.o
	g++ -c -g -Wall -o obj/KeyWordIndex.o -I inc/ -I utils/inc src/KeyWordIndex.cpp

obj/PageHistory.o : src/PageHistory.cpp inc/PageHistory.h obj/Page.o
	g++ -c -g -Wall -o obj/PageHistory.o -I inc/ -I utils/inc src/PageHistory.cpp

obj/PrintXml.o : src/PrintXml.cpp inc/PrintXml.h obj/Page.o obj/KeyWordIndex.o obj/OccurrenceSet.o obj/Url.o
	g++ -c -g -Wall -o obj/PrintXml.o -I inc/ -I utils/inc src/PrintXml.cpp
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
