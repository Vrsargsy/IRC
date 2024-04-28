#if !defined(SERVER_HPP)
#define SERVER_HPP

#include "ClientManager.hpp"
#include "Channel.hpp"
#include "CommandResponse.hpp"

class Server : public CommandResponse //this is the class prototpy which inheriting from class called CommandResponse
{
	private: // for singleton
		static Server *instance; //this is the main part of the singletone with static pointer of the same class you can handle 
								 //single allocation of your class  
	
	private:
		int	master_socket; // this is the main socket descriptor of our server with this descriptor you can manage your server
		int max_sd;// with this property you can have a limitation of how many pepole could join to your server
		int	port; //this is the port property that you assign your server port with
		std::string password;// with this property you can create a password to protect your server 
		int	bot_fd; // this property related to bot_file descriptor
		std::map<std::string, Channel> channels; //this is a container of the channels with unique key and value with channel name as a key and channel class properties as a value
		struct sockaddr_in address; // this is a builtin struct written in C lang which you creacte and open your server socket as a host 
		socklen_t	addrlen;
		fd_set readfds;

	public:
		Server(int port, std::string password);//this is a constuctor of the server class
		~Server();//this is a destructor of the server class

		static Server	*getServer();// this is a static method which you can get the allocated server.
		void Setup();// Handles the implementations of server sockets to prepare it for start

		void ResetSockets();// Prevents the program from crashing
		void CreateServer();// Helper function for Setup()
		void SetOptions();// Makes the server asynchronous
		void BindSocket();// Binds the server socket
		void StartListening();// Starts listening for accepting new users
		int AcceptNewSocket();// Accepts new users
		void ListenForClientInput();// Listens for client input
		void SendToClient(int sockfd, const char *message) const;// Sends a message to a client
		void SendMessageToBot(const std::string &message) const;// Sends a message to the bot
		void WaitForActivity();// Waits for activity
		void HandleIncomingConnections();// Handles incoming connections
		void ClearClientFromChannels(const Client &client);// Clears a client from channels
		int getaddrlen();// Gets the address length
		
	public:
		int		getBotDescriptor() const;
		void	SetBotDescriptor(int new_fd);
		void	RemoveBot();
		bool	IsBotConnected() const;
		bool	IsBot(const Client &client) const;

		bool HasChannel(std::string const &name);
		//const Channel &getChannel(std::string const &name)const;
		Channel &getChannel(std::string const &name);
		//void AddChannel(std::string const &name);
		void removeChannel(std::string const &name);
		void ChangeNick(Client const &client);

	private:
		Server();
};

/* void Server::ChangeNick(Client const &client)
{
	std::map<std::string,Channel>::iterator it = channels.begin();
	for (; it !=  channels.end() ; ++it)
	{
		Channel &chan  = this->getChannel(it->first);

	}
	 
} */
//void Server::AddChannel(std::string const &name);//der chem grel!!

#endif // SERVER_HPP



