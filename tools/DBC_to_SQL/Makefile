#
#	DBC to SQL Converter
#	Copyright (C) 2009  David Vas, Anubisss
#	<http://code.google.com/p/dbctosql/>
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

CC = g++
CXXFLAGS = -c

OUT_FILE = dbctosql

OBJECTS = dbc.o progressbar.o main.o
SRC = src
INCLUDES = -I$(SRC)/

$(OUT_FILE): $(OBJECTS)
		$(CC) $(OBJECTS) -o $(OUT_FILE)

dbc.o: $(SRC)/dbc/dbc.cpp $(SRC)/dbc/dbc.h
		$(CC) $(CXXFLAGS) $(INCLUDES) $(SRC)/dbc/dbc.cpp
progressbar.o: $(SRC)/common/progressbar.cpp $(SRC)/common/progressbar.h $(SRC)/common/common.h
		$(CC) $(CXXFLAGS) $(INCLUDES) $(SRC)/common/progressbar.cpp
main.o: $(SRC)/main/main.cpp $(SRC)/common/common.h $(SRC)/dbc/dbc.h $(SRC)/structs/spell.h $(SRC)/structs/achievement.h $(SRC)/structs/achievement_category.h $(SRC)/structs/achievement_criteria.h $(SRC)/common/progressbar.h
		$(CC) $(CXXFLAGS) $(INCLUDES) $(SRC)/main/main.cpp

clean:
		rm -rf *.o $(OUT_FILE)
