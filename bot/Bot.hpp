#if !defined(BOT_HPP)
#define BOT_HPP

#include "../server/irc.hpp"

/* 

AcceptSocket() - Հաստատում է սոկետի ստացողը։
SendReply() - Ուղարկում է պատասխանը։
GiveResponse() - Տալու է պատասխանը նամակի հրահանգում։
RunBot() - Կաշխատում է բոտը։
Bot() - Կառավարվում է կառավարվող բոտը։
~Bot() - Մահվում է բոտը։
SetUser() - Սահմանում է օգտագործողը։
SetNick() - Սահմանում է անվանումը։
AddToRecvMsg() - Ավելացնում է ստացված նամակները։
GetRecvMsg() - Ստանում է ստացված նամակները։
 */

class Bot
{
    private:
		socklen_t	addrlen;
		struct sockaddr_in address;
		int				port;
		int				socketfd;
		int				clientfd;
		std::string		host;
		std::string		pass;
		std::string 	user;
		std::string 	nick;
		char			buffer[1025];
		std::string		recvMessage;

		void	Setup();//- Նախապատրաստում է սերվերը։
		void	CreateServer();//- Ստեղծում է սերվերը։
		void	SetOptions();//- Կազմում է սուպերատրիկ կապ։
		void	BindSocket();//- Հաստատում է սոկետը։
		void	ConnectToServer();//- Կապվում է սերվերին։
		void	ReceiveMsg();//- Ստանում է նամակներ։
		void	AcceptSocket();//- Հաստատում է սոկետի ստացողը։
		void	SendReply();//- Ուղարկում է պատասխանը։
		std::string	GiveResponse(const std::string &command);//- Տալու է պատասխանը նամակի հրահանգում։


	public:
		int socketCLIENT;
		void	RunBot();//- Կաշխատում է բոտը։
		Bot(const std::string &host, int _port, const std::string &_pass,
			const std::string &_user = "havayi", const std::string &_nick = "butul");//- Կառավարվում է կառավարվող բոտը։
        ~Bot();//- Մահվում է բոտը։
		
		void	SetUser(const std::string &_user);//- Սահմանում է օգտագործողը։
		void	SetNick(const std::string &_nick);//- Սահմանում է անվանումը։

		void		AddToRecvMsg(const std::string &msg);//- Ավելացնում է ստացված նամակները։
		std::string	GetRecvMsg(void) const;//- Ստանում է ստացված նամակները։
};	


#endif // BOT_HPP
