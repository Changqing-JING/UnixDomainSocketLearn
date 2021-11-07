
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
            tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));
            std::string message = "hello from server\n";

            for (;;)
            {
                tcp::socket socket(io_service);
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