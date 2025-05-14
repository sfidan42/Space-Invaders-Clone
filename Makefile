SRC		:=	ACharacter.cpp MonsterCharacter.cpp PlayerCharacter.cpp GameInstance.cpp
SRC		:=	$(addprefix source/, $(SRC))
OBJ		:=	$(SRC:.cpp=.o)

NAME	:=	SpaceInvaders
LIB		:=	lib$(NAME).a

CPP		:=	c++ -std=c++20 -Wall -Wextra -Werror

all: $(NAME)
	./$(NAME)

%.o : %.cpp
	$(CPP) -c -I include $< -o $@

$(NAME): main.cpp $(LIB)
	$(CPP) main.cpp -L . -l $(NAME) -I include -o $(NAME)

$(LIB): $(OBJ)
	ar -rcs $(LIB) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) $(LIB)

re: fclean all

.PHONY = all clean fclean re