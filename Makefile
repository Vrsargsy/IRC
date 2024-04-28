#Makefile-ը նման է բաղադրատոմսերի գրքի՝ ծրագրային նախագծերի կառավարման համար: Այն պարունակում է հրահանգներ (հայտնի են որպես կանոններ) այնպիսի առաջադրանքների համար, ինչպիսիք են կոդ կազմելը, ֆայլերը կառավարելը և նախագծի հետ կապված այլ գործողություններ: Յուրաքանչյուր կանոն ունի թիրախ (ինչ ստեղծել), կախվածություններ (ինչ է անհրաժեշտ) և հրամաններ (ինչպես դա անել): Երբ դուք գործարկում եք make-ը տերմինալում, այն կարդում է Makefile-ը և կատարում է նշված կանոնները՝ ձեր նախագիծը թարմացնելու կամ կառուցելու համար: Սա օգտակար է առաջադրանքների ավտոմատացման, հետևողականության ապահովման և բարդ նախագծերի արդյունավետ կառավարման համար:

NAME = ircserv
BOT_NAME = botserv

OBJECTS_FOLDER = ./objects/

SRCS = $(wildcard server/*.cpp)
BOT_SRCS = $(wildcard bot/*.cpp)

OBJS = $(SRCS:%.cpp=$(OBJECTS_FOLDER)%.o)
BOT_OBJS = $(BOT_SRCS:%.cpp=$(OBJECTS_FOLDER)%.o)

HEADERS = $(wildcard server/*.hpp)
BOT_HEADERS = $(wildcard bot/*.hpp)

PRE_HEADERS = $(HEADERS:%.hpp=$(OBJECTS_FOLDER)%.hpp.gch)
BOT_PRE_HEADERS = $(BOT_HEADERS:%.hpp=$(OBJECTS_FOLDER)%.hpp.gch)

CFLAGS = -Wall -Wextra -Werror -std=c++98 # -fsanitize=address -g

CC = c++

RM = rm -rf

all: objs $(PRE_HEADERS) $(NAME)

run_bot: bot_objs $(BOT_PRE_HEADERS) $(BOT_NAME)

$(OBJECTS_FOLDER)server/%.hpp.gch: server/%.hpp
	@$(CC) $(CFLAGS) $< -o $@

$(OBJECTS_FOLDER)bot/%.hpp.gch: bot/%.hpp
	@$(CC) $(CFLAGS) $< -o $@

$(OBJECTS_FOLDER)server/%.o: server/%.cpp $(PRE_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS_FOLDER)bot/%.o: bot/%.cpp $(BOT_PRE_HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $? -o $(NAME)

$(BOT_NAME) : $(BOT_OBJS)
	@$(CC) $(CFLAGS) $? -o $(BOT_NAME)

objs:
	@(mkdir -p objects/server)

bot_objs:
	@(mkdir -p objects/bot)

clean:
	@$(RM) $(OBJECTS_FOLDER)
	@$(RM) $(PRE_HEADERS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all



test:
	@echo $(OBJS)
	@echo $(PRE_HEADERS)

.PHONY: all clean fclean re run_bot