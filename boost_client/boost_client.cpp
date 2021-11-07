#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>

    using boost::asio::ip::tcp;

    int main(int argc, char* argv[])
    {
        try
        {
            boost::asio::io_service io_service;
            tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 3200);

            std::string message = "hello from client\n";

            tcp::socket socket(io_service);
            socket.connect(end_point);

            for (;;)
            {
                boost::array<char, 128> buf;
                boost::system::error_code error;
                boost::system::error_code ignored_error;
                socket.write_some(boost::asio::buffer(message), ignored_error);

                size_t len = socket.read_some(boost::asio::buffer(buf), error);

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                std::cout.write(buf.data(), len);
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        return 0;
    }