#ifndef PLAYER_H
#define PLAYER_H

void ent_player(FILE *infile, LIST **plist);
void show_all_player(LIST **plist);
void show_player(LIST **plist, int gn);
void quit(LIST **plist);
void add_player(LIST **plist);
void remove_player(LIST **plist);
#endif