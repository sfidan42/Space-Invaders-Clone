SRC		:=	ACharacter.cpp MonsterCharacter.cpp PlayerCharacter.cpp GameInstance.cpp GameScene.cpp Scene.cpp
HDR		:=	$(addprefix include/, $(SRC:.cpp=.hpp) Conversions.hpp)
SRC		:=	$(addprefix source/, $(SRC))
OBJ		:=	$(SRC:.cpp=.o)

NAME	:=	SpaceInvaders
LIB		:=	lib$(NAME).a

CPP		=	c++ -Wall -Wextra -Werror -std=c++20
FLAGS	=	-L . -l $(NAME) \
			-L raylib/build/raylib -l raylib \
			-I raylib/build/raylib/include \
			-I include \
			-I json/include

all: $(NAME)
	./$(NAME)

%.o : %.cpp $(HDR)
	@$(CPP) -c $(FLAGS) $< -o $@
	@echo Compiling $< ...

$(NAME): main.cpp $(LIB)
	@$(CPP) main.cpp $(FLAGS) -o $(NAME)
	@echo Creating $(NAME) ...

$(LIB): $(OBJ)
	@ar -rcs $(LIB) $(OBJ)
	@echo Creating $(LIB) ...

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) $(LIB)

re: fclean all

.PHONY: all clean fclean re