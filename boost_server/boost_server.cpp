
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

    using namespace boost;
    using boost::asio::ip::tcp;

    int main()
    {
        try
        {
            asio::io_service io_service;
            
            std::string message = "hello from server\n";

            ::unlink("/tmp/foobar"); // Remove previous binding.
            boost::asio::local::stream_protocol::endpoint ep("/tmp/foobar");
            boost::asio::local::stream_protocol::acceptor acceptor(io_service, ep);

            for (;;)
            {
                boost::asio::local::stream_protocol::socket socket(io_service);
                acceptor.accept(socket);

                while(true){
                    boost::array<char, 128> buf;
                    boost::system::error_code error;

                    size_t len = socket.read_some(boost::asio::buffer(buf), error);

                    std::cout.write(buf.data(), len);

                    system::error_code ignored_error;
                    socket.write_some(asio::buffer(message), ignored_error);
                }
                
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        return 0;
    }